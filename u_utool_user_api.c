// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */
#include <pthread.h>
#include <inttypes.h>

#include "./common/u_utool_error.h"
#include "./common/u_utool_fwctl.h"
#include "./feature/u_utool_port_info.h"
#include "./protocol_layer/u_utool_dl.h"
#include "./protocol_layer/u_utool_nl.h"
#include "u_utool_pkt.h"
#include "./include/u_utool_user_api.h"
#include "./u_utool_dispatch.h"

#define UBCTL_OPCODE_MAX_LEN 1016U
#define SSU_VL_PKT_REG_FIRST 0
#define SSU_VL_PKT_REG_SECOND 1
#define SSU_VL_PKT_REG_THIRD 2
#define PORT_ID_IDX 0
#define ENABLE_FLAG_IDX 1
#define REG_CTRL_IDX 2
#define RX_IN_DFX_VL_SEL_START 0
#define RX_IN_DFX_VL_SEL_END 3
#define TX_IN_DFX_VL_SEL_START 4
#define TX_IN_DFX_VL_SEL_END 7
#define RX_OUT_DFX_VL_SEL_START 8
#define RX_OUT_DFX_VL_SEL_END 11
#define TX_OUT_DFX_VL_SEL_START 12
#define TX_OUT_DFX_VL_SEL_END 15
#define RESERVED_0_START 16
#define RESERVED_0_END 31
#define CHANNEL_FIELD_WIDTH 4
#define RX_0_OUT_DFX_VL_SEL_START 0
#define RX_0_OUT_DFX_VL_SEL_END 3
#define RX_1_OUT_DFX_VL_SEL_START 4
#define RX_1_OUT_DFX_VL_SEL_END 7
#define RX_2_OUT_DFX_VL_SEL_START 8
#define RX_2_OUT_DFX_VL_SEL_END 11
#define TX_0_OUT_DFX_VL_SEL_START 12
#define TX_0_OUT_DFX_VL_SEL_END 15
#define TX_1_OUT_DFX_VL_SEL_START 16
#define TX_1_OUT_DFX_VL_SEL_END 19
#define TX_2_OUT_DFX_VL_SEL_START 20
#define TX_2_OUT_DFX_VL_SEL_END 23
#define RESERVED_CH_START 24
#define RESERVED_CH_END 31
#define V01_RX_CNT_START_IDX 3
#define V01_COPY_REG_COUNT 4
#define CAP2_TX_SF_CNT_START_IDX 7
#define CAP2_COPY_SF_REG_COUNT 4
#define CAP2_REG_OUT_DFX_IDX 11
#define CAP2_REG_IN_SF_DFX_IDX 12
#define CAP2_REG_IN_BPS_DFX_IDX 13
#define RX_0_IN_DFX_VL_SEL_START 0
#define RX_0_IN_DFX_VL_SEL_END 3
#define RX_1_IN_DFX_VL_SEL_START 4
#define RX_1_IN_DFX_VL_SEL_END 7
#define RX_2_IN_DFX_VL_SEL_START 8
#define RX_2_IN_DFX_VL_SEL_END 11
#define TX_0_IN_DFX_VL_SEL_START 12
#define TX_0_IN_DFX_VL_SEL_END 15
#define TX_1_IN_DFX_VL_SEL_START 16
#define TX_1_IN_DFX_VL_SEL_END 19
#define TX_2_IN_DFX_VL_SEL_START 20
#define TX_2_IN_DFX_VL_SEL_END 23
#define CAP3_TX_VL_CNT0_START_IDX 7
#define CAP3_COPY_VL_CNT0_COUNT 2
#define CAP3_REG_OUT_DFX_IDX 9
#define CAP3_REG_IN_SF_DFX_IDX 10
#define CAP3_REG_IN_BPS_DFX_IDX 11

static pthread_mutex_t g_api_lock = PTHREAD_MUTEX_INITIALIZER;

struct ubctl_query_comm {
	uint32_t ubctl_cmd;
	int (*check_in)(struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out);
	int (*execute)(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
		       struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out);
};
struct ubctl_cmd_map {
	uint32_t user_cmd;
	enum ub_fwctl_cmdrpc_type rpc_type;
};

static struct ubctl_cmd_map g_cmd_map_table[] = {
	{ UBCTL_USER_CMD_COMM, UTOOL_CMD_QUERY_CONF_USER_COMM },
};

static int utool_user_api_check_param(uint32_t *ubctl_cmd, const struct ubctl_cmd_buf *in,
				      const struct ubctl_cmd_buf *out, uint32_t *max_data_len)
{
	uint32_t cmd_map_size = UTOOL_ARRAY_SIZE(g_cmd_map_table);
	uint32_t i;

	if (in == NULL || out == NULL) {
		utool_err_msg("Invalid param: in or out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (in->is_read && (!out->data || out->data_size == 0)) {
		utool_err_msg("Invalid param: out buffer is empty.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (in->data_size > 0 && in->data == NULL) {
		utool_err_msg("Invalid param: in data size = %u bytes and in->data is NULL.\n", in->data_size);
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (out->data_size > 0 && out->data == NULL) {
		utool_err_msg("Invalid param: out data size = %u bytes and out->data is NULL.\n", out->data_size);
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (in->data_size > UBCTL_OPCODE_MAX_LEN || out->data_size > UBCTL_OPCODE_MAX_LEN) {
		utool_err_msg("Invalid param: in data size = %u bytes or out data size = %u bytes"
			      " is bigger than max size = %u bytes.\n",
			      in->data_size, out->data_size, UBCTL_OPCODE_MAX_LEN);
		return UTOOL_ERR_INVALID_PARAM;
	}

	*max_data_len = (in->data_size > out->data_size) ? in->data_size : out->data_size;

	for (i = 0; i < cmd_map_size; i++) {
		if (g_cmd_map_table[i].user_cmd == *ubctl_cmd) {
			*ubctl_cmd = g_cmd_map_table[i].rpc_type;
			return UTOOL_OK;
		}
	}

	utool_err_msg("Invalid param: unknown ubctl_cmd = %u.\n", *ubctl_cmd);
	return UTOOL_ERR_INVALID_CMD;
}

static struct fwctl_rpc_ub_in *utool_create_pkt_in_api(uint32_t *pkt_in_len, uint32_t rpc_cmd,
						       const struct ubctl_cmd_buf *in, uint32_t max_data_len)
{
	uint32_t head_len = sizeof(struct ubctl_cmd_in_head);
	struct ubctl_cmd_in_head *head = NULL;
	struct fwctl_rpc_ub_in *rpc_in = NULL;
	uint32_t in_data_len = max_data_len;
	uint32_t total_data_len;

	total_data_len = head_len + in_data_len;
	*pkt_in_len = (uint32_t)(sizeof(struct fwctl_rpc_ub_in) + total_data_len);

	rpc_in = (struct fwctl_rpc_ub_in *)UTOOL_MALLOC(*pkt_in_len);
	if (rpc_in == NULL) {
		utool_err_msg("Failed to malloc space for pkt in.\n");
		return NULL;
	}

	memset(rpc_in, 0x0, *pkt_in_len);
	rpc_in->rpc_cmd = rpc_cmd;
	rpc_in->data_size = total_data_len;
	rpc_in->version = UTOOL_VERSION;

	head = (struct ubctl_cmd_in_head *)rpc_in->data;
	head->opcode = in->opcode;
	head->is_read = in->is_read;

	if (in->data && in->data_size != 0) {
		memcpy((uint8_t *)(rpc_in->data) + head_len, in->data, in->data_size);
	}
	return rpc_in;
}

static struct fwctl_rpc_ub_out *utool_create_pkt_out_api(uint32_t *pkt_out_len, uint32_t max_data_len)
{
	struct fwctl_rpc_ub_out *rpc_out = NULL;
	uint32_t out_data_len = max_data_len;

	*pkt_out_len = (uint32_t)(sizeof(struct fwctl_rpc_ub_out) + out_data_len);
	rpc_out = (struct fwctl_rpc_ub_out *)UTOOL_MALLOC(*pkt_out_len);
	if (rpc_out == NULL) {
		utool_err_msg("Failed to malloc space for pkt out.\n");
		return NULL;
	}

	memset(rpc_out, 0x0, *pkt_out_len);
	return rpc_out;
}

int ubctl_user_comm_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
			struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	struct fwctl_rpc_ub_out *rpc_out = NULL;
	struct fwctl_rpc_ub_in *rpc_in = NULL;
	struct utool_dev dev = {};
	uint32_t max_data_len = 0;
	uint32_t rpc_out_len = 0;
	uint32_t rpc_in_len = 0;
	int ret;

	ret = utool_user_api_check_param(&ubctl_cmd, in, out, &max_data_len);
	if (ret != UTOOL_OK) {
		return ret;
	}

	ret = utool_open_dev_step(&dev, chip_id, die_id, UTOOL_DEV_STEP_SCAN);
	if (ret != UTOOL_OK) {
		return ret;
	}

	rpc_in = utool_create_pkt_in_api(&rpc_in_len, ubctl_cmd, in, max_data_len);
	if (rpc_in == NULL) {
		ret = UTOOL_ERR_MALLOC;
		goto close_dev;
	}

	rpc_out = utool_create_pkt_out_api(&rpc_out_len, max_data_len);
	if (rpc_out == NULL) {
		ret = UTOOL_ERR_MALLOC;
		goto free_pkt_in;
	}

	ret = utool_cmd_exec(&dev, rpc_in, rpc_in_len, rpc_out, &rpc_out_len);
	if (rpc_out->retval != 0) {
		if (ret == UTOOL_OK) {
			ret = UTOOL_ERR_IOCTL;
		}
		utool_err_msg("Command execution failed, retval = %d.\n", rpc_out->retval);
		goto free_pkt_out;
	}

	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute cmd, ret = %d.\n", ret);
		goto free_pkt_out;
	}

	if (out->data_size == 0) {
		goto free_pkt_out;
	}

	memcpy(out->data, rpc_out->data, out->data_size);

free_pkt_out:
	UTOOL_FREE(rpc_out);
free_pkt_in:
	UTOOL_FREE(rpc_in);
close_dev:
	utool_close(&dev);

	return ret;
}

static int utool_query_ubase_info_check_cmd(uint32_t *ubctl_cmd, struct ubctl_cmd_map *map, uint32_t cmd_map_size)
{
	uint32_t i;

	for (i = 0; i < cmd_map_size; i++) {
		if (map[i].user_cmd == *ubctl_cmd) {
			*ubctl_cmd = map[i].rpc_type;
			return UTOOL_OK;
		}
	}

	utool_err_msg("Invalid param: unknown ubctl_cmd = %u.\n", *ubctl_cmd);
	return UTOOL_ERR_INVALID_CMD;
}

static void utool_fill_dev_name_in_data(const char *dev_name, uint32_t ubctl_cmd,
					struct fwctl_rpc_ub_in *rpc_in)
{
	uint32_t pkt_in_len = (uint32_t)sizeof(struct fwctl_pkt_in_dev_name);
	struct fwctl_pkt_in_dev_name pkt_in = {};

	strncpy(pkt_in.dev_name, dev_name, sizeof(pkt_in.dev_name) - 1);
	memcpy(rpc_in->data, &pkt_in, pkt_in_len);
	rpc_in->data_size = pkt_in_len;
	rpc_in->version = UTOOL_VERSION;
	rpc_in->rpc_cmd = ubctl_cmd;
}

static struct fwctl_rpc_ub_in *utool_create_pkt_in_buf(uint32_t *rpc_in_len)
{
	uint32_t pkt_in_len = (uint32_t)sizeof(struct fwctl_pkt_in_dev_name);
	struct fwctl_rpc_ub_in *rpc_in;

	*rpc_in_len = (uint32_t)(sizeof(struct fwctl_rpc_ub_in) + pkt_in_len);
	rpc_in = (struct fwctl_rpc_ub_in *)UTOOL_MALLOC(*rpc_in_len);
	if (rpc_in == NULL) {
		utool_err_msg("Failed to malloc space for rpc in.\n");
		return NULL;
	}

	return rpc_in;
}

static struct fwctl_rpc_ub_out *utool_create_out_buf(uint32_t buf_size, uint32_t *rpc_out_len)
{
	struct fwctl_rpc_ub_out *rpc_out;

	*rpc_out_len = (uint32_t)sizeof(struct fwctl_rpc_ub_out) + buf_size;
	rpc_out = (struct fwctl_rpc_ub_out *)UTOOL_MALLOC(*rpc_out_len);
	if (rpc_out == NULL) {
		utool_err_msg("Failed to malloc space for rpc out.\n");
		return NULL;
	}
	memset(rpc_out, 0x0, *rpc_out_len);

	return rpc_out;
}

static int ubctl_query_ubase_comm_info(const char *dev_name, uint32_t ubctl_cmd,
				       void *buf, uint32_t buf_size)
{
	uint32_t rpc_out_len = 0, rpc_in_len = 0;
	struct fwctl_rpc_ub_out *rpc_out;
	struct fwctl_rpc_ub_in *rpc_in;
	struct utool_dev dev = {};
	int ret;

	ret = utool_open_dev_step(&dev, 0, 0, UTOOL_DEV_UBASE_INFO);
	if (ret != UTOOL_OK) {
		return ret;
	}

	rpc_in = utool_create_pkt_in_buf(&rpc_in_len);
	if (rpc_in == NULL) {
		ret = UTOOL_ERR_MALLOC;
		goto close_dev;
	}

	rpc_out = utool_create_out_buf(buf_size, &rpc_out_len);
	if (rpc_out == NULL) {
		ret = UTOOL_ERR_MALLOC;
		UTOOL_FREE(rpc_in);
		goto close_dev;
	}

	utool_fill_dev_name_in_data(dev_name, ubctl_cmd, rpc_in);

	ret = utool_cmd_exec(&dev, rpc_in, rpc_in_len, rpc_out, &rpc_out_len);
	if (rpc_out->retval != 0) {
		if (ret == UTOOL_OK) {
			ret = UTOOL_ERR_IOCTL;
		}
		utool_err_msg("Command execution failed, retval = %d.\n", rpc_out->retval);
		goto free_pkt_buf;
	}

	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute cmd, ret = %d.\n", ret);
		goto free_pkt_buf;
	}

	if (buf_size < rpc_out->data_size) {
		utool_err_msg("Buffer size %u bytes < required data %u bytes.\n", buf_size, rpc_out->data_size);
		ret = UTOOL_ERR_INVALID_PARAM;
		goto free_pkt_buf;
	}

	memcpy(buf, rpc_out->data, rpc_out->data_size);

free_pkt_buf:
	UTOOL_FREE(rpc_out);
	UTOOL_FREE(rpc_in);
close_dev:
	utool_close(&dev);

	return ret;
}

int ubctl_query_ubase_info_api(const char *dev_name, uint32_t ubctl_cmd,
			       void *buf, uint32_t buf_size)
{
#define UBCTL_MAX_OUT_LEN 0x200000U
#define UBCTL_MIN_OUT_LEN 64U
	uint32_t ubctl_max_len = UBCTL_MAX_OUT_LEN - (uint32_t)(sizeof(struct fwctl_rpc_ub_out));
	struct ubctl_cmd_map map[] = {
		{ UBCTL_QUERY_AEQC_CMD_COMM, UTOOL_CMD_QUERY_AEQC_INFO },
		{ UBCTL_QUERY_CEQC_CMD_COMM, UTOOL_CMD_QUERY_CEQC_INFO },
	};
	int ret;

	if (dev_name == NULL || buf == NULL) {
		utool_err_msg("Invalid param: dev name or buf is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (buf_size < UBCTL_MIN_OUT_LEN || buf_size > ubctl_max_len) {
		utool_err_msg("Invalid param: buf size = %u, it must be in [%u, %u].\n",
			      buf_size, UBCTL_MIN_OUT_LEN, ubctl_max_len);
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_query_ubase_info_check_cmd(&ubctl_cmd, map, UTOOL_ARRAY_SIZE(map));
	if (ret) {
		return ret;
	}

	ret = ubctl_query_ubase_comm_info(dev_name, ubctl_cmd, buf, buf_size);
	if (ret) {
		utool_err_msg("Failed to query dscp vl, ret = %d.\n", ret);
	}

	return ret;
}

int ubctl_query_dscp_vl_api(const char *dev_name, uint32_t ubctl_cmd,
			    struct ubctl_ubase_dbg_dscp_vl_map *data)
{
	struct ubctl_cmd_map map[] = {
		{ UBCTL_QUERY_DSCP_CMD_COMM, UTOOL_CMD_QUERY_DSCP_INFO },
	};
	int ret;

	if (dev_name == NULL || data == NULL) {
		utool_err_msg("Invalid param: dev name or buf is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_query_ubase_info_check_cmd(&ubctl_cmd, map, UTOOL_ARRAY_SIZE(map));
	if (ret) {
		return ret;
	}

	ret = ubctl_query_ubase_comm_info(dev_name, ubctl_cmd, (void *)data, sizeof(struct ubctl_ubase_dbg_dscp_vl_map));
	if (ret) {
		utool_err_msg("Failed to query dscp vl, ret = %d.\n", ret);
	}

	return ret;
}

int ubctl_query_sl_vl_map_api(const char *dev_name, uint32_t ubctl_cmd,
			      struct ubctl_ubase_dbg_sl_vl_map *data)
{
	struct ubctl_cmd_map map[] = {
		{ UBCTL_QUERY_SL_VL_MAP_CMD_COMM, UTOOL_CMD_QUERY_SL_VL_MAP_INFO },
	};
	int ret;

	if (dev_name == NULL || data == NULL) {
		utool_err_msg("Invalid param: dev name or buf is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_query_ubase_info_check_cmd(&ubctl_cmd, map, UTOOL_ARRAY_SIZE(map));
	if (ret) {
		return ret;
	}

	ret = ubctl_query_ubase_comm_info(dev_name, ubctl_cmd, (void *)data, sizeof(struct ubctl_ubase_dbg_sl_vl_map));
	if (ret) {
		utool_err_msg("Failed to query sl vl map, ret = %d.\n", ret);
	}

	return ret;
}

int ubctl_query_caps_info_api(const char *dev_name, uint32_t ubctl_cmd,
			      struct ubctl_ubase_dbg_caps_info *data)
{
	struct ubctl_cmd_map map[] = {
		{ UBCTL_QUERY_CAPS_CMD_COMM, UTOOL_CMD_QUERY_CAPS_INFO },
	};
	int ret;

	if (dev_name == NULL || data == NULL) {
		utool_err_msg("Invalid param: dev name or buf is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_query_ubase_info_check_cmd(&ubctl_cmd, map, UTOOL_ARRAY_SIZE(map));
	if (ret) {
		return ret;
	}

	ret = ubctl_query_ubase_comm_info(dev_name, ubctl_cmd, (void *)data, sizeof(struct ubctl_ubase_dbg_caps_info));
	if (ret) {
		utool_err_msg("Failed to query caps info, ret = %d.\n", ret);
	}

	return ret;
}

int ubctl_query_icrc_api(uint32_t chip_id, uint32_t die_id, uint32_t port_id, struct ubctl_icrc_info *data)
{
#define UBCTL_QUERY_BA_ICRC_DFX 0xA03C

	struct ubctl_cmd_buf in = {
		.opcode = UBCTL_QUERY_BA_ICRC_DFX,
		.is_read = true,
		.data_size = sizeof(uint32_t),
		.data = &port_id
	};

	struct ubctl_cmd_buf out = {
		.opcode = UBCTL_QUERY_BA_ICRC_DFX,
		.is_read = true,
		.data_size = sizeof(struct ubctl_icrc_info),
		.data = data
	};

	return ubctl_user_comm_api(chip_id, die_id, UBCTL_USER_CMD_COMM, &in, &out);
}

static int ubctl_api_common_get_data(struct utool_cmd_param *cmd_param, struct ubctl_cmd_buf *out,
				     struct utool_dev *dev, enum utool_dev_step_flag step_flag)
{
	struct ubctl_api_param api_param = {};
	struct dev_data *dev_data = {};
	int ret;

	ret = utool_open_dev_step(dev, cmd_param->chip_id, cmd_param->die_id, step_flag);
	if (ret != UTOOL_OK) {
		return ret;
	}
	api_param.user_data_size = out->data_size;
	api_param.user_data = out->data;

	dev_data = dev->dev_data;
	dev_data->is_api_query = true;
	dev_data->api_param = &api_param;

	ret = utool_cmd_select(dev, cmd_param);
	if (ret != UTOOL_OK) {
		utool_err_msg("API function failed to get data, ret = %d.\n", ret);
		goto utool_close_dev;
	}
	out->data_size = dev->dev_data->api_param->user_used_size;

utool_close_dev:
	utool_close(dev);

	return ret;
}

static int ubctl_check_in_comm(struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	if (in == NULL || out == NULL) {
		utool_err_msg("Invalid param: in or out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (in->is_read && out->data_size == 0) {
		utool_err_msg("Invalid param: out buffer is empty.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (in->data_size > 0 && in->data == NULL) {
		utool_err_msg("Invalid param: in data size = %u bytes and in data is NULL.\n",
			      in->data_size);
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (out->data_size > 0 && out->data == NULL) {
		utool_err_msg("Invalid param: out data size = %u bytes but out data is NULL.\n",
			      out->data_size);
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

static int ubctl_ls_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
			struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	struct ubctl_api_param api_param = {};
	struct dev_data dev_data = {};
	struct utool_dev dev = {};
	int ret;

	UTOOL_SET_USED(ubctl_cmd);
	UTOOL_SET_USED(in);

	api_param.user_data_size = out->data_size;
	api_param.user_data = out->data;

	dev_data.api_param = &api_param;
	dev_data.is_api_query = true;
	dev_data.execute = utool_api_common_copy;

	dev.dev_data = &dev_data;
	ret = utool_open_dev_step(&dev, chip_id, die_id, UTOOL_DEV_STEP_LS_API);
	if (ret != UTOOL_OK && ret != UTOOL_OK_LS) {
		utool_err_msg("Failed to get ls data, ret = %d.\n", ret);
		return ret;
	}

	out->data_size = dev.dev_data->api_param->user_used_size;

	return ret == UTOOL_OK_LS ? UTOOL_OK : ret;
}

static int ubctl_port_info_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
			       struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	struct utool_cmd_param cmd_param = {};
	enum utool_dev_step_flag step_flag;
	struct dev_data dev_data = {};
	struct utool_dev dev = {};
	int ret;

	UTOOL_SET_USED(ubctl_cmd);

	cmd_param.module_id = UTOOL_MODULE_NAME_PORT_INFO;
	cmd_param.flags = UTOOL_FLAG_M | UTOOL_FLAG_P;
	cmd_param.port = *(uint32_t *)in->data;
	cmd_param.chip_id = chip_id;
	cmd_param.die_id = die_id;

	dev.dev_data = &dev_data;
	step_flag = UTOOL_DEV_STEP_SCAN;

	ret = ubctl_api_common_get_data(&cmd_param, out, &dev, step_flag);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to get port_info data, ret = %d.\n", ret);
	}

	return ret;
}

static int ubctl_check_port(struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	UTOOL_SET_USED(out);
	if (in->is_read == false) {
		utool_err_msg("The parameter 'in' is invalid, the 'is_read' parameter must be set to 'true'.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (in->data_size != sizeof(uint32_t) || in->data == NULL) {
		utool_err_msg("The parameter 'in' is invalid, please provide a valid port_id.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

static int ubctl_check_port_time(struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	UTOOL_SET_USED(out);
	if (in->is_read == false) {
		utool_err_msg("The parameter 'in' is invalid, the 'is_read' parameter must be set to 'true'.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (in->data_size != sizeof(struct utool_port_time_api_in_data) || in->data == NULL) {
		utool_err_msg("The parameter 'in' is invalid, please provide a valid port_id and time.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

static int ubctl_port_pkt_stats_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
				    struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	struct utool_cmd_param cmd_param = {};
	enum utool_dev_step_flag step_flag;
	struct dev_data dev_data = {};
	struct utool_dev dev = {};
	int ret;

	UTOOL_SET_USED(ubctl_cmd);

	cmd_param.module_id = UTOOL_MODULE_NAME_PORT_PKT_STATS;
	cmd_param.flags = UTOOL_FLAG_M | UTOOL_FLAG_P;
	cmd_param.port = *(uint32_t *)in->data;
	cmd_param.chip_id = chip_id;
	cmd_param.die_id = die_id;

	dev_data.execute = utool_api_common_copy;
	dev.dev_data = &dev_data;
	step_flag = UTOOL_DEV_STEP_SCAN;

	ret = ubctl_api_common_get_data(&cmd_param, out, &dev, step_flag);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to get port_pkt_stats data, ret = %d.\n", ret);
	}

	return ret;
}

static int ubctl_check_port_pkt_stats(struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	if (ubctl_check_port(in, out) != UTOOL_OK) {
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (out->data_size < sizeof(struct ubctl_port_pkt_stats_data)) {
		utool_err_msg("Invalid param: out is NULL or out data size < %zu bytes.\n",
			      sizeof(struct ubctl_port_pkt_stats_data));
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}
static void utool_fill_dl_perf_stats(uint32_t *pkt_out_data, struct utool_dl_perf_stats *performance_stats)
{
#define VALID_START_BIT 0
#define VALID_END_BIT 0
#define PORT_ID_START_BIT 8
#define PORT_ID_END_BIT 15

	uint32_t first_reg;
	size_t copy_size;

	if (!pkt_out_data || !performance_stats) {
		return;
	}

	first_reg = pkt_out_data[0];
	performance_stats->valid = UTOOL_EXTRACT_BITS(first_reg, VALID_START_BIT, VALID_END_BIT);
	if (performance_stats->valid == 0) {
		return;
	}
	performance_stats->port_id = UTOOL_EXTRACT_BITS(first_reg, PORT_ID_START_BIT, PORT_ID_END_BIT);

	copy_size = sizeof(struct utool_dl_perf_stats) - sizeof(first_reg);
	memcpy(&performance_stats->tx_port_bw, &pkt_out_data[1], copy_size);
}

static int utool_api_performance_copy(struct fwctl_rpc_ub_out *performance_out, struct ubctl_api_param *api_param)
{
	struct utool_dl_perf_stats *current_user_data_ptr;
	struct utool_dl_perf_stats dl_perf_stats = {0};
	uint32_t *current_performance_out_data_ptr;
	uint32_t reg_count, i, user_data_size;
	uint32_t user_used_size = 0;
	void *user_data;

	user_data = api_param->user_data;
	user_data_size = api_param->user_data_size;
	reg_count = sizeof(struct utool_dl_perf_stats) / sizeof(uint32_t);
	for (i = 0; i < UTOOL_MAX_PORT; i++) {
		current_performance_out_data_ptr = (uint32_t *)(&performance_out->data[i * reg_count]);
		utool_fill_dl_perf_stats(current_performance_out_data_ptr, &dl_perf_stats);
		if (dl_perf_stats.valid == 0) {
			continue;
		}
		if ((user_data_size < user_used_size) ||
		    ((user_data_size - user_used_size) < sizeof(struct utool_dl_perf_stats))) {
			utool_err_msg("User data is invalid, user data size = %u bytes, user used size = %u bytes, next copy size = %zu bytes.\n",
				      user_data_size, user_used_size, sizeof(struct utool_dl_perf_stats));
			return UTOOL_ERR_PARSE;
		}
		current_user_data_ptr = (struct utool_dl_perf_stats *)((uint8_t *)(user_data) + user_used_size);
		memcpy(current_user_data_ptr, &dl_perf_stats, sizeof(struct utool_dl_perf_stats));
		user_used_size += sizeof(struct utool_dl_perf_stats);
		memset(&dl_perf_stats, 0, sizeof(dl_perf_stats));
	}
	api_param->user_used_size = user_used_size;
	return UTOOL_OK;
}

static int ubctl_performance_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
				 struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	struct utool_port_time_api_in_data in_data = {};
	struct utool_cmd_param cmd_param = {};
	enum utool_dev_step_flag step_flag;
	struct dev_data dev_data = {};
	struct utool_dev dev = {};
	int ret;

	UTOOL_SET_USED(ubctl_cmd);
	memcpy(&in_data, in->data, sizeof(struct utool_port_time_api_in_data));

	cmd_param.flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_T;
	cmd_param.module_id = UTOOL_MODULE_NAME_DL;
	cmd_param.port = in_data.port_id;
	cmd_param.time = in_data.time;
	cmd_param.chip_id = chip_id;
	cmd_param.die_id = die_id;
	strcpy(cmd_param.func, DL_PERFORMANCE);

	dev_data.execute = utool_api_performance_copy;
	dev.dev_data = &dev_data;
	step_flag = UTOOL_DEV_STEP_SCAN;

	ret = ubctl_api_common_get_data(&cmd_param, out, &dev, step_flag);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to get performance data, ret = %d.\n", ret);
	}

	return ret;
}

static int ubctl_rt_bandwidth_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
				  struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	struct utool_port_time_api_in_data in_data = {};
	struct utool_cmd_param cmd_param = {};
	enum utool_dev_step_flag step_flag;
	struct dev_data dev_data = {};
	struct utool_dev dev = {};
	int ret;

	UTOOL_SET_USED(ubctl_cmd);
	memcpy(&in_data, in->data, sizeof(struct utool_port_time_api_in_data));

	cmd_param.flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_T;
	cmd_param.module_id = UTOOL_MODULE_NAME_DL;
	cmd_param.port = in_data.port_id;
	cmd_param.time = in_data.time;
	cmd_param.chip_id = chip_id;
	cmd_param.die_id = die_id;
	strcpy(cmd_param.func, DL_RT_BANDWIDTH);

	dev.dev_data = &dev_data;
	step_flag = UTOOL_DEV_STEP_SCAN;
	pthread_mutex_lock(&g_api_lock);
	ret = ubctl_api_common_get_data(&cmd_param, out, &dev, step_flag);
	pthread_mutex_unlock(&g_api_lock);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to get rt_bandwidth data, ret = %d.\n", ret);
	}

	return ret;
}

static int ubctl_fw_version_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
				struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	struct utool_cmd_param cmd_param = {};
	enum utool_dev_step_flag step_flag;
	struct dev_data dev_data = {};
	struct utool_dev dev = {};
	int ret;

	UTOOL_SET_USED(ubctl_cmd);
	UTOOL_SET_USED(in);

	cmd_param.flags = UTOOL_FLAG_M;
	cmd_param.module_id = UTOOL_MODULE_NAME_FIRMWARE_VERSION;
	cmd_param.chip_id = chip_id;
	cmd_param.die_id = die_id;

	dev_data.execute = utool_api_common_copy;
	dev.dev_data = &dev_data;
	step_flag = UTOOL_DEV_STEP_SCAN;

	ret = ubctl_api_common_get_data(&cmd_param, out, &dev, step_flag);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to get fw_version data, ret = %d.\n", ret);
	}

	return ret;
}

static int ubctl_check_fw_version(struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	if (in->is_read == false) {
		utool_err_msg("The parameter 'in' is invalid, the 'is_read' parameter must be set to 'true'.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (out->data_size < sizeof(struct ubctl_fw_version_data)) {
		utool_err_msg("Invalid param: out is NULL or out data size < %zu bytes.\n",
			      sizeof(struct ubctl_fw_version_data));
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

static int ubctl_port_link_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
			       struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	struct utool_cmd_param cmd_param = {};
	enum utool_dev_step_flag step_flag;
	struct dev_data dev_data = {};
	struct utool_dev dev = {};
	int ret;

	UTOOL_SET_USED(ubctl_cmd);

	cmd_param.flags = UTOOL_FLAG_M | UTOOL_FLAG_P;
	cmd_param.module_id = UTOOL_MODULE_NAME_PORT_LINK;
	cmd_param.port = *(uint32_t *)in->data;
	cmd_param.chip_id = chip_id;
	cmd_param.die_id = die_id;

	dev_data.execute = utool_api_common_copy;
	dev.dev_data = &dev_data;
	step_flag = UTOOL_DEV_STEP_SCAN;

	ret = ubctl_api_common_get_data(&cmd_param, out, &dev, step_flag);
	if (ret != UTOOL_OK) {
		utool_err_msg("Faild to get port_link data, ret = %d.\n", ret);
	}

	return ret;
}

static int ubctl_check_port_value(struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	UTOOL_SET_USED(out);
	if (in->is_read == true) {
		utool_err_msg("The parameter 'in' is invalid, the 'is_read' parameter must be set to 'false'.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (in->data_size != sizeof(struct utool_port_value_api_in_data) || in->data == NULL) {
		utool_err_msg("The parameter 'in' is invalid, please provide a valid port_id and value.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

static int utool_api_dummy_copy(struct fwctl_rpc_ub_out *rpc_out, struct ubctl_api_param *api_param)
{
	UTOOL_SET_USED(rpc_out);
	UTOOL_SET_USED(api_param);

	utool_reg_msg("The copy portion of the API function has been executed successfully.\n");

	return UTOOL_OK;
}

static int ubctl_perf_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
			  struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	struct utool_port_time_value_api_in_data in_data_start = {};
	struct utool_port_value_api_in_data in_data_end = {};
	struct utool_cmd_param cmd_param = {};
	enum utool_dev_step_flag step_flag;
	struct dev_data dev_data = {};
	struct utool_dev dev = {};
	int ret;

	switch (ubctl_cmd) {
		case UBCTL_CONFIG_PERF_START_COMM:
			cmd_param.flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_E | UTOOL_FLAG_T;
			memcpy(&in_data_start, in->data, sizeof(struct utool_port_time_value_api_in_data));
			cmd_param.port = in_data_start.port_id;
			cmd_param.time = in_data_start.time;
			cmd_param.value = in_data_start.value;
			dev_data.execute = utool_api_dummy_copy;
			break;
		case UBCTL_QUERY_PERF_COMM:
			cmd_param.flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F;
			cmd_param.port = *(uint32_t *)in->data;
			dev_data.execute = utool_api_performance_copy;
			break;
		case UBCTL_CONFIG_PERF_END_COMM:
			cmd_param.flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_E;
			memcpy(&in_data_end, in->data, sizeof(struct utool_port_value_api_in_data));
			cmd_param.port = in_data_end.port_id;
			cmd_param.value = in_data_end.value;
			dev_data.execute = utool_api_dummy_copy;
			break;
	default:
		utool_err_msg("Invalid param: ubctl cmd is not found in ubctl_perf_api function, ubctl_cmd = %u\n",
			      ubctl_cmd);
		return UTOOL_ERR_CMD_NOT_FOUND;
	}
	cmd_param.module_id = UTOOL_MODULE_NAME_DL;
	cmd_param.chip_id = chip_id;
	cmd_param.die_id = die_id;
	strcpy(cmd_param.func, DL_PERF);

	dev.dev_data = &dev_data;
	step_flag = UTOOL_DEV_STEP_SCAN;

	ret = ubctl_api_common_get_data(&cmd_param, out, &dev, step_flag);
	if (ret != UTOOL_OK) {
		utool_err_msg("Faild to execute perf api, ret = %d, ubctl_cmd = %u.\n", ret, ubctl_cmd);
	}

	return ret;
}

static int ubctl_check_port_time_value(struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	UTOOL_SET_USED(out);
	if (in->is_read == true) {
		utool_err_msg("The parameter 'in' is invalid, the 'is_read' parameter must be set to 'false'.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (in->data_size != sizeof(struct utool_port_time_value_api_in_data) || in->data == NULL) {
		utool_err_msg("The parameter 'in' is invalid, please provide a valid port_id, time and value.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

static int ubctl_loopback_api_parse_input(uint32_t ubctl_cmd, const struct ubctl_cmd_buf *in,
					  struct utool_cmd_param *cmd_param)
{
	struct utool_port_value_api_in_data in_data = {};

	switch (ubctl_cmd) {
		case UBCTL_CONFIG_RXMAC2TXMAC_COMM:
			cmd_param->flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_E;
			memcpy(&in_data, in->data, sizeof(struct utool_port_value_api_in_data));
			cmd_param->port = in_data.port_id;
			cmd_param->value = in_data.value;
			strcpy(cmd_param->func, UBOE_LOOPBACK_MAC_OUTER);
			break;
		case UBCTL_QUERY_RXMAC2TXMAC_COMM:
			cmd_param->flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F;
			cmd_param->port = *(uint32_t *)in->data;
			strcpy(cmd_param->func, UBOE_LOOPBACK_MAC_OUTER);
			break;
		case UBCTL_CONFIG_TXMAC2RXMAC_COMM:
			cmd_param->flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_E;
			memcpy(&in_data, in->data, sizeof(struct utool_port_value_api_in_data));
			cmd_param->port = in_data.port_id;
			cmd_param->value = in_data.value;
			strcpy(cmd_param->func, UBOE_LOOPBACK_MAC_INNER);
			break;
		case UBCTL_QUERY_TXMAC2RXMAC_COMM:
			cmd_param->flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F;
			cmd_param->port = *(uint32_t *)in->data;
			strcpy(cmd_param->func, UBOE_LOOPBACK_MAC_INNER);
			break;
		case UBCTL_CONFIG_TXPCS2RXPCS_COMM:
			cmd_param->flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_E;
			memcpy(&in_data, in->data, sizeof(struct utool_port_value_api_in_data));
			cmd_param->port = in_data.port_id;
			cmd_param->value = in_data.value;
			strcpy(cmd_param->func, UBOE_LOOPBACK_PCS_INNER);
			break;
		case UBCTL_QUERY_TXPCS2RXPCS_COMM:
			cmd_param->flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F;
			cmd_param->port = *(uint32_t *)in->data;
			strcpy(cmd_param->func, UBOE_LOOPBACK_PCS_INNER);
			break;
	default:
		utool_err_msg("Invalid param: ubctl cmd is not found in loopback api, ubctl_cmd = %u\n", ubctl_cmd);
		return UTOOL_ERR_CMD_NOT_FOUND;
	}

	return UTOOL_OK;
}

static int ubctl_loopback_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
			      struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	struct utool_cmd_param cmd_param = {};
	enum utool_dev_step_flag step_flag;
	struct dev_data dev_data = {};
	struct utool_dev dev = {};
	int ret;

	ret = ubctl_loopback_api_parse_input(ubctl_cmd, in, &cmd_param);
	if (ret != UTOOL_OK) {
		utool_err_msg("Faild to parse input, ret = %d.\n", ret);
		return ret;
	}
	cmd_param.module_id = UTOOL_MODULE_NAME_UBOE;
	cmd_param.chip_id = chip_id;
	cmd_param.die_id = die_id;

	dev_data.execute = utool_api_common_copy;
	dev.dev_data = &dev_data;
	step_flag = UTOOL_DEV_STEP_SCAN;

	ret = ubctl_api_common_get_data(&cmd_param, out, &dev, step_flag);
	if (ret != UTOOL_OK) {
		utool_err_msg("Faild to get port_link data, ret = %d.\n", ret);
	}

	return ret;
}

static void utool_fill_ssu_vl_pkt_CAP_V01(uint32_t *ssu_vl_pkt_out_data,
					  union ssu_vl_pkt_info_CAP_VERSION *ssu_vl_pkt_info)
{
	struct ssu_vl_pkt_info_CAP_V01 *CAP_01;
	uint32_t reg;

	CAP_01 = (struct ssu_vl_pkt_info_CAP_V01 *)ssu_vl_pkt_info;
	CAP_01->port_id = ssu_vl_pkt_out_data[PORT_ID_IDX];
	CAP_01->enable_flag = ssu_vl_pkt_out_data[ENABLE_FLAG_IDX];

	reg = ssu_vl_pkt_out_data[REG_CTRL_IDX];
	CAP_01->ssu_rx_in_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_IN_DFX_VL_SEL_START, RX_IN_DFX_VL_SEL_END);
	CAP_01->ssu_tx_in_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_IN_DFX_VL_SEL_START, TX_IN_DFX_VL_SEL_END);
	CAP_01->ssu_rx_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_OUT_DFX_VL_SEL_START, RX_OUT_DFX_VL_SEL_END);
	CAP_01->ssu_tx_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_OUT_DFX_VL_SEL_START, TX_OUT_DFX_VL_SEL_END);
	CAP_01->reserved = UTOOL_EXTRACT_BITS(reg, RESERVED_0_START, RESERVED_0_END);

	memcpy(&CAP_01->rx_packet_in_vl_cnt, &ssu_vl_pkt_out_data[V01_RX_CNT_START_IDX],
	       (V01_COPY_REG_COUNT * sizeof(uint32_t)));
}

static void utool_fill_ssu_vl_pkt_CAP_2(uint32_t *ssu_vl_pkt_out_data,
					union ssu_vl_pkt_info_CAP_VERSION *ssu_vl_pkt_info)
{
	struct ssu_vl_pkt_info_CAP_2 *CAP_2;
	uint32_t reg;

	CAP_2 = (struct ssu_vl_pkt_info_CAP_2 *)ssu_vl_pkt_info;
	CAP_2->port_id = ssu_vl_pkt_out_data[PORT_ID_IDX];
	CAP_2->enable_flag = ssu_vl_pkt_out_data[ENABLE_FLAG_IDX];

	reg = ssu_vl_pkt_out_data[REG_CTRL_IDX];
	CAP_2->ssu_rx_in_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_IN_DFX_VL_SEL_START, RX_IN_DFX_VL_SEL_END);
	CAP_2->ssu_tx_in_dfx_vl_sel  = UTOOL_EXTRACT_BITS(reg, TX_IN_DFX_VL_SEL_START, TX_IN_DFX_VL_SEL_END);
	CAP_2->ssu_rx_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_OUT_DFX_VL_SEL_START, RX_OUT_DFX_VL_SEL_END);
	CAP_2->ssu_tx_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_OUT_DFX_VL_SEL_START, TX_OUT_DFX_VL_SEL_END);
	CAP_2->reserved_0 = UTOOL_EXTRACT_BITS(reg, RESERVED_0_START, RESERVED_0_END);

	memcpy(&CAP_2->tx_packet_in_sf_vl_cnt, &ssu_vl_pkt_out_data[CAP2_TX_SF_CNT_START_IDX],
	       (CAP2_COPY_SF_REG_COUNT * sizeof(uint32_t)));

	reg = ssu_vl_pkt_out_data[CAP2_REG_OUT_DFX_IDX];
	CAP_2->ssu_rx_0_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_0_OUT_DFX_VL_SEL_START, RX_0_OUT_DFX_VL_SEL_END);
	CAP_2->ssu_rx_1_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_1_OUT_DFX_VL_SEL_START, RX_1_OUT_DFX_VL_SEL_END);
	CAP_2->ssu_rx_2_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_2_OUT_DFX_VL_SEL_START, RX_2_OUT_DFX_VL_SEL_END);
	CAP_2->ssu_tx_0_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_0_OUT_DFX_VL_SEL_START, TX_0_OUT_DFX_VL_SEL_END);
	CAP_2->ssu_tx_1_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_1_OUT_DFX_VL_SEL_START, TX_1_OUT_DFX_VL_SEL_END);
	CAP_2->ssu_tx_2_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_2_OUT_DFX_VL_SEL_START, TX_2_OUT_DFX_VL_SEL_END);
	CAP_2->reserved_1 = UTOOL_EXTRACT_BITS(reg, RESERVED_CH_START, RESERVED_CH_END);

	reg = ssu_vl_pkt_out_data[CAP2_REG_IN_SF_DFX_IDX];
	CAP_2->ssu_rx_0_in_sf_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_0_IN_DFX_VL_SEL_START, RX_0_IN_DFX_VL_SEL_END);
	CAP_2->ssu_rx_1_in_sf_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_1_IN_DFX_VL_SEL_START, RX_1_IN_DFX_VL_SEL_END);
	CAP_2->ssu_rx_2_in_sf_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_2_IN_DFX_VL_SEL_START, RX_2_IN_DFX_VL_SEL_END);
	CAP_2->ssu_tx_0_in_sf_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_0_IN_DFX_VL_SEL_START, TX_0_IN_DFX_VL_SEL_END);
	CAP_2->ssu_tx_1_in_sf_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_1_IN_DFX_VL_SEL_START, TX_1_IN_DFX_VL_SEL_END);
	CAP_2->ssu_tx_2_in_sf_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_2_IN_DFX_VL_SEL_START, TX_2_IN_DFX_VL_SEL_END);
	CAP_2->reserved_2 = UTOOL_EXTRACT_BITS(reg, RESERVED_CH_START, RESERVED_CH_END);

	reg = ssu_vl_pkt_out_data[CAP2_REG_IN_BPS_DFX_IDX];
	CAP_2->ssu_rx_0_in_bps_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_0_IN_DFX_VL_SEL_START, RX_0_IN_DFX_VL_SEL_END);
	CAP_2->ssu_rx_1_in_bps_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_1_IN_DFX_VL_SEL_START, RX_1_IN_DFX_VL_SEL_END);
	CAP_2->ssu_rx_2_in_bps_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_2_IN_DFX_VL_SEL_START, RX_2_IN_DFX_VL_SEL_END);
	CAP_2->ssu_tx_0_in_bps_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_0_IN_DFX_VL_SEL_START, TX_0_IN_DFX_VL_SEL_END);
	CAP_2->ssu_tx_1_in_bps_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_1_IN_DFX_VL_SEL_START, TX_1_IN_DFX_VL_SEL_END);
	CAP_2->ssu_tx_2_in_bps_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_2_IN_DFX_VL_SEL_START, TX_2_IN_DFX_VL_SEL_END);
	CAP_2->reserved_3 = UTOOL_EXTRACT_BITS(reg, RESERVED_CH_START, RESERVED_CH_END);
}

static void utool_fill_ssu_vl_pkt_CAP_3(uint32_t *ssu_vl_pkt_out_data,
					union ssu_vl_pkt_info_CAP_VERSION *ssu_vl_pkt_info)
{
	struct ssu_vl_pkt_info_CAP_3 *CAP_3;
	uint32_t reg;

	CAP_3 = (struct ssu_vl_pkt_info_CAP_3 *)ssu_vl_pkt_info;
	CAP_3->port_id = ssu_vl_pkt_out_data[PORT_ID_IDX];
	CAP_3->enable_flag = ssu_vl_pkt_out_data[ENABLE_FLAG_IDX];

	reg = ssu_vl_pkt_out_data[REG_CTRL_IDX];
	CAP_3->ssu_rx_in_dfx_vl_sel  = UTOOL_EXTRACT_BITS(reg, RX_IN_DFX_VL_SEL_START, RX_IN_DFX_VL_SEL_END);
	CAP_3->ssu_tx_in_dfx_vl_sel  = UTOOL_EXTRACT_BITS(reg, TX_IN_DFX_VL_SEL_START, TX_IN_DFX_VL_SEL_END);
	CAP_3->ssu_rx_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_OUT_DFX_VL_SEL_START, RX_OUT_DFX_VL_SEL_END);
	CAP_3->ssu_tx_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_OUT_DFX_VL_SEL_START, TX_OUT_DFX_VL_SEL_END);
	CAP_3->reserved_0 = UTOOL_EXTRACT_BITS(reg, RESERVED_0_START, RESERVED_0_END);

	memcpy(&CAP_3->tx_packet_in_vl_cnt0, &ssu_vl_pkt_out_data[CAP3_TX_VL_CNT0_START_IDX],
	       (CAP3_COPY_VL_CNT0_COUNT * sizeof(uint32_t)));

	reg = ssu_vl_pkt_out_data[CAP3_REG_OUT_DFX_IDX];
	CAP_3->ssu_rx_0_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_0_OUT_DFX_VL_SEL_START, RX_0_OUT_DFX_VL_SEL_END);
	CAP_3->ssu_rx_1_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_1_OUT_DFX_VL_SEL_START, RX_1_OUT_DFX_VL_SEL_END);
	CAP_3->ssu_rx_2_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_2_OUT_DFX_VL_SEL_START, RX_2_OUT_DFX_VL_SEL_END);
	CAP_3->ssu_tx_0_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_0_OUT_DFX_VL_SEL_START, TX_0_OUT_DFX_VL_SEL_END);
	CAP_3->ssu_tx_1_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_1_OUT_DFX_VL_SEL_START, TX_1_OUT_DFX_VL_SEL_END);
	CAP_3->ssu_tx_2_out_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_2_OUT_DFX_VL_SEL_START, TX_2_OUT_DFX_VL_SEL_END);
	CAP_3->reserved_1 = UTOOL_EXTRACT_BITS(reg, RESERVED_CH_START, RESERVED_CH_END);

	reg = ssu_vl_pkt_out_data[CAP3_REG_IN_SF_DFX_IDX];
	CAP_3->ssu_rx_0_in_sf_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_0_IN_DFX_VL_SEL_START, RX_0_IN_DFX_VL_SEL_END);
	CAP_3->ssu_rx_1_in_sf_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_1_IN_DFX_VL_SEL_START, RX_1_IN_DFX_VL_SEL_END);
	CAP_3->ssu_rx_2_in_sf_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_2_IN_DFX_VL_SEL_START, RX_2_IN_DFX_VL_SEL_END);
	CAP_3->ssu_tx_0_in_sf_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_0_IN_DFX_VL_SEL_START, TX_0_IN_DFX_VL_SEL_END);
	CAP_3->ssu_tx_1_in_sf_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_1_IN_DFX_VL_SEL_START, TX_1_IN_DFX_VL_SEL_END);
	CAP_3->ssu_tx_2_in_sf_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_2_IN_DFX_VL_SEL_START, TX_2_IN_DFX_VL_SEL_END);
	CAP_3->reserved_2 = UTOOL_EXTRACT_BITS(reg, RESERVED_CH_START, RESERVED_CH_END);

	reg = ssu_vl_pkt_out_data[CAP3_REG_IN_BPS_DFX_IDX];
	CAP_3->ssu_rx_0_in_bps_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_0_IN_DFX_VL_SEL_START, RX_0_IN_DFX_VL_SEL_END);
	CAP_3->ssu_rx_1_in_bps_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_1_IN_DFX_VL_SEL_START, RX_1_IN_DFX_VL_SEL_END);
	CAP_3->ssu_rx_2_in_bps_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, RX_2_IN_DFX_VL_SEL_START, RX_2_IN_DFX_VL_SEL_END);
	CAP_3->ssu_tx_0_in_bps_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_0_IN_DFX_VL_SEL_START, TX_0_IN_DFX_VL_SEL_END);
	CAP_3->ssu_tx_1_in_bps_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_1_IN_DFX_VL_SEL_START, TX_1_IN_DFX_VL_SEL_END);
	CAP_3->ssu_tx_2_in_bps_dfx_vl_sel = UTOOL_EXTRACT_BITS(reg, TX_2_IN_DFX_VL_SEL_START, TX_2_IN_DFX_VL_SEL_END);
	CAP_3->reserved_3 = UTOOL_EXTRACT_BITS(reg, RESERVED_CH_START, RESERVED_CH_END);
}


static int utool_fill_ssu_vl_pkt(uint32_t *ssu_vl_pkt_out_data, uint32_t env_version,
				 union ssu_vl_pkt_info_CAP_VERSION *ssu_vl_pkt_info)
{
	switch (env_version) {
		case UTOOL_ENV_VER_A_0:
		case UTOOL_ENV_VER_K_0:
			utool_fill_ssu_vl_pkt_CAP_V01(ssu_vl_pkt_out_data, ssu_vl_pkt_info);
			break;
		case UTOOL_ENV_VER_A_1:
			utool_fill_ssu_vl_pkt_CAP_2(ssu_vl_pkt_out_data, ssu_vl_pkt_info);
			break;
		case UTOOL_ENV_VER_K_1:
			utool_fill_ssu_vl_pkt_CAP_3(ssu_vl_pkt_out_data, ssu_vl_pkt_info);
			break;
		default:
			utool_err_msg("Unknown env_version: %u.\n", env_version);
			return UTOOL_ERR_PARSE;
	}

	return UTOOL_OK;
}

static int utool_api_query_ssu_vl_pkt_copy(struct fwctl_rpc_ub_out *ssu_vl_pkt_out, struct ubctl_api_param *api_param)
{
	struct ssu_vl_pkt_info ssu_vl_pkt_info = {};
	uint32_t user_data_size;
	void *user_data;
	int ret;

	user_data_size = api_param->user_data_size;
	user_data = api_param->user_data;
	ssu_vl_pkt_info.env_version = ssu_vl_pkt_out->env_version;

	ret = utool_fill_ssu_vl_pkt(ssu_vl_pkt_out->data, ssu_vl_pkt_out->env_version, &ssu_vl_pkt_info.ssu_vl_pkt_info_CAP);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to fill ssu_vl_pkt, ret = %d bytes.\n", ret);
		return ret;
	}

	if (user_data_size < sizeof(struct ssu_vl_pkt_info)) {
		utool_err_msg("User data is invalid, user data size = %u bytes, current need = %zu bytes.\n",
			      user_data_size, sizeof(struct ssu_vl_pkt_info));
		return UTOOL_ERR_PARSE;
	}

	memcpy(user_data, &ssu_vl_pkt_info, sizeof(struct ssu_vl_pkt_info));
	api_param->user_used_size = sizeof(struct ssu_vl_pkt_info);

	return UTOOL_OK;
}

static int ubctl_ssu_vl_pkt_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
				struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	struct utool_port_value_api_in_data in_data = {};
	struct utool_cmd_param cmd_param = {};
	enum utool_dev_step_flag step_flag;
	struct dev_data dev_data = {};
	struct utool_dev dev = {};
	int ret;

	if (ubctl_cmd == UBCTL_CONFIG_SSU_VL_PKT_COMM) {
		cmd_param.flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_E;
		memcpy(&in_data, in->data, sizeof(struct utool_port_value_api_in_data));
		cmd_param.port = in_data.port_id;
		cmd_param.value = in_data.value;
		dev_data.execute = utool_api_common_copy;
	} else {
		cmd_param.flags = UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F;
		cmd_param.port = *(uint32_t *)in->data;
		dev_data.execute = utool_api_query_ssu_vl_pkt_copy;
	}

	cmd_param.module_id = UTOOL_MODULE_NAME_NL;
	cmd_param.chip_id = chip_id;
	cmd_param.die_id = die_id;
	strcpy(cmd_param.func, NL_SSU_VL_PKT);

	dev.dev_data = &dev_data;
	step_flag = UTOOL_DEV_STEP_SCAN;

	ret = ubctl_api_common_get_data(&cmd_param, out, &dev, step_flag);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to get port_link data, ret = %d.\n", ret);
	}

	return ret;
}

static struct ubctl_query_comm g_query_comm_table[] = {
	{ UBCTL_LS_CMD_COMM, NULL, ubctl_ls_api },
	{ UBCTL_QUERY_PORT_INFO_CMD_COMM, ubctl_check_port, ubctl_port_info_api },
	{ UBCTL_QUERY_PERFORMANCE_CMD_COMM, ubctl_check_port_time, ubctl_performance_api },
	{ UBCTL_QUERY_RT_BANDWIDTH_CMD_COMM, ubctl_check_port_time, ubctl_rt_bandwidth_api },
	{ UBCTL_QUERY_PORT_PKT_STATS_COMM, ubctl_check_port_pkt_stats, ubctl_port_pkt_stats_api },
	{ UBCTL_QUERY_FW_VERSION_COMM, ubctl_check_fw_version, ubctl_fw_version_api },
	{ UBCTL_QUERY_PORT_LINK_COMM, ubctl_check_port, ubctl_port_link_api },
	{ UBCTL_CONFIG_PERF_START_COMM, ubctl_check_port_time_value, ubctl_perf_api },
	{ UBCTL_QUERY_PERF_COMM, ubctl_check_port, ubctl_perf_api },
	{ UBCTL_CONFIG_PERF_END_COMM, ubctl_check_port_value, ubctl_perf_api },
	{ UBCTL_CONFIG_RXMAC2TXMAC_COMM, ubctl_check_port_value, ubctl_loopback_api },
	{ UBCTL_QUERY_RXMAC2TXMAC_COMM, ubctl_check_port, ubctl_loopback_api },
	{ UBCTL_CONFIG_TXMAC2RXMAC_COMM, ubctl_check_port_value, ubctl_loopback_api },
	{ UBCTL_QUERY_TXMAC2RXMAC_COMM, ubctl_check_port, ubctl_loopback_api },
	{ UBCTL_CONFIG_TXPCS2RXPCS_COMM, ubctl_check_port_value, ubctl_loopback_api },
	{ UBCTL_QUERY_TXPCS2RXPCS_COMM, ubctl_check_port, ubctl_loopback_api },
	{ UBCTL_CONFIG_SSU_VL_PKT_COMM, ubctl_check_port_value, ubctl_ssu_vl_pkt_api },
	{ UBCTL_QUERY_SSU_VL_PKT_COMM, ubctl_check_port, ubctl_ssu_vl_pkt_api },
};

int ubctl_query_comm_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
			 struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out)
{
	struct ubctl_query_comm *dispatch = NULL;
	uint32_t table_cnt, i;
	int ret;

	ret = ubctl_check_in_comm(in, out);
	if (ret != UTOOL_OK) {
		return ret;
	}
	table_cnt = UTOOL_ARRAY_SIZE(g_query_comm_table);
	for (i = 0; i < table_cnt; i++) {
		dispatch = &g_query_comm_table[i];
		if (dispatch->ubctl_cmd != ubctl_cmd || dispatch->execute == NULL) {
			continue;
		}
		if (dispatch->check_in != NULL) {
			ret = dispatch->check_in(in, out);
			if (ret != UTOOL_OK) {
				return ret;
			}
		}
		return dispatch->execute(chip_id, die_id, ubctl_cmd, in, out);
	}

	utool_err_msg("Invalid param: ubctl cmd is not found.\n");
	return UTOOL_ERR_CMD_NOT_FOUND;
}
