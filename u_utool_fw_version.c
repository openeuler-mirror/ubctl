// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <stdio.h>

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_fw_version.h"

struct utool_fw_version_data {
	uint32_t fw_version;
	uint32_t reserved[5];
};

int utool_fw_version_parse_rpc_pkt(struct fwctl_rpc_ub_out *fw_version_out)
{
#define UTOOL_FW_HIGH_MASK 0xFFFF
#define UTOOL_FW_HIGH_OFFSET 16
	struct utool_fw_version_data *version_data = NULL;

	if (fw_version_out == NULL) {
		utool_err_msg("Failed to parse firmware version rpc pkt, firmware version out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}
	if (fw_version_out->data_size != sizeof(struct utool_fw_version_data)) {
		utool_err_msg("Failed to parse firmware version rpc pkt, out data size = %u.\n",
			      fw_version_out->data_size);
		return UTOOL_ERR_INVALID_PARAM;
	}

	version_data = (struct utool_fw_version_data *)(fw_version_out->data);
	utool_reg_msg("firmware version: B%04X_%04X\n",
		      (version_data->fw_version >> UTOOL_FW_HIGH_OFFSET) & UTOOL_FW_HIGH_MASK,
		      version_data->fw_version & UTOOL_FW_HIGH_MASK);

	return UTOOL_OK;
}

static int utool_fw_version_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
				struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec fw_version_pkt_exec = { UTOOL_CMD_QUERY_FIRMWARE_VERSION, 0, NULL };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	fw_version_pkt_exec.data_len = sizeof(struct utool_fw_version_data);
	fw_version_pkt_exec.execute = utool_fw_version_parse_rpc_pkt;

	pkt_in = utool_null_create_pkt_in(&pkt_in_len, param);
	if (pkt_in == NULL) {
		return UTOOL_ERR_MALLOC;
	}

	ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &fw_version_pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	utool_destroy_pkt_in(&pkt_in);

	return ret;
}

int utool_fw_version_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_cmd_fw_version_table[] = {
		{ UTOOL_FLAG_M, utool_fw_version_cmd, NULL, 0 },
	};
	uint32_t cmd_fw_version_cnt = UTOOL_ARRAY_SIZE(utool_cmd_fw_version_table);
	uint32_t i = 0;

	if ((dev == NULL) || (param == NULL)) {
		utool_err_msg("Failed to dispatch firmware version, dev==NULL(%d), param==NULL(%d).\n",
			      (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < cmd_fw_version_cnt; i++) {
		if (param->flags == utool_cmd_fw_version_table[i].flags) {
			if (utool_cmd_fw_version_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch firmware version, execute is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

		return utool_cmd_fw_version_table[i].execute(dev, param,
							     utool_cmd_fw_version_table[i].func_table,
							     utool_cmd_fw_version_table[i].func_cnt);
		}
	}
	utool_err_msg("The ubctl firmware version command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m fw_version\n");

	return UTOOL_ERR_CMD_NOT_FOUND;
}
