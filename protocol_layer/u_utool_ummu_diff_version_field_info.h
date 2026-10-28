/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef U_UTOOL_UMMU_DIFF_VERSION_FIELD_INFO_H
#define U_UTOOL_UMMU_DIFF_VERSION_FIELD_INFO_H

#include "u_utool_ummu.h"

struct utool_insert_positions {
	uint32_t insert_position;
	uint32_t field_count;
};

const struct utool_field_info *utool_ummu_get_k1_only_field_info(void);
uint32_t utool_ummu_get_k1_only_field_count(void);
const struct utool_insert_positions *utool_ummu_get_insert_positions(void);
uint32_t utool_ummu_get_insert_positions_count(void);

#endif // U_UTOOL_UMMU_DIFF_VERSION_FIELD_INFO_H
