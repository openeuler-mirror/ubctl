// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_tp_field_info.h"
#include "u_utool_tp.h"

#define TP_PKT_STATS "pkt_stats"
#define TP_ABN_STATS "abn_stats"
#define TP_ROUTE_RESULT "route_result"
#define TP_SCC_VERSION "scc_version"
#define TP_SCC_LOG "scc_log"
#define TP_SCC_DEBUG "scc_debug_en"

#define UTOOL_TX_PKT_STATS_CNT 226U
#define UTOOL_RX_PKT_STATS_CNT 176U
#define UTOOL_TX_ABN_STATS_CNT 11U
#define UTOOL_RX_ABN_STATS_CNT 14U
#define UTOOL_BONDING_REG_CNT 6U

#define UTOOL_SCC_LOG_DIR_PATH "/var/log/ubtool/operation_logs/"
#define UTOOL_SCC_LOG_FILE_PATH_MAX_LEN 256U
#define UTOOL_SCC_LOG_NAME_MAX_LEN 128U
#define UTOOL_SZ_1M 0x100000
#define UTOOL_SCC_LOG_CNT UTOOL_SZ_1M
#define UTOOL_SCC_CNT 24U
#define UTOOL_SCC_LOG_FILE_AUTHORITY 0440
#define UTOOL_SCC_LOG_PATH_AUTHORITY 0550
#define UTOOL_START_YEAR 1900

#define UTOOL_ABN_STATS_CNT (UTOOL_TX_PKT_STATS_CNT + UTOOL_RX_PKT_STATS_CNT + \
			     UTOOL_TX_ABN_STATS_CNT + UTOOL_RX_ABN_STATS_CNT + UTOOL_BONDING_REG_CNT)
#define UTOOL_ABN_STATS_LEN ((UTOOL_ABN_STATS_CNT) * (sizeof(uint32_t)))
#define UTOOL_PORT_CNT 1

struct utool_type_trans {
	char type_base;
	uint32_t type_size;
};

struct utool_cal_reg_table_dp {
	uint32_t func_cnt;
	struct utool_cal_reg_cnt_dp *reg_table;
};

static struct utool_cal_reg_table_dp *utool_tp_get_cal_reg_table(void)
{
#define INDEX0 0
#define INDEX1 1
#define INDEX2 2
#define INDEX3 3

	static struct utool_cal_reg_cnt_dp utool_tp_cal_reg_table[] = {
		{ true, true, TP_PKT_STATS, 0, NULL },
		{ false, false, TP_ABN_STATS, 0, NULL },
		{ true, true, TP_ROUTE_RESULT, 0, NULL },
		{ true, true, TP_RX_BANK, 0, NULL },
		{ false, false, TP_SCC_VERSION, 0, NULL },
		{ false, false, TP_SCC_LOG, 0, NULL },
		{ false, false, TP_SCC_DEBUG, 0, NULL },
	};
	static struct utool_cal_reg_table_dp cal_reg_table_dp = {};

	struct utool_field_info_dp *pkt_stats_field_info = NULL;
	struct utool_field_info_dp *abn_stats_field_info = NULL;
	struct utool_field_info_dp *route_result_field_info = NULL;
	struct utool_field_info_dp *rx_bank_field_info = NULL;

	pkt_stats_field_info = utool_tp_get_field_info_by_name(TP_PKT_STATS_FIELD_INFO);
	abn_stats_field_info = utool_tp_get_field_info_by_name(TP_ABN_STATS_FIELD_INFO);
	route_result_field_info = utool_tp_get_field_info_by_name(TP_TX_ROUTE_FIELD_INFO);
	rx_bank_field_info = utool_tp_get_field_info_by_name(TP_RX_BANK_FIELD_INFO);

	if ((pkt_stats_field_info == NULL) || (abn_stats_field_info == NULL) || (route_result_field_info == NULL) ||
	    (rx_bank_field_info == NULL)) {
		utool_err_msg("Failed to get field info.\n");
		return NULL;
	}

	utool_tp_cal_reg_table[INDEX0].field_cnt = pkt_stats_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX0].field_info = pkt_stats_field_info->field_info;
	utool_tp_cal_reg_table[INDEX1].field_cnt = abn_stats_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX1].field_info = abn_stats_field_info->field_info;
	utool_tp_cal_reg_table[INDEX2].field_cnt = route_result_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX2].field_info = route_result_field_info->field_info;
	utool_tp_cal_reg_table[INDEX3].field_cnt = rx_bank_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX3].field_info = rx_bank_field_info->field_info;

	cal_reg_table_dp.func_cnt = UTOOL_ARRAY_SIZE(utool_tp_cal_reg_table);
	cal_reg_table_dp.reg_table = utool_tp_cal_reg_table;

	return &cal_reg_table_dp;
}

int utool_tp_cal_data_len(uint32_t *tp_data_len)
{
	struct utool_cal_reg_func_param tp_cal_reg_param = { tp_data_len, UTOOL_REG_CNT_DEFAULT, NULL, NULL, 0 };
	struct utool_cal_reg_table_dp *cal_reg_table_dp = NULL;
	int ret = UTOOL_OK;

	if (tp_data_len == NULL) {
		utool_err_msg("Param is invalid, tp data len is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	cal_reg_table_dp = utool_tp_get_cal_reg_table();
	if (cal_reg_table_dp == NULL) {
		utool_err_msg("Failed to get cal reg table.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	tp_cal_reg_param.utool_cal_reg_table = cal_reg_table_dp->reg_table;
	tp_cal_reg_param.func_cnt = cal_reg_table_dp->func_cnt;

	ret = utool_cal_func_reg_len(UTOOL_FUNC_ALL, &tp_cal_reg_param);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate reg cnt, ret = %d.\n", ret);
		return ret;
	}

	*tp_data_len += UTOOL_ABN_STATS_CNT * sizeof(uint32_t);

	return UTOOL_OK;
}

static int utool_tp_parse_pkt_stats(struct fwctl_rpc_ub_out *tp_pkt_stats_out)
{
	struct utool_field_info_dp *pkt_stats_field_info = NULL;
	int ret = UTOOL_OK;

	pkt_stats_field_info = utool_tp_get_field_info_by_name(TP_PKT_STATS_FIELD_INFO);
	if (pkt_stats_field_info == NULL) {
		utool_err_msg("Failed to get pkt stats field info.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_pkt_parse(tp_pkt_stats_out, pkt_stats_field_info->field_cnt, pkt_stats_field_info->field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_TP, TP_PKT_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse tp pkt stats data.\n");
		return ret;
	}

	return UTOOL_OK;
}

static int ubtool_tp_abn_copy_data(struct fwctl_rpc_ub_out *abn_stats_out, struct fwctl_rpc_ub_out *tp_abn_stats_out,
				   uint32_t abn_cnt)
{
#define UTOOL_BONDING_PORT (UTOOL_TX_PKT_STATS_CNT + UTOOL_RX_PKT_STATS_CNT + \
			    UTOOL_TX_ABN_STATS_CNT + UTOOL_RX_ABN_STATS_CNT)

	uint32_t data_cnt = tp_abn_stats_out->data_size / sizeof(uint32_t);
	uint32_t *abn_data = NULL, *data = NULL;
	uint32_t abn_data_len = 0;
	uint32_t data_size = 0;
	uint32_t offset = 0;

	data = tp_abn_stats_out->data;
	abn_data = abn_stats_out->data;

	if (data_cnt <= UTOOL_BONDING_PORT) {
		utool_err_msg("Invalid out data cnt: %u.\n", data_cnt);
		return UTOOL_ERR_INVALID_PARAM;
	}
	abn_data[0] = data[UTOOL_BONDING_PORT];

	offset += UTOOL_TX_PKT_STATS_CNT;
	abn_data_len = (abn_cnt - UTOOL_PORT_CNT) * sizeof(uint32_t);
	data_size = UTOOL_TX_ABN_STATS_CNT * sizeof(uint32_t);
	memcpy(abn_data + UTOOL_PORT_CNT, data + offset, data_size);
	offset += UTOOL_TX_ABN_STATS_CNT + UTOOL_RX_PKT_STATS_CNT;
	data_size = abn_data_len - data_size;
	memcpy(abn_data + UTOOL_TX_ABN_STATS_CNT + UTOOL_PORT_CNT, data + offset, data_size);
	abn_stats_out->data_size = data_size + UTOOL_TX_ABN_STATS_CNT * sizeof(uint32_t);
	abn_stats_out->retval = 0;

	return UTOOL_OK;
}

static int utool_tp_parse_abn_stats(struct fwctl_rpc_ub_out *tp_abn_stats_out)
{
	uint32_t abn_cnt = UTOOL_TX_ABN_STATS_CNT + UTOOL_RX_ABN_STATS_CNT + UTOOL_BONDING_REG_CNT + UTOOL_PORT_CNT;
	uint32_t data_size = sizeof(struct fwctl_rpc_ub_out) + abn_cnt * sizeof(uint32_t);
	struct utool_field_info_dp *abn_stats_field_info = NULL;
	struct fwctl_rpc_ub_out *abn_stats_out = NULL;
	int ret = UTOOL_OK;

	abn_stats_field_info = utool_tp_get_field_info_by_name(TP_ABN_STATS_FIELD_INFO);
	if (abn_stats_field_info == NULL) {
		utool_err_msg("Failed to get abn stats field info.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	abn_stats_out = (struct fwctl_rpc_ub_out *)UTOOL_MALLOC(data_size);
	if (abn_stats_out == NULL) {
		utool_err_msg("Failed to malloc abn stats out, size = %u.\n", data_size);
		return UTOOL_ERR_MALLOC;
	}

	ret = ubtool_tp_abn_copy_data(abn_stats_out, tp_abn_stats_out, abn_cnt);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to copy abn data.\n");
		UTOOL_FREE(abn_stats_out);
		return ret;
	}

	ret = utool_pkt_parse(abn_stats_out, abn_stats_field_info->field_cnt, abn_stats_field_info->field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_TP, TP_ABN_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse tp abn stats data.\n");
	}

	UTOOL_FREE(abn_stats_out);
	return ret;
}

static int utool_tp_parse_route_result(struct fwctl_rpc_ub_out *tp_route_result_out)
{
	struct utool_field_info_dp *route_result_field_info = NULL;
	int ret = UTOOL_OK;

	route_result_field_info = utool_tp_get_field_info_by_name(TP_TX_ROUTE_FIELD_INFO);
	if (route_result_field_info == NULL) {
		utool_err_msg("Failed to get route result field info.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_pkt_parse(tp_route_result_out, route_result_field_info->field_cnt, route_result_field_info->field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_TP, TP_ROUTE_RESULT));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse tp route result data.\n");
		return ret;
	}

	return UTOOL_OK;
}

static int utool_tp_parse_rx_bank(struct fwctl_rpc_ub_out *tp_pkt_out)
{
	struct utool_field_info_dp *rx_bank1_field_info = NULL;
	struct utool_field_info_dp *rx_bank2_field_info = NULL;
	struct utool_field_info_dp *rx_bank_field_info = NULL;
	struct fwctl_rpc_ub_out *out_temp = NULL;
	uint32_t data_size = 0;
	void *out_data = NULL;
	int ret = UTOOL_OK;
	int i;

	rx_bank_field_info = utool_tp_get_field_info_by_name(TP_RX_BANK_FIELD_INFO);
	rx_bank1_field_info = utool_tp_get_field_info_by_name(TP_RX_BANK_FIELD_INFO_BANK1);
	rx_bank2_field_info = utool_tp_get_field_info_by_name(TP_RX_BANK_FIELD_INFO_BANK2);
	if ((rx_bank_field_info == NULL) || (rx_bank1_field_info == NULL) || (rx_bank2_field_info == NULL)) {
		utool_err_msg("Failed to get rx bank field info.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	struct utool_field_info *field_info[] = { rx_bank_field_info->field_info,
						  rx_bank1_field_info->field_info,
						  rx_bank2_field_info->field_info };
	uint32_t field_cnts[] = { rx_bank_field_info->field_cnt,
				  rx_bank1_field_info->field_cnt,
				  rx_bank2_field_info->field_cnt };

	data_size = tp_pkt_out->data_size / UBCTL_TP_RX_BANK_NUM;
	out_temp = (struct fwctl_rpc_ub_out *)UTOOL_MALLOC(sizeof(struct fwctl_rpc_ub_out) + data_size);
	if (out_temp == NULL) {
		utool_err_msg("Failed to malloc rpc out mem.\n");
		return UTOOL_ERR_MALLOC;
	}

	out_data = (void *)(tp_pkt_out->data);
	out_temp->retval = tp_pkt_out->retval;
	out_temp->data_size = data_size;
	for (i = 0; i < UBCTL_TP_RX_BANK_NUM; i++) {
		memcpy(out_temp->data, out_data, data_size);
		ret = utool_pkt_parse(out_temp, field_cnts[i], field_info[i], UTOOL_CONCAT_STR(UTOOL_MODULE_TP, TP_RX_BANK));
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to parse tp rx bank data.\n");
			break;
		}
		out_data += data_size;
	}
	UTOOL_FREE(out_temp);

	return ret;
}

static int utool_get_rand_str(char *str, int length)
{
#define TYPE_NUMBER 0
#define TYPE_UPPERCASE 1
#define TYPE_LOWERCASE 2
#define RANDOM_CHAR_TYPE_NUM 3U
#define RANDOM_NUM 2
#define TYPE_NUMBER_LEN 10
#define TYPE_UPPERCASE_LEN 26
#define TYPE_LOWERCASE_LEN 26
#define URANDOM_PATH "/dev/urandom"

	struct utool_type_trans type_arr[RANDOM_CHAR_TYPE_NUM] = {
		[TYPE_NUMBER] = {'0', TYPE_NUMBER_LEN},
		[TYPE_UPPERCASE] = {'A', TYPE_UPPERCASE_LEN},
		[TYPE_LOWERCASE] = {'a', TYPE_LOWERCASE_LEN},
	};
	uint32_t utool_rands[RANDOM_NUM] = {};
	uint32_t type;
	int fd, i, j;
	int size;

	fd = open(URANDOM_PATH, O_RDONLY);
	if (fd < 0) {
		utool_err_msg("Failed to open urand, errno is %d.\n", errno);
		return UTOOL_ERR_OPEN_FILE;
	}

	for (i = 0; i < (length - 1); i++) {
		for (j = 0; j < RANDOM_NUM; j++) {
			size = read(fd, &utool_rands[j], sizeof(uint32_t));
			if (size < 0) {
				utool_err_msg("Failed to read random, errno is %d.\n", errno);
				close(fd);
				return UTOOL_ERR_READ_FILE;
			}
		}

		type = utool_rands[0] % RANDOM_CHAR_TYPE_NUM;
		str[i] = type_arr[type].type_base + utool_rands[1] % type_arr[type].type_size;
	}

	close(fd);

	return UTOOL_OK;
}

static int utool_generate_file_name(char *file_name, uint32_t file_name_len, const char *prefix)
{
#define RANDOM_STR_LENGTH 7

	char str_rand[RANDOM_STR_LENGTH] = {};
	time_t time_seconds = time(0);
	struct tm timeinfo = {};
	int ret = UTOOL_OK;

	ret = utool_get_rand_str(str_rand, RANDOM_STR_LENGTH);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to get random string.\n");
		return ret;
	}

	if (localtime_r(&time_seconds, &timeinfo) == NULL) {
		utool_err_msg("Failed to get local time, errno = %d.\n", errno);
		return UTOOL_ERR;
	}

	ret = snprintf(file_name, file_name_len, "%s_%d_%d_%d_%d_%d_%d_%s.log", prefix,
		       timeinfo.tm_year + UTOOL_START_YEAR, timeinfo.tm_mon + 1, timeinfo.tm_mday,
		       timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, str_rand);
	if (ret <= 0 || ret >= (int)file_name_len) {
		utool_err_msg("Failed to generate file name, errno = %d, ret = %d.\n", errno, ret);
		return UTOOL_ERR;
	}

	return UTOOL_OK;
}

static int utool_tp_parse_scc_version(struct fwctl_rpc_ub_out *tp_scc_version_out)
{
	uint32_t *scc_version = NULL;

	scc_version = tp_scc_version_out->data;
	utool_reg_msg("scc_version: 0x%x\n", *scc_version);

	return UTOOL_OK;
}

static int utool_is_dir_exists(const char *file_path)
{
	struct stat st = {};
	int ret = UTOOL_ERR;

	if (stat(file_path, &st) == 0) {
		ret = (S_ISDIR(st.st_mode) != 0) ? UTOOL_OK : UTOOL_ERR;
	}

	return ret;
}

static int utool_mkdir(const char *path, mode_t mode)
{
	if (utool_is_dir_exists(path) == UTOOL_OK) {
		return UTOOL_OK;
	}

	if (mkdir(path, mode) < 0) {
		return UTOOL_ERR;
	}

	return UTOOL_OK;
}

static int utool_mkdir_p(const char *path, mode_t mode)
{
	char file_path[UTOOL_SCC_LOG_FILE_PATH_MAX_LEN];
	char *p = NULL;
	uint32_t len;
	int ret = 0;

	ret = snprintf(file_path, sizeof(file_path), "%s", path);
	if (ret <= 0 || ret >= (int)sizeof(file_path)) {
		utool_err_msg("Failed to get tmp file path, errno = %d, ret = %d.\n", errno, ret);
		return UTOOL_ERR;
	}

	len = strlen(file_path);
	if (file_path[len - 1] == '/') {
		file_path[len - 1] = '\0';
	}

	for (p = file_path + 1; *p != '\0'; p++) {
		if (*p == '/') {
			*p = '\0';
			if (utool_mkdir(file_path, mode) != UTOOL_OK) {
				return UTOOL_ERR;
			}
			*p = '/';
		}
	}

	if (utool_mkdir(file_path, mode) != UTOOL_OK) {
		return UTOOL_ERR;
	}
	return UTOOL_OK;
}

static int utool_tp_parse_scc_log(struct fwctl_rpc_ub_out *tp_scc_log_out)
{
#define TP_SCC_STR "scc"

	static char file_path[UTOOL_SCC_LOG_FILE_PATH_MAX_LEN] = {};
	static char file_name[UTOOL_SCC_LOG_NAME_MAX_LEN] = {};
	char *data = (char *)(tp_scc_log_out->data);
	int ret = UTOOL_OK;
	FILE *fp = NULL;

	if (file_path[0] == 0 && file_name[0] == 0) {
		if (utool_is_dir_exists(UTOOL_SCC_LOG_DIR_PATH) != UTOOL_OK) {
			ret = utool_mkdir_p(UTOOL_SCC_LOG_DIR_PATH, UTOOL_SCC_LOG_PATH_AUTHORITY);
			if (ret != 0) {
				utool_err_msg("Failed to mkdir file path, ret = %d.\n", ret);
				return UTOOL_ERR;
			}
		}

		ret = utool_generate_file_name(file_name, UTOOL_SCC_LOG_NAME_MAX_LEN, TP_SCC_STR);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to generate file name.\n");
			return ret;
		}

		ret = snprintf(file_path, sizeof(file_path), UTOOL_SCC_LOG_DIR_PATH"%s", file_name);
		if (ret <= 0 || ret >= (int)sizeof(file_path)) {
			utool_err_msg("Failed to create log file, errno = %d, ret = %d.\n", errno, ret);
			return UTOOL_ERR;
		}
	}

	fp = fopen(file_path, "a+");
	if (fp == NULL) {
		utool_err_msg("Failed to open file, errno = %d.\n", errno);
		return UTOOL_ERR_OPEN_FILE;
	}

	if (fwrite(data, sizeof(char), tp_scc_log_out->data_size, fp) <= 0) {
		utool_err_msg("Failed to write file, errno = %d.\n", errno);
		(void)chmod(file_path, UTOOL_SCC_LOG_FILE_AUTHORITY);
		(void)fclose(fp);
		return UTOOL_ERR_WRITE_FILE;
	}

	(void)chmod(file_path, UTOOL_SCC_LOG_FILE_AUTHORITY);
	(void)fclose(fp);

	return UTOOL_OK;
}

static int utool_tp_parse_scc_debug(struct fwctl_rpc_ub_out *tp_scc_debug_out)
{
	uint32_t *scc_debug = tp_scc_debug_out->data;

	utool_reg_msg("scc_debug_en: 0x%x\n", *scc_debug);

	return UTOOL_OK;
}

static int utool_scc_loop_call(struct utool_dev *dev, void *pkt_in, uint32_t pkt_in_len,
			       struct utool_cmd_param *param, struct utool_pkt_exec *pkt_exec)
{
#define UTOOL_SCC_NUM 2

	struct fwctl_pkt_in_index *ptr_pkt_in = (struct fwctl_pkt_in_index *)pkt_in;
	int ret = UTOOL_OK;
	uint32_t i;

	for (i = 0; i < UTOOL_SCC_NUM; i++) {
		ptr_pkt_in->index = i;
		ret = utool_pkt_operation(dev, ptr_pkt_in, pkt_in_len, pkt_exec);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to execute %s cmd, ret = %d.\n", param->func, ret);
			return ret;
		}
	}

	return ret;
}

static struct utool_func_dispatch g_utool_tp_mf_table[] = {
	{ true, TP_PKT_STATS, UTOOL_CMD_QUERY_TP_PKT_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_pkt_stats, utool_null_create_pkt_in },
	{ true, TP_ROUTE_RESULT, UTOOL_CMD_QUERY_TP_TX_ROUTE, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_route_result, utool_null_create_pkt_in },
	{ true, TP_RX_BANK, UTOOL_CMD_QUERY_TP_RX_BANK, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_rx_bank, utool_null_create_pkt_in },
	{ false, TP_SCC_VERSION, UTOOL_CMD_QUERY_SCC_VERSION, UTOOL_SCC_CNT,
	  utool_tp_parse_scc_version, utool_index_create_pkt_in },
	{ false, TP_SCC_LOG, UTOOL_CMD_QUERY_SCC_LOG, UTOOL_SCC_LOG_CNT,
	  utool_tp_parse_scc_log, utool_index_create_pkt_in },
	{ false, TP_SCC_DEBUG, UTOOL_CMD_QUERY_SCC_DEBUG_EN, UTOOL_SCC_CNT,
	  utool_tp_parse_scc_debug, utool_null_create_pkt_in },
};

static int utool_tp_dump_abn_stats(struct fwctl_rpc_ub_out *tp_out)
{
	uint32_t data_len = sizeof(struct fwctl_rpc_ub_out) + UTOOL_ABN_STATS_CNT * sizeof(uint32_t);
	uint32_t data_cnt = tp_out->data_size / sizeof(uint32_t);
	struct fwctl_rpc_ub_out *abn_out = NULL;
	uint32_t *data = tp_out->data;
	uint32_t *abn_data = NULL;
	int ret = UTOOL_OK;

	abn_out = (struct fwctl_rpc_ub_out *)UTOOL_MALLOC(data_len);
	if (abn_out == NULL) {
		utool_err_msg("Failed to malloc abn stats out, size = %u.\n", data_len);
		return UTOOL_ERR_MALLOC;
	}

	abn_data = abn_out->data;
	data += data_cnt - UTOOL_ABN_STATS_CNT;

	abn_out->data_size = UTOOL_ABN_STATS_LEN;
	memcpy(abn_data, data, UTOOL_ABN_STATS_LEN);
	abn_out->retval = 0;

	ret = utool_tp_parse_abn_stats(abn_out);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse tp abn stats data.\n");
	}

	UTOOL_FREE(abn_out);
	return ret;
}

int utool_tp_parse_rpc_pkt(struct fwctl_rpc_ub_out *tp_out)
{
	struct utool_cal_reg_table_dp *cal_reg_table_dp = NULL;
	int ret = UTOOL_OK;

	if (tp_out == NULL) {
		utool_err_msg("Param is invalid, tp out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	cal_reg_table_dp = utool_tp_get_cal_reg_table();
	if (cal_reg_table_dp == NULL) {
		utool_err_msg("Failed to get cal reg table.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_module_parse(tp_out, UTOOL_ARRAY_SIZE(g_utool_tp_mf_table), g_utool_tp_mf_table,
				 cal_reg_table_dp->func_cnt, cal_reg_table_dp->reg_table);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse tp rpc pkt.\n");
		return ret;
	}

	ret = utool_tp_dump_abn_stats(tp_out);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to dump tp abn stats data.\n");
	}

	return ret;
}

static void utool_tp_print_help(void)
{
	utool_err_msg("The ubctl tp command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m tp -p ${port}\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m tp -f pkt_stats/route_result/rx_bank/"
		      "scc_version/scc_log/scc_debug_en\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m tp -f abn_stats -p ${port}\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m tp -f scc_debug_en -e ${value}\n");
}

static int utool_handle_matched_func(struct utool_dev *dev, struct utool_cmd_param *param,
				     struct utool_func_dispatch *func_entry,
				     struct utool_cal_reg_func_param *tp_cal_reg_param)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_BUTT, 0, NULL };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret;

	func_pkt_exec.rpc_cmd = func_entry->rpc_cmd;
	func_pkt_exec.execute = func_entry->execute;

	tp_cal_reg_param->user_def_data_len = func_entry->data_len;

	ret = utool_cal_func_reg_len(param->func, tp_cal_reg_param);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to cal tp func %s reg cnt.\n", param->func);
		return ret;
	}

	func_pkt_exec.data_len = *tp_cal_reg_param->data_len;
	if (func_entry->create_pkt_in == NULL) {
		utool_err_msg("Failed to create tp func pkt in. Callback is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	pkt_in = func_entry->create_pkt_in(&pkt_in_len, param);
	if (pkt_in == NULL) {
		utool_err_msg("Failed to create pkt in.\n");
		return UTOOL_ERR_MALLOC;
	}

	if (strcmp(func_entry->func, TP_SCC_LOG) == 0) {
		ret = utool_scc_loop_call(dev, pkt_in, pkt_in_len, param, &func_pkt_exec);
		if (ret == UTOOL_OK) {
			utool_info_msg("Succeed to query scc log.\n");
		}
	} else {
		ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &func_pkt_exec);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to execute command, ret = %d.\n", ret);
		}
	}

	utool_destroy_pkt_in(&pkt_in);
	return ret;
}

static int utool_tp_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			     struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_cal_reg_table_dp *cal_reg_table_dp = utool_tp_get_cal_reg_table();
	struct utool_cal_reg_func_param tp_cal_reg_param = {};
	uint32_t data_len = 0;
	uint32_t i;

	if (cal_reg_table_dp == NULL) {
		utool_err_msg("Failed to get cal reg table.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	tp_cal_reg_param.utool_cal_reg_table = cal_reg_table_dp->reg_table;
	tp_cal_reg_param.func_cnt = cal_reg_table_dp->func_cnt;
	tp_cal_reg_param.data_len = &data_len;

	for (i = 0; i < func_cnt; i++) {
		if (strcmp(param->func, func_table[i].func) == 0) {
			return utool_handle_matched_func(dev, param, &func_table[i], &tp_cal_reg_param);
		}
	}

	utool_tp_print_help();
	return UTOOL_ERR_FUNC_NOT_FOUND;
}

static int utool_tp_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
			struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_TP, 0, NULL };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	func_pkt_exec.execute = utool_tp_parse_rpc_pkt;

	ret = utool_tp_cal_data_len(&func_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate reg cnt of all, ret = %d.\n", ret);
		return ret;
	}

	pkt_in = utool_port_create_pkt_in(&pkt_in_len, param);
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

int utool_tp_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	static struct utool_func_dispatch utool_tp_flag_mfe_table[] = {
		{ false, TP_SCC_DEBUG, UTOOL_CMD_CONF_SCC_DEBUG_EN, UTOOL_SCC_CNT,
		  utool_tp_parse_scc_debug, utool_enable_create_pkt_in },
	};
	static struct utool_func_dispatch utool_tp_flag_mfp_table[] = {
		{ false, TP_ABN_STATS, UTOOL_CMD_QUERY_TP_ABN_STATS, UTOOL_ABN_STATS_LEN,
		  utool_tp_parse_abn_stats, utool_port_create_pkt_in },
	};
	struct utool_cmd_dispatch utool_tp_cmd_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_F, utool_tp_cmd_func,
		  g_utool_tp_mf_table, UTOOL_ARRAY_SIZE(g_utool_tp_mf_table) },
		{ UTOOL_FLAG_M | UTOOL_FLAG_F | UTOOL_FLAG_P, utool_tp_cmd_func,
		  utool_tp_flag_mfp_table, UTOOL_ARRAY_SIZE(utool_tp_flag_mfp_table) },
		{ UTOOL_FLAG_M | UTOOL_FLAG_F | UTOOL_FLAG_E, utool_tp_cmd_func,
		  utool_tp_flag_mfe_table, UTOOL_ARRAY_SIZE(utool_tp_flag_mfe_table) },
		{ UTOOL_FLAG_M | UTOOL_FLAG_P, utool_tp_cmd, NULL, 0 },
	};
	uint32_t tp_cmd_cnt = UTOOL_ARRAY_SIZE(utool_tp_cmd_table);
	uint32_t i = 0;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < tp_cmd_cnt; i++) {
		if (param->flags == utool_tp_cmd_table[i].flags) {
			if (utool_tp_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch, execute is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}
			return utool_tp_cmd_table[i].execute(dev, param,
							     utool_tp_cmd_table[i].func_table,
							     utool_tp_cmd_table[i].func_cnt);
		}
	}

	utool_tp_print_help();

	return UTOOL_ERR_CMD_NOT_FOUND;
}
