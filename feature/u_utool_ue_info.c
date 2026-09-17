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

struct utool_ue_info {
	uint32_t ue_id : 16,
		 is_mue : 1,
		 rsv0 : 15;
	uint32_t extq_mue_sta;
	uint32_t tqs_extq_mue_tp_shift_cfg : 5,
		 tqs_extq_mue_tp_shift_cfg_en : 1,
		 rsv1 : 26;
	uint32_t extq_mue_alm;
	uint32_t mb_status : 1,
		 hw_run : 1,
		 rsv2 : 30;
	uint32_t rsv3;
};

static int utool_ue_info_parse_modules(struct fwctl_rpc_ub_out *pkt_out)
{
	struct utool_ue_info *ue;

	if (pkt_out == NULL) {
		utool_err_msg("Failed to parse ue info rpc pkt, ue info out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ue = (struct utool_ue_info *)pkt_out->data;

	utool_reg_msg("-------------------------- ue --------------------------\n");
	utool_reg_msg("ue_id: %u\n", ue->ue_id);
	if (ue->is_mue) {
		utool_reg_msg("extq_mue_sta: 0x%x\n", ue->extq_mue_sta);
		utool_reg_msg("tqs_extq_mue_tp_shift_cfg_en: 0x%x\n", (unsigned int)ue->tqs_extq_mue_tp_shift_cfg_en);
		utool_reg_msg("tqs_extq_mue_tp_shift_cfg: 0x%x\n", (unsigned int)ue->tqs_extq_mue_tp_shift_cfg);
		utool_reg_msg("extq_mue_alm: 0x%x\n", ue->extq_mue_alm);
	}

	utool_reg_msg("hw_run: 0x%x\n", (unsigned int)ue->hw_run);
	utool_reg_msg("mb_status: 0x%x\n", (unsigned int)ue->mb_status);

	return 0;
}

static int utool_ue_info_cmd(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_pkt_exec pkt_exec = { UTOOL_CMD_QUERY_UE_INFO, 0, NULL };
	struct fwctl_pkt_in_ue_info *pkt_in;
	uint32_t pkt_in_len = 0;
	int ret;

	pkt_exec.execute = utool_ue_info_parse_modules;
	pkt_exec.data_len = sizeof(struct utool_ue_info);

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
