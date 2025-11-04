/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_BA_H__
#define __U_UTOOL_BA_H__

#include "u_utool_fwctl.h"
#include "u_utool_common.h"

int utool_ba_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param);
int utool_ba_cal_data_len(uint32_t *ba_data_len);
int utool_ba_parse_rpc_pkt(struct fwctl_rpc_ub_out *ba_out);

#endif
