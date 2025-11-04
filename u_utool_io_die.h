/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_IO_DIE_H__
#define __U_UTOOL_IO_DIE_H__

#include "u_utool_common.h"
#include "u_utool_fwctl.h"

struct fwctl_port_info {
	uint32_t port_id;
	uint32_t link_status;
	uint32_t link_state_info;
	uint32_t port_type;
	uint32_t reserved[2];
};

struct fwctl_io_die_info {
	uint32_t port_count;
	uint32_t chip_id;
	uint32_t die_id;
	uint32_t reserved[3];
	struct fwctl_port_info port_info[0];
};

int utool_io_die_cmd(struct utool_dev *dev, struct utool_cmd_param *param);
int utool_io_die_parse_rpc_pkt(struct fwctl_rpc_ub_out *out);
uint32_t utool_get_ubctl_id(void);

#endif
