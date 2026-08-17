// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_nl_diff_version_field_info.h"

static struct utool_field_info g_utool_nl_A1_pkt_103rd_field_info[] = {
	{ false, true, UTOOL_LOC21, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_2, "o_rx_seq_tnl1_fifo_emprd_en" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_2, "o_rx_seq_tnl0_fifo_emprd_en" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_2, "o_rx_deq_fifo_emprd_en" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_2, "o_drop_seq_fifo_emprd_en" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_2, "o_drop_deq_fifo_emprd_en" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_2, "o_stash_fifo_emprd_en" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_2, "o_drop_mir_fifo_emprd_en" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_2, "o_hos_mir_fifo_emprd_en" },
	{ false, true, UTOOL_LOC11, UTOOL_LOC12, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_2, "oq_pre_sch_fifo_underflow_en" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_2, "p2p_pre_sch_fifo_underflow_en" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "p2p_ot_tnl1_fifo_underflow_en" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "p2p_ot_tnl0_fifo_underflow_en" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "p2p_data_ack_fifo_underflow_en" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC5, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "cmd_fifo_eof_rx_emprd_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "cmd_fifo_eof_tx_emprd_en" },
};

static struct utool_field_info g_utool_nl_A1_pkt_104th_field_info[] = {
	{ false, true, UTOOL_LOC21, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_2, "o_rx_seq_tnl1_fifo_emprd_int" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_2, "o_rx_seq_tnl0_fifo_emprd_int" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_2, "o_rx_deq_fifo_emprd_int" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_2, "o_drop_seq_fifo_emprd_int" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_2, "o_drop_deq_fifo_emprd_int" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_2, "o_stash_fifo_emprd_int" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_2, "o_drop_mir_fifo_emprd_int" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_2, "o_hos_mir_fifo_emprd_int" },
	{ false, true, UTOOL_LOC11, UTOOL_LOC12, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_2, "oq_pre_sch_fifo_underflow_int" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_2, "p2p_pre_sch_fifo_underflow_int" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "p2p_ot_tnl1_fifo_underflow_int" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "p2p_ot_tnl0_fifo_underflow_int" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "p2p_data_ack_fifo_underflow_int" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC5, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "cmd_fifo_eof_rx_emprd_int" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "cmd_fifo_eof_tx_emprd_int" },
};

static struct utool_field_info g_utool_nl_A1_pkt_105th_field_info[] = {
	{ false, true, UTOOL_LOC21, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_2, "o_rx_seq_tnl1_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_2, "o_rx_seq_tnl0_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_2, "o_rx_deq_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_2, "o_drop_seq_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_2, "o_drop_deq_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_2, "o_stash_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_2, "o_drop_mir_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_2, "o_hos_mir_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_2, "out_queue_bitmap_empty_en" },
	{ false, true, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_2, "oq_pre_sch_fifo_overflow_en" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_2, "p2p_pre_sch_fifo_overflow_en" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "p2p_ot_tnl1_fifo_overflow_en" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "p2p_ot_tnl0_fifo_overflow_en" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "p2p_data_ack_fifo_overflow_en" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC5, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "cmd_fifo_eof_rx_fulwr_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "cmd_fifo_eof_tx_fulwr_en" },
};

static struct utool_field_info g_utool_nl_A1_pkt_106th_field_info[] = {
	{ false, true, UTOOL_LOC21, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_2, "o_rx_seq_tnl1_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_2, "o_rx_seq_tnl0_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_2, "o_rx_deq_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_2, "o_drop_seq_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_2, "o_drop_deq_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_2, "o_stash_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_2, "o_drop_mir_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_2, "o_hos_mir_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_2, "out_queue_bitmap_empty_int" },
	{ false, true, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_2, "oq_pre_sch_fifo_overflow_int" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_2, "p2p_pre_sch_fifo_overflow_int" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "p2p_ot_tnl1_fifo_overflow_int" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "p2p_ot_tnl0_fifo_overflow_int" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "p2p_data_ack_fifo_overflow_int" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC5, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "cmd_fifo_eof_rx_fulwr_int" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "cmd_fifo_eof_tx_fulwr_int" },
};

static struct utool_field_info g_utool_nl_A1_K1_pkt_107th_field_info[] = {
	{ false, true, UTOOL_LOC25, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_V23, "rx_seop_err_en" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_V23, "tx_seop_err_en" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_V23, "tx_ct_plen_err_en" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_V23, "eth_rx_pfc_to_err_en" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_V23, "mac_crdt_uf_err_en" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_V23, "hos_crdt_uf_err_en" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_V23, "data_buff_bitmap_dup_rls_en" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_V23, "rx_pkt_cnt_uf_err_en" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_V23, "tx_pkt_cnt_uf_err_en" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_V23, "rx_pkt_oversize_en" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_V23, "tx_pkt_oversize_en" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_V23, "data_buff_bitmap_full_write_en" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_V23, "data_buff_bitmap_empty_read_en" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_V23, "tx_pre_sch_fifo_full_write_en" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_V23, "tx_pre_sch_fifo_empty_read_en" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "rx_pre_sch_fifo_full_write_en" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "rx_pre_sch_fifo_empty_read_en" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V23, "drop_pre_sch_fifo_full_write_en" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V23, "drop_pre_sch_fifo_empty_read_en" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_V23, "reserved" },
};

static struct utool_field_info g_utool_nl_A1_K1_pkt_108th_field_info[] = {
	{ false, true, UTOOL_LOC25, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_V23, "rx_seop_err" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_V23, "tx_seop_err" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_V23, "tx_ct_plen_err" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_V23, "eth_rx_pfc_to_err" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_V23, "mac_crdt_uf_err" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_V23, "hos_crdt_uf_err" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_V23, "data_buff_bitmap_dup_rls" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_V23, "rx_pkt_cnt_uf_err" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_V23, "tx_pkt_cnt_uf_err" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_V23, "rx_pkt_oversize" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_V23, "tx_pkt_oversize" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_V23, "data_buff_bitmap_full_write" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_V23, "data_buff_bitmap_empty_read" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_V23, "tx_pre_sch_fifo_full_write" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_V23, "tx_pre_sch_fifo_empty_read" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "rx_pre_sch_fifo_full_write" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "rx_pre_sch_fifo_empty_read" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V23, "drop_pre_sch_fifo_full_write" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V23, "drop_pre_sch_fifo_empty_read" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_V23, "reserved" },
};

static struct utool_field_info g_utool_nl_A1_K1_pkt_109th_field_info[] = {
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_V23, "bps_hos_fifo_full_write_en" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_V23, "bps_hos_fifo_empty_read_en" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_V23, "bps_mac_fifo_full_write_en" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_V23, "bps_mac_fifo_empty_read_en" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_V23, "rxdma_bp_timeout5_en" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_V23, "rxdma_bp_timeout4_en" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_V23, "rxdma_bp_timeout3_en" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_V23, "rxdma_bp_timeout2_en" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_V23, "rxdma_bp_timeout1_en" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_V23, "rxdma_bp_timeout0_en" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "ig_tx_bitmap_full_write_en" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "ig_tx_bitmap_empty_read_en" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V23, "ig_rx_bitmap_full_write_en" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V23, "ig_rx_bitmap_empty_read_en" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC5, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V23, "cks_edit_condition_err_en" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "cks_edit_position_err_en" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "ssu_eg_master_credit_underflow_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "ssu_eg_master_credit_overflow_en" },
};

static struct utool_field_info g_utool_nl_A1_K1_pkt_110th_field_info[] = {
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_V23, "bps_hos_fifo_full_write" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_V23, "bps_hos_fifo_empty_read" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_V23, "bps_mac_fifo_full_write" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_V23, "bps_mac_fifo_empty_read" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_V23, "rxdma_bp_timeout5" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_V23, "rxdma_bp_timeout4" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_V23, "rxdma_bp_timeout3" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_V23, "rxdma_bp_timeout2" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_V23, "rxdma_bp_timeout1" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_V23, "rxdma_bp_timeout0" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "ig_tx_bitmap_full_write" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "ig_tx_bitmap_empty_read" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V23, "ig_rx_bitmap_full_write" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V23, "ig_rx_bitmap_empty_read" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC5, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V23, "cks_edit_condition_err" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "cks_edit_position_err" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "ssu_eg_master_credit_underflow" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "ssu_eg_master_credit_overflow" },
};

static struct utool_field_info g_utool_nl_A1_K1_pkt_111th_field_info[] = {
	{ false, true, UTOOL_LOC18, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_V23, "eg_hos_fifo8_full_write_en" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_V23, "eg_hos_fifo8_empty_read_en" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_V23, "eg_hos_fifo7_full_write_en" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_V23, "eg_hos_fifo7_empty_read_en" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_V23, "eg_hos_fifo6_full_write_en" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_V23, "eg_hos_fifo6_empty_read_en" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_V23, "eg_hos_fifo5_full_write_en" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_V23, "eg_hos_fifo5_empty_read_en" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "eg_hos_fifo4_full_write_en" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "eg_hos_fifo4_empty_read_en" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V23, "eg_hos_fifo3_full_write_en" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V23, "eg_hos_fifo3_empty_read_en" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V23, "eg_hos_fifo2_full_write_en" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V23, "eg_hos_fifo2_empty_read_en" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V23, "eg_hos_fifo1_full_write_en" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "eg_hos_fifo1_empty_read_en" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "eg_hos_fifo0_full_write_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "eg_hos_fifo0_empty_read_en" },
};

static struct utool_field_info g_utool_nl_A1_K1_pkt_112th_field_info[] = {
	{ false, true, UTOOL_LOC18, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_V23, "eg_hos_fifo8_full_write" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_V23, "eg_hos_fifo8_empty_read" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_V23, "eg_hos_fifo7_full_write" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_V23, "eg_hos_fifo7_empty_read" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_V23, "eg_hos_fifo6_full_write" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_V23, "eg_hos_fifo6_empty_read" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_V23, "eg_hos_fifo5_full_write" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_V23, "eg_hos_fifo5_empty_read" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "eg_hos_fifo4_full_write" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "eg_hos_fifo4_empty_read" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V23, "eg_hos_fifo3_full_write" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V23, "eg_hos_fifo3_empty_read" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V23, "eg_hos_fifo2_full_write" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V23, "eg_hos_fifo2_empty_read" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V23, "eg_hos_fifo1_full_write" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "eg_hos_fifo1_empty_read" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "eg_hos_fifo0_full_write" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "eg_hos_fifo0_empty_read" },
};

static struct utool_field_info g_utool_nl_A1_pkt_113th_field_info[] = {
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_2, "eg_rx_hos_bps_mem_pkt_type_fifo1_full_write" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_2, "eg_rx_hos_bps_mem_pkt_type_fifo1_empty_read" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_2, "eg_rx_hos_bps_mem_pkt_type_fifo0_full_write" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_2, "eg_rx_hos_bps_mem_pkt_type_fifo0_empty_read" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_ctp_fifo1_full_write" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_ctp_fifo1_empty_read" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_ctp_fifo0_full_write" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_ctp_fifo0_empty_read" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioack_fifo1_full_write" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioack_fifo1_empty_read" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioack_fifo0_full_write" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioack_fifo0_empty_read" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_fifo1_full_write" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_fifo1_empty_read" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_fifo0_full_write" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_fifo0_empty_read" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_2, "eg_rx_p2p_bps_fifo1_full_write" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "eg_rx_p2p_bps_fifo1_empty_read" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "eg_rx_p2p_bps_fifo0_full_write" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "eg_rx_p2p_bps_fifo0_empty_read" },
};

static struct utool_field_info g_utool_nl_A1_pkt_114th_field_info[] = {
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_2, "eg_rx_hos_bps_mem_pkt_type_fifo1_full_write_en" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_2, "eg_rx_hos_bps_mem_pkt_type_fifo1_empty_read_en" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_2, "eg_rx_hos_bps_mem_pkt_type_fifo0_full_write_en" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_2, "eg_rx_hos_bps_mem_pkt_type_fifo0_empty_read_en" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_ctp_fifo1_full_write_en" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_ctp_fifo1_empty_read_en" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_ctp_fifo0_full_write_en" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_ctp_fifo0_empty_read_en" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioack_fifo1_full_write_en" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioack_fifo1_empty_read_en" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioack_fifo0_full_write_en" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioack_fifo0_empty_read_en" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_fifo1_full_write_en" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_fifo1_empty_read_en" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_fifo0_full_write_en" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_2, "eg_rx_hos_bps_ioreq_fifo0_empty_read_en" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_2, "eg_rx_p2p_bps_fifo1_full_write_en" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "eg_rx_p2p_bps_fifo1_empty_read_en" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "eg_rx_p2p_bps_fifo0_full_write_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "eg_rx_p2p_bps_fifo0_empty_read_en" },
};

static struct utool_field_info g_utool_nl_A1_K1_pkt_115th_field_info[] = {
	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V23, "bm_data_row5_ecc_merr_int" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V23, "bm_data_row4_ecc_merr_int" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V23, "bm_data_row3_ecc_merr_int" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "bm_data_row2_ecc_merr_int" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "bm_data_row1_ecc_merr_int" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "bm_data_row0_ecc_merr_int" },
};

static struct utool_field_info g_utool_nl_A1_K1_pkt_125th_field_info[] = {
	{ false, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_V23, "ssu_oq_sel_index" },
};

static struct utool_field_info g_utool_nl_A1_pkt_127th_field_info[] = {
	{ false, true, UTOOL_LOC18, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC17, 0, UTOOL_CAP_2, "tx_cmd_get_indx_sel" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_2, "tx_cmd_get_rlt_status" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_2, "tx_cmd_get_eop_status" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_2, "tx_cmd_get_info_status" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC8, 0, UTOOL_CAP_2, "rx_cmd_get_indx_sel" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "rx_cmd_get_rlt_status" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "rx_cmd_get_eop_status" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "rx_cmd_get_info_status" },
};

static struct utool_field_info g_utool_nl_A1_pkt_128th_field_info[] = {
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC7, 0, UTOOL_CAP_2, "ssu_link_down_finish_hst" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_2, "data_buff_bitmap_full" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_2, "data_buff_bitmap_empty" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_2, "reserved" },
};

static struct utool_field_info g_utool_nl_A1_pkt_136th_field_info[] = {
	{ false, true, UTOOL_LOC14, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_2, "bm_clk_gating_i" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_2, "bm_clk_gating_e" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_2, "reserved" },
};

static struct utool_field_info g_utool_nl_A1_pkt_137th_field_info[] = {
	{ false, true, UTOOL_LOC13, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty12" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty11" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty10" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty9" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty8" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty7" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty6" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty5" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty4" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty3" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty2" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "bm_pre_sch_fifo_empty0" },
};

static struct utool_field_info g_utool_nl_A1_K1_pkt_144th_field_info[] = {
	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V23, "bm_data_row5_ecc_serr_int" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V23, "bm_data_row4_ecc_serr_int" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V23, "bm_data_row3_ecc_serr_int" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "bm_data_row2_ecc_serr_int" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "bm_data_row1_ecc_serr_int" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "bm_data_row0_ecc_serr_int" },
};

static struct utool_field_info g_utool_nl_A1_K1_pkt_145th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_V23, "oq_sch_bm_tx_credit_cnt_of_int" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_V23, "oq_sch_bm_tx_credit_cnt_uf_int" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC13, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "ets_tx_port_shap_wr_int" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "ets_tx_port_shap_rd_int" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_V23, "ets_tx_tcg_shap_wr_int" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_V23, "ets_tx_tcg_shap_rd_int" },
};

static struct utool_field_info g_utool_nl_A1_K1_pkt_146th_field_info[] = {
	{ false, true, UTOOL_LOC11, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_V23, "eg_mac_fifo_full_write" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "eg_mac_fifo_empty_read" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V23, "rx_pkt_more_key_port" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V23, "tx_pkt_more_key_port" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V23, "rx_sop_mis_match_port" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V23, "tx_sop_mis_match_port" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V23, "rx_eop_mis_match_port" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "tx_eop_mis_match_port" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "rx_pkt_without_key_port" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "tx_pkt_without_key_port" },
};

static struct utool_field_info g_utool_nl_A1_K1_pkt_149th_field_info[] = {
	{ false, true, UTOOL_LOC23, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_V23, "cfg_ot_ba_link_up_sel" },
	{ false, true, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC20, 0, UTOOL_CAP_V23, "cfg_ot_link_down_flag_en" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_V23, "cfg_link_down_response_en" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC17, 0, UTOOL_CAP_V23, "cfg_ot_link_down_flag_th" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_V23, "cfg_ot_link_down_waiting_th" },
};

static struct utool_field_info g_utool_nl_A1_ssu_6th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_2, "tx_full_drop_num" },
};

static struct utool_field_info g_utool_nl_A1_ssu_7th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_2, "tx_part_drop_num" },
};

static struct utool_field_info g_utool_nl_A1_ssu_28th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_2, "rx_packet_in_bps_cnt" },
};

static struct utool_field_info g_utool_nl_A1_ssu_29th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_2, "tx_packet_in_bps_cnt" },
};

static struct utool_field_info g_utool_nl_A1_ssu_32nd_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_2, "rx_ub_packet_in_sf_cnt" },
};

static struct utool_field_info g_utool_nl_A1_ssu_33rd_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_2, "tx_ub_packet_in_sf_cnt" },
};

static struct utool_field_info g_utool_nl_A1_ssu_39th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_2, "rx_nic_packet_in_sf_cnt" },
};

static struct utool_field_info g_utool_nl_A1_ssu_40th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_2, "tx_nic_packet_in_sf_cnt" },
};

static struct utool_field_info g_utool_nl_A1_ssu_54th_field_info[] = {
	{ false, false, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_2, "ssu_egrx_hos_que_fifo_cnt7" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC27, 0, UTOOL_CAP_2, "ssu_egrx_hos_que_fifo_cnt6" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC23, 0, UTOOL_CAP_2, "ssu_egrx_hos_que_fifo_cnt5" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_2, "ssu_egrx_hos_que_fifo_cnt4" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC15, 0, UTOOL_CAP_2, "ssu_egrx_hos_que_fifo_cnt3" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_2, "ssu_egrx_hos_que_fifo_cnt2" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_2, "ssu_egrx_hos_que_fifo_cnt1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_2, "ssu_egrx_hos_que_fifo_cnt0" },
};

static struct utool_field_info g_utool_nl_A1_K1_ssu_71st_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "rx_packet_p2p_bps_out_cnt" },
};

static struct utool_field_info g_utool_nl_A1_ssu_74th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_2, "ssu_rsv_cnt_1" },
};

static struct utool_field_info g_utool_nl_A1_ssu_86th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_2, "rxdma_bp_status" },
};

static struct utool_field_info g_utool_nl_A1_ssu_87th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_2, "ssu_rxpa_pfc_hst" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_2, "ssu_rxpa_pfc_status" },
};

static struct utool_field_info g_utool_nl_A1_ssu_88th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_2, "rxpa_ssu_pfc_hst" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_2, "rxpa_ssu_pfc_status" },
};

static struct utool_field_info g_utool_nl_A1_ssu_sw_2nd_field_info[] = {
	{ false, true, UTOOL_LOC18, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC17, 0, UTOOL_CAP_2, "tx_cmd_get_indx_sel" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_2, "tx_cmd_get_rlt_status" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_2, "tx_cmd_get_eop_status" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_2, "tx_cmd_get_info_status" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC8, 0, UTOOL_CAP_2, "rx_cmd_get_indx_sel" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "rx_cmd_get_rlt_status" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "rx_cmd_get_eop_status" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "rx_cmd_get_info_status" },
};

static struct utool_field_info g_utool_nl_A1_ssu_oq_1st_field_info[] = {
	{ false, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "index" },
};

static struct utool_field_info g_utool_nl_A1_p2p_3rd_field_info[] = {
	{ false, true, UTOOL_LOC29, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_2, "p2p_port_shap_en" },
	{ false, true, UTOOL_LOC26, UTOOL_LOC27, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC25, 0, UTOOL_CAP_2, "p2p_port_shap_cfg" },
};

static struct utool_field_info g_utool_nl_K1_pkt_87th_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl0)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_88th_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl1)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_89th_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl2)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_90th_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl3)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_91st_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl4)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_92rd_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl5)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_93nd_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl6)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_94th_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl7)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_95th_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl8)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_96th_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl9)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_97th_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl10)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_98th_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl11)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_99th_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl12)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_100th_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl13)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_101st_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl14)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_102rd_field_info[] = {
	{false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved"},
	{false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "link_cur_used_pri_credit_cnt(vl15)"},
};

static struct utool_field_info g_utool_nl_K1_pkt_103rd_field_info[] = {
	{ false, true, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_3, "o_drop_tx_deq_fifo_emprd_en" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_3, "o_drop_byp_fifo_emprd_en" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_3, "o_rx_seq_tnl1_fifo_emprd_en" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_3, "o_rx_seq_tnl0_fifo_emprd_en" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_3, "o_rx_deq_fifo_emprd_en" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_3, "o_drop_seq_fifo_emprd_en" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_3, "o_drop_rx_deq_fifo_emprd_en" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_3, "o_drop_mir_fifo_emprd_en" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_3, "o_hos_mir_fifo_emprd_en" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC12, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "cmd_fifo_eof_tx_emprd_en" },
};

static struct utool_field_info g_utool_nl_K1_pkt_104th_field_info[] = {
	{ false, true, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_3, "o_drop_tx_deq_fifo_emprd_int" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_3, "o_drop_byp_fifo_emprd_int" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_3, "o_rx_seq_tnl1_fifo_emprd_int" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_3, "o_rx_seq_tnl0_fifo_emprd_int" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_3, "o_rx_deq_fifo_emprd_int" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_3, "o_drop_seq_fifo_emprd_int" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_3, "o_drop_rx_deq_fifo_emprd_int" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_3, "o_drop_mir_fifo_emprd_int" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_3, "o_hos_mir_fifo_emprd_int" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC12, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "cmd_fifo_eof_tx_emprd_int" },
};

static struct utool_field_info g_utool_nl_K1_pkt_105th_field_info[] = {
	{ false, true, UTOOL_LOC23, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_3, "o_drop_tx_deq_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_3, "o_drop_byp_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_3, "o_rx_seq_tnl1_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_3, "o_rx_seq_tnl0_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_3, "o_rx_deq_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_3, "o_drop_seq_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_3, "o_drop_rx_deq_fifo_fulwr_en" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_3, "o_drop_mir_fifo_fulwr_en" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_3, "o_hos_mir_fifo_fulwr_en" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC12, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "cmd_fifo_eof_tx_fulwr_en" },
};

static struct utool_field_info g_utool_nl_K1_pkt_106th_field_info[] = {
	{ false, true, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_3, "o_drop_tx_deq_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_3, "o_drop_byp_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_3, "o_rx_seq_tnl1_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_3, "o_rx_seq_tnl0_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_3, "o_rx_deq_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_3, "o_drop_seq_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_3, "o_drop_rx_deq_fifo_fulwr_int" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_3, "o_drop_mir_fifo_fulwr_int" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_3, "o_hos_mir_fifo_fulwr_int" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC12, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "cmd_fifo_eof_tx_fulwr_int" },
};

static struct utool_field_info g_utool_nl_K1_pkt_113th_field_info[] = {
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC29, UTOOL_LOC29, 0, UTOOL_CAP_3, "eg_rx_upa_ctp_sp1_fifo_full_write" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_3, "eg_rx_upa_ctp_sp1_fifo_empty_read" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC27, 0, UTOOL_CAP_3, "eg_rx_upa_ack_sp1_fifo_full_write" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_3, "eg_rx_upa_ack_sp1_fifo_empty_read" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_3, "eg_rx_upa_req_sp1_fifo_full_write" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_3, "eg_rx_upa_req_sp1_fifo_empty_read" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_3, "eg_rx_hos_bps_fifo1_full_write" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_3, "eg_rx_hos_bps_fifo1_empty_read" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_3, "eg_rx_hos_bps_fifo0_full_write" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_3, "eg_rx_hos_bps_fifo0_empty_read" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_3, "eg_rx_hos_bps_mem_pkt_type_fifo1_full_write" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_3, "eg_rx_hos_bps_mem_pkt_type_fifo1_empty_read" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_3, "eg_rx_hos_bps_mem_pkt_type_fifo0_full_write" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_3, "eg_rx_hos_bps_mem_pkt_type_fifo0_empty_read" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_3, "eg_rx_hos_bps_ioreq_ctp_fifo1_full_write" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_3, "eg_rx_hos_bps_ioreq_ctp_fifo1_empty_read" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_3, "eg_rx_hos_bps_ioreq_ctp_fifo0_full_write" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_3, "eg_rx_hos_bps_ioreq_ctp_fifo0_empty_read" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_3, "eg_rx_hos_bps_ioack_fifo1_full_write" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_3, "eg_rx_hos_bps_ioack_fifo1_empty_read" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_3, "eg_rx_upa_ctp_sp0_fifo_full_write" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_3, "eg_rx_upa_ctp_sp0_fifo_empty_read" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_3, "eg_rx_upa_ack_sp0_fifo_full_write" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_3, "eg_rx_upa_ack_sp0_fifo_empty_read" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "eg_rx_upa_req_sp0_fifo_full_write" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "eg_rx_upa_req_sp0_fifo_empty_read" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "eg_rx_p2p_bps_fifo1_full_write" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "eg_rx_p2p_bps_fifo1_empty_read" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "eg_rx_p2p_bps_fifo0_full_write" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "eg_rx_p2p_bps_fifo0_empty_read" },
};

static struct utool_field_info g_utool_nl_K1_pkt_114th_field_info[] = {
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC29, UTOOL_LOC29, 0, UTOOL_CAP_3, "eg_rx_upa_ctp_sp1_fifo_full_write_en" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_3, "eg_rx_upa_ctp_sp1_fifo_empty_read_en" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC27, 0, UTOOL_CAP_3, "eg_rx_upa_ack_sp1_fifo_full_write_en" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_3, "eg_rx_upa_ack_sp1_fifo_empty_read_en" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_3, "eg_rx_upa_req_sp1_fifo_full_write_en" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_3, "eg_rx_upa_req_sp1_fifo_empty_read_en" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_3, "eg_rx_hos_bps_fifo1_full_write_en" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_3, "eg_rx_hos_bps_fifo1_empty_read_en" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_3, "eg_rx_hos_bps_fifo0_full_write_en" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_3, "eg_rx_hos_bps_fifo0_empty_read_en" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_3, "eg_rx_hos_bps_mem_pkt_type_fifo1_full_write_en" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_3, "eg_rx_hos_bps_mem_pkt_type_fifo1_empty_read_en" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_3, "eg_rx_hos_bps_mem_pkt_type_fifo0_full_write_en" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_3, "eg_rx_hos_bps_mem_pkt_type_fifo0_empty_read_en" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_3, "eg_rx_hos_bps_ioreq_ctp_fifo1_full_write_en" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_3, "eg_rx_hos_bps_ioreq_ctp_fifo1_empty_read_en" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_3, "eg_rx_hos_bps_ioreq_ctp_fifo0_full_write_en" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_3, "eg_rx_hos_bps_ioreq_ctp_fifo0_empty_read_en" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_3, "eg_rx_hos_bps_ioack_fifo1_full_write_en" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_3, "eg_rx_hos_bps_ioack_fifo1_empty_read_en" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_3, "eg_rx_upa_ctp_sp0_fifo_full_write_en" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_3, "eg_rx_upa_ctp_sp0_fifo_empty_read_en" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_3, "eg_rx_upa_ack_sp0_fifo_full_write_en" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_3, "eg_rx_upa_ack_sp0_fifo_empty_read_en" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "eg_rx_upa_req_sp0_fifo_full_write_en" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "eg_rx_upa_req_sp0_fifo_empty_read_en" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "eg_rx_p2p_bps_fifo1_full_write_en" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "eg_rx_p2p_bps_fifo1_empty_read_en" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "eg_rx_p2p_bps_fifo0_full_write_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "eg_rx_p2p_bps_fifo0_empty_read_en" },
};

static struct utool_field_info g_utool_nl_K1_pkt_116th_field_info[] = {
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3, "ssu_ecc_merr_int_en" },
};

static struct utool_field_info g_utool_nl_K1_pkt_124th_ssu_p2p_5th_field_info[] = {
	{ false, false, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_3, "p2p_q_status_3" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "p2p_q_specu_ing_bp" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "p2p_q_during_arrive" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "p2p_q_during_retry" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "p2p_q_pre_sch_fifo_empty" },
};

static struct utool_field_info g_utool_nl_K1_pkt_126th_field_info[] = {
	{ false, false, UTOOL_LOC22, UTOOL_LOC31, 0, UTOOL_CAP_3, "oq_inner_status_0" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_3, "tc_sch_rdy" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC20, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC14, 0, UTOOL_CAP_3, "queue_cnt" },
};

static struct utool_field_info g_utool_nl_K1_pkt_127th_field_info[] = {
	{ false, true, UTOOL_LOC18, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC17, 0, UTOOL_CAP_3, "tx_cmd_get_indx_sel" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_3, "tx_cmd_get_rlt_status" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_3, "tx_cmd_get_info_status" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC8, 0, UTOOL_CAP_3, "rx_cmd_get_indx_sel" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "rx_cmd_get_rlt_status" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "rx_cmd_get_info_status" },
};

static struct utool_field_info g_utool_nl_K1_pkt_128th_field_info[] = {
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC19, 0, UTOOL_CAP_3, "ssu_init_rx_err_hst" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC17, 0, UTOOL_CAP_3, "ssu_init_tx_err_hst" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC15, 0, UTOOL_CAP_3, "ssu_tx_ct_with_err_hst" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC13, 0, UTOOL_CAP_3, "ssu_tx_ct_out_hst" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC11, 0, UTOOL_CAP_3, "ssu_link_down_hst" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC9, 0, UTOOL_CAP_3, "ssu_link_down_pro" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC7, 0, UTOOL_CAP_3, "ssu_link_down_finish_hst" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "data_buff_bitmap_full" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "data_buff_bitmap_empty" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_3, "reserved" },
};

static struct utool_field_info g_utool_nl_K1_pkt_137th_field_info[] = {
	{ false, true, UTOOL_LOC17, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty16" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty15" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty14" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty13" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty12" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty11" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty10" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty9" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty8" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty7" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty6" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty5" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty4" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty3" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty2" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "bm_pre_sch_fifo_empty0" },
};

static struct utool_field_info g_utool_nl_K1_vl_7th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "tx_packet_in_vl_cnt0" },
};

static struct utool_field_info g_utool_nl_K1_vl_8th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "rx_packet_in_vl_cnt0" },
};

static struct utool_field_info g_utool_nl_rsv_field_info[] = {
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_diff_version_field_info g_utool_nl_diff_version_field_info[] = {
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC103,
	  g_utool_nl_A1_pkt_103rd_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_pkt_103rd_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC104,
	  g_utool_nl_A1_pkt_104th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_pkt_104th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC105,
	  g_utool_nl_A1_pkt_105th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_pkt_105th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC106,
	  g_utool_nl_A1_pkt_106th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_pkt_106th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC107,
	  g_utool_nl_A1_K1_pkt_107th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_107th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC108,
	  g_utool_nl_A1_K1_pkt_108th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_108th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC109,
	  g_utool_nl_A1_K1_pkt_109th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_109th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC110,
	  g_utool_nl_A1_K1_pkt_110th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_110th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC111,
	  g_utool_nl_A1_K1_pkt_111th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_111th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC112,
	  g_utool_nl_A1_K1_pkt_112th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_112th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC113,
	  g_utool_nl_A1_pkt_113th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_pkt_113th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC114,
	  g_utool_nl_A1_pkt_114th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_pkt_114th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC115,
	  g_utool_nl_A1_K1_pkt_115th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_115th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC117,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC125,
	  g_utool_nl_A1_K1_pkt_125th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_125th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC127,
	  g_utool_nl_A1_pkt_127th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_pkt_127th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC128,
	  g_utool_nl_A1_pkt_128th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_pkt_128th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC132,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC133,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC136,
	  g_utool_nl_A1_pkt_136th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_pkt_136th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC137,
	  g_utool_nl_A1_pkt_137th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_pkt_137th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC139,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC140,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC144,
	  g_utool_nl_A1_K1_pkt_144th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_144th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC145,
	  g_utool_nl_A1_K1_pkt_145th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_145th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC146,
	  g_utool_nl_A1_K1_pkt_146th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_146th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC149,
	  g_utool_nl_A1_K1_pkt_149th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_149th_field_info) },

	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC2,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC3,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC4,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC5,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC6,
	  g_utool_nl_A1_ssu_6th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_6th_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC7,
	  g_utool_nl_A1_ssu_7th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_7th_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC8,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC14,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC15,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC18,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC19,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC20,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC21,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC28,
	  g_utool_nl_A1_ssu_28th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_28th_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC29,
	  g_utool_nl_A1_ssu_29th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_29th_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC30,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC31,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC32,
	  g_utool_nl_A1_ssu_32nd_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_32nd_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC33,
	  g_utool_nl_A1_ssu_33rd_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_33rd_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC39,
	  g_utool_nl_A1_ssu_39th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_39th_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC40,
	  g_utool_nl_A1_ssu_40th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_40th_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC50,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC51,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC52,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC53,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC54,
	  g_utool_nl_A1_ssu_54th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_54th_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC55,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC71,
	  g_utool_nl_A1_K1_ssu_71st_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_ssu_71st_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC74,
	  g_utool_nl_A1_ssu_74th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_74th_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC78,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC79,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC86,
	  g_utool_nl_A1_ssu_86th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_86th_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC87,
	  g_utool_nl_A1_ssu_87th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_87th_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC88,
	  g_utool_nl_A1_ssu_88th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_88th_field_info) },

	{ "nl-ssu_sw", UTOOL_ENV_VER_A_1, UTOOL_LOC2,
	  g_utool_nl_A1_ssu_sw_2nd_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_sw_2nd_field_info) },

	{ "nl-ssu_oq", UTOOL_ENV_VER_A_1, UTOOL_LOC1,
	  g_utool_nl_A1_ssu_oq_1st_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_ssu_oq_1st_field_info) },

	{ "nl-p2p", UTOOL_ENV_VER_A_1, UTOOL_LOC3,
	  g_utool_nl_A1_p2p_3rd_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_p2p_3rd_field_info) },

	{ "nl-ssu_vl_pkt", UTOOL_ENV_VER_A_1, UTOOL_LOC2,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_vl_pkt", UTOOL_ENV_VER_A_1, UTOOL_LOC3,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_vl_pkt", UTOOL_ENV_VER_A_1, UTOOL_LOC4,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },

	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC87,
	  g_utool_nl_K1_pkt_87th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_87th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC88,
	  g_utool_nl_K1_pkt_88th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_88th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC89,
	  g_utool_nl_K1_pkt_89th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_89th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC90,
	  g_utool_nl_K1_pkt_90th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_90th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC91,
	  g_utool_nl_K1_pkt_91st_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_91st_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC92,
	  g_utool_nl_K1_pkt_92rd_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_92rd_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC93,
	  g_utool_nl_K1_pkt_93nd_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_93nd_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC94,
	  g_utool_nl_K1_pkt_94th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_94th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC95,
	  g_utool_nl_K1_pkt_95th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_95th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC96,
	  g_utool_nl_K1_pkt_96th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_96th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC97,
	  g_utool_nl_K1_pkt_97th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_97th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC98,
	  g_utool_nl_K1_pkt_98th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_98th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC99,
	  g_utool_nl_K1_pkt_99th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_99th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC100,
	  g_utool_nl_K1_pkt_100th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_100th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC101,
	  g_utool_nl_K1_pkt_101st_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_101st_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC102,
	  g_utool_nl_K1_pkt_102rd_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_102rd_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC103,
	  g_utool_nl_K1_pkt_103rd_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_103rd_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC104,
	  g_utool_nl_K1_pkt_104th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_104th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC105,
	  g_utool_nl_K1_pkt_105th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_105th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC106,
	  g_utool_nl_K1_pkt_106th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_106th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC107,
	  g_utool_nl_A1_K1_pkt_107th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_107th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC108,
	  g_utool_nl_A1_K1_pkt_108th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_108th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC109,
	  g_utool_nl_A1_K1_pkt_109th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_109th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC110,
	  g_utool_nl_A1_K1_pkt_110th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_110th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC111,
	  g_utool_nl_A1_K1_pkt_111th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_111th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC112,
	  g_utool_nl_A1_K1_pkt_112th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_112th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC113,
	  g_utool_nl_K1_pkt_113th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_113th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC114,
	  g_utool_nl_K1_pkt_114th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_114th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC115,
	  g_utool_nl_A1_K1_pkt_115th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_115th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC116,
	  g_utool_nl_K1_pkt_116th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_116th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC117,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC124, g_utool_nl_K1_pkt_124th_ssu_p2p_5th_field_info,
	  UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_124th_ssu_p2p_5th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC125,
	  g_utool_nl_A1_K1_pkt_125th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_125th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC126,
	  g_utool_nl_K1_pkt_126th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_126th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC127,
	  g_utool_nl_K1_pkt_127th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_127th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC128,
	  g_utool_nl_K1_pkt_128th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_128th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC132,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC133,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC134,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC135,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC136,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC137,
	  g_utool_nl_K1_pkt_137th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_137th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC139,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC140,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC144,
	  g_utool_nl_A1_K1_pkt_144th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_144th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC145,
	  g_utool_nl_A1_K1_pkt_145th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_145th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC149,
	  g_utool_nl_A1_K1_pkt_149th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_pkt_149th_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC151,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC152,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC153,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC154,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },

	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC2,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC3,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC4,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC5,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC6,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC7,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC8,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC13,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC14,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC15,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC18,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC19,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC20,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC21,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC21,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC22,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC23,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC24,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC28,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC29,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC30,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC31,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC32,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC33,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC39,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC40,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC50,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC51,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC52,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC53,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC54,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC55,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC61,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC62,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC63,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC64,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC65,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC66,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC67,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC68,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC69,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC70,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC71,
	  g_utool_nl_A1_K1_ssu_71st_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_A1_K1_ssu_71st_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC72,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC73,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC74,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC78,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC79,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC80,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC81,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC82,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC83,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC84,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC86,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC87,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC88,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },

	{ "nl-ssu_p2p", UTOOL_ENV_VER_K_1, UTOOL_LOC5, g_utool_nl_K1_pkt_124th_ssu_p2p_5th_field_info,
	  UTOOL_ARRAY_SIZE(g_utool_nl_K1_pkt_124th_ssu_p2p_5th_field_info) },

	{ "nl-ssu_vl_pkt", UTOOL_ENV_VER_K_1, UTOOL_LOC3,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_vl_pkt", UTOOL_ENV_VER_K_1, UTOOL_LOC4,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_vl_pkt", UTOOL_ENV_VER_K_1, UTOOL_LOC5,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_vl_pkt", UTOOL_ENV_VER_K_1, UTOOL_LOC7,
	  g_utool_nl_K1_vl_7th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_vl_7th_field_info) },
	{ "nl-ssu_vl_pkt", UTOOL_ENV_VER_K_1, UTOOL_LOC8,
	  g_utool_nl_K1_vl_8th_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_K1_vl_8th_field_info) },
	{ "nl-ssu_vl_pkt", UTOOL_ENV_VER_K_1, UTOOL_LOC9,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
	{ "nl-ssu_vl_pkt", UTOOL_ENV_VER_K_1, UTOOL_LOC10,
	  g_utool_nl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_nl_rsv_field_info) },
};

struct utool_field_info *utool_nl_cmd_diff_ver_dispatch(const char *module_func_name,
							uint32_t reg_version, uint32_t reg_info_index,
							uint32_t *replace_field_cnt)
{
	uint32_t i;

	if (module_func_name == NULL || module_func_name[0] == '\0') {
		utool_err_msg("Module func name is invalid.\n");
		return NULL;
	}

	for (i = 0; i < UTOOL_ARRAY_SIZE(g_utool_nl_diff_version_field_info); i++) {
		if (strcmp(module_func_name, g_utool_nl_diff_version_field_info[i].module_func_name) != 0) {
			continue;
		}

		if (reg_version != g_utool_nl_diff_version_field_info[i].reg_version) {
			continue;
		}

		if (reg_info_index == g_utool_nl_diff_version_field_info[i].reg_info_index) {
			*replace_field_cnt = g_utool_nl_diff_version_field_info[i].replace_field_cnt;
			return g_utool_nl_diff_version_field_info[i].replace_field_info;
		}
	}

	return NULL;
}
