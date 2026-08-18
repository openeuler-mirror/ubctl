// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "./common/u_utool_error.h"
#include "./common/u_utool_fwctl.h"
#include "./include/u_utool_user_api.h"

#define UBCTL_OPCODE_MAX_LEN 1016U

struct ubctl_cmd_map {
	uint32_t user_cmd;
	enum ub_fwctl_cmdrpc_type rpc_type;
};

static struct ubctl_cmd_map g_cmd_map_table[] = {
	{ UBCTL_USER_CMD_COMM, UBCTL_CMD_QUERY_CONF_USER_COMM },
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
		utool_err_msg("Invalid param: in data size = %ubytes and in->data is NULL.\n", in->data_size);
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (out->data_size > 0 && out->data == NULL) {
		utool_err_msg("Invalid param: out data size = %ubytes and out->data is NULL.\n", out->data_size);
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (in->data_size > UBCTL_OPCODE_MAX_LEN || out->data_size > UBCTL_OPCODE_MAX_LEN) {
		utool_err_msg("Invalid param: in data size = %ubytes or out data size = %ubytes is bigger than max size = %ubytes.\n",
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
		utool_err_msg("Buffer size %ubytes < required data %ubytes.\n", buf_size, rpc_out->data_size);
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
	struct ubctl_cmd_map map[] = {
		{ UBCTL_QUERY_AEQC_CMD_COMM, UTOOL_CMD_QUERY_AEQC_INFO },
		{ UBCTL_QUERY_CEQC_CMD_COMM, UTOOL_CMD_QUERY_CEQC_INFO},
	};
	int ret;

	if (dev_name == NULL || buf == NULL) {
		utool_err_msg("Invalid param: dev name or buf is null.\n");
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
