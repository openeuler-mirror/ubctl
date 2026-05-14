// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <errno.h>

#include "u_utool_error.h"
#include "u_utool_fwctl.h"

int utool_cmd_exec(struct utool_dev *dev, struct fwctl_rpc_ub_in *in, uint32_t inlen,
		   struct fwctl_rpc_ub_out *out, uint32_t *outlen)
{
#define UBCTL_MAX_OUT_LEN 0x200000
	struct fwctl_cmdrpc rpc = {};
	int ret = UTOOL_OK;

	if (dev == NULL || in == NULL || out == NULL || outlen == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), in==null(%d), out==null(%d), outlen==null(%d).\n",
			      (dev == NULL), (in == NULL), (out == NULL), (outlen == NULL));

		return UTOOL_ERR_INVALID_PARAM;
	}

	rpc.in = (__aligned_u64)(uintptr_t)(void *)in;
	rpc.inlen = inlen;
	rpc.out = (__aligned_u64)(uintptr_t)(void *)out;
	rpc.outlen = *outlen;
	rpc.size = sizeof(struct fwctl_cmdrpc);

	ret = ioctl(dev->fd, FWCTL_RPC, &rpc);
	if (ret != 0) {
		if (errno == ENOTTY) {
			utool_err_msg("The cmd is not supported at current env type.\n");
			return UTOOL_ERR_IOCTL;
		}
		utool_err_msg("Failed to interaction with the kernel, ret = %d, errno = %d.\n", ret, errno);
		return UTOOL_ERR_IOCTL;
	}

	if (rpc.outlen > UBCTL_MAX_OUT_LEN) {
		utool_err_msg("The out data is bigger than max size.\n");
		return UTOOL_ERR_IOCTL;
	}

	*outlen = rpc.outlen;

	return UTOOL_OK;
}
