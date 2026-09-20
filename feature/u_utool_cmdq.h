/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_CMDQ_H__
#define __U_UTOOL_CMDQ_H__

#include "../common/u_utool_fwctl.h"
#include "../common/u_utool_common.h"

int utool_cmdq_cal_data_len(uint32_t *cmdq_data_len);
int utool_cmdq_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param);
int utool_cmdq_parse_rpc_pkt(struct fwctl_rpc_ub_out *cmdq_out);

#endif
