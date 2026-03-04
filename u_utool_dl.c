// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_error.h"
#include "u_utool_dl.h"
#include "u_utool_pkt.h"

#define DL_PKT_STATS "pkt_stats"
#define DL_LINK_STATUS "link_status"
#define DL_LANE "lane"
#define DL_BIT_ERR "bit_err"
#define DL_BIST "bist"
#define DL_BIST_ERR "bist_err"
#define DL_LINK_TRACE "link_trace"
#define DL_RT_BANDWIDTH "rt_bandwidth"

#define UTOOL_TRACE_4K 0x0001000
#define UTOOL_MAX_PORT 64U
#define UBCTL_MAX_QUERY_NUM 2

struct utool_rt_bandwidth_info {
	uint32_t port_id;
	uint32_t is_valid;
	uint64_t tx_bandwidth;
	uint64_t rx_bandwidth;
};
static uint32_t g_query_rt_bw_num = 0;
static struct utool_rt_bandwidth_info *g_rt_bw_result_data[UBCTL_MAX_QUERY_NUM];

static struct utool_field_info g_utool_pkt_stats_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl0_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl0_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl1_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl1_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl2_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl2_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl3_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl3_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl4_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl4_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl5_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl5_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl6_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl6_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl7_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl7_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl8_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl8_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl9_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl9_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl10_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl10_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl11_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl11_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl0_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl0_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl1_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl1_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl2_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl2_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl3_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl3_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl4_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl4_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl5_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl5_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl6_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl6_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl7_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl7_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl8_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl8_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl9_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl9_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl10_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl10_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl11_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl11_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_busi_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_busi_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_busi_block_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_busi_block_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_busi_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_busi_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_busi_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_busi_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_busi_block_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_busi_block_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_busi_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_busi_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_ctrl_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_ctrl_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_ctrl_pkt_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_ctrl_pkt_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_ctrl_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_ctrl_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_ctrl_pkt_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_ctrl_pkt_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl0_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl0_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl1_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl1_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl2_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl2_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl3_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl3_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl4_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl4_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl5_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl5_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl6_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl6_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl7_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl7_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl8_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl8_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl9_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl9_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl10_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl10_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl11_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl11_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl0_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl0_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl1_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl1_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl2_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl2_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl3_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl3_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl4_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl4_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl5_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl5_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl6_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl6_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl7_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl7_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl8_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl8_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl9_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl9_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl10_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl10_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl11_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl11_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_recv_ack_flit" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_recv_ack_flit" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_send_ack_flit" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_send_ack_flit" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "retry_req_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "retry_req_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "retry_ack_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "retry_ack_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "crc_error_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "crc_error_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl12_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl12_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl13_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl13_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl14_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl14_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl15_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl15_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl12_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl12_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl13_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl13_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl14_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl14_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl15_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl15_pkt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl12_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl12_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl13_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl13_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl14_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl14_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_vl15_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_vl15_from_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl12_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl12_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl13_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl13_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl14_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl14_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_vl15_to_nl_crd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_vl15_to_nl_crd" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn0_exist_num" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn1_exist_num" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn2_exist_num" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn3_exist_num" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn4_exist_num" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn5_exist_num" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn6_exist_num" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn7_exist_num" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn8_exist_num" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn9_exist_num" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn10_exist_num" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn11_exist_num" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_ack_exist_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn12_exist_num" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_crd_vn13_exist_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_crd_vn14_exist_num" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_crd_vn15_exist_num" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_err_pkt_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_pkt_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_norm_pkt_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_pkt_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_norm_err_pkt_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_err_pkt_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_short_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_long_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_mode_err_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_norm_short_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_norm_long_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_norm_mode_err_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_short_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_mode_err_pkt_cnt" },

	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_tx_norm_long_pkt_chk_en" },
	{ false, false, UTOOL_REG_LOC30, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "pfa_tx_norm_short_pkt_chk_en" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC29, UTOOL_FIELD_INDEX_START, "pfa_tx_norm_short_pkt_len" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "pfa_tx_fast_long_pkt_chk_en" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "pfa_tx_fast_short_pkt_chk_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "pfa_tx_fast_short_pkt_len" },

	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "pfa_rx_short_pkt_chk_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "pfa_rx_short_pkt_len" },

	{ false, true, UTOOL_REG_LOC9, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "pfa_rx_pkt_rate_chk_en" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "pfa_tx_norm_pkt_rate_chk_en" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "pfa_tx_fast_pkt_rate_chk_en" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "pfa_rx_pkt_mode_chk_en" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "pfa_tx_norm_pkt_mode_chk_en" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "pfa_tx_fast_pkt_mode_chk_en" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "pfa_rx_pkt_bounds_chk_en" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "pfa_tx_norm_pkt_bounds_chk_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "pfa_tx_fast_pkt_bounds_chk_en" },

	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_length_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_length_fifo_full" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_length_fifo_empty" },
	{ false, true, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_data_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_data_fifo_full" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_data_fifo_empty" },

	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_fast_crd_cnt" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_dropind_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_dropind_fifo_full" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_dropind_fifo_empty" },
	{ false, true, UTOOL_REG_LOC14, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_err_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_err_fifo_full" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_err_fifo_empty" },
	{ false, true, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_data_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_data_fifo_full" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_data_fifo_empty" },

	{ false, true, UTOOL_REG_LOC22, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_lng_bp" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_sht_bp" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_norm_bp" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_lng_pause_send" },
	{ false, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "pfa_dfx_nl_linkdown_flag" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_norm_pause_send" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_pause_send" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_bp" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "pfa_dfx_rx_fast_bp" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "pfa_dfx_port_200g_en" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "pfa_dfx_port_400g_en" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "pfa_dfx_dl_link_state" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "pfa_dfx_pkt_crc_mode" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "pfa_dfx_pkt_rate_mode" },

	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_sht_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_sht_fifo_full" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_sht_fifo_empty" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_lng_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_lng_fifo_full" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_lng_fifo_empty" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_norm_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_norm_fifo_full" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_norm_fifo_empty" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_lng_pkt_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_lng_err_pkt_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_lng_short_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_lng_long_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_tx_fast_lng_mode_err_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_dfx_dynamic_cg_status" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dlmac_ras_int_dl" },
	{ false, true, UTOOL_REG_LOC7, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "buf_ouf" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "illegal_flit" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "num_free_buf_ouf" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "crd_ouf" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "ack_ouf" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "lrsm_into_abort" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "link_up" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "phy_link_up" },
	{ false, true, UTOOL_REG_LOC29, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC28, UTOOL_FIELD_INDEX_START, "cur_port_type" },
	{ false, true, UTOOL_REG_LOC26, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC25, UTOOL_FIELD_INDEX_START, "lstm_state" },
	{ false, true, UTOOL_REG_LOC17, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "cur_rx_link_wid" },
	{ false, true, UTOOL_REG_LOC9, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "cur_tx_link_wid" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "cur_link_speed" },
	{ false, true, UTOOL_REG_LOC4, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "link_layer_credit_stall" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "init_cfg_done" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "link_layer_credit_refund_stall" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "link_layer_init_stall" },
	{ false, true, UTOOL_REG_LOC19, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "cca_cur_st" },
	{ false, true, UTOOL_REG_LOC14, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "num_phy_reinit" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "num_retry" },
	{ false, true, UTOOL_REG_LOC5, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "rrsm_cur_st" },
	{ false, true, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "lrsm_cur_st" },
	{ false, true, UTOOL_REG_LOC2, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "link_cur_st" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "phy_reinit_cnt" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC21, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "retry_buff_full" },
	{ false, true, UTOOL_REG_LOC17, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "retry_buff_afull" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "link_layer_retry_queue_consumed" },
	{ false, true, UTOOL_REG_LOC22, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "cfg_recv_retry_count_mode" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "cfg_nop_wr_en" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "cfg_nop_wr_retry_buf" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "cfg_after_drst_retry_enable" },
	{ false, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "cfg_hpcs_reinit_enable" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "cfg_retry_abort_enable" },
	{ false, true, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "cfg_max_num_phy_reinit" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "cfg_max_num_retry" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "cfg_retry_ctrl_flit_length" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cfg_mac_training_start" },
	{ false, true, UTOOL_REG_LOC3, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "cfg_full_lane_link" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "cfg_order_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cfg_full_lane_order_en" },
	{ false, true, UTOOL_REG_LOC5, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "cfg_scram_poly_mode" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cfg_scram_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_scram_seed_l0_low" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "cfg_scram_seed_l0_high" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_scram_seed_l1_low" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "cfg_scram_seed_l1_high" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_scram_seed_l2_low" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "cfg_scram_seed_l2_high" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_scram_seed_l3_low" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "cfg_scram_seed_l3_high" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "cfg_tx_margin_mask" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "cfg_remote_txidle_exit_mask" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cfg_alos_mask" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "cfg_qdlws_rx_adapt_mode" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "rxeq_mode_bypass" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "cfg_link_idle_electrical" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cfg_rxeq_mode" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_link_ltssm_control" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_link_control" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cfg_link_ctrl_icg" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "port_change_lane" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "port_change_speed" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "port_detect_ei" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "port_soft_retrain" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "port_dl_retrain" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "port_fec_err" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "port_recv_edf" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "port_deskew_overflow" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "port_asyn_buf_overflow" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "port_am_loss" },
	{ false, true, UTOOL_REG_LOC4, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "cfg_mac_pwr_chg_fast_en" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "cfg_mac_spd_chg_fast_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "cfg_mac_link_fast_en" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_send_null_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_send_ctsb_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "st_ub_link_fsm_history0" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "st_ub_cnt_link_idle" },
	{ false, true, UTOOL_REG_LOC3, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "st_port_en" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "st_dl2mac_link_down" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "st_link_rdy" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cfg_mux_dlphy_port_en" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "cfg_ub_mac_switch" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cfg_ub_link_ctrl_switch" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "muxpcs_st_of_cfg_linkdown_stall" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "muxpcs_st_of_cfg_linkdown_done" },
	{ false, true, UTOOL_REG_LOC4, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "muxpcs_cfg_linkdown_stall" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "muxpcs_cfg_linkdown_timeout" },
	{ false, true, UTOOL_REG_LOC12, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "cfg_rate_speed3_width" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "cfg_rate_speed2_width" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "cfg_rate_speed1_width" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "cfg_rate_speed0_width" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "muxpcs_cfg_port_en_dly_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "muxpcs_cfg_rst_dly_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "muxpcs_ras_int_macmux" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_pcs_idle_exit_pwr_en" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "cfg_pcs_idle_pwr_en" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_pcs_pwr_en" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cfg_sds_pwr_mode" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "cfg_rx_powrstate_code" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "cfg_txrx_powrstate_code" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "st_rx_lanes_am_sdf" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "st_rx_lanes_am_lock" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "st_pcs_rx_am_dec_period(lane0)" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "st_pcs_rx_am_lane_reverse(lane0)" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "st_pcs_rx_am_det_pn(lane0)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "st_pcs_rx_am_lane_id(lane0)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "st_pcs_rx_am_dec_period(lane1)" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "st_pcs_rx_am_lane_reverse(lane1)" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "st_pcs_rx_am_det_pn(lane1)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "st_pcs_rx_am_lane_id(lane1)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "st_tx_lanes_data_err" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "st_tx_lanes_data_running" },

	{ false, true, UTOOL_REG_LOC25, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC24, UTOOL_FIELD_INDEX_START, "st_p2s_tx_common_disalbe(lane0)" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "st_p2s_rx_eidetect_disalbe(lane0)" },
	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "st_p2s_tx_beacon_en(lane0)" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "st_p2s_detect_rx_en(lane0)" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "st_p2s_rxeq_coars_tune(lane0)" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "st_p2s_rxeq_fine_tune(lane0)" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "st_p2s_tx_idle_en(lane0)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "st_p2s_rxpowerstate(lane0)" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "st_p2s_powerstate(lane0)" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "st_p2s_rxdatarate(lane0)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "st_p2s_datarate(lane0)" },

	{ false, true, UTOOL_REG_LOC25, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC24, UTOOL_FIELD_INDEX_START, "st_p2s_tx_common_disalbe(lane1)" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "st_p2s_rx_eidetect_disalbe(lane1)" },
	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "st_p2s_tx_beacon_en(lane1)" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "st_p2s_detect_rx_en(lane1)" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "st_p2s_rxeq_coars_tune(lane1)" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "st_p2s_rxeq_fine_tune(lane1)" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "st_p2s_tx_idle_en(lane1)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "st_p2s_rxpowerstate(lane1)" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "st_p2s_powerstate(lane1)" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "st_p2s_rxdatarate(lane1)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "st_p2s_datarate(lane1)" },

	{ false, true, UTOOL_REG_LOC25, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC24, UTOOL_FIELD_INDEX_START, "st_p2s_tx_common_disalbe(lane2)" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "st_p2s_rx_eidetect_disalbe(lane2)" },
	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "st_p2s_tx_beacon_en(lane2)" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "st_p2s_detect_rx_en(lane2)" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "st_p2s_rxeq_coars_tune(lane2)" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "st_p2s_rxeq_fine_tune(lane2)" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "st_p2s_tx_idle_en(lane2)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "st_p2s_rxpowerstate(lane2)" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "st_p2s_powerstate(lane2)" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "st_p2s_rxdatarate(lane2)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "st_p2s_datarate(lane2)" },

	{ false, true, UTOOL_REG_LOC25, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC24, UTOOL_FIELD_INDEX_START, "st_p2s_tx_common_disalbe(lane3)" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "st_p2s_rx_eidetect_disalbe(lane3)" },
	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "st_p2s_tx_beacon_en(lane3)" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "st_p2s_detect_rx_en(lane3)" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "st_p2s_rxeq_coars_tune(lane3)" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "st_p2s_rxeq_fine_tune(lane3)" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "st_p2s_tx_idle_en(lane3)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "st_p2s_rxpowerstate(lane3)" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "st_p2s_powerstate(lane3)" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "st_p2s_rxdatarate(lane3)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "st_p2s_datarate(lane3)" },

	{ false, true, UTOOL_REG_LOC14, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "st_s2p_rxctle_adapt_done(lane0)" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "st_s2p_messagebus(lane0)" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "st_s2p_detectrx_out(lane0)" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "st_s2p_detectrx_ready(lane0)" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "st_s2p_alos(lane0)" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "st_s2p_rx_status(lane0)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "st_s2p_rxtx_status(lane0)" },

	{ false, true, UTOOL_REG_LOC14, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "st_s2p_rxctle_adapt_done(lane1)" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "st_s2p_messagebus(lane1)" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "st_s2p_detectrx_out(lane1)" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "st_s2p_detectrx_ready(lane1)" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "st_s2p_alos(lane1)" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "st_s2p_rx_status(lane1)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "st_s2p_rxtx_status(lane1)" },

	{ false, true, UTOOL_REG_LOC14, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "st_s2p_rxctle_adapt_done(lane2)" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "st_s2p_messagebus(lane2)" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "st_s2p_detectrx_out(lane2)" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "st_s2p_detectrx_ready(lane2)" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "st_s2p_alos(lane2)" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "st_s2p_rx_status(lane2)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "st_s2p_rxtx_status(lane2)" },

	{ false, true, UTOOL_REG_LOC14, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "st_s2p_rxctle_adapt_done(lane3)" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "st_s2p_messagebus(lane3)" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "st_s2p_detectrx_out(lane3)" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "st_s2p_detectrx_ready(lane3)" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "st_s2p_alos(lane3)" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "st_s2p_rx_status(lane3)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "st_s2p_rxtx_status(lane3)" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "crd_vn1_compensate_exist_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "crd_vn0_compensate_exist_num" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "crd_vn3_compensate_exist_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "crd_vn2_compensate_exist_num" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "crd_vn5_compensate_exist_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "crd_vn4_compensate_exist_num" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "crd_vn7_compensate_exist_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "crd_vn6_compensate_exist_num" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "crd_vn9_compensate_exist_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "crd_vn8_compensate_exist_num" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "crd_vn11_compensate_exist_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "crd_vn10_compensate_exist_num" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "crd_vn13_compensate_exist_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "crd_vn12_compensate_exist_num" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "crd_vn15_compensate_exist_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "crd_vn14_compensate_exist_num" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl0" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl1" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl2" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl3" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl4" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl5" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl6" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl7" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl8" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl9" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl10" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl11" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl12" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl13" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl14" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_remote_crd_vl15" },

	{ false, true, UTOOL_REG_LOC2, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "ubdl_bp" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "mac_rdy" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "retry_buff_rd_ptr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "retry_buff_wr_ptr" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_field_info g_utool_link_status_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "link_state" },

	{ false, true, UTOOL_REG_LOC29, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC28, UTOOL_FIELD_INDEX_START, "cur_port_type" },
	{ false, true, UTOOL_REG_LOC26, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC25, UTOOL_FIELD_INDEX_START, "lstm_state" },
	{ false, true, UTOOL_REG_LOC17, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "cur_rx_link_wid" },
	{ false, true, UTOOL_REG_LOC9, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "cur_tx_link_wid" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "cur_link_speed" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_field_info g_utool_lane_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ false, true, UTOOL_REG_LOC21, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "target_rx_link_width" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "target_tx_link_width" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "cur_link_speed" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "cur_tx_link_wid" },
	{ false, true, UTOOL_REG_LOC9, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "cur_rx_link_wid" },
	{ false, true, UTOOL_REG_LOC17, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "tx_physical_lane_use" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_physical_lane_use" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cfg_tx_lane_disable" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_rx_lane_disable" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_field_info g_utool_bit_err_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "decoding_success_block_low" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "decoding_success_block_high" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "st_fec_decoding_fail_num_low" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "st_fec_decoding_fail_num_high" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "st_fec_err_bit_num_low" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "st_fec_err_bit_num_high" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_field_info g_utool_dl_bist_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC5, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "cfg_rx_bist_en" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cfg_tx_bist_en" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_field_info g_utool_dl_bist_err_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },

	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "st_rx_bist_err" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

struct utool_cal_reg_cnt_dp g_utool_dl_cal_reg_table[] = {
	{ true, true, DL_PKT_STATS, UTOOL_ARRAY_SIZE(g_utool_pkt_stats_field_info), g_utool_pkt_stats_field_info },
	{ true, true, DL_LINK_STATUS, UTOOL_ARRAY_SIZE(g_utool_link_status_field_info),
	  g_utool_link_status_field_info },
	{ true, true, DL_LANE, UTOOL_ARRAY_SIZE(g_utool_lane_field_info), g_utool_lane_field_info },
	{ true, true, DL_BIT_ERR, UTOOL_ARRAY_SIZE(g_utool_bit_err_field_info), g_utool_bit_err_field_info },
	{ true, false, DL_BIST, UTOOL_ARRAY_SIZE(g_utool_dl_bist_field_info), g_utool_dl_bist_field_info },
	{ true, false, DL_BIST_ERR, UTOOL_ARRAY_SIZE(g_utool_dl_bist_err_field_info), g_utool_dl_bist_err_field_info },
	{ false, false, DL_LINK_TRACE, 0, NULL },
};

int utool_dl_cal_data_len(uint32_t *dl_data_len)
{
	struct utool_cal_reg_func_param dl_cal_reg_param = {
		dl_data_len, UTOOL_REG_CNT_DEFAULT, NULL,
		g_utool_dl_cal_reg_table, UTOOL_ARRAY_SIZE(g_utool_dl_cal_reg_table)
	};
	int ret = UTOOL_OK;

	if (dl_data_len == NULL) {
		utool_err_msg("Param is invalid, dl data len is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_cal_func_reg_len(UTOOL_FUNC_ALL, &dl_cal_reg_param);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate reg cnt, ret = %d.\n", ret);
		return ret;
	}

	return UTOOL_OK;
}

static int utool_dl_pkt_stats_parse_rpc_pkt(struct fwctl_rpc_ub_out *dl_pkt_stats_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(dl_pkt_stats_out, UTOOL_ARRAY_SIZE(g_utool_pkt_stats_field_info),
			      g_utool_pkt_stats_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_DL, DL_PKT_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse dl pkt stats data.\n");
		return ret;
	}

	return UTOOL_OK;
}

static int utool_dl_link_status_parse_rpc_pkt(struct fwctl_rpc_ub_out *dl_link_status_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(dl_link_status_out, UTOOL_ARRAY_SIZE(g_utool_link_status_field_info),
			      g_utool_link_status_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_DL, DL_LINK_STATUS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse dl link status data.\n");
		return ret;
	}

	return UTOOL_OK;
}

static int utool_dl_lane_parse_rpc_pkt(struct fwctl_rpc_ub_out *dl_lane_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(dl_lane_out, UTOOL_ARRAY_SIZE(g_utool_lane_field_info),
			      g_utool_lane_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_DL, DL_LANE));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse dl lane data.\n");
		return ret;
	}

	return UTOOL_OK;
}

static int utool_dl_bit_err_parse_rpc_pkt(struct fwctl_rpc_ub_out *dl_bit_err_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(dl_bit_err_out, UTOOL_ARRAY_SIZE(g_utool_bit_err_field_info),
			      g_utool_bit_err_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_DL, DL_BIT_ERR));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse dl bit err data.\n");
		return ret;
	}

	return UTOOL_OK;
}

static int utool_dl_bist_parse_rpc_pkt(struct fwctl_rpc_ub_out *dl_bist_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(dl_bist_out, UTOOL_ARRAY_SIZE(g_utool_dl_bist_field_info),
			      g_utool_dl_bist_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_DL, DL_BIST));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse dl bist data, ret = %d.\n", ret);
	}

	return ret;
}

struct utool_dl_bist_data {
	uint32_t port_id;
	uint32_t conf_bist;
};

static int utool_dl_conf_bist_parse_rpc_pkt(struct fwctl_rpc_ub_out *dl_conf_bist_out)
{
	struct utool_dl_bist_data *dl_conf_bist_data = (struct utool_dl_bist_data *)(dl_conf_bist_out->data);

	utool_reg_msg("port_id: 0x%x\n", dl_conf_bist_data->port_id);
	utool_reg_msg("Config bist succeeded. value = %u\n", dl_conf_bist_data->conf_bist);

	return UTOOL_OK;
}

static int utool_dl_bist_err_parse_rpc_pkt(struct fwctl_rpc_ub_out *dl_bist_err_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(dl_bist_err_out, UTOOL_ARRAY_SIZE(g_utool_dl_bist_err_field_info),
			      g_utool_dl_bist_err_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_DL, DL_BIST_ERR));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse dl bist err data, ret = %d.\n", ret);
	}

	return ret;
}

static int utool_dl_trace_parse_rpc_pkt(struct fwctl_rpc_ub_out *dl_trace_out)
{
#define UTOOL_DEFAULT_FSM "UNKNOWN_FSM_NAME"
#define UTOOL_TRACE_LSM_NAME_BIT_START 24
#define UTOOL_TRACE_LSM_NAME_BIT_END 31
#define UTOOL_TRACE_TOTAL_CNT_INDEX 3
#define UTOOL_TRACE_FIXED_LEN 4
#define UTOOL_TRACE_SINGLE_TRACE_LEN 4
#define UTOOL_TRACE_SINGLE_TRACE_INDEX_1 1
#define UTOOL_TRACE_SINGLE_TRACE_INDEX_2 2
#define UTOOL_TRACE_SINGLE_TRACE_INDEX_3 3
#define UTOOL_TRACE_MAX_CACHE ((UTOOL_TRACE_4K) / (sizeof(uint32_t)))

	static const char *dl_trace_lstm_state[] = {
		"LINK_IDLE", "RX_EQ", "DETECT WAIT", "DETECT CONFIRM", "DISCOVERY ACTIVE", "DISCOVERY CONFIRM",
		"CONFIG ACTIVE", "CONFIG CHECK", "CONFIG CONFIRM", "SENT NULL", "LINK ACTIVE", "RETRAIN ACTIVE",
		"RETRAIN CONFIRM", UTOOL_DEFAULT_FSM, "CHANGE SPEED", "RETRAIN_WAIT_AMLOCK", "EQ COARSE ACTIVE",
		"EQ PASSIVE","EQ ACTIVE", "LOOPBACK CONFIRM", "LOOPBACK ACTIVE", "LOOPBACK EXIT", "SEBT EEIB",
		"CHANGE POWER", "SENT FLB", "TX LP0S ACTIVE", "RX LP0S ACTIVE", "RX LP0S WAIT SDF", "IDLE POWER",
		"SUB DIACOVERY CROSSLINK", "EQ COARSE CONFIRM",
	};

	uint32_t *dl_trace_data = dl_trace_out->data;
	const char *fsm_name = UTOOL_DEFAULT_FSM;
	uint8_t lstm_state_idx = 0;
	uint32_t total_count = 0;
	uint32_t trace_start = 0;
	uint32_t i;

	total_count = dl_trace_data[UTOOL_TRACE_TOTAL_CNT_INDEX];
	if ((UTOOL_TRACE_FIXED_LEN + total_count * UTOOL_TRACE_SINGLE_TRACE_LEN) > UTOOL_TRACE_MAX_CACHE) {
		utool_err_msg("Trace data count is illegal.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	utool_reg_msg("-------------------------- dl-trace --------------------------\n");
	utool_reg_msg("port_id: 0x%x\n", dl_trace_data[0]);
	utool_reg_msg("trace total count: %u\n", total_count);
	utool_reg_msg("----------------------bit127~96----bit95~64----bit63~32----bit31~0----fsm_name\n");
	for (i = 0; i < total_count; i++) {
		trace_start = UTOOL_TRACE_FIXED_LEN + i * UTOOL_TRACE_SINGLE_TRACE_LEN;
		lstm_state_idx = (uint8_t)UTOOL_EXTRACT_BITS(dl_trace_data[trace_start], UTOOL_TRACE_LSM_NAME_BIT_START,
							     UTOOL_TRACE_LSM_NAME_BIT_END);
		if (lstm_state_idx < UTOOL_ARRAY_SIZE(dl_trace_lstm_state)) {
			fsm_name = dl_trace_lstm_state[lstm_state_idx];
		}
		utool_reg_msg("fsm_trace_rd_data_%u: {0x%08x, 0x%08x, 0x%08x, 0x%08x, %s}\n", i,
			      dl_trace_data[trace_start],
			      dl_trace_data[trace_start + UTOOL_TRACE_SINGLE_TRACE_INDEX_1],
			      dl_trace_data[trace_start + UTOOL_TRACE_SINGLE_TRACE_INDEX_2],
			      dl_trace_data[trace_start + UTOOL_TRACE_SINGLE_TRACE_INDEX_3],
			      fsm_name);
	}

	return UTOOL_OK;
}

int utool_rt_bandwidth_parse_rpc_pkt(struct fwctl_rpc_ub_out *rt_bandwidth_out)
{
	if (rt_bandwidth_out == NULL) {
		utool_err_msg("Failed to parse real time bandwidth, rt bandwidth out is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}
	if (rt_bandwidth_out->data_size !=
		sizeof(struct utool_rt_bandwidth_info) * UTOOL_MAX_PORT) {
		utool_err_msg("Failed to parse real time bandwidth, data size = %u.\n",
			      rt_bandwidth_out->data_size);
		return UTOOL_ERR_INVALID_PARAM;
	}
	if (g_query_rt_bw_num >= UBCTL_MAX_QUERY_NUM) {
		utool_err_msg("Failed to parse real time bandwidth, query num = %u.\n", g_query_rt_bw_num);
		return UTOOL_ERR_INVALID_PARAM;
	}

	memcpy(g_rt_bw_result_data[g_query_rt_bw_num], rt_bandwidth_out->data, rt_bandwidth_out->data_size);
	g_query_rt_bw_num++;

	return UTOOL_OK;
}

static void utool_rt_bandwidth_data_print(const char *reg_name, uint64_t bandwidth)
{
#define KBPS_PER_MBPS 1000U
#define MAX_FRACTION_DIGITS 4
	char frac_str[MAX_FRACTION_DIGITS];
	uint32_t fractional_part;
	uint64_t integer_part;
	int ret = 0;
	int len;

	if (bandwidth < KBPS_PER_MBPS) {
		utool_reg_msg("%s: %lu kbps\n", reg_name, bandwidth);
		return;
	}
	integer_part = bandwidth / KBPS_PER_MBPS;
	fractional_part = bandwidth % KBPS_PER_MBPS;

	if (fractional_part == 0) {
		utool_reg_msg("%s: %lu Mbps\n", reg_name, integer_part);
		return;
	}

	ret = snprintf(frac_str, sizeof(frac_str), "%03u", fractional_part);
	if (ret < 0) {
		utool_err_msg("Failed to get frac str, ret = %d.\n", ret);
		return;
	}

	len = strlen(frac_str);
	while (len > 0 && frac_str[len - 1] == '0') {
		frac_str[--len] = '\0';
	}

	utool_reg_msg("%s: %lu.%s Mbps\n", reg_name, integer_part, frac_str);
}

static void utool_rt_bandwidth_parse(uint32_t time)
{
#define UBCTL_IS_VALID 1
#define UBCTL_BYTE_TO_BIT 8

	struct utool_rt_bandwidth_info *first_result_data = g_rt_bw_result_data[0];
	struct utool_rt_bandwidth_info *second_result_data = g_rt_bw_result_data[1];
	struct utool_rt_bandwidth_info count_result;
	uint32_t i = 0;

	for (; i < UTOOL_MAX_PORT; i++) {
		if ((first_result_data[i].is_valid == UBCTL_IS_VALID) &&
		    (second_result_data[i].is_valid == UBCTL_IS_VALID)) {
			if (first_result_data[i].rx_bandwidth > second_result_data[i].rx_bandwidth ||
			    first_result_data[i].tx_bandwidth > second_result_data[i].tx_bandwidth) {
				utool_err_msg("The second traffic is less than the first, port id = %u.\n",
					      first_result_data[i].port_id);
				break;
			}
			count_result.port_id = first_result_data[i].port_id;
			count_result.tx_bandwidth = second_result_data[i].tx_bandwidth -
						    first_result_data[i].tx_bandwidth;
			count_result.rx_bandwidth = second_result_data[i].rx_bandwidth -
						    first_result_data[i].rx_bandwidth;
			utool_reg_msg("port_id : %u\n", count_result.port_id);
			utool_rt_bandwidth_data_print("real_time_bandwidth_tx",
						      (count_result.tx_bandwidth * UBCTL_BYTE_TO_BIT) / time);
			utool_rt_bandwidth_data_print("real_time_bandwidth_rx",
						      (count_result.rx_bandwidth * UBCTL_BYTE_TO_BIT) / time);
		}
	}
}

static int utool_rt_bandwidth_pkt_operation(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_DL_RT_BANDWIDTH, 0, NULL };
	int ret = UTOOL_OK;

	func_pkt_exec.execute = utool_rt_bandwidth_parse_rpc_pkt;
	func_pkt_exec.data_len = sizeof(struct utool_rt_bandwidth_info) * UTOOL_MAX_PORT;

	ret = utool_pkt_operation_have_port(dev, param, &func_pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	return ret;
}

static int utool_rt_result_data_buf_init(void)
{
	uint32_t i = 0;

	for (; i < UBCTL_MAX_QUERY_NUM; i++) {
		g_rt_bw_result_data[i] = (struct utool_rt_bandwidth_info *)UTOOL_MALLOC
			(sizeof(struct utool_rt_bandwidth_info) * UTOOL_MAX_PORT);
		if (g_rt_bw_result_data[i] == NULL) {
			utool_err_msg("Failed to init real time bandwidth result data.\n");
			break;
		}
	}

	if (i < UBCTL_MAX_QUERY_NUM) {
		while (i > 0) {
			i--;
			UTOOL_FREE(g_rt_bw_result_data[i]);
			g_rt_bw_result_data[i] = NULL;
		}
		return UTOOL_ERR_MALLOC;
	}
	g_query_rt_bw_num = 0;

	return UTOOL_OK;
}

static struct utool_func_dispatch g_utool_dl_func_table[] = {
	{ true, DL_PKT_STATS, UTOOL_CMD_QUERY_DL_PKT_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_dl_pkt_stats_parse_rpc_pkt, utool_port_create_pkt_in },
	{ true, DL_LINK_STATUS, UTOOL_CMD_QUERY_DL_LINK_STATUS, UTOOL_REG_CNT_DEFAULT,
	  utool_dl_link_status_parse_rpc_pkt, utool_port_create_pkt_in },
	{ true, DL_LANE, UTOOL_CMD_QUERY_DL_LANE, UTOOL_REG_CNT_DEFAULT,
	  utool_dl_lane_parse_rpc_pkt, utool_port_create_pkt_in },
	{ true, DL_BIT_ERR, UTOOL_CMD_QUERY_DL_BIT_ERR, UTOOL_REG_CNT_DEFAULT,
	  utool_dl_bit_err_parse_rpc_pkt, utool_port_create_pkt_in },
	{ false, DL_BIST, UTOOL_CMD_QUERY_DL_BIST, UTOOL_REG_CNT_DEFAULT,
	  utool_dl_bist_parse_rpc_pkt, utool_port_create_pkt_in },
	{ false, DL_BIST_ERR, UTOOL_CMD_QUERY_DL_BIST_ERR, UTOOL_REG_CNT_DEFAULT,
	  utool_dl_bist_err_parse_rpc_pkt, utool_port_create_pkt_in },
	{ false, DL_LINK_TRACE, UTOOL_CMD_QUERY_DL_LINK_TRACE, UTOOL_TRACE_4K,
	  utool_dl_trace_parse_rpc_pkt, utool_port_create_pkt_in },
};

static void utool_dl_print_help(void)
{
	utool_err_msg("The ubctl dl command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -p ${port_id} -m dl -f pkt_stats/link_status/lane/bit_err"
		      "/bist/bist_err/link_trace\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m dl -p ${port}\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m dl -p ${port} -f bist -e ${value}\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m dl -p ${port_bitmap} -t ${period} -f rt_bandwidth\n");
}

static int utool_dl_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			     struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_BUTT, 0, NULL };
	struct utool_cal_reg_func_param dl_cal_reg_param = {
		NULL, 0, NULL, g_utool_dl_cal_reg_table, UTOOL_ARRAY_SIZE(g_utool_dl_cal_reg_table)
	};
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;
	uint32_t i;

	for (i = 0; i < func_cnt; i++) {
		if (strcmp(param->func, func_table[i].func) != 0) {
			continue;
		}
		func_pkt_exec.rpc_cmd = func_table[i].rpc_cmd;
		func_pkt_exec.execute = func_table[i].execute;

		if ((func_table[i].rpc_cmd == UTOOL_CMD_CONF_DL_BIST) && (param->value > 1)) {
			utool_err_msg("DL config bist value is invalid, must be 0 or 1.\n");
			return UTOOL_ERR_INVALID_PARAM;
		}

		dl_cal_reg_param.data_len = &func_pkt_exec.data_len;
		dl_cal_reg_param.user_def_data_len = func_table[i].data_len;

		ret = utool_cal_func_reg_len(param->func, &dl_cal_reg_param);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to calculate dl func %s data len.\n", param->func);
			return ret;
		}

		if (func_table[i].create_pkt_in == NULL) {
			utool_err_msg("Failed to create dl func pkt in. Callback is NULL.\n");
			return UTOOL_ERR_INVALID_PARAM;
		}

		pkt_in = func_table[i].create_pkt_in(&pkt_in_len, param);
		if (pkt_in == NULL) {
			utool_err_msg("Failed to create pkt in.\n");
			return UTOOL_ERR_MALLOC;
		}

		ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &func_pkt_exec);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to execute command, ret = %d.\n", ret);
		}

		utool_destroy_pkt_in(&pkt_in);
		return ret;
	}
	utool_dl_print_help();

	return UTOOL_ERR_FUNC_NOT_FOUND;
}

static int utool_dl_bandwidth_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
				  struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
#define MIN_PERIOD_SIZE 100U
#define MAX_PERIOD_SIZE 10000U
#define UTOOL_MS_TO_US 1000U

	int ret = UTOOL_OK;
	uint32_t i;

	if (param->time > MAX_PERIOD_SIZE || param->time < MIN_PERIOD_SIZE) {
		utool_err_msg("Invalid time, time = %u.\n", param->time);
		return UTOOL_ERR_INVALID_CMD;
	}

	ret = utool_rt_result_data_buf_init();
	if (ret != UTOOL_OK) {
		return ret;
	}

	ret = utool_rt_bandwidth_pkt_operation(dev, param);
	if (ret != UTOOL_OK) {
		utool_err_msg("first query real time bandwidth failed, ret = %d.\n", ret);
		goto query_err;
	}
	usleep(param->time * UTOOL_MS_TO_US);
	ret = utool_rt_bandwidth_pkt_operation(dev, param);
	if (ret != UTOOL_OK) {
		utool_err_msg("second query real time bandwidth failed, ret = %d.\n", ret);
		goto query_err;
	}
	utool_rt_bandwidth_parse(param->time);

query_err:
	for (i = 0; i < UBCTL_MAX_QUERY_NUM; i++) {
		UTOOL_FREE(g_rt_bw_result_data[i]);
		g_rt_bw_result_data[i] = NULL;
	}

	return ret;
}

int utool_dl_parse_rpc_pkt(struct fwctl_rpc_ub_out *dl_out)
{
	int ret = UTOOL_OK;

	if (dl_out == NULL) {
		utool_err_msg("Param is invalid, dl out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_module_parse(dl_out, UTOOL_ARRAY_SIZE(g_utool_dl_func_table), g_utool_dl_func_table,
				 UTOOL_ARRAY_SIZE(g_utool_dl_cal_reg_table), g_utool_dl_cal_reg_table);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse dl rpc pkt.\n");
	}

	return ret;
}

static int utool_dl_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
			struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_DL, 0, NULL };
	int ret = UTOOL_OK;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	func_pkt_exec.execute = utool_dl_parse_rpc_pkt;

	ret = utool_dl_cal_data_len(&func_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate reg cnt of dl all, ret = %d.\n", ret);
		return ret;
	}

	ret = utool_pkt_operation_have_port(dev, param, &func_pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	return ret;
}

int utool_dl_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	static struct utool_func_dispatch utool_dl_flag_mpfe_table[] = {
		{ false, DL_BIST, UTOOL_CMD_CONF_DL_BIST, UTOOL_REG_CNT_DEFAULT,
		  utool_dl_conf_bist_parse_rpc_pkt, utool_port_enable_create_pkt_in },
	};
	static struct utool_func_dispatch utool_dl_port_perf_table[] = {
		{ false, DL_RT_BANDWIDTH, UTOOL_CMD_QUERY_DL_RT_BANDWIDTH, UTOOL_REG_CNT_DEFAULT,
		  utool_rt_bandwidth_parse_rpc_pkt, utool_port_create_pkt_in },
	};
	struct utool_cmd_dispatch utool_dl_cmd_table[] = {
		{
			UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_E,
			utool_dl_cmd_func, utool_dl_flag_mpfe_table, UTOOL_ARRAY_SIZE(utool_dl_flag_mpfe_table)
		}, {
			UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F,
			utool_dl_cmd_func, g_utool_dl_func_table, UTOOL_ARRAY_SIZE(g_utool_dl_func_table)
		}, {
			UTOOL_FLAG_M | UTOOL_FLAG_P,
			utool_dl_cmd, g_utool_dl_func_table, UTOOL_ARRAY_SIZE(g_utool_dl_func_table)
		}, {
			UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_T,
			utool_dl_bandwidth_cmd, utool_dl_port_perf_table, UTOOL_ARRAY_SIZE(utool_dl_port_perf_table)
		}
	};

	uint32_t table_cnt = UTOOL_ARRAY_SIZE(utool_dl_cmd_table);
	uint32_t i;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n",
			      (dev == NULL), (param == NULL));

		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < table_cnt; i++) {
		if (param->flags != utool_dl_cmd_table[i].flags) {
			continue;
		}
		if (utool_dl_cmd_table[i].execute == NULL) {
			utool_err_msg("Failed to dispatch. Callback is NULL.\n");
			return UTOOL_ERR_INVALID_PARAM;
		}

		return utool_dl_cmd_table[i].execute(dev, param,
						     utool_dl_cmd_table[i].func_table,
						     utool_dl_cmd_table[i].func_cnt);

	}

	utool_dl_print_help();

	return UTOOL_ERR_CMD_NOT_FOUND;
}
