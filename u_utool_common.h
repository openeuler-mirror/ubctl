/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_COMMON_H__
#define __U_UTOOL_COMMON_H__

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <linux/types.h>

#include "./kernel_headers/ub_fwctl.h"

#define UTOOL_VERSION 0

#define UBCTL_ARG_MAX_LEN 20
#define UTOOL_LINE_BUF_LEN 300
#define UTOOL_DEV_NAME_LEN_MAX 512
#define UTOOL_DEV_CHIP_DIE_ID_MAX (1U << 16)
#define UTOOL_REG_CNT_DEFAULT 0U

#define UTOOL_BIT(shift) (1U << (shift))

#define UTOOL_ARRAY_SIZE(arr) (uint32_t)(sizeof(arr) / sizeof((arr)[0]))

#define UTOOL_CONCAT_STR(str1, str2) (str1 "-" str2)
#define UTOOL_SET_USED(x) (void)(x)

#define UTOOL_FLAG_M UTOOL_BIT(0) /* -m */
#define UTOOL_FLAG_P UTOOL_BIT(1) /* -p */
#define UTOOL_FLAG_F UTOOL_BIT(2) /* -f */
#define UTOOL_FLAG_E UTOOL_BIT(3) /* -e */

#define UTOOL_MALLOC(length) malloc(length)
#define UTOOL_FREE(x)			\
do {					\
	if ((x) != NULL) {		\
		free((void *)(x));	\
		(x) = NULL;		\
	}				\
} while (0)

#define UTOOL_EXTRACT_BITS(value, start, end) \
	(((value) >> (start)) & ((1UL << ((end) - (start) + 1)) - 1))

#define utool_err_msg(fmt, ...) \
	fprintf(stderr, "ERROR : " fmt, ##__VA_ARGS__)

#define utool_info_msg(fmt, ...) \
	fprintf(stdout, "INFO : " fmt, ##__VA_ARGS__)

#define utool_warn_msg(fmt, ...) \
	fprintf(stdout, "WARN : " fmt, ##__VA_ARGS__)

#define utool_reg_msg(fmt, ...) \
	fprintf(stdout, fmt, ##__VA_ARGS__)

#define UTOOL_FUNC_ALL "all"
#define UTOOL_MODULE_DL "dl"
#define UTOOL_MODULE_NL "nl"
#define UTOOL_MODULE_TA "ta"
#define UTOOL_MODULE_TP "tp"

enum utool_module_name {
	UTOOL_MODULE_NAME_DL,
	UTOOL_MODULE_NAME_NL,
	UTOOL_MODULE_NAME_TA,
	UTOOL_MODULE_NAME_TP,

	UTOOL_MODULE_NAME_BUTT,
};

enum utool_reg_location {
	UTOOL_REG_LOC0,
	UTOOL_REG_LOC1,
	UTOOL_REG_LOC2,
	UTOOL_REG_LOC3,
	UTOOL_REG_LOC4,
	UTOOL_REG_LOC5,
	UTOOL_REG_LOC6,
	UTOOL_REG_LOC7,
	UTOOL_REG_LOC8,
	UTOOL_REG_LOC9,
	UTOOL_REG_LOC10,
	UTOOL_REG_LOC11,
	UTOOL_REG_LOC12,
	UTOOL_REG_LOC13,
	UTOOL_REG_LOC14,
	UTOOL_REG_LOC15,
	UTOOL_REG_LOC16,
	UTOOL_REG_LOC17,
	UTOOL_REG_LOC18,
	UTOOL_REG_LOC19,
	UTOOL_REG_LOC20,
	UTOOL_REG_LOC21,
	UTOOL_REG_LOC22,
	UTOOL_REG_LOC23,
	UTOOL_REG_LOC24,
	UTOOL_REG_LOC25,
	UTOOL_REG_LOC26,
	UTOOL_REG_LOC27,
	UTOOL_REG_LOC28,
	UTOOL_REG_LOC29,
	UTOOL_REG_LOC30,
	UTOOL_REG_LOC31 = 31,
};

struct utool_dev {
	char devname[UTOOL_DEV_NAME_LEN_MAX];
	int32_t fd;
};

struct utool_cmd_param {
	uint32_t port;
	uint32_t flags;
	uint32_t chip_id;
	uint32_t die_id;
	uint32_t module_id;
	uint32_t value;
	char func[UBCTL_ARG_MAX_LEN];
	char module[UBCTL_ARG_MAX_LEN];
};

struct utool_module_dispatch {
	char module_name[UBCTL_ARG_MAX_LEN];
	uint32_t module_flags;
	int (*execute)(struct utool_dev *dev, struct utool_cmd_param *param);
};

struct utool_func_dispatch {
	bool is_dump;
	char func[UBCTL_ARG_MAX_LEN];
	enum ub_fwctl_cmdrpc_type rpc_cmd;
	uint32_t data_len;
	int (*execute)(struct fwctl_rpc_ub_out *out);
	void *(*create_pkt_in)(uint32_t *pkt_in_len, struct utool_cmd_param *param);
};

struct utool_cmd_dispatch {
	uint32_t flags;
	int (*execute)(struct utool_dev *dev, struct utool_cmd_param *param,
		       struct utool_func_dispatch *func_table, uint32_t func_cnt);
	struct utool_func_dispatch *func_table;
	uint32_t func_cnt;
};

struct utool_cmd_option_parse {
	char option;
	int (*cmd_select_func) (char *param);
};

#endif
