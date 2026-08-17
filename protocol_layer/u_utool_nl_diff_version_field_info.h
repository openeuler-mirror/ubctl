/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_NL_DIFF_VERSION_FIELD_INFO__
#define __U_UTOOL_NL_DIFF_VERSION_FIELD_INFO__

#include "../common/u_utool_fwctl.h"
#include "../common/u_utool_common.h"

struct utool_field_info *utool_nl_cmd_diff_ver_dispatch(const char *module_func_name,
							uint32_t reg_version, uint32_t reg_info_index,
							uint32_t *replace_field_cnt);

#endif
