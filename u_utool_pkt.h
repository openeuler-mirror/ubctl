/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_PKT_H__
#define __U_UTOOL_PKT_H__

#include <stdbool.h>

#include "./common/u_utool_fwctl.h"
#include "./common/u_utool_common.h"
#include "./common/u_utool_create_pkt_in.h"

#define UTOOL_INDEX_1 1

#define UTOOL_REG_MAX_LEN 32U
#define UTOOL_REG_NAME_MAX_LEN 256U

#define TP_RX_BANK "rx_bank"
#define UBCTL_TP_RX_BANK_NUM 3

/* Applicable to all environmental types. */
struct utool_field_info {
	bool is_high_before; /* true：high_before， false: low_before */
	bool is_reserved;
	uint8_t start;
	uint8_t end;
	uint8_t index;
	uint8_t cap_bitmap;
	char reg_name[UTOOL_REG_NAME_MAX_LEN];
};

struct utool_diff_version_field_info {
	const char module_func_name[UTOOL_REG_NAME_MAX_LEN];
	uint32_t reg_version;
	uint32_t reg_info_index;
	struct utool_field_info *replace_field_info;
	uint32_t replace_field_cnt;
};

struct utool_get_diff_version_field_info {
	const char module_func_name[UTOOL_REG_NAME_MAX_LEN];
	struct utool_field_info *(*get_diff_ver_field_info)(const char *module_func_name,
							    uint32_t reg_version, uint32_t reg_info_index,
							    uint32_t *replace_field_cnt);
};

struct utool_pkt_exec {
	enum ub_fwctl_cmdrpc_type rpc_cmd;
	uint32_t data_len;
	int (*execute)(struct fwctl_rpc_ub_out *out);
};

struct utool_cal_reg_cnt_dp {
	bool is_read_reg;
	bool is_dump;
	char func[UBCTL_ARG_MAX_LEN];
	uint32_t field_cnt;
	struct utool_field_info *field_info;
};

struct utool_cal_reg_func_param {
	uint32_t *data_len;
	uint32_t user_def_data_len;
	uint32_t *offset_data_len;
	struct utool_cal_reg_cnt_dp *utool_cal_reg_table;
	uint32_t func_cnt;
};

int utool_cal_func_reg_len(const char *func_name, struct utool_cal_reg_func_param *cal_reg_param);
void utool_pkt_print(bool is_reserved, const char *reg_name, uint64_t merge_data, uint8_t cap_bitmap, uint32_t env_ver);
int utool_module_parse(struct fwctl_rpc_ub_out *out,
		       uint32_t func_table_cnt, struct utool_func_dispatch *func_table,
		       uint32_t cal_reg_table_cnt, struct utool_cal_reg_cnt_dp *cal_reg_table);
int utool_pkt_parse(struct fwctl_rpc_ub_out *out, uint32_t field_cnt,
		    struct utool_field_info *field_info, const char *module_func_name);
int utool_pkt_operation(struct utool_dev *dev, void *pkt_in, uint32_t pkt_in_len, struct utool_pkt_exec *pkt_exec);
int utool_cal_reg_cnt(struct utool_field_info *field_info, uint32_t field_cnt, uint32_t *reg_cnt);
void utool_destroy_pkt_in(void **pkt_in);
int utool_pkt_operation_have_port(struct utool_dev *dev, struct utool_cmd_param *param,
				  struct utool_pkt_exec *pkt_exec);
#endif
