// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_tp_field_info.h"
#include "u_utool_tp.h"

#define TP_PKT_STATS "pkt_stats"

struct utool_cal_reg_table_dp {
	uint32_t func_cnt;
	struct utool_cal_reg_cnt_dp *reg_table;
};

static struct utool_cal_reg_table_dp *utool_tp_get_cal_reg_table(void)
{
#define INDEX0 0

	static struct utool_cal_reg_cnt_dp utool_tp_cal_reg_table[] = {
		{ true, true, TP_PKT_STATS, 0, NULL },
	};
	static struct utool_cal_reg_table_dp cal_reg_table_dp = {};

	struct utool_field_info_dp *pkt_stats_field_info = NULL;

	pkt_stats_field_info = utool_tp_get_field_info_by_name(TP_PKT_STATS_FIELD_INFO);

	if ((pkt_stats_field_info == NULL)) {
		utool_err_msg("Failed to get field info.\n");
		return NULL;
	}

	utool_tp_cal_reg_table[INDEX0].field_cnt = pkt_stats_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX0].field_info = pkt_stats_field_info->field_info;

	cal_reg_table_dp.func_cnt = UTOOL_ARRAY_SIZE(utool_tp_cal_reg_table);
	cal_reg_table_dp.reg_table = utool_tp_cal_reg_table;

	return &cal_reg_table_dp;
}

static int utool_tp_parse_pkt_stats(struct fwctl_rpc_ub_out *tp_pkt_stats_out)
{
	struct utool_field_info_dp *pkt_stats_field_info = NULL;
	int ret = UTOOL_OK;

	pkt_stats_field_info = utool_tp_get_field_info_by_name(TP_PKT_STATS_FIELD_INFO);
	if (pkt_stats_field_info == NULL) {
		utool_err_msg("Failed to get pkt stats field info.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_pkt_parse(tp_pkt_stats_out, pkt_stats_field_info->field_cnt, pkt_stats_field_info->field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_TP, TP_PKT_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse tp pkt stats data.\n");
		return ret;
	}

	return UTOOL_OK;
}

static struct utool_func_dispatch g_utool_tp_mf_table[] = {
	{ true, TP_PKT_STATS, UTOOL_CMD_QUERY_TP_PKT_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_pkt_stats, utool_null_create_pkt_in },
};

static void utool_tp_print_help(void)
{
	utool_err_msg("The ubctl tp command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m tp -f pkt_stats\n");
}

static int utool_tp_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			     struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_cal_reg_func_param tp_cal_reg_param = {NULL, 0, NULL, NULL, 0};
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_BUTT, 0, NULL };
	struct utool_cal_reg_table_dp *cal_reg_table_dp = NULL;
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;
	uint32_t i;

	cal_reg_table_dp = utool_tp_get_cal_reg_table();
	if (cal_reg_table_dp == NULL) {
		utool_err_msg("Failed to get cal reg table.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	tp_cal_reg_param.utool_cal_reg_table = cal_reg_table_dp->reg_table;
	tp_cal_reg_param.func_cnt = cal_reg_table_dp->func_cnt;

	for (i = 0; i < func_cnt; i++) {
		if (strcmp(param->func, func_table[i].func) == 0) {
			func_pkt_exec.rpc_cmd = func_table[i].rpc_cmd;
			func_pkt_exec.execute = func_table[i].execute;

			tp_cal_reg_param.data_len = &func_pkt_exec.data_len;
			tp_cal_reg_param.user_def_data_len = func_table[i].data_len;

			ret = utool_cal_func_reg_len(param->func, &tp_cal_reg_param);
			if (ret != UTOOL_OK) {
				utool_err_msg("Failed to cal tp func %s reg cnt.\n", param->func);
				return ret;
			}
			if (func_table[i].create_pkt_in == NULL) {
				utool_err_msg("Failed to create tp func pkt in. Callback is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}
			pkt_in = func_table[i].create_pkt_in(&pkt_in_len, param);
			if (pkt_in == NULL) {
				utool_err_msg("Failed to create pkt in.\n");
				return UTOOL_ERR_MALLOC;
			}

			ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &func_pkt_exec);
			if (ret != UTOOL_OK) {
				utool_err_msg("Failed to execute command, ret = %d.\n", ret);
			}

			utool_destroy_pkt_in(&pkt_in);
			return ret;
		}
	}
	utool_tp_print_help();

	return UTOOL_ERR_FUNC_NOT_FOUND;
}

int utool_tp_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_tp_cmd_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_F, utool_tp_cmd_func,
		  g_utool_tp_mf_table, UTOOL_ARRAY_SIZE(g_utool_tp_mf_table) },
	};
	uint32_t tp_cmd_cnt = UTOOL_ARRAY_SIZE(utool_tp_cmd_table);
	uint32_t i = 0;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < tp_cmd_cnt; i++) {
		if (param->flags == utool_tp_cmd_table[i].flags) {
			if (utool_tp_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch, execute is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}
			return utool_tp_cmd_table[i].execute(dev, param,
							     utool_tp_cmd_table[i].func_table,
							     utool_tp_cmd_table[i].func_cnt);
		}
	}

	utool_tp_print_help();

	return UTOOL_ERR_CMD_NOT_FOUND;
}
