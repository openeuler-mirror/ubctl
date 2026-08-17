// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <inttypes.h>

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_ue_info.h"

static struct utool_field_info g_utool_ue_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "ue_id" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "extq_pf_sta" },

	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V13, "tqs_extq_pf_tp_shift_cfg_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC4, 0, UTOOL_CAP_V13, "tqs_extq_pf_tp_shift_cfg" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "extq_pf_alm" },

	{ false, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V13, "hw_run" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "mb_status" },

	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
};

static int utool_ue_info_parse_modules(struct fwctl_rpc_ub_out *pkt_out)
{
	int ret;

	if (pkt_out == NULL) {
		utool_err_msg("Failed to parse ue info rpc pkt, ue info out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_pkt_parse(pkt_out, UTOOL_ARRAY_SIZE(g_utool_ue_info), g_utool_ue_info, UTOOL_MODULE_UE);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ue info data.\n");
	}

	return ret;
}

static int utool_ue_info_cmd(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_pkt_exec pkt_exec = { UTOOL_CMD_QUERY_UE_INFO, 0, NULL };
	struct fwctl_pkt_in_ue_info *pkt_in;
	uint32_t pkt_in_len = 0;
	uint32_t reg_cnt = 0;
	int ret;

	pkt_exec.execute = utool_ue_info_parse_modules;

	ret = utool_cal_reg_cnt(g_utool_ue_info, UTOOL_ARRAY_SIZE(g_utool_ue_info), &reg_cnt);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate ue reg cnt.\n");
		return ret;
	}

	pkt_exec.data_len = reg_cnt * sizeof(uint32_t);

	pkt_in = (struct fwctl_pkt_in_ue_info *)utool_create_pkt_in(&pkt_in_len, param,
								    sizeof(struct fwctl_pkt_in_ue_info));
	if (pkt_in == NULL) {
		utool_err_msg("Failed to create ue info pkt in.\n");
		return UTOOL_ERR_MALLOC;
	}

	pkt_in->ue_id = param->index;

	ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	utool_destroy_pkt_in((void **)&pkt_in);

	return ret;
}

int utool_ue_info_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (param->flags != (UTOOL_FLAG_M | UTOOL_FLAG_I)) {
		utool_err_msg("The ubctl port_info command must be in the following formats:\n"
			      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m %s -i ${ue_id}\n", UTOOL_MODULE_UE);
		return UTOOL_ERR_CMD_NOT_FOUND;
	}

	return utool_ue_info_cmd(dev, param);
}
