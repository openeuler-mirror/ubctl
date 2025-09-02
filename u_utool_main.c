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

#include "u_utool_error.h"
#include "u_utool_common.h"
#include "u_utool_dispatch.h"

enum utool_dev_step_flag {
	UTOOL_DEV_STEP_SCAN = 0,
};

static void utool_help(void)
{
	utool_info_msg("Usage: ubctl <-c ${chip_id}> <-d ${ub_ctl_id}> <-m ${module}> [-f ${function}]\n"
		       "       [-p ${port}] [-e ${value}] [-h]\n\n"
		       "options:\n\n"
		       "  -c $chip_id: chip id, chip id and ub ctl id  are used to find the valid device.\n\n"
		       "  -d $ub_ctl_id : ub ctl id, chip id and ub ctl id  are used to find the valid device.\n\n"
		       "  -m $module: module name, current module include: dl.\n\n"
		       "  -f $function: function name, different processing functions are provided for each module.\n"
		       "                dl: pkt_stats, lane, link_status, bit_err, bist, bist_err, link_trace.\n"
		       "  -p $port: port index, indicates the physical port index.\n\n"
		       "  -e $value: value, used to set the value of the register.\n\n"
		       "  -h: help. display the help information, also use -h or --help or help or -help.\n\n"
		       "example:\n\n"
		       "   ubctl -m dl -p 0 -f bit_err -d 0 -c 0       query the number of bit errors by port\n\n");
}

static void utool_close(struct utool_dev *dev)
{
	if (dev->fd >= 0) {
		close(dev->fd);
	}
}

static int utool_open(struct utool_dev *dev)
{
#define UTOOL_INVALID_FD (-1)

	char *resolved_path = NULL;

	dev->fd = UTOOL_INVALID_FD;
	resolved_path = realpath(dev->devname, NULL);
	if (resolved_path == NULL) {
		utool_err_msg("Failed to resolve the devname, errno = %d.\n", errno);
		return UTOOL_ERR;
	}

	dev->fd = open(resolved_path, O_RDWR);
	if (dev->fd < 0) {
		utool_err_msg("Please insmod ub_fwctl.ko and make sure the device file exists, errno = %d.\n", errno);
		UTOOL_FREE(resolved_path);
		return UTOOL_ERR;
	}

	UTOOL_FREE(resolved_path);
	return UTOOL_OK;
}

static FILE *utool_open_file(const char *file_path, const char *mode)
{
	char *resolved_path = NULL;
	FILE *fp = NULL;

	resolved_path = realpath(file_path, NULL);
	if (resolved_path == NULL) {
		utool_err_msg("Failed to get realpath, errno = %d.\n", errno);
		return NULL;
	}
	fp = fopen(resolved_path, mode);
	UTOOL_FREE(resolved_path);
	return fp;
}

static int utool_check_ubase_device(char *file_path, char *dev_name)
{
#define UTOOL_UB_ENTITY_NAME_STR "UB_ENTITY_NAME"
#define UTOOL_UBASE_DRIVER "ubase"
#define UTOOL_DRIVER_STR "DRIVER"

	char line[UTOOL_LINE_BUF_LEN];
	char *tmp_con = NULL;
	char *token = NULL;
	int ret = UTOOL_OK;
	char *con = NULL;
	FILE *fp = NULL;

	fp = utool_open_file(file_path, "r");
	if (fp == NULL) {
		utool_err_msg("Failed to open the device file.\n");
		return UTOOL_ERR;
	}

	while (fgets(line, UTOOL_LINE_BUF_LEN, fp) != NULL) {
		token = strtok(line, "=");
		if ((token == NULL) || ((con = strtok(NULL, "")) == NULL)) {
			continue;
		}

		tmp_con = strtok(con, "\n");
		if ((strcmp(token, UTOOL_DRIVER_STR) == 0) &&
			(strcmp(tmp_con, UTOOL_UBASE_DRIVER) != 0)) {
			utool_warn_msg("Device is not ubase device, type = %s.\n", tmp_con);
			(void)fclose(fp);
			return UTOOL_ERR;
		}

		if (strcmp(token, UTOOL_UB_ENTITY_NAME_STR) == 0) {
			ret = snprintf(dev_name, UTOOL_DEV_NAME_LEN_MAX, "%s", tmp_con);
			if (ret <= 0 || ret >= UTOOL_DEV_NAME_LEN_MAX) {
				utool_err_msg("Failed to format dev name, errno = %d, ret = %d.\n", errno, ret);
				(void)fclose(fp);
				return UTOOL_ERR;
			}
			(void)fclose(fp);
			return UTOOL_OK;
		}
	}

	(void)fclose(fp);
	utool_err_msg("Failed to find ubase device.\n");

	return UTOOL_ERR;
}

static int utool_check_dev_chip_ctl_id(char *file_path, uint32_t chip_id, uint32_t die_id)
{
#define UTOOL_CHIP_ID_STR "chip_id"
#define UTOOL_DIE_ID_STR "die_id"
#define UTOOL_TAB_ASCII 9

	uint32_t chip_id_tmp = UTOOL_DEV_CHIP_DIE_ID_MAX;
	uint32_t die_id_tmp = UTOOL_DEV_CHIP_DIE_ID_MAX;
	char *trimmed_str, *tmp_con, *token, *con;
	char tab_char = UTOOL_TAB_ASCII;
	char line[UTOOL_LINE_BUF_LEN];
	int ret = UTOOL_OK;
	FILE *fp;

	fp = utool_open_file(file_path, "r");
	if (fp == NULL) {
		utool_err_msg("Failed to open the config file.\n");
		return UTOOL_ERR;
	}

	while (fgets(line, UTOOL_LINE_BUF_LEN, fp) != NULL) {
		token = strtok(line, ":");
		if ((token == NULL) || ((con = strtok(NULL, "")) == NULL)) {
			continue;
		}

		trimmed_str = token;
		while (*trimmed_str == tab_char) {
			trimmed_str++;
		}
		tmp_con = strtok(con, "\n");
		if (strcmp(trimmed_str, UTOOL_CHIP_ID_STR) == 0) {
			ret = utool_transform_str(tmp_con, &chip_id_tmp);
			if (ret != UTOOL_OK) {
				utool_err_msg("Failed to transform chip id.\n");
				break;
			}
			continue;
		}
		if (strcmp(trimmed_str, UTOOL_DIE_ID_STR) == 0) {
			ret = utool_transform_str(tmp_con, &die_id_tmp);
			if (ret != UTOOL_OK) {
				utool_err_msg("Failed to transform die id.\n");
				break;
			}
			continue;
		}
	}
	(void)fclose(fp);

	if ((chip_id_tmp == chip_id) && (die_id_tmp == die_id)) {
		return UTOOL_OK;
	}

	return UTOOL_ERR;
}

static int utool_proc_excption_dev(uint32_t chip_id, uint32_t die_id, enum utool_dev_step_flag step_flag)
{
	if (step_flag == UTOOL_DEV_STEP_SCAN) {
		utool_err_msg("Ubctl device not found. chip_id = %u, die_id = %u\n", chip_id, die_id);
	} else {
		utool_err_msg("Ubctl device not found\n");
	}
	return UTOOL_ERR;
}

#define UTOOL_FWCTL_PATH "/dev/fwctl"
static int utool_format_dev_path(struct utool_dev *dev, char *driver_path, struct dirent *entry)
{
#define UTOOL_SYS_CLASS_PATH "/sys/class/fwctl"
#define UTOOL_DEV_UEVENT_NAME "device/uevent"

	int ret;

	ret = snprintf(driver_path, UTOOL_DEV_NAME_LEN_MAX, UTOOL_SYS_CLASS_PATH "/%s/" UTOOL_DEV_UEVENT_NAME,
		       entry->d_name);
	if (ret <= 0 || ret >= UTOOL_DEV_NAME_LEN_MAX) {
		utool_err_msg("Failed to format driver path, errno = %d, ret = %d.\n", errno, ret);
		return UTOOL_ERR;
	}

	ret = snprintf(dev->devname, UTOOL_DEV_NAME_LEN_MAX, UTOOL_FWCTL_PATH "/%s", entry->d_name);
	if (ret <= 0 || ret >= UTOOL_DEV_NAME_LEN_MAX) {
		utool_err_msg("Failed to format fwctl dev name, errno = %d, ret = %d.\n", errno, ret);
		return UTOOL_ERR;
	}

	return UTOOL_OK;
}

static int utool_open_dev_step(struct utool_dev *dev, uint32_t chip_id, uint32_t die_id,
			       enum utool_dev_step_flag step_flag)
{
#define UTOOL_SYS_CAP_INFO_PATH "/sys/kernel/debug/ubase/%s/caps_info"

	char sys_cap_path[UTOOL_DEV_NAME_LEN_MAX] = {};
	char driver_path[UTOOL_DEV_NAME_LEN_MAX] = {};
	char ub_entity_name[UTOOL_DEV_NAME_LEN_MAX] = {};
	struct dirent *entry = NULL;
	DIR *class_dir = NULL;
	int ret = UTOOL_OK;

	class_dir = opendir(UTOOL_FWCTL_PATH);
	if (class_dir == NULL) {
		utool_err_msg("Failed to open dir %s, errno = %d.\n", UTOOL_FWCTL_PATH, errno);
		return UTOOL_ERR;
	}

	while ((entry = readdir(class_dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}

		ret = utool_format_dev_path(dev, driver_path, entry);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to format dev name.\n");
			(void)closedir(class_dir);
			return ret;
		}

		if (utool_check_ubase_device(driver_path, ub_entity_name) != UTOOL_OK) {
			utool_warn_msg("Ubctl device: %s not ubase device\n", entry->d_name);
			continue;
		}

		ret = snprintf(sys_cap_path, UTOOL_DEV_NAME_LEN_MAX, UTOOL_SYS_CAP_INFO_PATH, ub_entity_name);
		if (ret <= 0 || ret >= UTOOL_DEV_NAME_LEN_MAX) {
			utool_err_msg("Failed to format sys cap path, errno = %d, ret = %d.\n", errno, ret);
			continue;
		}
		if (utool_check_dev_chip_ctl_id(sys_cap_path, chip_id, die_id) != UTOOL_OK) {
			continue;
		}

		(void)closedir(class_dir);
		if (utool_open(dev) != UTOOL_OK) {
			return UTOOL_ERR;
		}

		return UTOOL_OK;
	}
	(void)closedir(class_dir);

	return utool_proc_excption_dev(chip_id, die_id, step_flag);
}

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
		if (argv_len > UBCTL_ARG_MAX_LEN) {
			utool_err_msg("The input parameter length is too long.\n");
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
		utool_help();
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
		return ret;
	}

	cmd_param = utool_get_cmd_param();
	if (cmd_param == NULL) {
		utool_err_msg("Failed to get cmd param.\n");
		return UTOOL_ERR;
	}

	ret = utool_open_dev_step(&dev, cmd_param->chip_id, cmd_param->die_id,
				  UTOOL_DEV_STEP_SCAN);

	if (ret != UTOOL_OK) {
		return ret;
	}

	ret = utool_cmd_select(&dev);

	utool_close(&dev);

	return ret;
}
