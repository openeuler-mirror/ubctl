// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_fwctl.h"
#include "u_utool_msg.h"

#define MSGQ_QUE_STATS "que_stats"
#define MSGQ_ENTRY "entry"

static struct utool_field_info g_utool_msgq_que_stats_field_info[] = {
	{ true, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "sq_pi" },

	{ true, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "sq_ci" },

	{ true, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "sq_depth" },

	{ true, true, UTOOL_REG_LOC2, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "sq_empty" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "sq_full" },

	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "sq_int_msk" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "sq_int_st" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "sq_int_ro" },

	{ true, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "rq_pi" },

	{ true, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "rq_ci" },

	{ true, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "rq_depth" },

	{ true, true, UTOOL_REG_LOC3, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "rq_entry_blk_size" },

	{ true, true, UTOOL_REG_LOC2, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "rq_empty" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "rq_full" },

	{ true, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "cq_pi" },

	{ true, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "cq_ci" },

	{ true, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "cq_depth" },

	{ true, true, UTOOL_REG_LOC2, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "cq_empty" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cq_full" },

	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cq_int_msk" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cq_int_st" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cq_int_ro" },

	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_field_info g_utool_msgq_entry_field_info[] = {
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "sq_task_type" },
	{ true, true, UTOOL_REG_LOC2, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "sq_local" },
	{ true, false, UTOOL_REG_LOC5, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "sq_dev_type" },
	{ true, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "sq_icrc" },
	{ true, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "sq_op_code" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "sq_msn" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "cq_task_type" },
	{ true, true, UTOOL_REG_LOC2, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cq_op_code" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cq_msn" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "rq_pi" },
	{ true, true, UTOOL_REG_LOC10, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "cq_status" },
	{ true, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_cal_reg_cnt_dp g_utool_msgq_cal_reg_table[] = {
	{ true, false, MSGQ_QUE_STATS, UTOOL_ARRAY_SIZE(g_utool_msgq_que_stats_field_info),
	  g_utool_msgq_que_stats_field_info },
	{ true, false, MSGQ_ENTRY, UTOOL_ARRAY_SIZE(g_utool_msgq_entry_field_info),
	  g_utool_msgq_entry_field_info },
};

static int utool_msgq_que_stats_parse_rpc_pkt(struct fwctl_rpc_ub_out *msgq_que_stats_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(msgq_que_stats_out, UTOOL_ARRAY_SIZE(g_utool_msgq_que_stats_field_info),
			      g_utool_msgq_que_stats_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_MSGQ, MSGQ_QUE_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse msgq que stats data.\n");
		return ret;
	}

	return UTOOL_OK;
}

static int utool_msgq_entry_parse_rpc_pkt(struct fwctl_rpc_ub_out *msgq_entry_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(msgq_entry_out, UTOOL_ARRAY_SIZE(g_utool_msgq_entry_field_info),
			      g_utool_msgq_entry_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_MSGQ, MSGQ_ENTRY));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse msgq cq and sq entry data.\n");
		return ret;
	}

	return UTOOL_OK;
}

static void utool_msg_print_help(void)
{
	utool_err_msg("The ubctl msgq command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m msgq -f que_stats\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m msgq -f entry -i ${index}\n");
}

static int utool_msgq_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			       struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_BUTT, 0, NULL };
	struct utool_cal_reg_func_param msgq_cal_reg_param = {
		NULL, 0, NULL, g_utool_msgq_cal_reg_table, UTOOL_ARRAY_SIZE(g_utool_msgq_cal_reg_table)
	};
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;
	uint32_t i;

	for (i = 0; i < func_cnt; i++) {
		if (strcmp(param->func, func_table[i].func) == 0) {
			func_pkt_exec.rpc_cmd = func_table[i].rpc_cmd;
			func_pkt_exec.execute = func_table[i].execute;

			msgq_cal_reg_param.data_len = &func_pkt_exec.data_len;
			msgq_cal_reg_param.user_def_data_len = func_table[i].data_len;

			ret = utool_cal_func_reg_len(param->func, &msgq_cal_reg_param);
			if (ret != UTOOL_OK) {
				utool_err_msg("Failed to cal msgq func %s data len.\n", param->func);
				return ret;
			}

			if (func_table[i].create_pkt_in == NULL) {
				utool_err_msg("Failed to create msgq func pkt in. Callback is NULL.\n");
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

	utool_msg_print_help();

	return UTOOL_ERR_FUNC_NOT_FOUND;
}

int utool_msgq_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_func_dispatch utool_msgq_flag_mf_table[] = {
		{ false, MSGQ_QUE_STATS, UTOOL_CMD_QUERY_MSGQ_QUE_STATS, UTOOL_REG_CNT_DEFAULT,
		  utool_msgq_que_stats_parse_rpc_pkt, utool_null_create_pkt_in },
	};
	struct utool_func_dispatch utool_msgq_flag_mfi_table[] = {
		{ false, MSGQ_ENTRY, UTOOL_CMD_QUERY_MSGQ_ENTRY, UTOOL_REG_CNT_DEFAULT,
		  utool_msgq_entry_parse_rpc_pkt, utool_index_create_pkt_in },
	};

	struct utool_cmd_dispatch utool_msgq_cmd_table[] = {
		{
			UTOOL_FLAG_M | UTOOL_FLAG_F,
			utool_msgq_cmd_func,
			utool_msgq_flag_mf_table, UTOOL_ARRAY_SIZE(utool_msgq_flag_mf_table)
		}, {
			UTOOL_FLAG_M | UTOOL_FLAG_F | UTOOL_FLAG_I,
			utool_msgq_cmd_func,
			utool_msgq_flag_mfi_table, UTOOL_ARRAY_SIZE(utool_msgq_flag_mfi_table)
		}
	};
	uint32_t msgq_cmd_cnt = UTOOL_ARRAY_SIZE(utool_msgq_cmd_table);
	uint32_t i = 0;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < msgq_cmd_cnt; i++) {
		if (param->flags == utool_msgq_cmd_table[i].flags) {
			if (utool_msgq_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch. Callback is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

			return utool_msgq_cmd_table[i].execute(dev, param,
							       utool_msgq_cmd_table[i].func_table,
							       utool_msgq_cmd_table[i].func_cnt);
		}
	}

	utool_msg_print_help();

	return UTOOL_ERR_CMD_NOT_FOUND;
}
