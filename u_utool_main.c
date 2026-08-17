// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <ctype.h>
#include <stddef.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

#include "./common/u_utool_error.h"
#include "./common/u_utool_common.h"
#include "./common/u_utool_help.h"
#include "./feature/u_utool_io_die.h"
#include "u_utool_dispatch.h"
#include "u_utool_pkt.h"

static int utool_check_arg(int argc, char **argv)
{
	char *argv_ptr = NULL;
	char argv_value = ' ';
	size_t argv_len = 0;
	size_t j = 0;
	int i = 0;

	for (i = 1; i < argc; i++) {
		if (strchr(argv[i], '\0') == NULL) {
			utool_err_msg("The input parameter is not string.\n");
			return UTOOL_ERR;
		}

		argv_len = strlen(argv[i]);
		if (argv_len > UBCTL_FILE_NAME_MAX_LEN) {
			utool_err_msg("The input param length = %zubytes is bigger than maximum %ubytes.\n",
				      argv_len, UBCTL_FILE_NAME_MAX_LEN);
			return UTOOL_ERR;
		}

		argv_ptr = argv[i];
		for (j = 0; j < argv_len; j++) {
			argv_value = argv_ptr[j];
			if ((isalnum(argv_value) == 0) && argv_value != '_' && argv_value != '-') {
				utool_err_msg("The input parameter is illegal string.\n");
				return UTOOL_ERR;
			}
		}
	}

	return UTOOL_OK;
}

static int utool_main_parse_sub(int argc, char **argv, struct utool_dev *dev)
{
#define UBCTL_ARG_MIN_NUM 2

	int ret = UTOOL_OK;

	do {
		if (argc < UBCTL_ARG_MIN_NUM) {
			ret = UTOOL_ERR_INVALID_PARAM;
			break;
		}

		ret = utool_check_arg(argc, argv);
		if (ret != UTOOL_OK) {
			break;
		}

		if (strcmp(argv[1], "ls") == 0) {
			return utool_open_dev_step(dev, 0, 0, UTOOL_DEV_STEP_LS);
		}

		if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0) ||
		    (strcmp(argv[1], "help") == 0) || (strcmp(argv[1], "-help") == 0)) {
			ret = UTOOL_ERR_HELP;
			break;
		}

		ret = utool_parse_command(argc, argv);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to parse command.\n");
			break;
		}
	} while (0);

	if (ret != UTOOL_OK) {
		utool_print_help();
	}

	return ret;
}

int main(int argc, char *argv[])
{
	const struct utool_cmd_param *cmd_param = NULL;
	struct utool_dev dev = {};
	int ret = UTOOL_OK;

	ret = utool_main_parse_sub(argc, argv, &dev);
	if (ret != UTOOL_OK) {
		return ret == UTOOL_OK_LS ? UTOOL_OK : ret;
	}

	cmd_param = utool_get_cmd_param();
	if (cmd_param == NULL) {
		utool_err_msg("Failed to get cmd param.\n");
		return UTOOL_ERR;
	}

	if (cmd_param->module_id == UTOOL_MODULE_NAME_UMMU) {
		ret = utool_open_dev_step(&dev, 0, 0, UTOOL_DEV_STEP_UMMU);
	} else if (cmd_param->module_id == UTOOL_MODULE_NAME_DEBUGFS) {
		dev.fd = UTOOL_INVALID_FD; // debugfs does not need to open dev.
	} else {
		ret = utool_open_dev_step(&dev, cmd_param->chip_id, cmd_param->die_id,
					  UTOOL_DEV_STEP_SCAN);
	}

	if (ret != UTOOL_OK) {
		return ret;
	}

	ret = utool_cmd_select(&dev);

	utool_close(&dev);

	return ret;
}
