// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_diff_version.h"
#include "u_utool_error.h"
#include "u_utool_ba_diff_version_field_info.h"
#include "u_utool_dl.h"
#include "u_utool_ecc_2b.h"
#include "u_utool_ta_diff_version_field_info.h"
#include "u_utool_tp.h"
#include "u_utool_nl_diff_version_field_info.h"

static struct utool_get_diff_version_field_info g_utool_diff_ver_reg_sum[] = {
	{ "ta-pkt_stats", utool_ta_cmd_diff_ver_dispatch },
	{ "ta-abn_stats", utool_ta_cmd_diff_ver_dispatch },
	{ "tp-pkt_stats", utool_tp_cmd_diff_ver_dispatch },
	{ "nl-pkt_stats", utool_nl_cmd_diff_ver_dispatch },
	{ "nl-ssu_stats", utool_nl_cmd_diff_ver_dispatch },
	{ "nl-ssu_sw", utool_nl_cmd_diff_ver_dispatch },
	{ "nl-ssu_oq", utool_nl_cmd_diff_ver_dispatch },
	{ "nl-p2p", utool_nl_cmd_diff_ver_dispatch },
	{ "dl-pkt_stats", utool_dl_cmd_diff_ver_dispatch },
	{ "dl-lane", utool_dl_cmd_diff_ver_dispatch },
	{ "ba-pkt_stats", utool_ba_cmd_diff_ver_dispatch },
	{ "ba-mar", utool_ba_cmd_diff_ver_dispatch },
	{ "ecc_2b", utool_ecc_2b_cmd_diff_ver_dispatch },
	{ "nl-ssu_p2p", utool_nl_cmd_diff_ver_dispatch },
	{ "nl-ssu_vl_pkt", utool_nl_cmd_diff_ver_dispatch },
};

int utool_diff_version_pkt_parse(struct fwctl_rpc_ub_out *out, const char *module_func_name, uint32_t reg_index)
{
	struct utool_field_info *replace_field_info = NULL;
	uint32_t replace_field_cnt = 0;
	uint32_t data = 0;
	uint32_t i, j;
	uint32_t len;

	if ((out == NULL) || (module_func_name == NULL) || (module_func_name[0] == '\0')) {
		utool_err_msg("Failed to parse pkt, data or module func name is invalid.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (out->data_size == 0) {
		utool_err_msg("Failed to parse pkt, out data size is 0.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < UTOOL_ARRAY_SIZE(g_utool_diff_ver_reg_sum); i++) {
		if (strcmp(module_func_name, g_utool_diff_ver_reg_sum[i].module_func_name) == 0) {
			if (g_utool_diff_ver_reg_sum[i].get_diff_ver_field_info == NULL) {
				utool_err_msg("Failed to dispatch. Callback is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

			replace_field_info = g_utool_diff_ver_reg_sum[i].get_diff_ver_field_info(module_func_name,
												 out->env_version,
												 reg_index,
												 &replace_field_cnt);
			break;
		}
	}
	if (replace_field_info == NULL || replace_field_cnt == 0) {
		return UTOOL_OK_CYCLE;
	}

	for (j = 0; j < replace_field_cnt; j++) {
		if (replace_field_info[j].end < replace_field_info[j].start) {
			utool_err_msg("Failed to parse pkt, start is bigger than end.\n");
			return UTOOL_ERR_PARSE;
		}

		len = replace_field_info[j].end - replace_field_info[j].start + 1;

		if (len > UTOOL_REG_MAX_LEN) {
			utool_err_msg("Failed to parse pkt, length of field is bigger than 32.\n");
			return UTOOL_ERR_PARSE;
		} else if (len == UTOOL_REG_MAX_LEN) {
			data = out->data[reg_index];
		} else {
			data = UTOOL_EXTRACT_BITS(out->data[reg_index], replace_field_info[j].start,
						  replace_field_info[j].end);
		}

		utool_pkt_print(replace_field_info[j].is_reserved, replace_field_info[j].reg_name, data,
				replace_field_info[j].cap_bitmap, out->env_version);
	}

	return UTOOL_OK;
}
