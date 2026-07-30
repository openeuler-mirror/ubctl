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

static void utool_handle_eopnotsupp_error(uint32_t rpc_cmd)
{
	switch (rpc_cmd) {
		case UTOOL_CMD_CONF_NL_SSU_VL_PKT:
		case UTOOL_CMD_QUERY_NL_SSU_VL_PKT:
		case UTOOL_CMD_QUERY_LOOPBACK:
		case UTOOL_CMD_CONF_LOOPBACK:
		case UTOOL_CMD_QUERY_PRBS_EN:
		case UTOOL_CMD_CONF_PRBS_EN:
		case UTOOL_CMD_QUERY_PRBS_RESULT:
			utool_err_msg("The cmd(%#x) is not supported at current port type(UB).\n", rpc_cmd);
			break;
		case UTOOL_CMD_QUERY_DL:
		case UTOOL_CMD_QUERY_DL_PKT_STATS:
		case UTOOL_CMD_QUERY_DL_LINK_STATUS:
		case UTOOL_CMD_QUERY_DL_LANE:
		case UTOOL_CMD_QUERY_DL_BIT_ERR:
		case UTOOL_CMD_QUERY_DL_LINK_TRACE:
		case UTOOL_CMD_QUERY_DL_BIST:
		case UTOOL_CMD_CONF_DL_BIST:
		case UTOOL_CMD_QUERY_DL_BIST_ERR:
		case UTOOL_CMD_QUERY_DL_PERFORMANCE:
		case UTOOL_CMD_QUERY_DL_RT_BANDWIDTH:
		case UTOOL_CMD_QUERY_DL_PERF_START:
		case UTOOL_CMD_QUERY_DL_PERF:
		case UTOOL_CMD_QUERY_DL_PERF_STOP:
			utool_err_msg("The cmd(%#x) is not supported at current port type(UBOE).\n", rpc_cmd);
			break;
		default:
			utool_err_msg("Failed to interaction with the kernel.\n");
			break;
	}
}

static void utool_handle_ioctl_errors(int errno_value, uint32_t rpc_cmd)
{
	if (errno_value == ENOTTY) {
		utool_err_msg("The cmd(%#x) is not supported at current env type.\n", rpc_cmd);
		return;
	}

	if (errno_value == EOPNOTSUPP) {
		utool_handle_eopnotsupp_error(rpc_cmd);
		return;
	}
}

int utool_cmd_exec(struct utool_dev *dev, struct fwctl_rpc_ub_in *in, uint32_t inlen,
		   struct fwctl_rpc_ub_out *out, uint32_t *outlen)
{
#define UBCTL_MAX_OUT_LEN 0x200000U
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
		utool_handle_ioctl_errors(errno, in->rpc_cmd);
		utool_err_msg("Failed to interaction with the kernel, ret = %d, errno = %d.\n", ret, errno);
		return UTOOL_ERR_IOCTL;
	}

	if (out->retval == -EACCES) {
		utool_err_msg("Permission denied: root user required for configuration commands.\n");
		return UTOOL_ERR_IOCTL;
	}

	if (rpc.outlen > UBCTL_MAX_OUT_LEN) {
		utool_err_msg("The out data size = %ubytes is bigger than max size = %ubytes.\n",
			      rpc.outlen, UBCTL_MAX_OUT_LEN);
		return UTOOL_ERR_IOCTL;
	}

	*outlen = rpc.outlen;

	return UTOOL_OK;
}
