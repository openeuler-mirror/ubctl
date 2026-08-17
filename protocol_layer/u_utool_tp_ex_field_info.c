// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_tp_ex_field_info.h"

struct utool_field_info g_utool_tp_rx_bank_field_info[] = {
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "bank_id" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "cnt_clr_ce" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "snap_en" },
	{ true, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_tx_in_lpbk_pkt_in_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_tx_in_lpbk_pkt_in_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_tx_in_route_pkt_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_tx_in_route_pkt_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_ub_pkt_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_in_ub_pkt_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_uboe_pkt_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_in_uboe_pkt_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_unic_pkt_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_in_unic_pkt_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_out_default_pkt_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_out_default_pkt_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_eid_upi_zero_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_npi_zero_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_guid_zero_cnt" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_in_mc_req_pkt_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_in_mc_req_pkt_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_in_mc_req_single_pkt_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_in_mc_req_single_pkt_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_in_mc_drop_pkt_cnt" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_tx_out_pkt_lpbk_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_tx_out_pkt_lpbk_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_tx_out_pkt_route_drop_total_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_tx_out_pkt_soft_assign_total_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_uc_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_uc_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_mc_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_mc_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_d2h_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_d2h_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_drop_total_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_no_des_drop_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_ecc_drop_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_mbid_full_drop_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_out_mc_pkt_total_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_out_mc_pkt_total_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_out_mc_pkt_drop_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_link_up_status" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_0_fifo_empty" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_0_fifo_full" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_0_fifo_ovf" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_0_fifo_cnt" },
	{ true, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_1_fifo_empty" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_1_fifo_full" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_1_fifo_ovf" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_1_fifo_cnt" },
	{ true, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_0_fifo_empty" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_0_fifo_full" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_0_fifo_ovf" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_0_fifo_cnt" },
	{ true, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_1_fifo_empty" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_1_fifo_full" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_1_fifo_ovf" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_1_fifo_cnt" },
	{ true, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_lkup_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_dip_lkup_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_compact_lkup_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_tbl_hit_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_tbl_drop_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_tbl_miss_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "ppp_tp_dip_cam_cnt" },
	{ true, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_lkup_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_deid_lkup_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_compact_lkup_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_tbl_hit_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_tbl_drop_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_tbl_upi_drop_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "ppp_tp_deid_cam_cnt" },
	{ true, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_d2h_eid_lkup_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_d2h_eid_tbl_drop_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_d2h_ubc_lkup_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_d2h_ubc_tbl_drop_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_h2d_tbl_hit_pass_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_h2d_tbl_hit_fail_cnt" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_npi_lkup_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_npi_lkup_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ppp_tp_npi_filter_drop_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_bonding_trunk0_lkup_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_bonding_trunk0_lkup_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_bonding_trunk1_lkup_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_bonding_trunk1_lkup_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_guid_lkup_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_guid_lkup_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_guid_tbl_hit_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_guid_tbl_drop_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dguid_hit_uc_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dguid_hit_mc_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_promis_lkup_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_promis_lkup_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_multi_tbl_lkup_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_multi_tbl_lkup_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_multi_tbl_rlt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_multi_tbl_rlt_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_avl_mbid_cnt" },
	{ true, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_mbid_aempty" },
	{ true, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_fifo_ovf" },
	{ true, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_fifo_full" },
	{ true, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_fifo_empty" },
	{ true, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_lite_rss_err_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "ppp_tp_lite_rss_err_function" },
	{ true, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

struct utool_field_info g_utool_tp_rx_bank_field_info_bank1[] = {
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "bank_id" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_total_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_total_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_ub_pkt_total_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_in_ub_pkt_total_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_uboe_pkt_total_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_in_uboe_pkt_total_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_unic_pkt_total_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_in_unic_pkt_total_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_out_default_pkt_total_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL,
	  "ppp_tp_a_out_default_pkt_total_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_eid_upi_zero_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_npi_zero_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_guid_zero_cnt_bank1" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_in_mc_req_pkt_total_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_in_mc_req_pkt_total_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_in_mc_req_single_pkt_total_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL,
	  "ppp_tp_in_mc_req_single_pkt_total_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_in_mc_drop_pkt_cnt_bank1" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_total_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_total_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_uc_total_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_uc_total_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_mc_total_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_mc_total_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_d2h_total_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_d2h_total_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_drop_total_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_no_des_drop_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_ecc_drop_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_mbid_full_drop_cnt_bank1" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_out_mc_pkt_total_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_out_mc_pkt_total_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_out_mc_pkt_drop_cnt_bank1" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_0_fifo_empty_bank1" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_0_fifo_full_bank1" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_0_fifo_ovf_bank1" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_0_fifo_cnt_bank1" },
	{ true, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_1_fifo_empty_bank1" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_1_fifo_full_bank1" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_1_fifo_ovf_bank1" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_1_fifo_cnt_bank1" },
	{ true, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_0_fifo_empty_bank1" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_0_fifo_full_bank1" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_0_fifo_ovf_bank1" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_0_fifo_cnt_bank1" },
	{ true, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_1_fifo_empty_bank1" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_1_fifo_full_bank1" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_1_fifo_ovf_bank1" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_1_fifo_cnt_bank1" },
	{ true, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_lkup_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_dip_lkup_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_compact_lkup_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_tbl_hit_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_tbl_drop_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_tbl_miss_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "ppp_tp_dip_cam_cnt_bank1" },
	{ true, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_lkup_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_deid_lkup_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_compact_lkup_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_tbl_hit_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_tbl_drop_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_tbl_upi_drop_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "ppp_tp_deid_cam_cnt_bank1" },
	{ true, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_d2h_eid_lkup_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_d2h_eid_tbl_drop_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_d2h_ubc_lkup_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_d2h_ubc_tbl_drop_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_h2d_tbl_hit_pass_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_h2d_tbl_hit_fail_cnt_bank1" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_npi_lkup_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_npi_lkup_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ppp_tp_npi_filter_drop_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_guid_lkup_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_guid_lkup_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_guid_tbl_hit_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_guid_tbl_drop_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dguid_hit_uc_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dguid_hit_mc_cnt_bank1" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_promis_lkup_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_promis_lkup_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_multi_tbl_lkup_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_multi_tbl_lkup_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_multi_tbl_rlt_cnt_bank1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_multi_tbl_rlt_cnt_bank1" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_avl_mbid_cnt_bank1" },
	{ true, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_mbid_aempty_bank1" },
	{ true, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_fifo_ovf_bank1" },
	{ true, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_fifo_full_bank1" },
	{ true, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_fifo_empty_bank1" },
	{ true, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_lite_rss_err_cnt_bank1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "ppp_tp_lite_rss_err_function_bank1" },
	{ true, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

struct utool_field_info g_utool_tp_rx_bank_field_info_bank2[] = {
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "bank_id" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_total_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_total_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_ub_pkt_total_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_in_ub_pkt_total_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_uboe_pkt_total_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_in_uboe_pkt_total_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_unic_pkt_total_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_in_unic_pkt_total_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_out_default_pkt_total_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_a_out_default_pkt_total_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_eid_upi_zero_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_npi_zero_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_a_in_pkt_guid_zero_cnt_bank2" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_in_mc_req_pkt_total_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_in_mc_req_pkt_total_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_in_mc_req_single_pkt_total_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_in_mc_req_single_pkt_total_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_in_mc_drop_pkt_cnt_bank2" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_total_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_total_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_uc_total_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_uc_total_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_mc_total_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_mc_total_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_d2h_total_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_d2h_total_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_drop_total_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_no_des_drop_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_ecc_drop_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_b0_out_pkt_mbid_full_drop_cnt_bank2" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_out_mc_pkt_total_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_out_mc_pkt_total_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_out_mc_pkt_drop_cnt_bank2" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_0_fifo_empty_bank2" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_0_fifo_full_bank2" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_0_fifo_ovf_bank2" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_ig_nl_0_fifo_cnt_bank2" },
	{ true, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_0_fifo_empty_bank2" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_0_fifo_full_bank2" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_0_fifo_ovf_bank2" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_uboe_ig_nl_0_fifo_cnt_bank2" },
	{ true, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_lkup_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_dip_lkup_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_compact_lkup_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_tbl_hit_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_tbl_drop_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dip_tbl_miss_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "ppp_tp_dip_cam_cnt_bank2" },
	{ true, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_lkup_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_deid_lkup_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_compact_lkup_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_tbl_hit_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_tbl_drop_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_deid_tbl_upi_drop_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "ppp_tp_deid_cam_cnt_bank2" },
	{ true, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_d2h_eid_lkup_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_d2h_eid_tbl_drop_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_d2h_ubc_lkup_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_d2h_ubc_tbl_drop_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_h2d_tbl_hit_pass_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_h2d_tbl_hit_fail_cnt_bank2" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_npi_lkup_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_npi_lkup_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ppp_tp_npi_filter_drop_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_guid_lkup_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_guid_lkup_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_guid_tbl_hit_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_guid_tbl_drop_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dguid_hit_uc_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_dguid_hit_mc_cnt_bank2" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_promis_lkup_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_promis_lkup_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_multi_tbl_lkup_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_multi_tbl_lkup_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_multi_tbl_rlt_cnt_bank2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_multi_tbl_rlt_cnt_bank2" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, false, UTOOL_LOC0, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_avl_mbid_cnt_bank2" },
	{ true, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_mbid_aempty_bank2" },
	{ true, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_fifo_ovf_bank2" },
	{ true, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_fifo_full_bank2" },
	{ true, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "ppp_tp_cfg_mc_rslt_fifo_empty_bank2" },
	{ true, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_lite_rss_err_cnt_bank2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "ppp_tp_lite_rss_err_function_bank2" },
	{ true, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

struct utool_field_info g_utool_tp_abn_stats_field_info[] = {
	// opcode 0xA01D
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "port_id" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_tx_out_bonding_port_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "ppp_tp_tx_out_bonding_port_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqs_err_db_dfx_bk0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_ram_ecc_1b_int_bank0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_tp_ram_ecc_2b_int_bank0" },
};

struct utool_field_info g_utool_tp_tx_route_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_tab_miss_drop(tp_ppp_glb)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_lpm_hit" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_lpm_hit" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_lpm_drop" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_tab_hit_a" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_seg_tab_hit_a" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_tab_hit_b" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_seg_tab_hit_b" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_tab_hit_c" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_seg_tab_hit_c" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_tab_hit_d" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_seg_tab_hit_d" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_tab_hit_e" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_seg_tab_hit_e" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_tab_hit_f" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_seg_tab_hit_f" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_hit_a" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_hit_a" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_hit_b" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_hit_b" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_hit_c" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_hit_c" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_hit_d" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_hit_d" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_hit_e" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_hit_e" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_hit_f" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_hit_f" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_tab_drop_a" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_tab_drop_b" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_tab_drop_c" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_tab_drop_d" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_tab_drop_e" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_tab_drop_f" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_drop_a" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_drop_b" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_drop_c" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_drop_d" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_drop_e" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_seg_nt_tab_drop_f" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_def_tab_hit" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_def_tab_hit" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_def_nt_tab_hit" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_def_nt_tab_hit" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_def_tab_drop" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_def_nt_tab_drop" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_route_mirr_ind" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_route_mirr_ind" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_source_route_fwd" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_source_route_fwd" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static int utool_tp_check_field_info_len(void)
{
	if (UTOOL_ARRAY_SIZE(g_utool_tp_rx_bank_field_info) > FIELD_INFO_MAX_LEN ||
	    UTOOL_ARRAY_SIZE(g_utool_tp_abn_stats_field_info) > FIELD_INFO_MAX_LEN ||
	    UTOOL_ARRAY_SIZE(g_utool_tp_tx_route_field_info) > FIELD_INFO_MAX_LEN) {
		utool_err_msg("Field info length is too long, pls check!\n");
		return UTOOL_ERR;
	}

	return UTOOL_OK;
}

struct utool_field_info_dp *utool_tp_get_ex_field_info_by_name(const char *field_name)
{
	static struct utool_field_info_dp field_info_dp[] = {
		{ TP_RX_BANK_FIELD_INFO, UTOOL_ARRAY_SIZE(g_utool_tp_rx_bank_field_info),
		  g_utool_tp_rx_bank_field_info },
		{ TP_RX_BANK_FIELD_INFO_BANK1, UTOOL_ARRAY_SIZE(g_utool_tp_rx_bank_field_info_bank1),
		  g_utool_tp_rx_bank_field_info_bank1 },
		{ TP_RX_BANK_FIELD_INFO_BANK2, UTOOL_ARRAY_SIZE(g_utool_tp_rx_bank_field_info_bank2),
		  g_utool_tp_rx_bank_field_info_bank2 },
		{ TP_ABN_STATS_FIELD_INFO, UTOOL_ARRAY_SIZE(g_utool_tp_abn_stats_field_info),
		  g_utool_tp_abn_stats_field_info },
		{ TP_TX_ROUTE_FIELD_INFO, UTOOL_ARRAY_SIZE(g_utool_tp_tx_route_field_info),
		  g_utool_tp_tx_route_field_info },
	};
	uint32_t i;

	if (field_name == NULL || field_name[0] == '\0') {
		utool_err_msg("Field name is invalid.\n");
		return NULL;
	}

	if (utool_tp_check_field_info_len() != UTOOL_OK) {
		return NULL;
	}

	for (i = 0; i < UTOOL_ARRAY_SIZE(field_info_dp); i++) {
		if (strcmp(field_name, field_info_dp[i].field_name) == 0) {
			return &field_info_dp[i];
		}
	}

	utool_err_msg("Unknown field name: %s.\n", field_name);
	return NULL;
}
