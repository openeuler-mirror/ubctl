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
#define TP_ABN_STATS "abn_stats"
#define TP_ROUTE_RESULT "route_result"

#define UTOOL_TX_PKT_STATS_CNT 226U
#define UTOOL_RX_PKT_STATS_CNT 176U
#define UTOOL_TX_ABN_STATS_CNT 11U
#define UTOOL_RX_ABN_STATS_CNT 14U
#define UTOOL_BONDING_REG_CNT 6U

#define UTOOL_ABN_STATS_CNT (UTOOL_TX_PKT_STATS_CNT + UTOOL_RX_PKT_STATS_CNT + \
			     UTOOL_TX_ABN_STATS_CNT + UTOOL_RX_ABN_STATS_CNT + UTOOL_BONDING_REG_CNT)
#define UTOOL_ABN_STATS_LEN ((UTOOL_ABN_STATS_CNT) * (sizeof(uint32_t)))
#define UTOOL_PORT_CNT 1

struct utool_cal_reg_table_dp {
	uint32_t func_cnt;
	struct utool_cal_reg_cnt_dp *reg_table;
};

static struct utool_cal_reg_table_dp *utool_tp_get_cal_reg_table(void)
{
#define INDEX0 0
#define INDEX1 1
#define INDEX2 2
#define INDEX3 3

	static struct utool_cal_reg_cnt_dp utool_tp_cal_reg_table[] = {
		{ true, true, TP_PKT_STATS, 0, NULL },
		{ false, false, TP_ABN_STATS, 0, NULL },
		{ true, true, TP_ROUTE_RESULT, 0, NULL },
		{ true, true, TP_RX_BANK, 0, NULL },
	};
	static struct utool_cal_reg_table_dp cal_reg_table_dp = {};

	struct utool_field_info_dp *pkt_stats_field_info = NULL;
	struct utool_field_info_dp *abn_stats_field_info = NULL;
	struct utool_field_info_dp *route_result_field_info = NULL;
	struct utool_field_info_dp *rx_bank_field_info = NULL;

	pkt_stats_field_info = utool_tp_get_field_info_by_name(TP_PKT_STATS_FIELD_INFO);
	abn_stats_field_info = utool_tp_get_field_info_by_name(TP_ABN_STATS_FIELD_INFO);
	route_result_field_info = utool_tp_get_field_info_by_name(TP_TX_ROUTE_FIELD_INFO);
	rx_bank_field_info = utool_tp_get_field_info_by_name(TP_RX_BANK_FIELD_INFO);

	if ((pkt_stats_field_info == NULL) || abn_stats_field_info == NULL || (route_result_field_info == NULL) ||
	    (rx_bank_field_info == NULL)) {
		utool_err_msg("Failed to get field info.\n");
		return NULL;
	}

	utool_tp_cal_reg_table[INDEX0].field_cnt = pkt_stats_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX0].field_info = pkt_stats_field_info->field_info;
	utool_tp_cal_reg_table[INDEX1].field_cnt = abn_stats_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX1].field_info = abn_stats_field_info->field_info;
	utool_tp_cal_reg_table[INDEX2].field_cnt = route_result_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX2].field_info = route_result_field_info->field_info;
	utool_tp_cal_reg_table[INDEX3].field_cnt = rx_bank_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX3].field_info = rx_bank_field_info->field_info;

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

static int ubtool_tp_abn_copy_data(struct fwctl_rpc_ub_out *abn_stats_out, struct fwctl_rpc_ub_out *tp_abn_stats_out,
				   uint32_t abn_cnt)
{
#define UTOOL_BONDING_PORT (UTOOL_TX_PKT_STATS_CNT + UTOOL_RX_PKT_STATS_CNT + \
			    UTOOL_TX_ABN_STATS_CNT + UTOOL_RX_ABN_STATS_CNT)

	uint32_t data_cnt = tp_abn_stats_out->data_size / sizeof(uint32_t);
	uint32_t *abn_data = NULL, *data = NULL;
	uint32_t abn_data_len = 0;
	uint32_t data_size = 0;
	uint32_t offset = 0;

	data = tp_abn_stats_out->data;
	abn_data = abn_stats_out->data;

	if (data_cnt <= UTOOL_BONDING_PORT) {
		utool_err_msg("Invalid out data cnt: %u.\n", data_cnt);
		return UTOOL_ERR_INVALID_PARAM;
	}
	abn_data[0] = data[UTOOL_BONDING_PORT];

	offset += UTOOL_TX_PKT_STATS_CNT;
	abn_data_len = (abn_cnt - UTOOL_PORT_CNT) * sizeof(uint32_t);
	data_size = UTOOL_TX_ABN_STATS_CNT * sizeof(uint32_t);
	memcpy(abn_data + UTOOL_PORT_CNT, data + offset, data_size);
	offset += UTOOL_TX_ABN_STATS_CNT + UTOOL_RX_PKT_STATS_CNT;
	data_size = abn_data_len - data_size;
	memcpy(abn_data + UTOOL_TX_ABN_STATS_CNT + UTOOL_PORT_CNT, data + offset, data_size);
	abn_stats_out->data_size = data_size + UTOOL_TX_ABN_STATS_CNT * sizeof(uint32_t);
	abn_stats_out->retval = 0;

	return UTOOL_OK;
}

static int utool_tp_parse_abn_stats(struct fwctl_rpc_ub_out *tp_abn_stats_out)
{
	uint32_t abn_cnt = UTOOL_TX_ABN_STATS_CNT + UTOOL_RX_ABN_STATS_CNT + UTOOL_BONDING_REG_CNT + UTOOL_PORT_CNT;
	uint32_t data_size = sizeof(struct fwctl_rpc_ub_out) + abn_cnt * sizeof(uint32_t);
	struct utool_field_info_dp *abn_stats_field_info = NULL;
	struct fwctl_rpc_ub_out *abn_stats_out = NULL;
	int ret = UTOOL_OK;

	abn_stats_field_info = utool_tp_get_field_info_by_name(TP_ABN_STATS_FIELD_INFO);
	if (abn_stats_field_info == NULL) {
		utool_err_msg("Failed to get abn stats field info.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	abn_stats_out = (struct fwctl_rpc_ub_out *)UTOOL_MALLOC(data_size);
	if (abn_stats_out == NULL) {
		utool_err_msg("Failed to malloc abn stats out, size = %u.\n", data_size);
		return UTOOL_ERR_MALLOC;
	}

	ret = ubtool_tp_abn_copy_data(abn_stats_out, tp_abn_stats_out, abn_cnt);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to copy abn data.\n");
		UTOOL_FREE(abn_stats_out);
		return ret;
	}

	ret = utool_pkt_parse(abn_stats_out, abn_stats_field_info->field_cnt, abn_stats_field_info->field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_TP, TP_ABN_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse tp abn stats data.\n");
	}

	UTOOL_FREE(abn_stats_out);
	return ret;
}

static int utool_tp_parse_route_result(struct fwctl_rpc_ub_out *tp_route_result_out)
{
	struct utool_field_info_dp *route_result_field_info = NULL;
	int ret = UTOOL_OK;

	route_result_field_info = utool_tp_get_field_info_by_name(TP_TX_ROUTE_FIELD_INFO);
	if (route_result_field_info == NULL) {
		utool_err_msg("Failed to get route result field info.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_pkt_parse(tp_route_result_out, route_result_field_info->field_cnt, route_result_field_info->field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_TP, TP_ROUTE_RESULT));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse tp route result data.\n");
		return ret;
	}

	return UTOOL_OK;
}

static int utool_tp_parse_rx_bank(struct fwctl_rpc_ub_out *tp_pkt_out)
{
	struct utool_field_info_dp *rx_bank1_field_info = NULL;
	struct utool_field_info_dp *rx_bank2_field_info = NULL;
	struct utool_field_info_dp *rx_bank_field_info = NULL;
	struct fwctl_rpc_ub_out *out_temp = NULL;
	uint32_t data_size = 0;
	void *out_data = NULL;
	int ret = UTOOL_OK;
	int i;

	rx_bank_field_info = utool_tp_get_field_info_by_name(TP_RX_BANK_FIELD_INFO);
	rx_bank1_field_info = utool_tp_get_field_info_by_name(TP_RX_BANK_FIELD_INFO_BANK1);
	rx_bank2_field_info = utool_tp_get_field_info_by_name(TP_RX_BANK_FIELD_INFO_BANK2);
	if ((rx_bank_field_info == NULL) || (rx_bank1_field_info == NULL) || (rx_bank2_field_info == NULL)) {
		utool_err_msg("Failed to get rx bank field info.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	struct utool_field_info *field_info[] = { rx_bank_field_info->field_info,
						  rx_bank1_field_info->field_info,
						  rx_bank2_field_info->field_info };
	uint32_t field_cnts[] = { rx_bank_field_info->field_cnt,
				  rx_bank1_field_info->field_cnt,
				  rx_bank2_field_info->field_cnt };

	data_size = tp_pkt_out->data_size / UBCTL_TP_RX_BANK_NUM;
	out_temp = (struct fwctl_rpc_ub_out *)UTOOL_MALLOC(sizeof(struct fwctl_rpc_ub_out) + data_size);
	if (out_temp == NULL) {
		utool_err_msg("Failed to malloc rpc out mem.\n");
		return UTOOL_ERR_MALLOC;
	}

	out_data = (void *)(tp_pkt_out->data);
	out_temp->retval = tp_pkt_out->retval;
	out_temp->data_size = data_size;
	for (i = 0; i < UBCTL_TP_RX_BANK_NUM; i++) {
		memcpy(out_temp->data, out_data, data_size);
		ret = utool_pkt_parse(out_temp, field_cnts[i], field_info[i], UTOOL_CONCAT_STR(UTOOL_MODULE_TP, TP_RX_BANK));
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to parse tp rx bank data.\n");
			break;
		}
		out_data += data_size;
	}
	UTOOL_FREE(out_temp);

	return ret;
}

static struct utool_func_dispatch g_utool_tp_mf_table[] = {
	{ true, TP_PKT_STATS, UTOOL_CMD_QUERY_TP_PKT_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_pkt_stats, utool_null_create_pkt_in },
	{ true, TP_ROUTE_RESULT, UTOOL_CMD_QUERY_TP_TX_ROUTE, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_route_result, utool_null_create_pkt_in },
	{ true, TP_RX_BANK, UTOOL_CMD_QUERY_TP_RX_BANK, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_rx_bank, utool_null_create_pkt_in },
};

static void utool_tp_print_help(void)
{
	utool_err_msg("The ubctl tp command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m tp -f pkt_stats/route_result/rx_bank\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m tp -f abn_stats -p ${port}\n");
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
	static struct utool_func_dispatch utool_tp_flag_mfp_table[] = {
		{ false, TP_ABN_STATS, UTOOL_CMD_QUERY_TP_ABN_STATS, UTOOL_ABN_STATS_LEN,
		  utool_tp_parse_abn_stats, utool_port_create_pkt_in },
	};
	struct utool_cmd_dispatch utool_tp_cmd_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_F, utool_tp_cmd_func,
		  g_utool_tp_mf_table, UTOOL_ARRAY_SIZE(g_utool_tp_mf_table) },
		{ UTOOL_FLAG_M | UTOOL_FLAG_F | UTOOL_FLAG_P, utool_tp_cmd_func,
		  utool_tp_flag_mfp_table, UTOOL_ARRAY_SIZE(utool_tp_flag_mfp_table) },
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
