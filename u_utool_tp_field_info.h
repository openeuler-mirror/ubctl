/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_TP_FIELD_INFO_H__
#define __U_UTOOL_TP_FIELD_INFO_H__

#include "u_utool_pkt.h"

#define TP_PKT_STATS_FIELD_INFO "utool_tp_pkt_stats_field_info"
#define TP_ABN_STATS_FIELD_INFO "utool_tp_abn_stats_field_info"
#define TP_TX_ROUTE_FIELD_INFO "utool_tp_tx_route_field_info"

struct utool_field_info_dp {
	char field_name[UTOOL_REG_NAME_MAX_LEN];
	uint32_t field_cnt;
	struct utool_field_info *field_info;
};

struct utool_field_info_dp *utool_tp_get_field_info_by_name(const char *field_name);

#endif
