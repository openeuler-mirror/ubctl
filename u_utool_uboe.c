// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_uboe.h"

#define UBOE_DEFAULT_CNT 24U

static int utool_uboe_parse_loopback(struct fwctl_rpc_ub_out *out)
{
	struct fwctl_pkt_in_loopback *loopback_out = (struct fwctl_pkt_in_loopback *)(out->data);

	utool_reg_msg("port_id: 0x%x\n", loopback_out->port_id);
	utool_reg_msg("loopback_en: 0x%x\n", loopback_out->enable);

	return UTOOL_OK;
}

static int utool_uboe_parse_prbs(struct fwctl_rpc_ub_out *out)
{
	uint32_t *prbs_out = out->data;

	utool_reg_msg("port_id: 0x%x\n", *prbs_out++);
	utool_reg_msg("prbs_en: 0x%x\n", *prbs_out);

	return UTOOL_OK;
}

static int utool_uboe_parse_prbs_result(struct fwctl_rpc_ub_out *out)
{
#define UBCTL_PRBS_PORT_EN_OFFSET 2U
	uint32_t *prbs_out = out->data;

	utool_reg_msg("port_id: 0x%x\n", *prbs_out);
	prbs_out += UBCTL_PRBS_PORT_EN_OFFSET;
	utool_reg_msg("prbs_err_count: %u\n", *prbs_out);

	return UTOOL_OK;
}

static struct utool_func_dispatch g_utool_uboe_mfpe_table[] = {
	{ false, UBOE_LOOPBACK_MAC_OUTER, UTOOL_CMD_CONF_LOOPBACK, UBOE_DEFAULT_CNT,
	  utool_uboe_parse_loopback, utool_loopback_create_pkt_in },
	{ false, UBOE_LOOPBACK_MAC_INNER, UTOOL_CMD_CONF_LOOPBACK, UBOE_DEFAULT_CNT,
	  utool_uboe_parse_loopback, utool_loopback_create_pkt_in },
	{ false, UBOE_LOOPBACK_PCS_INNER, UTOOL_CMD_CONF_LOOPBACK, UBOE_DEFAULT_CNT,
	  utool_uboe_parse_loopback, utool_loopback_create_pkt_in },
	{ false, UBOE_PRBS_EN, UTOOL_CMD_CONF_PRBS_EN, UBOE_DEFAULT_CNT,
	  utool_uboe_parse_prbs, utool_port_enable_create_pkt_in },
};

static struct utool_func_dispatch g_utool_uboe_mfp_table[] = {
	{ false, UBOE_LOOPBACK_MAC_OUTER, UTOOL_CMD_QUERY_LOOPBACK, UBOE_DEFAULT_CNT,
	  utool_uboe_parse_loopback, utool_loopback_create_pkt_in },
	{ false, UBOE_LOOPBACK_MAC_INNER, UTOOL_CMD_QUERY_LOOPBACK, UBOE_DEFAULT_CNT,
	  utool_uboe_parse_loopback, utool_loopback_create_pkt_in },
	{ false, UBOE_LOOPBACK_PCS_INNER, UTOOL_CMD_QUERY_LOOPBACK, UBOE_DEFAULT_CNT,
	  utool_uboe_parse_loopback, utool_loopback_create_pkt_in },
	{ false, UBOE_PRBS_EN, UTOOL_CMD_QUERY_PRBS_EN, UBOE_DEFAULT_CNT,
	  utool_uboe_parse_prbs, utool_loopback_create_pkt_in },
	{ false, UBOE_PRBS_RESULT, UTOOL_CMD_QUERY_PRBS_RESULT, UBOE_DEFAULT_CNT,
	  utool_uboe_parse_prbs_result, utool_prbs_create_pkt_in },
};

static void utool_uboe_print_help(void)
{
	utool_err_msg("The ubctl uboe command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m uboe -p ${port} -f rxmac2txmac/txmac2rxmac/"
		      "txpcs2rxpcs/prbs/prbs_err_cnt\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m uboe -p ${port} -f rxmac2txmac/txmac2rxmac/"
		      "txpcs2rxpcs/prbs/prbs_err_cnt -e ${value}\n");
}

static int utool_uboe_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			       struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
#define UBCTL_MAX_ENABLE_VAL 1U
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_BUTT, UBOE_DEFAULT_CNT, NULL };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;
	uint32_t i;

	if (param->value > UBCTL_MAX_ENABLE_VAL) {
		utool_err_msg("The param for '-e' exceeds the max value.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < func_cnt; i++) {
		if (strcmp(param->func, func_table[i].func) == 0) {
			func_pkt_exec.rpc_cmd = func_table[i].rpc_cmd;
			func_pkt_exec.execute = func_table[i].execute;

			if (func_table[i].create_pkt_in == NULL) {
				utool_err_msg("Failed to create uboe func pkt in, create pkt in is NULL.\n");
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
	utool_uboe_print_help();

	return UTOOL_ERR_FUNC_NOT_FOUND;
}

int utool_uboe_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_uboe_cmd_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_F | UTOOL_FLAG_E | UTOOL_FLAG_P, utool_uboe_cmd_func,
		  g_utool_uboe_mfpe_table, UTOOL_ARRAY_SIZE(g_utool_uboe_mfpe_table) },
		{ UTOOL_FLAG_M | UTOOL_FLAG_F | UTOOL_FLAG_P, utool_uboe_cmd_func,
		  g_utool_uboe_mfp_table, UTOOL_ARRAY_SIZE(g_utool_uboe_mfp_table) },
	};
	uint32_t i;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Failed to dispatch uboe, dev==NULL(%d), param==NULL(%d).\n",
			      (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < UTOOL_ARRAY_SIZE(utool_uboe_cmd_table); i++) {
		if (param->flags == utool_uboe_cmd_table[i].flags) {
			if (utool_uboe_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch, execute is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}
			return utool_uboe_cmd_table[i].execute(dev, param,
							       utool_uboe_cmd_table[i].func_table,
							       utool_uboe_cmd_table[i].func_cnt);
		}
	}
	utool_uboe_print_help();

	return UTOOL_ERR_CMD_NOT_FOUND;
}
