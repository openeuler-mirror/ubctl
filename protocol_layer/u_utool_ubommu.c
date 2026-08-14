// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_ubommu.h"

static struct utool_field_info g_utool_ubommu_field[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "axim_aw_request_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "axim_aw_bresp_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "axim_aw_data_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "axim_aw_outstanding_num" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "axim_ar_request_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "axim_ar_resp_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "axim_ar_data_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "axim_ar_outstanding_num" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ubommu_trans_request_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ubommu_trans_resp_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ubommu_trans_outstanding_num" },

	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "ubommu_int_src" },

	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	// opcode 0xA031
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ubommu_syn_req_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ubommu_syn_resp_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mmio_base_addr0" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "mmio_base_addr1" },

	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "mmio_size_cfg" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cmdq_size_cfg" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "eventq_size_cfg" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "eventq_size_use" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "eventq_en" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_idx" },

	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "ubommu_ram_ecc_1b_int" },

	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "ubommu_ram_ecc_2b_int" },

	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "ubommu_ecc_int_src_ce" },

	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "ubommu_ecc_int_src_nue" },

	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "ubommu_ecc_int_src_ue" },

	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "ubommu_ram_ecc_1b_int_mask" },

	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "ubommu_ram_ecc_2b_int_mask" },

	{ false, true, UTOOL_LOC5, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "ubommu_int_src_nue" },

	{ false, true, UTOOL_LOC5, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "ubommu_int_serverity_ue" },

	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ue0_trust_host_enable" },

	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "ue0_upi_supported" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ue0_upi" },
	// V160
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "ummu_stall_iopf_num" },
	// reserved 88~95
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
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
