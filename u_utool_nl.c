// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_nl.h"

#define NL_PKT_STATS "pkt_stats"
#define NL_SSU_STATS "ssu_stats"
#define NL_ABN_STATS "abn_stats"
#define NL_SSU_SW "ssu_sw"
#define NL_SSU_OQ "ssu_oq"
#define NL_SSU_P2P "ssu_p2p"

static struct utool_field_info g_utool_pkt_stats_field_info[] = {
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_all_pkt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_1, "pa_out_all_pkt(TX)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_key_num(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_1, "pa_out_key_num(TX)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_non_tun_l2_pkt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_non_tun_l3_pkt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_non_tun_l4_pkt(TX)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_non_tun_pkt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_1, "pa_out_non_tun_pkt(TX)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_l3e_pkt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_l4e_pkt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_ub_pkt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_outer_udp0_pkt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_ipv4_pkt_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_ipv6_pkt_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ipv4_pkt_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ipv6_pkt_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ncp_pkt_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_compact_pkt_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_umoc_ctph_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_umoc_ntph_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_mem_pkt_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unknown_pkt_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "drop_ind_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "err_ind_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "noc_ind_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lpbk_ind_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "out_err_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "length_err_cnt(TX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "interface_err_cnt(TX)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_all_pkt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_1, "pa_out_all_pkt(RX)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_key_num(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_1, "pa_out_key_num(RX)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_non_tun_l2_pkt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_non_tun_l3_pkt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_non_tun_l4_pkt(RX)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_non_tun_pkt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_1, "pa_out_non_tun_pkt(RX)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_l3e_pkt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_l4e_pkt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_ub_pkt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_outer_udp0_pkt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_ipv4_pkt_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_ipv6_pkt_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ipv4_pkt_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ipv6_pkt_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ncp_pkt_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_compact_pkt_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_umoc_ctph_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_umoc_ntph_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_mem_pkt_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unknown_pkt_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "drop_ind_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "err_ind_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pack_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_host_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_imp_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_mar_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_link_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_noc_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "route_err_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "out_err_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "length_err_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "interface_err_cnt(RX)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_out_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "link_alloc_port_share_credit(vl0)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl0)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "link_alloc_port_share_credit(vl1)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl1)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "link_alloc_port_share_credit(vl2)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl2)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "link_alloc_port_share_credit(vl3)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl3)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "link_alloc_port_share_credit(vl4)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl4)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "link_alloc_port_share_credit(vl5)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl5)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "link_alloc_port_share_credit(vl6)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl6)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "link_alloc_port_share_credit(vl7)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl7)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "link_alloc_port_share_credit(vl8)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl8)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "link_alloc_port_share_credit(vl9)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl9)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_alloc_port_share_credit(vl10)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl10)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_alloc_port_share_credit(vl11)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl11)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_alloc_port_share_credit(vl12)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl12)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_alloc_port_share_credit(vl13)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl13)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_alloc_port_share_credit(vl14)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl14)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_alloc_port_share_credit(vl15)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "link_alloc_vl_pri_credit(vl15)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl0)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl0)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl1)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl1)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl2)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl2)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl3)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl3)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl4)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl4)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl5)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl5)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl6)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl6)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl7)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl7)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl8)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl8)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl9)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl9)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl10)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl10)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl11)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl11)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl12)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl12)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl13)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl13)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl14)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl14)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_share_credit_cnt(vl15)" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "link_cur_used_pri_credit_cnt(vl15)" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "qm_underflow_fifo_int_en" },

	{ false, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "oq_pre_sch_fifo_underflow_int" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "p2p_pre_sch_fifo_underflow_int" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "p2p_ot_tnl1_fifo_underflow_int" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "p2p_ot_tnl0_fifo_underflow_int" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "p2p_data_ack_fifo_underflow_int" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "bypass_ppp_rlt_fifo_underflow_int" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "dup_copy_buf_fifo_underflow_int" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "dup_cnt_drop_fifo_underflow_int" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "dup_uncopy_fifo_underflow_int" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "mb_rlt_fifo_underflow_int" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cmd_ot_fifo_underflow_int" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "qm_overflow_fifo_int_en" },

	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "out_queue_bitmap_empty_int" },
	{ false, true, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "oq_pre_sch_fifo_overflow_int" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "p2p_pre_sch_fifo_overflow_int" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "p2p_ot_tnl1_fifo_overflow_int" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "p2p_ot_tnl0_fifo_overflow_int" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "p2p_data_ack_fifo_overflow_int" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "bypass_ppp_rlt_fifo_overflow_int" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "dup_copy_buf_fifo_overflow_int" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "dup_cnt_drop_fifo_overflow_int" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "dup_uncopy_fifo_overflow_int" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "mb_rlt_fifo_overflow_int" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cmd_ot_fifo_overflow_int" },

	{ false, true, UTOOL_REG_LOC18, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "tx_credit_overused_en" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "txdma_overshoot_en" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_pkt_oversize_en" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tx_pkt_oversize_en" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "data_buff_bitmap_full_write_en" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "data_buff_bitmap_empty_read_en" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "tx_pre_sch_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "tx_pre_sch_fifo_empty_read_en" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "rx_pre_sch_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "rx_pre_sch_fifo_empty_read_en" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "tx_bm_key_info_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "tx_bm_key_info_fifo_empty_read_en" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "rx_bm_key_info_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "rx_bm_key_info_fifo_empty_read_en" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "tx_bm_eop_info_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "tx_bm_eop_info_fifo_empty_read_en" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "rx_bm_eop_info_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "rx_bm_eop_info_fifo_empty_read_en" },

	{ false, true, UTOOL_REG_LOC18, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "tx_credit_overused" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "txdma_overshoot" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_pkt_oversize" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tx_pkt_oversize" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "data_buff_bitmap_full_write" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "data_buff_bitmap_empty_read" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "tx_pre_sch_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "tx_pre_sch_fifo_empty_read" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "rx_pre_sch_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "rx_pre_sch_fifo_empty_read" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "tx_bm_key_info_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "tx_bm_key_info_fifo_empty_read" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "rx_bm_key_info_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "rx_bm_key_info_fifo_empty_read" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "tx_bm_eop_info_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "tx_bm_eop_info_fifo_empty_read" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "rx_bm_eop_info_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "rx_bm_eop_info_fifo_empty_read" },

	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "bps_hos_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "bps_hos_fifo_empty_read_en" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "bps_mac_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "bps_mac_fifo_empty_read_en" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout9_en" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout8_en" },
	{ false, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout7_en" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout6_en" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout5_en" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout4_en" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout3_en" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout2_en" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout1_en" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout0_en" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "ig_tx_bitmap_full_write_en" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "ig_tx_bitmap_empty_read_en" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "ig_rx_bitmap_full_write_en" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "ig_rx_bitmap_empty_read_en" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "ig_rx_3w1r_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "ig_rx_3w1r_fifo_empty_read_en" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "ig_tx_key_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "ig_tx_key_fifo_empty_read_en" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "ig_rx_key_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "ig_rx_key_fifo_empty_read_en" },

	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "bps_hos_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "bps_hos_fifo_empty_read" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "bps_mac_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "bps_mac_fifo_empty_read" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout9" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout8" },
	{ false, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout7" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout6" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout5" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout4" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout3" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout2" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout1" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout0" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "ig_tx_bitmap_full_write" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "ig_tx_bitmap_empty_read" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "ig_rx_bitmap_full_write" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "ig_rx_bitmap_empty_read" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "ig_rx_3w1r_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "ig_rx_3w1r_fifo_empty_read" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "ig_tx_key_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "ig_tx_key_fifo_empty_read" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "ig_rx_key_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "ig_rx_key_fifo_empty_read" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "eg_hos_fifo7_full_write_en" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "eg_hos_fifo7_empty_read_en" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "eg_hos_fifo6_full_write_en" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "eg_hos_fifo6_empty_read_en" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "eg_hos_fifo5_full_write_en" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "eg_hos_fifo5_empty_read_en" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "eg_hos_fifo4_full_write_en" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "eg_hos_fifo4_empty_read_en" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "eg_hos_fifo3_full_write_en" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "eg_hos_fifo3_empty_read_en" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "eg_hos_fifo2_full_write_en" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "eg_hos_fifo2_empty_read_en" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "eg_hos_fifo1_full_write_en" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "eg_hos_fifo1_empty_read_en" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "eg_hos_fifo0_full_write_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "eg_hos_fifo0_empty_read_en" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "eg_hos_fifo7_full_write" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "eg_hos_fifo7_empty_read" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "eg_hos_fifo6_full_write" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "eg_hos_fifo6_empty_read" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "eg_hos_fifo5_full_write" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "eg_hos_fifo5_empty_read" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "eg_hos_fifo4_full_write" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "eg_hos_fifo4_empty_read" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "eg_hos_fifo3_full_write" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "eg_hos_fifo3_empty_read" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "eg_hos_fifo2_full_write" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "eg_hos_fifo2_empty_read" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "eg_hos_fifo1_full_write" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "eg_hos_fifo1_empty_read" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "eg_hos_fifo0_full_write" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "eg_hos_fifo0_empty_read" },

	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "eg_rx_p2p_queueid_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "eg_rx_p2p_queueid_fifo_empty_read" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "eg_rx_p2p_ackid_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "eg_rx_p2p_ackid_fifo_empty_read" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "eg_rx_p2p_bypass_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "eg_rx_p2p_bypass_fifo_empty_read" },

	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START,
	  "eg_rx_p2p_queueid_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START,
	  "eg_rx_p2p_queueid_fifo_empty_read_en" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "eg_rx_p2p_ackid_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "eg_rx_p2p_ackid_fifo_empty_read_en" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START,
	  "eg_rx_p2p_bypass_fifo_full_write_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START,
	  "eg_rx_p2p_bypass_fifo_empty_read_en" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dup_mem_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cmd_fifo_eop_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "cmd_fifo_rlt_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "cmd_fifo_key_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "oq_pd_bank3_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "oq_pd_bank2_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "oq_pd_bank1_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "oq_pd_bank0_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "bm_data_row7_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "bm_data_row6_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "bm_data_row5_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "bm_data_row4_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "bm_data_row3_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "bm_data_row2_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "bm_data_row1_ecc_merr_int" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "bm_data_row0_ecc_merr_int" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_ecc_merr_int_en" },

	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "link_credit_ageing_th" },

	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "ssu_tx_port_dfx_sel(NL_SSU_IO_GLB)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "ssu_rx_port_dfx_sel(NL_SSU_IO_GLB)" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_bp_status" },

	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "ssu_p2p_q_sel_index" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "p2p_q_req_cell_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_q_specu_cell_num" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "p2p_q_wait_data_ack_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_q_cur_no_specu_num" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "p2p_q_get_credit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_q_wait_retry_cnt" },

	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "p2p_q_status_3" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "p2p_q_during_retry" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "p2p_q_pre_sch_fifo_empty" },

	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "ssu_oq_sel_index" },

	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "oq_inner_status_0" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "tc_sch_rdy" },
	{ false, true, UTOOL_REG_LOC18, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "oq_pre_sch_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "queue_cnt" },

	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "cmd_get_indx_sel" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "cmd_get_rlt_status" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "cmd_get_eop_status" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cmd_get_info_status" },

	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "data_buff_bitmap_full" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "data_buff_bitmap_empty" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "tx_bm_key_info_fifo_empty" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "rx_bm_key_info_fifo_empty" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "tx_bm_eop_info_fifo_empty" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "rx_bm_eop_info_fifo_empty" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_add_th0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_bp_add_th1" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_add_th2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_bp_add_th3" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_add_th4" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_bp_add_th5" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_add_th6" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_bp_add_th7" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_add_th8" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_bp_add_th9" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ssu_p2p_specu_more_th" },

	{ false, true, UTOOL_REG_LOC4, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "master_p2p_credit_init(NL_SSU)" },

	{ false, true, UTOOL_REG_LOC12, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "eg_hos_clk_gating_i" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "eg_hos_clk_gating_e" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "eg_mac_clk_gating_i" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "eg_mac_clk_gating_e" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "eg_clk_gating_i" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "eg_clk_gating_e" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "ig_hosbuf_clk_gating_i" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "ig_hosbuf_clk_gating_e" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "ig_macbuf_clk_gating_i" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "ig_macbuf_clk_gating_e" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "ig_clk_gating_i" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "ig_clk_gating_e" },

	{ false, true, UTOOL_REG_LOC19, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty18" },
	{ false, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty17" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty16" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty15" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty14" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty13" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty12" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty11" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty10" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty9" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty8" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty7" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty6" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty5" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty4" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty3" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty2" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "bm_pre_sch_fifo_empty0" },

	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "oq_inner_status_1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "queue_wait_retry_cnt" },

	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "ssu_macmux_fifo_cnt" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ppp_rlt_drop_num" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ppp_nl_ram_ecc_1b_int" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ppp_nl_ram_ecc_2b_int" },

	{ false, true, UTOOL_REG_LOC3, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "ppp_nl_eth_link_rlt_fifo_ovf" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "ppp_nl_int_rx_fifo_ovf" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "ppp_nl_int_rx_lpbk_fifo_ovf" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dup_mem_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cmd_fifo_eop_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "cmd_fifo_rlt_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "cmd_fifo_key_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "oq_pd_bank3_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "oq_pd_bank2_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "oq_pd_bank1_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "oq_pd_bank0_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "bm_data_row7_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "bm_data_row6_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "bm_data_row5_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "bm_data_row4_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "bm_data_row3_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "bm_data_row2_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "bm_data_row1_ecc_serr_int" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "bm_data_row0_ecc_serr_int" },

	{ false, true, UTOOL_REG_LOC22, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "ub_rx_credit_rcv_overtime_int" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "ub_rx_credit_rcv_overflow_int" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "ets_wr_int_tx_port" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "ets_rd_int_tx_port" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "hi_water_line_err_port" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "low_water_line_err_port" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "eg_mac_fifo_full_write" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "eg_mac_fifo_empty_read" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "eg_pfa_credit_return_too_much" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rx_pkt_more_key_port" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "tx_pkt_more_key_port" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "rx_sop_mis_match_port" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "tx_sop_mis_match_port" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "rx_eop_mis_match_port" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "tx_eop_mis_match_port" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "rx_pkt_without_key_port" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "tx_pkt_without_key_port" },

	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "tx_ub_bypass_en_cfg" },

	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cfg_ssu_mirror_en" },

	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "cfg_ot_link_down_flag_en" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "cfg_link_down_response_en" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "cfg_ot_link_down_flag_th" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "cfg_ot_link_down_waiting_th" },

	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "igu_no_vlan_map_pri_cfg" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "igu_pri7_map_tc_cfg" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "igu_pri6_map_tc_cfg" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "igu_pri5_map_tc_cfg" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "igu_pri4_map_tc_cfg" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "igu_pri3_map_tc_cfg" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "igu_pri2_map_tc_cfg" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "igu_pri1_map_tc_cfg" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "igu_pri0_map_tc_cfg" },

	{ false, true, UTOOL_REG_LOC4, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START,
	  "master_p2p_credit_init(NL_SSU_IO)" },

	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "p2p_nl7_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "p2p_nl6_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "p2p_nl5_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "p2p_nl4_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_nl3_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START,  "p2p_nl2_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START,   "p2p_nl1_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START,   "p2p_nl0_mst_req_ost" },

	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "p2p_nl15_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "p2p_nl14_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "p2p_nl13_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "p2p_nl12_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_nl11_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "p2p_nl10_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "p2p_nl9_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "p2p_nl8_mst_req_ost" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_nl19_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "p2p_nl18_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "p2p_nl17_mst_req_ost" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "p2p_nl16_mst_req_ost" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_field_info g_utool_ssu_stats_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_ppp_mac_key_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_ppp_host_key_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ppp_ssu_mac_rlt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ppp_ssu_host_rlt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "full_drop_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "part_drop_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ppp_rlt_drop_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "nic_tx_l2_err_drop_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_tx_l2_err_drop_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "nic_rx_l2_err_drop_pktcnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_rx_l2_err_drop_pkt_cnt" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_tx_oversize_drop_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ssu_rx_oversize_drop_num" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mb_uncopy_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "multicast_buf_drop_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_oq_drop_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_oq_drop_pkt_cnt" },

	{ false, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "multicast_buf_cur_cnt" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_ppp_multicast_rd_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ppp_rd_rlt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ppp_rd_rlt_drop_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_in_drop_ind_drop_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_in_drop_ind_drop_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_in_bypass_drop_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_in_bypass_drop_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_in_drop_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_packet_in_drop_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_in_bypass_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_packet_in_bypass_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx2rx_packet_in_bypass_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx2tx_packet_in_bypass_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_ub_packet_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_ub_packet_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_ub_packet_out_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_in_err_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_packet_in_err_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_out_err_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_packet_out_err_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_nic_packet_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_nic_packet_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_nic_packet_out_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_nic_packet_out_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_ig_bitmap_used_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "tx_ig_bitmap_used_cnt" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout_cnt0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout_cnt1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout_cnt2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout_cnt3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout_cnt4" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout_cnt5" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout_cnt6" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout_cnt7" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout_cnt8" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_bp_timeout_cnt9" },

	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_eg_rxdma_fifo_cnt7" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "ssu_eg_rxdma_fifo_cnt6" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "ssu_eg_rxdma_fifo_cnt5" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "ssu_eg_rxdma_fifo_cnt4" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ssu_eg_rxdma_fifo_cnt3" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "ssu_eg_rxdma_fifo_cnt2" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "ssu_eg_rxdma_fifo_cnt1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "ssu_eg_rxdma_fifo_cnt0" },

	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "ssu_eg_p2p_fifo_cnt1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "ssu_eg_p2p_fifo_cnt0" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt4" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt5" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt6" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt7" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt8" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt9" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt10" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt11" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt12" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt13" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_queue_out_cnt14" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_p2p_bypass_out_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_eg_rsv_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_ig_rsv_cnt" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_rsv_cnt_1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ssu_rsv_cnt_0" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_packet_in_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_packet_out_cnt" },

	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "macmux_ssu_credit_cnt" },

	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "ssu_macmux_fifo_cnt" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_packet_in_vl_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_packet_in_vl_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_packet_out_vl_cnt" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_full_drop_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_part_drop_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_rx_bypass_drop_num" },

	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "rxdma_ssu_bp_status" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "ssu_rxpa_pfc_status" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rxpa_ssu_pfc_status" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_tomac_pkt_len_cnt_1_160" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_tomac_pkt_len_cnt_161_320" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_tomac_pkt_len_cnt_321_480" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_tomac_pkt_len_cnt_481_640" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_tomac_pkt_len_cnt_641_800" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_tomac_pkt_len_cnt_801_1600" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_tomac_pkt_len_cnt_1601_2400" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_tomac_pkt_len_cnt_2401_3200" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_tomac_pkt_len_cnt_3201_4000" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ssu_tomac_pkt_len_cnt_4000_lt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "link_credit_vl_ageing_en" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_ub_packet_out_cnt" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_field_info g_utool_nl_abn_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "eth_com_err_sts(TX)" },
	{ true, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "outer_sctp_len_err(TX)" },
	{ true, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "outer_udp_len_err(TX)" },
	{ true, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "outer_udp_len_less_8(TX)" },
	{ true, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "outer_ipv6_ex_hd_less(TX)" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "outer_ipv6_hl_eq_0(TX)" },
	{ true, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "outer_ipv4_ttl_eq_0(TX)" },
	{ true, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "outer_ipv4_ihl_less(TX)" },
	{ true, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "igu_outer_sctp_hdr_less(TX)" },
	{ true, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "igu_outer_tcp_hdr_less(TX)" },
	{ true, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "igu_outer_udp_hdr_less(TX)" },
	{ true, false, UTOOL_REG_LOC22, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "igu_outer_ipv6_addr_less(TX)" },
	{ true, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "igu_outer_ipv6_ver_err(TX)" },
	{ true, true, UTOOL_REG_LOC24, UTOOL_REG_LOC25, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC26, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "outer_ipv6_total_len_less(TX)" },
	{ true, false, UTOOL_REG_LOC27, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "outer_ipv4_total_len_less(TX)" },
	{ true, false, UTOOL_REG_LOC28, UTOOL_REG_LOC28, UTOOL_FIELD_INDEX_START, "igu_outer_ipv4_addr_less(TX)" },
	{ true, false, UTOOL_REG_LOC29, UTOOL_REG_LOC29, UTOOL_FIELD_INDEX_START, "outer_l2_hdr_less(TX)" },
	{ true, false, UTOOL_REG_LOC30, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "igu_outer_ipv4_ihl_less5(TX)" },
	{ true, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "igu_outer_ipv4_ver_err(TX)" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "input_excptions(TX)" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_pkt_nlp_err_sts(TX)" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_pkt_fld_err_sts(TX)" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_pkt_len_err_sts(TX)" },

	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "eth_com_err_sts(RX)" },
	{ true, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "outer_sctp_len_err(RX)" },
	{ true, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "outer_udp_len_err(RX)" },
	{ true, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "outer_udp_len_less_8(RX)" },
	{ true, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "outer_ipv6_ex_hd_less(RX)" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "outer_ipv6_hl_eq_0(RX)" },
	{ true, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "outer_ipv4_ttl_eq_0(RX)" },
	{ true, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "outer_ipv4_ihl_less(RX)" },
	{ true, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "igu_outer_sctp_hdr_less(RX)" },
	{ true, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "igu_outer_tcp_hdr_less(RX)" },
	{ true, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "igu_outer_udp_hdr_less(RX)" },
	{ true, false, UTOOL_REG_LOC22, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "igu_outer_ipv6_addr_less(RX)" },
	{ true, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "igu_outer_ipv6_ver_err(RX)" },
	{ true, true, UTOOL_REG_LOC24, UTOOL_REG_LOC25, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC26, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "outer_ipv6_total_len_less(RX)" },
	{ true, false, UTOOL_REG_LOC27, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "outer_ipv4_total_len_less(RX)" },
	{ true, false, UTOOL_REG_LOC28, UTOOL_REG_LOC28, UTOOL_FIELD_INDEX_START, "igu_outer_ipv4_addr_less(RX)" },
	{ true, false, UTOOL_REG_LOC29, UTOOL_REG_LOC29, UTOOL_FIELD_INDEX_START, "outer_l2_hdr_less(RX)" },
	{ true, false, UTOOL_REG_LOC30, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "igu_outer_ipv4_ihl_less5(RX)" },
	{ true, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "igu_outer_ipv4_ver_err(RX)" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "input_excptions(RX)" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_pkt_nlp_err_sts(RX)" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_pkt_fld_err_sts(RX)" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_pkt_len_err_sts(RX)" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_field_info g_utool_ssu_sw_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "index" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cmd_get_info_status" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "cmd_get_eop_status" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "cmd_get_rlt_status" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "cmd_get_indx_sel" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_field_info g_utool_ssu_oq_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "ssu_oq_sel_index" },
	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "oq_inner_status_0" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "tc_sch_rdy" },
	{ false, true, UTOOL_REG_LOC18, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "oq_pre_sch_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "queue_cnt" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_field_info g_utool_ssu_p2p_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "ssu_p2p_q_sel_index" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "p2p_q_req_cell_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_q_specu_cell_num" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "p2p_q_wait_data_ack_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_q_cur_no_specu_num" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "p2p_q_get_credit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_q_wait_retry_cnt" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "p2p_q_status_3" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "p2p_q_during_retry" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "p2p_q_pre_sch_fifo_empty" },
};

struct utool_cal_reg_cnt_dp g_utool_nl_cal_reg_table[] = {
	{ true, true, NL_PKT_STATS, UTOOL_ARRAY_SIZE(g_utool_pkt_stats_field_info), g_utool_pkt_stats_field_info },
	{ true, true, NL_SSU_STATS, UTOOL_ARRAY_SIZE(g_utool_ssu_stats_field_info), g_utool_ssu_stats_field_info },
	{ true, true, NL_ABN_STATS, UTOOL_ARRAY_SIZE(g_utool_nl_abn_field_info), g_utool_nl_abn_field_info },
	{ true, false, NL_SSU_SW, UTOOL_ARRAY_SIZE(g_utool_ssu_sw_field_info), g_utool_ssu_sw_field_info },
	{ true, false, NL_SSU_OQ, UTOOL_ARRAY_SIZE(g_utool_ssu_oq_field_info), g_utool_ssu_oq_field_info },
	{ true, false, NL_SSU_P2P, UTOOL_ARRAY_SIZE(g_utool_ssu_p2p_field_info), g_utool_ssu_p2p_field_info },
};

static void utool_nl_print_help(void)
{
	utool_err_msg("The ubctl nl command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m nl -p ${port}\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m nl -f pkt_stats/abn_stats/ssu_stats -p ${port}\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m nl -f ssu_sw/ssu_oq/ssu_p2p -p ${port} -i ${index}\n");
}

int utool_nl_cal_data_len(uint32_t *nl_data_len)
{
	struct utool_cal_reg_func_param nl_cal_reg_param = {
		nl_data_len, UTOOL_REG_CNT_DEFAULT, NULL,
		g_utool_nl_cal_reg_table, UTOOL_ARRAY_SIZE(g_utool_nl_cal_reg_table)
	};
	int ret = UTOOL_OK;

	if (nl_data_len == NULL) {
		utool_err_msg("Param is invalid, nl data len is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_cal_func_reg_len(UTOOL_FUNC_ALL, &nl_cal_reg_param);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate reg cnt, ret = %d.\n", ret);
		return ret;
	}

	return UTOOL_OK;
}

static int utool_nl_pkt_stats_parse_rpc_pkt(struct fwctl_rpc_ub_out *nl_pkt_stats_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(nl_pkt_stats_out, UTOOL_ARRAY_SIZE(g_utool_pkt_stats_field_info),
			      g_utool_pkt_stats_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_NL, NL_PKT_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse nl pkt stats data.\n");
	}

	return ret;
}

static int utool_nl_ssu_stats_parse_rpc_pkt(struct fwctl_rpc_ub_out *nl_ssu_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(nl_ssu_out, UTOOL_ARRAY_SIZE(g_utool_ssu_stats_field_info),
			      g_utool_ssu_stats_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_NL, NL_SSU_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse nl ssu stats data.\n");
	}

	return ret;
}

static int utool_nl_abn_stats_parse_rpc_pkt(struct fwctl_rpc_ub_out *nl_abn_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(nl_abn_out, UTOOL_ARRAY_SIZE(g_utool_nl_abn_field_info),
			      g_utool_nl_abn_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_NL, NL_ABN_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse nl abn stats data.\n");
	}

	return ret;
}

static int utool_ssu_sw_parse_rpc_pkt(struct fwctl_rpc_ub_out *ssu_sw_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(ssu_sw_out, UTOOL_ARRAY_SIZE(g_utool_ssu_sw_field_info),
			      g_utool_ssu_sw_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_NL, NL_SSU_SW));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse nl ssu sw data.\n");
	}

	return ret;
}

static int utool_ssu_oq_parse_rpc_pkt(struct fwctl_rpc_ub_out *ssu_oq_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(ssu_oq_out, UTOOL_ARRAY_SIZE(g_utool_ssu_oq_field_info),
			      g_utool_ssu_oq_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_NL, NL_SSU_OQ));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse nl ssu oq data.\n");
	}

	return ret;
}

static int utool_ssu_p2p_parse_rpc_pkt(struct fwctl_rpc_ub_out *ssu_p2p_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(ssu_p2p_out, UTOOL_ARRAY_SIZE(g_utool_ssu_p2p_field_info),
			      g_utool_ssu_p2p_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_NL, NL_SSU_P2P));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse nl ssu p2p data.\n");
	}

	return ret;
}

struct utool_func_dispatch g_utool_nl_func_table[] = {
	{ true, NL_PKT_STATS, UTOOL_CMD_QUERY_NL_PKT_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_nl_pkt_stats_parse_rpc_pkt, utool_port_create_pkt_in },
	{ true, NL_SSU_STATS, UTOOL_CMD_QUERY_NL_SSU_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_nl_ssu_stats_parse_rpc_pkt, utool_port_create_pkt_in },
	{ true, NL_ABN_STATS, UTOOL_CMD_QUERY_NL_ABN, UTOOL_REG_CNT_DEFAULT,
	  utool_nl_abn_stats_parse_rpc_pkt, utool_port_create_pkt_in },
};

struct utool_func_dispatch g_utool_nl_ssu_func_table[] = {
	{ false, NL_SSU_SW, UTOOL_CMD_QUERY_NL_SSU_SW, UTOOL_REG_CNT_DEFAULT,
	  utool_ssu_sw_parse_rpc_pkt, utool_port_index_create_pkt_in },
	{ false, NL_SSU_OQ, UTOOL_CMD_QUERY_NL_SSU_OQ, UTOOL_REG_CNT_DEFAULT,
	  utool_ssu_oq_parse_rpc_pkt, utool_port_index_create_pkt_in },
	{ false, NL_SSU_P2P, UTOOL_CMD_QUERY_NL_SSU_P2P, UTOOL_REG_CNT_DEFAULT,
	  utool_ssu_p2p_parse_rpc_pkt, utool_port_index_create_pkt_in },
};

static int utool_nl_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			     struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_BUTT, 0, NULL };
	struct utool_cal_reg_func_param nl_cal_reg_param = {
		NULL, 0, NULL, g_utool_nl_cal_reg_table, UTOOL_ARRAY_SIZE(g_utool_nl_cal_reg_table)
	};
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;
	uint32_t i;

	for (i = 0; i < func_cnt; i++) {
		if (strcmp(param->func, func_table[i].func) == 0) {
			func_pkt_exec.rpc_cmd = func_table[i].rpc_cmd;
			func_pkt_exec.execute = func_table[i].execute;

			nl_cal_reg_param.data_len = &func_pkt_exec.data_len;
			nl_cal_reg_param.user_def_data_len = func_table[i].data_len;

			ret = utool_cal_func_reg_len(param->func, &nl_cal_reg_param);
			if (ret != UTOOL_OK) {
				utool_err_msg("Failed to cal nl func %s reg cnt.\n", param->func);
				return ret;
			}

			if (func_table[i].create_pkt_in == NULL) {
				utool_err_msg("Failed to create nl func pkt in, create pkt in is NULL.\n");
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
	}
	utool_nl_print_help();

	return UTOOL_ERR_FUNC_NOT_FOUND;
}

int utool_nl_parse_rpc_pkt(struct fwctl_rpc_ub_out *nl_out)
{
	int ret = UTOOL_OK;

	if (nl_out == NULL) {
		utool_err_msg("Param is invalid, nl out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_module_parse(nl_out, UTOOL_ARRAY_SIZE(g_utool_nl_func_table), g_utool_nl_func_table,
				 UTOOL_ARRAY_SIZE(g_utool_nl_cal_reg_table), g_utool_nl_cal_reg_table);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse nl rpc pkt.\n");
		return ret;
	}

	return UTOOL_OK;
}

static int utool_nl_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
			struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_NL, 0, NULL };
	int ret = UTOOL_OK;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	func_pkt_exec.execute = utool_nl_parse_rpc_pkt;

	ret = utool_nl_cal_data_len(&func_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate reg cnt of nl all, ret = %d.\n", ret);
		return ret;
	}

	ret = utool_pkt_operation_have_port(dev, param, &func_pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	return ret;
}

int utool_nl_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_nl_cmd_table[] = {
		{
			UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F,
			utool_nl_cmd_func, g_utool_nl_func_table, UTOOL_ARRAY_SIZE(g_utool_nl_func_table)
		}, {
			UTOOL_FLAG_M | UTOOL_FLAG_P, utool_nl_cmd,
			g_utool_nl_func_table, UTOOL_ARRAY_SIZE(g_utool_nl_func_table)
		}, {
			UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_I,
			utool_nl_cmd_func,
			g_utool_nl_ssu_func_table, UTOOL_ARRAY_SIZE(g_utool_nl_ssu_func_table)
		}
	};
	uint32_t nl_cmd_cnt = UTOOL_ARRAY_SIZE(utool_nl_cmd_table);
	uint32_t i = 0;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < nl_cmd_cnt; i++) {
		if (param->flags == utool_nl_cmd_table[i].flags) {
			if (utool_nl_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch. Callback is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

			return utool_nl_cmd_table[i].execute(dev, param,
							     utool_nl_cmd_table[i].func_table,
							     utool_nl_cmd_table[i].func_cnt);
		}
	}

	utool_nl_print_help();

	return UTOOL_ERR_CMD_NOT_FOUND;
}
