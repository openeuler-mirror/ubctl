/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_DIFF_VERSION_H__
#define __U_UTOOL_DIFF_VERSION_H_

#include "u_utool_common.h"
#include "u_utool_fwctl.h"
#include "u_utool_pkt.h"

int utool_diff_version_pkt_parse(struct fwctl_rpc_ub_out *out, const char *module_func_name, uint32_t reg_index);

#endif
