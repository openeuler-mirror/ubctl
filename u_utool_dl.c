// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_error.h"
#include "u_utool_dl.h"

int utool_dl_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_dl_cmd_table[] = {
		{
			UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F,
			NULL, NULL, 0
		}
	};

	uint32_t table_cnt = UTOOL_ARRAY_SIZE(utool_dl_cmd_table);
	uint32_t i;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n",
			      (dev == NULL), (param == NULL));

		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < table_cnt; i++) {
		if (param->flags != utool_dl_cmd_table[i].flags) {
			continue;
		}
		if (utool_dl_cmd_table[i].execute == NULL) {
			utool_err_msg("Failed to dispatch. Callback is NULL.\n");
			return UTOOL_ERR_INVALID_PARAM;
		}

		return utool_dl_cmd_table[i].execute(dev, param,
						     utool_dl_cmd_table[i].func_table,
						     utool_dl_cmd_table[i].func_cnt);

	}

	return UTOOL_ERR_CMD_NOT_FOUND;
}
