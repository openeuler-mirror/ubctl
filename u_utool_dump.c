// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_ba.h"
#include "u_utool_dl.h"
#include "u_utool_nl.h"
#include "u_utool_tp.h"
#include "u_utool_ta.h"
#include "u_utool_qos.h"
#include "u_utool_ubommu.h"
#include "u_utool_ecc_2b.h"
#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_dump.h"

static struct utool_dump_dp g_utool_dump_table[] = {
	{
		utool_nl_cal_data_len,
		utool_nl_parse_rpc_pkt,
	}, {
		utool_tp_cal_data_len,
		utool_tp_parse_rpc_pkt,
	}, {
		utool_ta_cal_data_len,
		utool_ta_parse_rpc_pkt,
	}, {
		utool_dl_cal_data_len,
		utool_dl_parse_rpc_pkt,
	}, {
		utool_ba_cal_data_len,
		utool_ba_parse_rpc_pkt,
	}, {
		utool_qos_cal_data_len,
		utool_qos_parse_rpc_pkt,
	}, {
		utool_ubommu_cal_data_len,
		utool_ubommu_parse_rpc_pkt,
	}, {
		utool_ecc_2b_cal_data_len,
		utool_ecc_2b_parse_rpc_pkt,
	},
};

static void utool_dump_lydata_format(struct fwctl_rpc_ub_out *out, uint32_t offset,
				     struct fwctl_rpc_ub_out *layer_out, uint32_t layer_data_len)
{
	uint32_t *pos_index = out->data[offset / sizeof(uint32_t)];

	layer_out->data_size = layer_data_len;
	memcpy(layer_out->data, pos_index, layer_data_len);
}

static int utool_check_dump_table(struct utool_dump_dp *dump_dp)
{
	if (dump_dp == NULL) {
		utool_err_msg("Failed to check function param, dump dp is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (dump_dp->utool_ly_cal_data_len == NULL) {
			utool_err_msg("Failed to check function param, cal data len function is NULL.\n");
			return UTOOL_ERR_INVALID_PARAM;
	}

	if (dump_dp->utool_ly_parse_rpc_pkt == NULL) {
			utool_err_msg("Failed to check function param, parse rpc pkt function is NULL.\n");
			return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

static int utool_dump_data_proc(struct fwctl_rpc_ub_out *out)
{
	struct fwctl_rpc_ub_out *layer_out = NULL;
	uint32_t layer_data_len = 0;
	uint32_t layer_out_len = 0;
	uint32_t dump_cnt = 0;
	uint32_t offset = 0;
	int ret = UTOOL_OK;
	uint32_t i;

	dump_cnt = UTOOL_ARRAY_SIZE(g_utool_dump_table);
	for (i = 0; i < dump_cnt; i++) {
		ret = utool_check_dump_table(&g_utool_dump_table[i]);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to check dump table, ret = %d.\n", ret);
			return ret;
		}

		ret = g_utool_dump_table[i].utool_ly_cal_data_len(&layer_data_len);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to cal data len, ret = %d.\n", ret);
			return UTOOL_ERR_CAL_REG_CNT;
		}

		layer_out_len = sizeof(struct fwctl_rpc_ub_out) + layer_data_len;
		layer_out = (struct fwctl_rpc_ub_out *)UTOOL_MALLOC(layer_out_len);
		if (layer_out == NULL) {
			utool_err_msg("Failed to malloc space.\n");
			ret = UTOOL_ERR_MALLOC;
			break;
		}

		utool_dump_lydata_format(out, offset, layer_out, layer_data_len);

		ret = g_utool_dump_table[i].utool_ly_parse_rpc_pkt(layer_out);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to parse data, ret = %d\n", ret);
			ret = UTOOL_ERR_PARSE;
			UTOOL_FREE(layer_out);
			break;
		}

		offset += layer_data_len;
		UTOOL_FREE(layer_out);
	}

	return ret;
}

static int utool_cmd_dump(struct utool_dev *dev, struct utool_cmd_param *param,
			  struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec pkt_exec = { UTOOL_CMD_QUERY_DUMP, 0, NULL };
	uint32_t layer_data_len = 0;
	uint32_t all_data_len = 0;
	uint32_t dump_cnt = 0;
	int ret = UTOOL_OK;
	uint32_t i = 0;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	dump_cnt = UTOOL_ARRAY_SIZE(g_utool_dump_table);
	for (i = 0; i < dump_cnt; i++) {
		ret = g_utool_dump_table[i].utool_ly_cal_data_len(&layer_data_len);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to calculate layer reg len.\n");
			return ret;
		}

		all_data_len += layer_data_len;
	}
	pkt_exec.data_len = all_data_len;
	pkt_exec.execute = utool_dump_data_proc;

	ret = utool_pkt_operation_have_port(dev, param, &pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	return ret;
}

static int utool_param_check(struct utool_dev *dev, struct utool_cmd_param *param)
{
	if (dev == NULL || param == NULL) {
		utool_err_msg("Failed to check param, dev==null(%d), param==null(%d).\n",
			      (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

int utool_dump_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_dump_cmd_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_P, utool_cmd_dump, NULL, 0 }
	};
	uint32_t table_cnt = UTOOL_ARRAY_SIZE(utool_dump_cmd_table);
	uint32_t i = 0;

	if (utool_param_check(dev, param) != UTOOL_OK) {
		utool_err_msg("Failed to check param.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < table_cnt; i++) {
		if (param->flags == utool_dump_cmd_table[i].flags) {
			if (utool_dump_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch. Callback is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

			return utool_dump_cmd_table[i].execute(dev, param,
							       utool_dump_cmd_table[i].func_table,
							       utool_dump_cmd_table[i].func_cnt);
		}
	}

	utool_err_msg("The ubctl dump command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m dump -p ${port}\n");

	return UTOOL_ERR_CMD_NOT_FOUND;
}
