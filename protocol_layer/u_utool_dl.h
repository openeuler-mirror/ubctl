/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_DL_H__
#define __U_UTOOL_DL_H__

#include "../common/u_utool_fwctl.h"
#include "../common/u_utool_common.h"

#define UTOOL_MAX_PORT 64U
#define DL_PERFORMANCE "performance"
#define DL_RT_BANDWIDTH "rt_bandwidth"
#define DL_PERF "perf"

int utool_dl_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param);
int utool_dl_cal_data_len(uint32_t *dl_data_len);
int utool_dl_parse_rpc_pkt(struct fwctl_rpc_ub_out *dl_out);

#endif
