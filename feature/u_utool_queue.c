// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_queue.h"

#define UTOOL_MSGQ_NUM 4
#define UTOOL_QUEUE_REGS_NAME "queue_regs"

static struct utool_field_info g_utool_queue_field_info[] = {
	// opcode 0xA02F
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "imp_axi_mst_err_addr" },

	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ctrl_cpu_mgtq_twqe_pi(0)" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ctrl_cpu_mgtq_twqe_pi(1)" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ctrl_cpu_mgtq_twqe_pi(2)" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ctrl_cpu_mgtq_twqe_pi(3)" },

	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ctrl_cpu_mgtq_twqe_ci(0)" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ctrl_cpu_mgtq_twqe_ci(1)" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ctrl_cpu_mgtq_twqe_ci(2)" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ctrl_cpu_mgtq_twqe_ci(3)" },

	{ true, true, UTOOL_LOC27, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC24, UTOOL_LOC26, 0, UTOOL_CAP_ALL, "eth_mac_ni_map" },
	{ true, false, UTOOL_LOC21, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "ccua_ni_map" },
	{ true, false, UTOOL_LOC18, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "ccum_ni_map" },
	{ true, false, UTOOL_LOC15, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "muxpcs_ni_map" },
	{ true, false, UTOOL_LOC12, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "dlmac_ni_map" },
	{ true, false, UTOOL_LOC9, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "nl_ni_map" },
	{ true, false, UTOOL_LOC6, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "ba_ni_map" },
	{ true, false, UTOOL_LOC3, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "ta_ni_map" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "tp_ni_map" },

	{ true, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC9, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "msgq_ni_3_map" },
	{ true, false, UTOOL_LOC6, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "msgq_ni_2_map" },
	{ true, false, UTOOL_LOC3, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "msgq_ni_1_map" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "msgq_ni_0_map" },

	{ true, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "imp_ni_0_map" },

	{ true, true, UTOOL_LOC7, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC4, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "local_fhi_to_normal_en" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "local_eri_to_normal_en" },

	{ true, true, UTOOL_LOC7, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC4, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "aer_fhi_to_normal_en" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "aer_eri_to_normal_en" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "cq_int_set" },

	{ true, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "msgq_int_sel_0" },
	{ true, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "msgq_int_sel_1" },
	{ true, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "msgq_int_sel_2" },
	{ true, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "msgq_int_sel_3" },

	{ true, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "msgq_sec_mode" },
	// Maintained by IMP
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "g_ctrl_cpu_tx_pkt_pi" },

	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

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
	struct fwctl_rpc_ub_out *queue_reg_out = NULL;
	uint32_t reg_data_size = 0;
	uint32_t out_len, offset;
	int ret;
	int i;

	if (queue_out == NULL) {
		utool_err_msg("Failed to parse queue rpc pkt, queue_out==NULL.\n");
		return UTOOL_ERR_INVALID_CMD;
	}

	if (queue_out->data_size <= sizeof(struct utool_mgmtq_msgq_info)) {
		utool_err_msg("Data size = %ubytes, it must be bigger than the struct size %zubytes.\n",
			      queue_out->data_size, sizeof(struct utool_mgmtq_msgq_info));
		return UTOOL_ERR_INVALID_PARAM;
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

	reg_data_size = queue_out->data_size - sizeof(struct utool_mgmtq_msgq_info);
	out_len = sizeof(struct fwctl_rpc_ub_out) + reg_data_size;
	queue_reg_out = (struct fwctl_rpc_ub_out *)UTOOL_MALLOC(out_len);
	if (queue_reg_out == NULL) {
		utool_err_msg("Failed to malloc space.\n");
		return UTOOL_ERR_MALLOC;
	}

	queue_reg_out->data_size = reg_data_size;
	queue_reg_out->retval = queue_out->retval;
	queue_reg_out->env_version = queue_out->env_version;
	offset = sizeof(struct utool_mgmtq_msgq_info);

	memcpy(queue_reg_out->data, (void *)queue_out->data + offset, reg_data_size);
	ret = utool_pkt_parse(queue_reg_out, UTOOL_ARRAY_SIZE(g_utool_queue_field_info),
			      g_utool_queue_field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_QUEUE, UTOOL_QUEUE_REGS_NAME));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse queue data.\n");
	}

	UTOOL_FREE(queue_reg_out);
	return ret;
}

static int utool_queue_cal_data_len(uint32_t *data_len)
{
	uint32_t reg_cnt = 0;
	int ret = UTOOL_OK;

	ret = utool_cal_reg_cnt(g_utool_queue_field_info, UTOOL_ARRAY_SIZE(g_utool_queue_field_info), &reg_cnt);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate queue reg cnt.\n");
		return ret;
	}

	*data_len = reg_cnt * sizeof(uint32_t) + sizeof(struct utool_mgmtq_msgq_info);
	return UTOOL_OK;
}

static int utool_queue_cmd(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_pkt_exec queue_pkt_exec = { UTOOL_CMD_QUERY_QUEUE, 0, NULL };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	queue_pkt_exec.execute = utool_queue_parse_rpc_pkt;
	ret = utool_queue_cal_data_len(&queue_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate the reg cnt for queue, ret = %d.\n", ret);
		return ret;
	}

	pkt_in = utool_null_create_pkt_in(&pkt_in_len, param);
	if (pkt_in == NULL) {
		utool_err_msg("Failed to create pkt in.\n");
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
