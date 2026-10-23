// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <stdio.h>
#include <string.h>

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_cmdq.h"

static struct utool_field_info g_utool_cmdq_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "storm_status(ue0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue0)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "storm_status(ue1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue1)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "storm_status(ue2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue2)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "storm_status(ue3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue3)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "storm_status(ue4)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue4)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "storm_status(ue5)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue5)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "storm_status(ue6)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue6)" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "storm_status(ue7)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue7)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "storm_status(ue8)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue8)" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "storm_status(ue9)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue9)" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "storm_status(ue10)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue10)" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "storm_status(ue11)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue11)" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "storm_status(ue12)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue12)" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "storm_status(ue13)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue13)" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "storm_status(ue14)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue14)" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "storm_status(ue15)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue15)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "storm_status(ue16)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue16)" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "storm_status(ue17)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue17)" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "storm_status(ue18)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue18)" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "storm_status(ue19)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue19)" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "storm_status(ue20)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue20)" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "storm_status(ue21)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue21)" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "storm_status(ue22)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue22)" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "storm_status(ue23)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue23)" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "storm_status(ue24)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue24)" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "storm_status(ue25)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue25)" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_ALL, "storm_status(ue26)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue26)" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "storm_status(ue27)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue27)" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_ALL, "storm_status(ue28)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue28)" },
	{ false, false, UTOOL_LOC29, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "storm_status(ue29)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue29)" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "storm_status(ue30)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue30)" },
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "storm_status(ue31)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue31)" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "storm_status(ue32)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue32)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "storm_status(ue33)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue33)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "storm_status(ue34)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue34)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "storm_status(ue35)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue35)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "storm_status(ue36)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue36)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "storm_status(ue37)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue37)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "storm_status(ue38)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue38)" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "storm_status(ue39)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue39)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "storm_status(ue40)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue40)" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "storm_status(ue41)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue41)" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "storm_status(ue42)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue42)" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "storm_status(ue43)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue43)" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "storm_status(ue44)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue44)" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "storm_status(ue45)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue45)" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "storm_status(ue46)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue46)" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "storm_status(ue47)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue47)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "storm_status(ue48)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue48)" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "storm_status(ue49)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue49)" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "storm_status(ue50)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue50)" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "storm_status(ue51)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue51)" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "storm_status(ue52)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue52)" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "storm_status(ue53)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue53)" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "storm_status(ue54)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue54)" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "storm_status(ue55)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue55)" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "storm_status(ue56)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue56)" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "storm_status(ue57)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue57)" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_ALL, "storm_status(ue58)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue58)" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "storm_status(ue59)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue59)" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_ALL, "storm_status(ue60)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue60)" },
	{ false, false, UTOOL_LOC29, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "storm_status(ue61)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue61)" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "storm_status(ue62)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue62)" },
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "storm_status(ue63)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "history_storm_time(ue63)" },

	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

int utool_cmdq_cal_data_len(uint32_t *cmdq_data_len)
{
	uint32_t cmdq_reg_cnt = 0;
	int ret = UTOOL_OK;

	if (cmdq_data_len == NULL) {
		utool_err_msg("Param is invalid, cmdq data len is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_cal_reg_cnt(g_utool_cmdq_field_info, UTOOL_ARRAY_SIZE(g_utool_cmdq_field_info), &cmdq_reg_cnt);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate cmdq reg cnt.\n");
		return ret;
	}

	*cmdq_data_len = cmdq_reg_cnt * sizeof(uint32_t);

	return UTOOL_OK;
}

int utool_cmdq_parse_rpc_pkt(struct fwctl_rpc_ub_out *cmdq_out)
{
#define UTOOL_HISTORY_STORM_TIME_OFFSET 2
#define UTOOL_UE_FILED_NUM 2U
#define UTOOL_MAX_UE_NUM 64U

	uint32_t field_cnt = UTOOL_ARRAY_SIZE(g_utool_cmdq_field_info);
	uint32_t table_cnt = 0;
	uint32_t *cmdq_data;
	int ret = UTOOL_OK;
	uint32_t i;

	if (cmdq_out == NULL) {
		utool_err_msg("Failed to parse cmdq rpc pkt, cmdq out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}
	if (field_cnt < UTOOL_MAX_UE_NUM * UTOOL_UE_FILED_NUM) {
		utool_err_msg("Field cnt = %u is too small, it must be bigger than %u.\n",
			      field_cnt, UTOOL_MAX_UE_NUM * UTOOL_UE_FILED_NUM);
		return UTOOL_ERR_INVALID_PARAM;
	}
	if (cmdq_out->data_size < UTOOL_MAX_UE_NUM + UTOOL_HISTORY_STORM_TIME_OFFSET) {
		utool_err_msg("Data size = %u is too small, it must be bigger than %u.\n",
			      cmdq_out->data_size, UTOOL_MAX_UE_NUM + UTOOL_HISTORY_STORM_TIME_OFFSET);
		return UTOOL_ERR_INVALID_PARAM;
	}

	cmdq_data = (uint32_t *)UTOOL_MALLOC(field_cnt * sizeof(uint32_t));
	if (cmdq_data == NULL) {
		utool_err_msg("Failed to malloc space for cmdq data.\n");
		return UTOOL_ERR_MALLOC;
	}
	memset(cmdq_data, 0x0, field_cnt * sizeof(uint32_t));
	for (i = 0; i < UTOOL_MAX_UE_NUM; i++) {
		cmdq_data[table_cnt++] = UTOOL_EXTRACT_ONE_BIT_32(cmdq_out->data[i / UTOOL_REG_MAX_LEN],
								  i % UTOOL_REG_MAX_LEN);
		cmdq_data[table_cnt++] = cmdq_out->data[i + UTOOL_HISTORY_STORM_TIME_OFFSET];
	}

	utool_reg_msg("-------------------------- cmdq --------------------------\n");
	for (i = 0; i < field_cnt; i++) {
		if (!g_utool_cmdq_field_info[i].is_reserved) {
			utool_reg_msg("%s: 0x%x\n", g_utool_cmdq_field_info[i].reg_name, cmdq_data[i]);
		}
	}

	UTOOL_FREE(cmdq_data);

	return ret;
}

static int utool_cmdq_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
			  struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec cmdq_pkt_exec = { UTOOL_CMD_QUERY_CMDQ_STATS, 0, utool_cmdq_parse_rpc_pkt };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	ret = utool_cmdq_cal_data_len(&cmdq_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to cal cmdq reg cnt.\n");
		return ret;
	}

	pkt_in = utool_null_create_pkt_in(&pkt_in_len, param);
	if (pkt_in == NULL) {
		utool_err_msg("Failed to create pkt in.\n");
		return UTOOL_ERR_MALLOC;
	}

	ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &cmdq_pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}
	utool_destroy_pkt_in(&pkt_in);

	return ret;
}

int utool_cmdq_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_cmd_cmdq_table[] = {
		{ UTOOL_FLAG_M, utool_cmdq_cmd, NULL, 0 },
	};
	uint32_t cmd_cmdq_cnt = UTOOL_ARRAY_SIZE(utool_cmd_cmdq_table);
	uint32_t i;

	if ((dev == NULL) || (param == NULL)) {
		utool_err_msg("Failed to dispatch cmdq, dev==NULL(%d), param==NULL(%d).\n",
			      (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < cmd_cmdq_cnt; i++) {
		if (param->flags == utool_cmd_cmdq_table[i].flags) {
			if (utool_cmd_cmdq_table[i].execute == NULL) {
				return UTOOL_ERR_INVALID_PARAM;
			}

			return utool_cmd_cmdq_table[i].execute(dev, param,
							       utool_cmd_cmdq_table[i].func_table,
							       utool_cmd_cmdq_table[i].func_cnt);
		}
	}
	utool_err_msg("The ubctl cmdq command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${udie_id} -m cmdq\n");

	return UTOOL_ERR_CMD_NOT_FOUND;
}
