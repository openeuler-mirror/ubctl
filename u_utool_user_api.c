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
