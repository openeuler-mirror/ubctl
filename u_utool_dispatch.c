// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <getopt.h>
#include <limits.h>
#include <errno.h>

#include "u_utool_dl.h"
#include "u_utool_nl.h"
#include "u_utool_ta.h"
#include "u_utool_tp.h"
#include "u_utool_ba.h"
#include "u_utool_qos.h"
#include "u_utool_port_info.h"
#include "u_utool_ubommu.h"
#include "u_utool_ecc_2b.h"
#include "u_utool_uboe.h"
#include "u_utool_ummu.h"
#include "u_utool_msg.h"
#include "u_utool_queue.h"
#include "u_utool_error.h"
#include "u_utool_common.h"
#include "u_utool_dispatch.h"

static struct utool_cmd_param g_utool_cmd_param = {};
static bool g_utool_cmd_chip_id_init = false;
static bool g_utool_cmd_die_id_init = false;

static struct utool_module_dispatch g_utool_cmd_table[] = {
	{ UTOOL_MODULE_DL, UTOOL_MODULE_NAME_DL, utool_dl_cmd_dispatch },
	{ UTOOL_MODULE_NL, UTOOL_MODULE_NAME_NL, utool_nl_cmd_dispatch },
	{ UTOOL_MODULE_TA, UTOOL_MODULE_NAME_TA, utool_ta_cmd_dispatch },
	{ UTOOL_MODULE_TP, UTOOL_MODULE_NAME_TP, utool_tp_cmd_dispatch },
	{ UTOOL_MODULE_BA, UTOOL_MODULE_NAME_BA, utool_ba_cmd_dispatch },
	{ UTOOL_MODULE_QOS, UTOOL_MODULE_NAME_QOS, utool_qos_cmd_dispatch },
	{ UTOOL_MODULE_PORT_INFO, UTOOL_MODULE_NAME_PORT_INFO, utool_port_info_cmd_dispatch },
	{ UTOOL_MODULE_UBOMMU, UTOOL_MODULE_NAME_UBOMMU, utool_ubommu_cmd_dispatch },
	{ UTOOL_MODULE_ECC_2B, UTOOL_MODULE_NAME_ECC_2B, utool_ecc_2b_cmd_dispatch },
	{ UTOOL_MODULE_UBOE, UTOOL_MODULE_NAME_UBOE, utool_uboe_cmd_dispatch },
	{ UTOOL_MODULE_UMMU, UTOOL_MODULE_NAME_UMMU, utool_ummu_cmd_dispatch },
	{ UTOOL_MODULE_MSGQ, UTOOL_MODULE_NAME_MSGQ, utool_msgq_cmd_dispatch },
	{ UTOOL_MODULE_QUEUE, UTOOL_MODULE_NAME_QUEUE, utool_queue_cmd_dispatch },
};

const struct utool_cmd_param *utool_get_cmd_param(void)
{
	return &g_utool_cmd_param;
}

static int utool_cmd_select_module(char *param)
{
	uint32_t table_cnt = UTOOL_ARRAY_SIZE(g_utool_cmd_table);
	uint32_t i = 0;

	g_utool_cmd_param.flags |= UTOOL_FLAG_M;

	for (; i < table_cnt; i++) {
		if (strcmp(param, g_utool_cmd_table[i].module_name) == 0) {
			g_utool_cmd_param.module_id = g_utool_cmd_table[i].module_flags;
			return UTOOL_OK;
		}
	}

	utool_err_msg("Unknown module name %s.\n", param);
	g_utool_cmd_param.module_id = UTOOL_MODULE_NAME_BUTT;

	return UTOOL_ERR_INVALID_CMD;
}

int utool_transform_str(char *param, uint32_t *value)
{
	unsigned long conv_value = 0;
	char *end = NULL;

	if (param == NULL || value == NULL) {
		utool_err_msg("Param is invalid, param==null(%d), value==null(%d).\n",
			      (param == NULL), (value == NULL));

		return UTOOL_ERR_INVALID_PARAM;
	}

	errno = 0;
	conv_value = strtoul(param, &end, 0);
	if (errno == ERANGE && conv_value == ULONG_MAX) {
		return UTOOL_ERR_INVALID_CMD;
	}
	if (end == NULL || *end != '\0' || end == param) {
		return UTOOL_ERR_INVALID_CMD;
	}
	if (conv_value > UINT32_MAX) {
		return UTOOL_ERR_INVALID_CMD;
	}
	*value = (uint32_t)conv_value;

	return UTOOL_OK;
}

static int utool_cmd_select_port(char *param)
{
	int ret = UTOOL_OK;

	g_utool_cmd_param.flags |= UTOOL_FLAG_P;
	ret = utool_transform_str(param, &g_utool_cmd_param.port);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to convert the type of port to int.\n");
	}

	return ret;
}

static int utool_cmd_select_func(char *param)
{
	int ret = UTOOL_OK;

	g_utool_cmd_param.flags |= UTOOL_FLAG_F;

	if (strlen(param) >= sizeof(g_utool_cmd_param.func)) {
		utool_err_msg("Func name %s too long.\n", param);
		return UTOOL_ERR_INVALID_CMD;
	}

	strncpy(g_utool_cmd_param.func, param, sizeof(g_utool_cmd_param.func) - 1);
	g_utool_cmd_param.func[sizeof(g_utool_cmd_param.func) - 1] = '\0';

	return ret;
}

static int utool_cmd_select_die_id(char *param)
{
	int ret = UTOOL_OK;

	ret = utool_transform_str(param, &g_utool_cmd_param.die_id);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to convert the type of die id to uint32.\n");
		return ret;
	}
	g_utool_cmd_die_id_init = true;

	return ret;
}

static int utool_cmd_select_chip_id(char *param)
{
	int ret = UTOOL_OK;

	ret = utool_transform_str(param, &g_utool_cmd_param.chip_id);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to convert type of chip id to uint32.\n");
		return ret;
	}
	g_utool_cmd_chip_id_init = true;

	return ret;
}

static int utool_cmd_select_value(char *param)
{
	int ret = UTOOL_OK;

	g_utool_cmd_param.flags |= UTOOL_FLAG_E;
	ret = utool_transform_str(param, &g_utool_cmd_param.value);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to convert the type of value to uint32.\n");
	}

	return ret;
}

static int utool_cmd_select_index(char *param)
{
	int ret = UTOOL_OK;

	g_utool_cmd_param.flags |= UTOOL_FLAG_I;
	ret = utool_transform_str(param, &g_utool_cmd_param.index);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to convert the type of index to int.\n");
	}

	return ret;
}

static int utool_cmd_select_time(char *param)
{
	int ret = UTOOL_OK;

	g_utool_cmd_param.flags |= UTOOL_FLAG_T;
	ret = utool_transform_str(param, &g_utool_cmd_param.time);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to convert the type of time to int.\n");
	}

	return ret;
}

static int utool_cmd_select_ummu_id(char *param)
{
	int ret = UTOOL_OK;

	g_utool_cmd_param.flags |= UTOOL_FLAG_U;
	ret = utool_transform_str(param, &g_utool_cmd_param.ummu_id);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to convert the type of ummu id to uint32.\n");
	}

	return ret;
}

static struct utool_cmd_option_parse g_utool_option_func[] = {
	{ 'd', utool_cmd_select_die_id },
	{ 'c', utool_cmd_select_chip_id },
	{ 'm', utool_cmd_select_module },
	{ 'p', utool_cmd_select_port },
	{ 'f', utool_cmd_select_func },
	{ 'e', utool_cmd_select_value },
	{ 'i', utool_cmd_select_index },
	{ 't', utool_cmd_select_time },
	{ 'u', utool_cmd_select_ummu_id },
};

static int utool_check_param(void)
{
	if (g_utool_cmd_param.module_id == (uint32_t)UTOOL_MODULE_NAME_BUTT) {
		utool_err_msg("Parameter of '-m' is not found.\n");
		return UTOOL_ERR_CMD_NOT_FOUND;
	}

	if (g_utool_cmd_param.module_id == (uint32_t)UTOOL_MODULE_NAME_UMMU) {
		return UTOOL_OK;
	}

	if (g_utool_cmd_chip_id_init && g_utool_cmd_die_id_init) {
		return UTOOL_OK;
	}

	utool_err_msg("All modules except 'ummu' must contain the '-c' and '-d' parameters.\n");

	return UTOOL_ERR_CMD_NOT_FOUND;
}

static void utool_param_init(void)
{
	memset(&g_utool_cmd_param, 0x0, sizeof(struct utool_cmd_param));
	g_utool_cmd_param.module_id = (uint32_t)UTOOL_MODULE_NAME_BUTT;
	g_utool_cmd_chip_id_init = false;
	g_utool_cmd_die_id_init = false;
}

int utool_parse_command(int argc, char **argv)
{
	uint32_t table_cnt = 0;
	int ret = UTOOL_ERR;
	uint32_t i = 0;
	int c = 0;

	if (argv == NULL) {
		utool_err_msg("Param is invalid, argv==null(%d).\n", (argv == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	utool_param_init();

	static const struct option long_options[] = {
		{ "die_id", required_argument, NULL, 'd' },
		{ "chip_id", required_argument, NULL, 'c' },
		{ "module", required_argument, NULL, 'm' },
		{ "port", required_argument, NULL, 'p' },
		{ "func", required_argument, NULL, 'f' },
		{ "value", required_argument, NULL, 'e' },
		{ "index", required_argument, NULL, 'i' },
		{ "time", required_argument, NULL, 't' },
		{ "ummu_id", required_argument, NULL, 'u' },
		{ 0, 0, 0, 0 }
	};

	while (1) {
		c = getopt_long(argc, argv, "d:c:m:p:f:e:i:t:u:", long_options, NULL);
		if (c == -1) {
			break;
		}

		table_cnt = UTOOL_ARRAY_SIZE(g_utool_option_func);
		for (i = 0; i < table_cnt; i++) {
			if ((c == g_utool_option_func[i].option) && (g_utool_option_func[i].cmd_select_func != NULL)) {
				ret = g_utool_option_func[i].cmd_select_func(optarg);
				break;
			}
		}

		if (i == table_cnt) {
			utool_err_msg("Option '%c' is not found.\n", (char)c);
			return UTOOL_ERR_CMD_NOT_FOUND;
		}

		if (ret != UTOOL_OK) {
			return ret;
		}
	}

	return utool_check_param();
}

int utool_cmd_select(struct utool_dev *dev)
{
	struct utool_module_dispatch *dispatch = NULL;
	uint32_t table_cnt = 0;
	uint32_t i = 0;

	if (dev == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d).\n", (dev == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	table_cnt = UTOOL_ARRAY_SIZE(g_utool_cmd_table);

	for (i = 0; i < table_cnt; i++) {
		dispatch = &g_utool_cmd_table[i];
		if ((g_utool_cmd_param.module_id == dispatch->module_flags) && (dispatch->execute != NULL)) {
			return dispatch->execute(dev, &g_utool_cmd_param);
		}
	}

	utool_err_msg("Parameter of '-m' is not found.\n");

	return UTOOL_ERR_CMD_NOT_FOUND;
}
