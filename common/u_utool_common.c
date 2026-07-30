// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
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
#include "../u_utool_dispatch.h"
#include "../u_utool_pkt.h"
#include "../feature/u_utool_io_die.h"
#include "u_utool_common.h"

void utool_close(struct utool_dev *dev)
{
	if (dev == NULL) {
		utool_err_msg("Dev is NULL.\n");
		return;
	}

	if (dev->fd >= 0) {
		close(dev->fd);
		dev->fd = UTOOL_INVALID_FD;
	}
}

static int utool_open(struct utool_dev *dev)
{
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
			utool_warn_msg("The device is not ubase device, type = %s.\n", tmp_con);
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

static int utool_excute_io_die(struct utool_dev *dev)
{
	struct utool_cmd_param cmd_param = {};

	if (utool_open(dev) != UTOOL_OK) {
		return UTOOL_ERR;
	}

	if (utool_io_die_cmd(dev, &cmd_param) != UTOOL_OK) {
		utool_close(dev);
		utool_err_msg("Failed to query port info , errno = %d.\n", errno);
		return UTOOL_ERR;
	}
	utool_close(dev);

	return UTOOL_OK;
}

static int utool_proc_excption_dev(uint32_t chip_id, uint32_t die_id, enum utool_dev_step_flag step_flag)
{
	if (step_flag == UTOOL_DEV_STEP_LS) {
		utool_reg_msg("\ntotal ubctl count: %u\n", utool_get_ubctl_id());
		return UTOOL_OK_LS;
	}

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

static int utool_process_device_info(struct fwctl_rpc_ub_out *out)
{
	struct fwctl_pkt_dev_info_match *dev_info_match;

	dev_info_match = (struct fwctl_pkt_dev_info_match *)out->data;
	if (dev_info_match->is_matched) {
		return UTOOL_OK;
	}

	return UTOOL_ERR;
}

static int utool_check_dev_info(struct utool_dev *dev, uint32_t chip_id, uint32_t die_id)
{
	uint32_t pkt_in_len = sizeof(struct fwctl_pkt_dev_info_match);
	struct utool_pkt_exec pkt_exec = {
		.rpc_cmd = UTOOL_CMD_QUERY_DEV_INFO,
		.data_len = sizeof(struct fwctl_pkt_dev_info_match),
		.execute = utool_process_device_info
	};
	struct fwctl_pkt_dev_info_match pkt_in_match = {
		.chip_id = chip_id,
		.die_id = die_id,
		.is_matched = false,
	};

	return utool_pkt_operation(dev, &pkt_in_match, pkt_in_len, &pkt_exec);
}

static int utool_process_step(struct utool_dev *dev, uint32_t chip_id, uint32_t die_id,
			      enum utool_dev_step_flag step_flag)
{
	int ret = UTOOL_OK;

	if (step_flag == UTOOL_DEV_STEP_LS) {
		if (utool_excute_io_die(dev) != UTOOL_OK) {
			utool_err_msg("Failed to query port bitmap.\n");
		}
		return UTOOL_ERR;
	}

	if (utool_open(dev) != UTOOL_OK) {
		return UTOOL_ERR;
	}

	if (step_flag == UTOOL_DEV_STEP_SCAN) {
		ret = utool_check_dev_info(dev, chip_id, die_id);
		if (ret != UTOOL_OK) {
			utool_close(dev);
		}
	}

	return ret;
}

int utool_open_dev_step(struct utool_dev *dev, uint32_t chip_id, uint32_t die_id,
			enum utool_dev_step_flag step_flag)
{
	char driver_path[UTOOL_DEV_NAME_LEN_MAX] = {};
	char ub_entity_name[UTOOL_DEV_NAME_LEN_MAX] = {};
	struct dirent *entry = NULL;
	DIR *class_dir = NULL;
	int ret = UTOOL_OK;

	if (dev == NULL) {
		utool_err_msg("Dev is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if ((class_dir = opendir(UTOOL_FWCTL_PATH)) == NULL) {
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

		ret = utool_process_step(dev, chip_id, die_id, step_flag);
		if (ret != UTOOL_OK) {
			continue;
		}

		(void)closedir(class_dir);

		return UTOOL_OK;
	}
	(void)closedir(class_dir);
	return utool_proc_excption_dev(chip_id, die_id, step_flag);
}
