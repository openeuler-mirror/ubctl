/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_FWCTL_H__
#define __U_UTOOL_FWCTL_H__

#include <stdint.h>
#include <sys/ioctl.h>

#include "./kernel_headers/fwctl.h"
#include "./kernel_headers/ub_fwctl.h"
#include "u_utool_common.h"

struct fwctl_cmdrpc {
	uint32_t size; /* sizeof(struct fwctl_rpc) */
	uint32_t scope; /* One of enum fwctl_rpc_scope, required scope for the RPC */
	uint32_t inlen; /* inbox buffer length */
	uint32_t outlen; /* outbox buffer length */
	__aligned_u64 in; /* RPC inbox buffer user */
	__aligned_u64 out; /* RPC outbox buffer user */
};

int utool_cmd_exec(struct utool_dev *dev, struct fwctl_rpc_ub_in *in, uint32_t inlen,
		   struct fwctl_rpc_ub_out *out, uint32_t *outlen);

#endif
