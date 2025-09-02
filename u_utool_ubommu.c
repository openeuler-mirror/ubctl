// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_ubommu.h"

static struct utool_field_info g_utool_ubommu_field[] = {
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "axim_aw_request_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "axim_aw_bresp_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "axim_aw_data_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "axim_aw_outstanding_num" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "axim_ar_request_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "axim_ar_resp_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "axim_ar_data_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "axim_ar_outstanding_num" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ubommu_trans_request_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ubommu_trans_resp_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ubommu_trans_outstanding_num" },

	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "ubommu_int_src" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

int utool_ubommu_cal_data_len(uint32_t *ubommu_data_len)
{
	uint32_t ubommu_reg_cnt = 0;
	int ret = UTOOL_OK;

	if (ubommu_data_len == NULL) {
		utool_err_msg("Param is invalid, ubommu data len is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_cal_reg_cnt(g_utool_ubommu_field, UTOOL_ARRAY_SIZE(g_utool_ubommu_field), &ubommu_reg_cnt);
	if (ret != UTOOL_OK) {
		utool_err_msg("Falied to cal ubommu reg cnt.\n");
		return ret;
	}

	*ubommu_data_len = ubommu_reg_cnt * sizeof(uint32_t);
	return UTOOL_OK;
}

int utool_ubommu_parse_rpc_pkt(struct fwctl_rpc_ub_out *ubommu_out)
{
	int ret = UTOOL_OK;

	if (ubommu_out == NULL) {
		utool_err_msg("Failed to parse ubommu rpc pkt, ubommu out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_pkt_parse(ubommu_out, UTOOL_ARRAY_SIZE(g_utool_ubommu_field),
			      g_utool_ubommu_field, UTOOL_MODULE_UBOMMU);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ubommu data.\n");
	}

	return ret;
}

static int utool_ubommu_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
			    struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec ubommu_pkt_exec = { UTOOL_CMD_QUERY_UBOMMU, 0, NULL };
	int ret = UTOOL_OK;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	ret = utool_ubommu_cal_data_len(&ubommu_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to cal ubommu reg cnt.\n");
		return ret;
	}

	ubommu_pkt_exec.execute = utool_ubommu_parse_rpc_pkt;

	ret = utool_pkt_operation_have_port(dev, param, &ubommu_pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	return ret;
}

int utool_ubommu_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_cmd_ubommu_table[] = {
		{ UTOOL_FLAG_M, utool_ubommu_cmd, NULL, 0 },
	};
	uint32_t cmd_ubommu_cnt = UTOOL_ARRAY_SIZE(utool_cmd_ubommu_table);
	uint32_t i = 0;

	if ((dev == NULL) || (param == NULL)) {
		utool_err_msg("Failed to dispatch ubommu, dev == NULL(%d), param == NULL(%d).\n",
			      (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < cmd_ubommu_cnt; i++) {
		if (param->flags == utool_cmd_ubommu_table[i].flags) {
			if (utool_cmd_ubommu_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch ubommu, execute is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

			return utool_cmd_ubommu_table[i].execute(dev, param,
								 utool_cmd_ubommu_table[i].func_table,
								 utool_cmd_ubommu_table[i].func_cnt);
		}
	}
	utool_err_msg("The ubctl ubommu command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m ubommu\n");

	return UTOOL_ERR_CMD_NOT_FOUND;
}
