/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_PORT_LINK_H__
#define __U_UTOOL_PORT_LINK_H__

#include <time.h>
#include "u_utool_fwctl.h"
#include "u_utool_common.h"

int utool_port_link_parse_rpc_pkt(struct fwctl_rpc_ub_out *out);
int utool_port_link_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param);

#endif
