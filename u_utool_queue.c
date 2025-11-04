// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_queue.h"

#define UTOOL_MSGQ_NUM 4
struct utool_mgmtq_msgq_info {
	uint32_t mgmtq_recv_cnt;
	uint32_t mgmtq_send_cnt;
	uint32_t mgmtq_recv_drop_cnt;
	uint32_t mgmtq_send_drop_cnt;
	uint32_t msgq_recv_sq_cnt[UTOOL_MSGQ_NUM];
	uint32_t msgq_send_rq_cnt[UTOOL_MSGQ_NUM];
	uint32_t msgq_send_cq_cnt[UTOOL_MSGQ_NUM];
	uint32_t msgq_recv_drop_cnt[UTOOL_MSGQ_NUM];
	uint32_t msgq_send_drop_cnt[UTOOL_MSGQ_NUM];
	uint32_t rsv[6];
};

static int utool_queue_parse_rpc_pkt(struct fwctl_rpc_ub_out *queue_out)
{
	struct utool_mgmtq_msgq_info *queue_stats = NULL;
	int i;

	if (queue_out == NULL) {
		utool_err_msg("Failed to parse queue rpc pkt, queue_out==NULL.\n");
		return UTOOL_ERR_INVALID_CMD;
	}

	queue_stats = (struct utool_mgmtq_msgq_info *)(queue_out->data);

	utool_reg_msg("mgmtq recv cnt: 0x%x\n", queue_stats->mgmtq_recv_cnt);
	utool_reg_msg("mgmtq send cnt: 0x%x\n", queue_stats->mgmtq_send_cnt);
	utool_reg_msg("mgmtq recv drop cnt: 0x%x\n", queue_stats->mgmtq_recv_drop_cnt);
	utool_reg_msg("mgmtq send drop cnt: 0x%x\n", queue_stats->mgmtq_send_drop_cnt);

	for (i = 0; i < UTOOL_MSGQ_NUM; i++) {
		utool_reg_msg("msgq%d recv sq cnt: 0x%x\n", i, queue_stats->msgq_recv_sq_cnt[i]);
		utool_reg_msg("msgq%d send rq cnt: 0x%x\n", i, queue_stats->msgq_send_rq_cnt[i]);
		utool_reg_msg("msgq%d send cq cnt: 0x%x\n", i, queue_stats->msgq_send_cq_cnt[i]);
		utool_reg_msg("msgq%d recv drop cnt: 0x%x\n", i, queue_stats->msgq_recv_drop_cnt[i]);
		utool_reg_msg("msgq%d send drop cnt: 0x%x\n", i, queue_stats->msgq_send_drop_cnt[i]);
	}

	return UTOOL_OK;
}

static int utool_queue_cmd(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_pkt_exec queue_pkt_exec = { UTOOL_CMD_QUERY_QUEUE, 0, NULL };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	queue_pkt_exec.data_len = sizeof(struct utool_mgmtq_msgq_info);

	queue_pkt_exec.execute = utool_queue_parse_rpc_pkt;
	pkt_in = utool_null_create_pkt_in(&pkt_in_len, param);
	if (pkt_in == NULL) {
		utool_err_msg("Failed to create pkt_in.\n");
		return UTOOL_ERR_MALLOC;
	}

	ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &queue_pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute queue cmd, ret = %d.\n", ret);
	}
	utool_destroy_pkt_in(&pkt_in);

	return ret;
}

int utool_queue_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	uint32_t queue_flags = UTOOL_FLAG_M;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Failed to dispatch queue, dev==NULL(%d), param==NULL(%d).\n",
			      (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (param->flags == queue_flags) {
		return utool_queue_cmd(dev, param);
	}

	utool_err_msg("The ubctl queue command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m queue\n");

	return UTOOL_ERR_CMD_NOT_FOUND;
}
