// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <ctype.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <libgen.h>

#include "u_utool_error.h"
#include "u_utool_pkt.h"
#include "u_utool_debugfs.h"

#define UBCTL_BUS_NUM_LEN 6
#define UBCTL_DEV_CNT_MAX 100
#define UBCTL_PATH_LEN_MAX 100
#define UBCTL_CMD_LEN_MAX 300
#define UBCTL_DEBUGFS_PATH "/sys/kernel/debug/ubase/%s"
#define UBCTL_DEBUGFS_PATH_LEN 30
#define UBCTL_BUFFER_LEN_MAX 2048
#define UBCTL_MATCH_NUM 2

static bool g_utool_has_catted_file = false;

struct utool_device_info {
	char bus_num[UBCTL_BUS_NUM_LEN];
	char device_name[UBCTL_ARG_MAX_LEN];
	char port_name[UBCTL_ARG_MAX_LEN];
	char device_id[UBCTL_ARG_MAX_LEN];
	char device_type[UBCTL_ARG_MAX_LEN];
};

struct utool_device_info g_utool_debugfs_devices[UBCTL_DEV_CNT_MAX];
uint32_t g_utool_debugfs_device_cnt = 0;

struct utool_dir_entry {
	char path[UBCTL_PATH_LEN_MAX];
	struct list_head list;
};

struct utool_traverse_params {
	char *file;
	char *bus_num;
	int (*callback)(char*, char*);
	struct list_head visited_paths;
	struct list_head dir_list;
};

static int utool_get_bus_num_by_device_name(char *device_name, char *bus_num)
{
	char search_file[UBCTL_PATH_LEN_MAX];
	char letters[UBCTL_ARG_MAX_LEN];
	char digits[UBCTL_ARG_MAX_LEN];
	char path[UBCTL_PATH_LEN_MAX];
	struct dirent *entry;
	DIR *dir;
	int ret;

	if (!device_name || !bus_num) {
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (sscanf(device_name, "%[^0-9]%[0-9]", letters, digits) != UBCTL_MATCH_NUM) {
		utool_err_msg("Failed to sscanf device name(%s)\n", device_name);
		return UTOOL_ERR;
	}
	ret = snprintf(search_file, sizeof(search_file), "ubase.%s.%s", letters, digits);
	if (ret <= 0 || ret >= UBCTL_PATH_LEN_MAX) {
		utool_err_msg("Failed to format search file, ret = %d.\n", ret);
		return UTOOL_ERR;
	}

	dir = opendir("/sys/bus/ub/devices");
	if (dir == NULL) {
		utool_err_msg("Failed to open directory, error: %s\n", strerror(errno));
		return UTOOL_ERR_INVALID_CMD;
	}

	while ((entry = readdir(dir)) != NULL) {
		ret = snprintf(path, sizeof(path), "/sys/bus/ub/devices/%s/%s", entry->d_name, search_file);
		if (ret <= 0 || ret >= UBCTL_PATH_LEN_MAX) {
			utool_err_msg("Failed to format path, ret = %d.\n", ret);
			goto printf_err;
		}
		if (access(path, F_OK) != -1) {
			ret = snprintf(bus_num, UBCTL_BUS_NUM_LEN, "%s", entry->d_name);
			if (ret <= 0 || ret >= UBCTL_BUS_NUM_LEN) {
				utool_err_msg("Failed to copy file name, ret = %d.\n", ret);
				goto printf_err;
			}
			closedir(dir);
			return UTOOL_OK;
		}
	}

	utool_err_msg("Failed to get bus number from %s.\n", device_name);
printf_err:
	closedir(dir);
	return UTOOL_ERR;
}

static int utool_get_bus_num_by_port_name(char *port_name, char *bus_num)
{
	char buffer[UBCTL_BUFFER_LEN_MAX];
	char cmd[UBCTL_CMD_LEN_MAX];
	FILE *ethtool_fp;
	int ret;

	if (!port_name || !bus_num) {
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = snprintf(cmd, sizeof(cmd), "ethtool -i %s 2>/dev/null | grep 'bus-info:' | awk -F': ' '{print $2}'",
		       port_name);
	if (ret <= 0 || ret >= UBCTL_CMD_LEN_MAX) {
		utool_err_msg("Failed to format ethtool cmd, ret = %d.\n", ret);
		return UTOOL_ERR;
	}

	ethtool_fp = popen(cmd, "r");
	if (ethtool_fp == NULL) {
		utool_err_msg("Failed to execute ethtool cmd, error:%s.\n", strerror(errno));
		return UTOOL_ERR_INVALID_CMD;
	}

	if (fgets(buffer, sizeof(buffer), ethtool_fp) != NULL) {
		buffer[strcspn(buffer, "\n")] = 0;
		ret = snprintf(bus_num, UBCTL_BUS_NUM_LEN, "%s", buffer);
		if (ret <= 0 || ret >= UBCTL_BUS_NUM_LEN) {
			utool_err_msg("Failed to copy buffer, ret = %d.\n", ret);
			goto printf_err;
		}
		pclose(ethtool_fp);
		return UTOOL_OK;
	}

	utool_err_msg("Failed to get bus number from %s.\n", port_name);
printf_err:
	pclose(ethtool_fp);
	return UTOOL_ERR;
}

static int utool_get_device_info(void)
{
	const char *commands[] = {"lsub 2>/dev/null", "/var/lsub 2>/dev/null"};
	char buffer[UBCTL_BUFFER_LEN_MAX];
	bool success = false;
	FILE *fp;

	for (size_t i = 0; i < UTOOL_ARRAY_SIZE(commands); ++i) {
		fp = popen(commands[i], "r");
		if (fp == NULL) {
			continue;
		}
		if (fgets(buffer, sizeof(buffer), fp) != NULL) {
			success = true;
			break;
		}
		pclose(fp);
	}

	if (!success) {
		if (fp) {
			pclose(fp);
		}
		utool_err_msg("Failed to get lsub info.\n");
		return UTOOL_ERR_CMD_NOT_FOUND;
	}

	do {
		if (sscanf(buffer, "<%5[^>]>%*[^<]<%*[^<]<%*[^<]<%4[^>]>",
			   g_utool_debugfs_devices[g_utool_debugfs_device_cnt].bus_num,
			   g_utool_debugfs_devices[g_utool_debugfs_device_cnt].device_id) == UBCTL_MATCH_NUM) {
			g_utool_debugfs_device_cnt++;
		}
	} while (fgets(buffer, sizeof(buffer), fp) != NULL && g_utool_debugfs_device_cnt < UBCTL_DEV_CNT_MAX);

	pclose(fp);
	return UTOOL_OK;
}

static int utool_get_port_names(void)
{
#define PORT_FILTER_CMD "ip a | awk -F ':' '{print $2}' | sed 's/^[ \\t]*//;s/[ \\t]*$//' | grep -E '^ublc|^ethc'"
	char buffer[UBCTL_BUFFER_LEN_MAX];
	char bus_num[UBCTL_BUS_NUM_LEN];
	uint32_t i;
	FILE *fp;
	int ret;

	fp = popen(PORT_FILTER_CMD, "r");
	if (!fp) {
		utool_err_msg("Failed to execute ip a command: %s\n", strerror(errno));
		return UTOOL_ERR_INVALID_CMD;
	}

	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		buffer[strcspn(buffer, "\n")] = 0;
		if (utool_get_bus_num_by_port_name(buffer, bus_num) != UTOOL_OK) {
			continue;
		}
		for (i = 0; i < g_utool_debugfs_device_cnt; i++) {
			if (strcmp(g_utool_debugfs_devices[i].bus_num, bus_num) == 0) {
				ret = snprintf(g_utool_debugfs_devices[i].port_name, UBCTL_ARG_MAX_LEN, "%s", buffer);
				if (ret <= 0 || ret >= UBCTL_ARG_MAX_LEN) {
					utool_err_msg("Failed to copy buffer, ret = %d.\n", ret);
					pclose(fp);
					return UTOOL_ERR;
				}
				break;
			}
		}
	}

	pclose(fp);
	return UTOOL_OK;
}

static void utool_get_device_name_by_ubus_num(char *ubus_num, char *device_name)
{
	char buffer[UBCTL_BUFFER_LEN_MAX];
	char letters[UBCTL_ARG_MAX_LEN];
	char digits[UBCTL_ARG_MAX_LEN];
	char cmd[UBCTL_CMD_LEN_MAX];
	FILE *fp;
	int ret;

	if (!ubus_num || !device_name) {
		return;
	}

	ret = snprintf(cmd, sizeof(cmd), "ls /sys/bus/ub/devices/%s | grep '^ubase.' | head -n 1", ubus_num);
	if (ret <= 0 || ret >= UBCTL_CMD_LEN_MAX) {
		utool_err_msg("Failed to format ls cmd, ret = %d.\n", ret);
		return;
	}

	fp = popen(cmd, "r");
	if (fp == NULL) {
		utool_err_msg("Failed to popen.\n");
		return;
	}

	if (fgets(buffer, sizeof(buffer), fp) != NULL) {
		buffer[strcspn(buffer, "\n")] = '\0';
		if (sscanf(buffer, "ubase.%[a-zA-Z].%[0-9]", letters, digits) == UBCTL_MATCH_NUM) {
			ret = snprintf(device_name, UBCTL_ARG_MAX_LEN, "%s%s", letters, digits);
			if (ret <= 0 || ret >= UBCTL_ARG_MAX_LEN) {
				utool_err_msg("Failed to format device name, ret = %d.\n", ret);
				pclose(fp);
				return;
			}
		}
	}

	pclose(fp);
}

static int utool_get_device_type(char *device_id, char *device_type)
{
#define UBCTL_TYPE_UNKNOWN "Unknown"
#define UBCTL_DEVICE_ID_NUM 28
	static struct utool_device_mapping {
		const char *device_id;
		const char *device_type;
	} utool_device_mapping_table[UBCTL_DEVICE_ID_NUM] = {
		{ "a001", "urma mue" }, { "a002", "urma ue" },
		{ "a003", "cdma mue" }, { "a004", "cdma ue" },
		{ "a005", "pmu mue" }, { "a006", "pmu ue" },
		{ "a00b", "urma mue" }, { "a00c", "urma ue" },
		{ "a00d", "cdma mue" }, { "a00e", "cdma ue" },
		{ "a00f", "pmu mue" }, { "a010", "pmu ue" },
		{ "d802", "urma mue" }, { "d803", "urma ue" },
		{ "d804", "cdma mue" }, { "d805", "cdma ue" },
		{ "d806", "pmu mue" }, { "d807", "pmu ue" },
		{ "d80b", "uboe mue" }, { "d80c", "uboe ue" },
		{ "d812", "urma mue" }, { "d813", "urma ue" },
		{ "d814", "cdma mue" }, { "d815", "cdma ue" },
		{ "d816", "pmu mue" }, { "d817", "pmu ue" },
		{ "d81b", "uboe mue" }, { "d81c", "uboe ue"}
	};
	int i, ret;

	if (!device_type) {
		utool_err_msg("device type is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < UBCTL_DEVICE_ID_NUM; i++) {
		if (strcmp(utool_device_mapping_table[i].device_id, device_id) == 0) {
			ret = snprintf(device_type, UBCTL_ARG_MAX_LEN, "%s", utool_device_mapping_table[i].device_type);
			if (ret <= 0 || ret >= UBCTL_ARG_MAX_LEN) {
				utool_err_msg("Failed to copy device type, ret = %d.\n", ret);
				return UTOOL_ERR;
			}
			return UTOOL_OK;
		}
	}

	ret = snprintf(device_type, UBCTL_ARG_MAX_LEN, "%s", UBCTL_TYPE_UNKNOWN);
	if (ret <= 0 || ret >= UBCTL_ARG_MAX_LEN) {
		utool_err_msg("Failed to copy device type, ret = %d.\n", ret);
	}
	return UTOOL_ERR;
}

static void utool_print_help(void)
{
	utool_err_msg("The ubctl dev command must be in the following formats:\n"
		      "ubctl -m debugfs ls\n"
		      "ubctl -m debugfs -dev [Bus_Num / Device_Name / NetDev_Name]\n"
		      "ubctl -m debugfs -dev [Bus_Num / Device_Name / NetDev_Name] -file [File_Name]\n");
}

static int utool_debugfs_cmd_ls(void)
{
	uint32_t i;

	if (utool_get_device_info() != UTOOL_OK) {
		utool_err_msg("Failed to get device information.\n");
		return UTOOL_ERR;
	}

	if (utool_get_port_names() != UTOOL_OK) {
		utool_err_msg("Failed to get port names.\n");
		return UTOOL_ERR;
	}

	utool_reg_msg("Bus Num  Device Name  NetDev_Name  Device ID  Device Type\n");
	for (i = 0; i < g_utool_debugfs_device_cnt; i++) {
		utool_get_device_name_by_ubus_num(g_utool_debugfs_devices[i].bus_num,
						  g_utool_debugfs_devices[i].device_name);
		if (utool_get_device_type(g_utool_debugfs_devices[i].device_id,
					  g_utool_debugfs_devices[i].device_type) != UTOOL_OK) {
			continue;
		}
		utool_reg_msg("%-9s%-12s%-14s0x%-9s%-11s\n",
			      g_utool_debugfs_devices[i].bus_num, g_utool_debugfs_devices[i].device_name,
			      g_utool_debugfs_devices[i].port_name, g_utool_debugfs_devices[i].device_id,
			      g_utool_debugfs_devices[i].device_type);
	}

	return UTOOL_OK;
}

static bool utool_debugfs_is_path_visited(struct list_head *visited_paths, char *path)
{
	struct utool_dir_entry *entry;

	list_for_each_entry(entry, visited_paths, list) {
		if (strcmp(entry->path, path) == 0) {
			return true;
		}
	}
	return false;
}

static int utool_debugfs_cmd_path(char *file, char *file_path)
{
	char *relative_path = file_path + UBCTL_DEBUGFS_PATH_LEN;
	char debugfs_path[UBCTL_DEBUGFS_PATH_LEN];
	static bool have_printed_path = false;

	UTOOL_SET_USED(file);

	if (!have_printed_path) {
		if (snprintf(debugfs_path, UBCTL_DEBUGFS_PATH_LEN, "%s", file_path) <= 0) {
			utool_err_msg("Failed to copy debugfs dir path.\n");
			return UTOOL_ERR;
		}
		utool_reg_msg("debugfs dir path:\n\t%s\ndebugfs file list:\n", debugfs_path);
		have_printed_path = true;
	}

	if (*relative_path == '/') {
		relative_path++;
	}

	utool_reg_msg("\t%s\n", relative_path);
	return UTOOL_OK;
}

static int utool_debugfs_cmd_file(char *file, char *file_path)
{
	char cmd[UBCTL_CMD_LEN_MAX];
	int ret;

	if (!file || !file_path) {
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (strcmp(basename(file_path), file) == 0) {
		if (g_utool_has_catted_file) {
			utool_reg_msg("\n");
		}
		utool_reg_msg("%s:\n", file_path);

		ret = snprintf(cmd, sizeof(cmd), "cat %s", file_path);
		if (ret <= 0 || ret >= UBCTL_CMD_LEN_MAX) {
			utool_err_msg("Failed to format cat cmd, ret = %d.\n", ret);
			return UTOOL_ERR;
		}

		if (system(cmd) != 0) {
			utool_err_msg("Failed to execute command.\n");
			return UTOOL_ERR;
		}
		g_utool_has_catted_file = true;
	}
	return UTOOL_OK;
}

static int utool_debugfs_process_directory(struct utool_traverse_params *params, char *debugfs_path)
{
	struct utool_dir_entry *utool_dir_entry_node;
	int ret;

	utool_dir_entry_node = (struct utool_dir_entry *)UTOOL_MALLOC(sizeof(struct utool_dir_entry));
	if (!utool_dir_entry_node) {
		utool_err_msg("Failed to allocate memory.\n");
		return UTOOL_ERR;
	}

	ret = snprintf(utool_dir_entry_node->path, UBCTL_DEBUGFS_PATH_LEN, "%s", debugfs_path);
	if (ret <= 0 || ret >= UBCTL_DEBUGFS_PATH_LEN) {
		utool_err_msg("Failed to copy entry node path, ret = %d.\n", ret);
		UTOOL_FREE(utool_dir_entry_node);
		return UTOOL_ERR;
	}
	list_add(&utool_dir_entry_node->list, &params->dir_list);

	return UTOOL_OK;
}

static int utool_debugfs_traverse_init(struct utool_traverse_params *params, char *file, char *bus_num,
				       int (*callback)(char*, char*))
{
	params->file = file;
	params->bus_num = bus_num;
	params->callback = callback;

	INIT_LIST_HEAD(&params->visited_paths);
	INIT_LIST_HEAD(&params->dir_list);

	return UTOOL_OK;
}

static int utool_process_directory_entry(struct utool_traverse_params *params, char *path)
{
	struct utool_dir_entry *new_utool_dir_entry;
	char new_path[UBCTL_PATH_LEN_MAX];
	struct dirent *d_entry;
	struct stat st;
	DIR *dir;
	int ret;

	dir = opendir(path);
	if (!dir) {
		utool_err_msg("Path: %s is not exist.\n", path);
		return UTOOL_ERR;
	}

	while ((d_entry = readdir(dir)) != NULL) {
		if (strcmp(d_entry->d_name, ".") == 0 || strcmp(d_entry->d_name, "..") == 0) {
			continue;
		}

		ret = snprintf(new_path, sizeof(new_path), "%s/%s", path, d_entry->d_name);
		if (ret <= 0 || ret >= UBCTL_PATH_LEN_MAX) {
			utool_err_msg("Failed to format new path, ret = %d.\n", ret);
			closedir(dir);
			return UTOOL_ERR;
		}

		if (stat(new_path, &st) == -1) {
			utool_err_msg("Failed to stat file.\n");
			closedir(dir);
			return UTOOL_ERR;
		}

		if (S_ISDIR(st.st_mode)) {
			new_utool_dir_entry = (struct utool_dir_entry *)UTOOL_MALLOC(sizeof(struct utool_dir_entry));
			if (!new_utool_dir_entry) {
				utool_err_msg("Failed to allocate memory.\n");
				closedir(dir);
				return UTOOL_ERR;
			}
			ret = snprintf(new_utool_dir_entry->path, UBCTL_PATH_LEN_MAX, "%s", new_path);
			if (ret <= 0 || ret >= UBCTL_PATH_LEN_MAX) {
				utool_err_msg("Failed to copy new path, ret = %d.\n", ret);
				closedir(dir);
				return UTOOL_ERR;
			}
			new_utool_dir_entry->path[UBCTL_PATH_LEN_MAX - 1] = '\0';
			list_add_tail(&new_utool_dir_entry->list, &params->dir_list);
		} else {
			if (params->callback(params->file, new_path) != UTOOL_OK) {
				closedir(dir);
				return UTOOL_ERR;
			}
		}
	}

	closedir(dir);
	return UTOOL_OK;
}

static int utool_mark_path_as_visited(struct utool_traverse_params *params, char *path)
{
	struct utool_dir_entry *visited_entry;
	int ret;

	if (utool_debugfs_is_path_visited(&params->visited_paths, path)) {
		utool_err_msg("Skipping already visited path: %s\n", path);
		return UTOOL_ERR;
	}

	visited_entry = (struct utool_dir_entry *)UTOOL_MALLOC(sizeof(struct utool_dir_entry));
	if (!visited_entry) {
		utool_err_msg("Failed to allocate memory for visited path.\n");
		return UTOOL_ERR;
	}
	ret = snprintf(visited_entry->path, UBCTL_PATH_LEN_MAX, "%s", path);
	if (ret <= 0 || ret >= UBCTL_PATH_LEN_MAX) {
		utool_err_msg("Failed to copy visited entry path, ret = %d.\n", ret);
		UTOOL_FREE(visited_entry);
		return UTOOL_ERR;
	}
	list_add(&visited_entry->list, &params->visited_paths);

	return UTOOL_OK;
}

static int utool_debugfs_traverse(struct utool_traverse_params *params)
{
	struct utool_dir_entry *utool_dir_entry_node;

	while (!list_empty(&params->dir_list)) {
		utool_dir_entry_node = list_first_entry(&params->dir_list, struct utool_dir_entry, list);
		list_del(&utool_dir_entry_node->list);

		if (utool_mark_path_as_visited(params, utool_dir_entry_node->path) != UTOOL_OK) {
			UTOOL_FREE(utool_dir_entry_node);
			continue;
		}

		if (utool_process_directory_entry(params, utool_dir_entry_node->path) != UTOOL_OK) {
			UTOOL_FREE(utool_dir_entry_node);
			return UTOOL_ERR;
		}

		UTOOL_FREE(utool_dir_entry_node);
	}

	if ((params->callback == utool_debugfs_cmd_file) && (!g_utool_has_catted_file)) {
		utool_err_msg("The file %s is not found.\n", params->file);
		return UTOOL_ERR;
	}

	return UTOOL_OK;
}

static void utool_debugfs_cleanup(struct utool_traverse_params *params)
{
	struct utool_dir_entry *entry, *tmp;

	list_for_each_entry_safe(entry, tmp, &params->visited_paths, list) {
		list_del(&entry->list);
		UTOOL_FREE(entry);
	}

	list_for_each_entry_safe(entry, tmp, &params->dir_list, list) {
		list_del(&entry->list);
		UTOOL_FREE(entry);
	}
}

static int utool_debugfs_cmd_traverse(char *file, char *bus_num, int (*callback)(char*, char*))
{
	char debugfs_path[UBCTL_DEBUGFS_PATH_LEN];
	struct utool_traverse_params params;
	int ret;

	ret = snprintf(debugfs_path, UBCTL_DEBUGFS_PATH_LEN, UBCTL_DEBUGFS_PATH, bus_num);
	if (ret <= 0 || ret >= UBCTL_DEBUGFS_PATH_LEN) {
		utool_err_msg("Failed to format debugfs path, ret = %d.\n", ret);
		return UTOOL_ERR;
	}

	ret = utool_debugfs_traverse_init(&params, file, bus_num, callback);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to init traverse.\n");
		goto cleanup;
	}

	ret = utool_debugfs_process_directory(&params, debugfs_path);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to process directory.\n");
		goto cleanup;
	}

	ret = utool_debugfs_traverse(&params);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to traverse.\n");
	}

cleanup:
	utool_debugfs_cleanup(&params);
	return ret;
}

static int utool_debugfs_cmd(struct utool_cmd_param *param, int (*cmd_exe)(char*, char *))
{
	char bus_num[UBCTL_BUS_NUM_LEN] = {0};
	int ret = UTOOL_OK;

	if (strncmp(param->device, "ub", strlen("ub")) == 0 || strncmp(param->device, "eth", strlen("eth")) == 0) {
		ret = utool_get_bus_num_by_port_name(param->device, bus_num);
		if (ret != UTOOL_OK) {
			return ret;
		}
	} else if (isdigit(param->device[0])) {
		if (strlen(param->device) != UBCTL_BUS_NUM_LEN - 1) {
			utool_err_msg("Length of bus num is invalid, expected %d, got %zu.\n",
				      UBCTL_BUS_NUM_LEN - 1, strlen(param->device));
			return UTOOL_ERR;
		}

		ret = snprintf(bus_num, UBCTL_BUS_NUM_LEN, "%s", param->device);
		if (ret <= 0 || ret >= UBCTL_BUS_NUM_LEN) {
			utool_err_msg("Failed to copy device, ret = %d.\n", ret);
		return UTOOL_ERR;
		}
	} else {
		ret = utool_get_bus_num_by_device_name(param->device, bus_num);
		if (ret != UTOOL_OK) {
			return ret;
		}
	}

	return utool_debugfs_cmd_traverse(param->file, bus_num, cmd_exe);
}

int utool_debugfs_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct {
		uint32_t flags;
		int (*execute)(char *file, char *file_path);
	} utool_debugfs_cmd_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_DEV, utool_debugfs_cmd_path },
		{ UTOOL_FLAG_M | UTOOL_FLAG_DEV | UTOOL_FLAG_FILE, utool_debugfs_cmd_file }
	};
	uint32_t table_cnt = UTOOL_ARRAY_SIZE(utool_debugfs_cmd_table);
	uint32_t i;

	UTOOL_SET_USED(dev);
	if (!param) {
		utool_err_msg("Param is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (param->flags == (UTOOL_FLAG_M | UTOOL_FLAG_LS)) {
		return utool_debugfs_cmd_ls();
	}

	for (i = 0; i < table_cnt; i++) {
		if (param->flags == utool_debugfs_cmd_table[i].flags) {
			if (utool_debugfs_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch. Callback is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}
			return utool_debugfs_cmd(param, utool_debugfs_cmd_table[i].execute);
		}
	}

	utool_print_help();
	return UTOOL_ERR_CMD_NOT_FOUND;
}
