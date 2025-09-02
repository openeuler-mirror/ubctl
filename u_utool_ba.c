// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_ba.h"

#define BA_PKT_STATS "pkt_stats"

static struct utool_field_info g_utool_ba_pkt_stats_field_info[] = {
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tlb_lkup_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tlb_retried_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tlb_rsp_suc_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tlb_rsp_fault_cnt" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_ta_req_hit_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dfx_tp_req_hit_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ba_eco_rw_reg" },
	{ true, true, UTOOL_REG_LOC3, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "p2p_type_sel_for_cqe" },
	{ true, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "p2p_type_sel_for_payl" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cbaw_en" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_sync_req_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dfx_sync_resp_cnt" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_inv_req_cnt0" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dfx_inv_req_cnt1" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_inv_req_cnt2" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dfx_inv_req_cnt3" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_inv_req_cnt4" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dfx_inv_req_cnt5" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_inv_req_cnt6" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dfx_inv_req_cnt7" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_rxdma_req_hit_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dfx_txdma_req_hit_cnt" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_ta_tp_dtlb_vld" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dfx_ta_tp_dtlb_pend" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_rxdma_dtlb_vld" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dfx_rxdma_dtlb_pend" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_txdma_dtlb_vld" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dfx_txdma_dtlb_pend" },
	{ true, true, UTOOL_REG_LOC7, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC4, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "dfx_uimmu_first_fault_permission" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC17, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "dfx_uimmu_first_fault_va_high" },
	{ true, false, UTOOL_REG_LOC12, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "dfx_uimmu_first_fault_va_low" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tp_wr_req_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tp_rd_req_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_ta_wr_req_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_ta_rd_req_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_txdma_wr_req_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_txdma_rd_req_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_rxdma_wr_req_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_rxdma_rd_req_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb0_wr_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb0_rd_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb0_awack_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb0_wlast_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb0_bresp_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb0_rd_outstanding" },
	{ true, true, UTOOL_REG_LOC7, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "amb0_rdata_ch1_bkpr" },
	{ true, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "amb0_rdata_ch0_bkpr" },
	{ true, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "amb0_awack_bkpr" },
	{ true, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "amb0_bresp_bkpr" },
	{ true, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "amb0_wdata_bkpr" },
	{ true, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "amb0_ar_ready" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "amb0_aw_bkpr" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb1_wr_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb1_rd_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb1_awack_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb1_wlast_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb1_bresp_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb1_rd_outstanding" },
	{ true, true, UTOOL_REG_LOC7, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "amb1_rdata_ch1_bkpr" },
	{ true, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "amb1_rdata_ch0_bkpr" },
	{ true, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "amb1_awack_bkpr" },
	{ true, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "amb1_bresp_bkpr" },
	{ true, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "amb1_wdata_bkpr" },
	{ true, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "amb1_ar_ready" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "amb1_aw_bkpr" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lkp_odr0_ctx0" },
	{ true, true, UTOOL_REG_LOC25, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC24, UTOOL_FIELD_INDEX_START, "lkp_odr0_ctx1" },
	{ true, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "lkp_odr0_ctx2" },
	{ true, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "lkp_odr0_ctx3" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lkp_odr0_outstanding" },
	{ true, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "lkp_odr0_idle" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lkp_odr1_ctx0" },
	{ true, true, UTOOL_REG_LOC25, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC24, UTOOL_FIELD_INDEX_START, "lkp_odr1_ctx1" },
	{ true, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "lkp_odr1_ctx2" },
	{ true, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "lkp_odr1_ctx3" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lkp_odr1_outstanding" },
	{ true, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "lkp_odr1_idle" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "amb0_ctx0" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC19, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "amb0_ctx2" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "amb0_idle" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "amb1_ctx0" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC19, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "amb1_ctx2" },
	{ true, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "amb1_idle" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC4, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "master_sub_icg_en" },
	{ true, true, UTOOL_REG_LOC1, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "master_icg_en" },
	{ true, true, UTOOL_REG_LOC12, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "master_us_time_set" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "axim0_max_read_delay" },
	{ true, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "am0_rd_max_dleay_clr" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "axim0_max_write_delay" },
	{ true, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "am0_wr_max_dleay_clr" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "axim1_max_read_delay" },
	{ true, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "am1_rd_max_dleay_clr" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "axim1_max_write_delay" },
	{ true, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "am1_wr_max_dleay_clr" },
	{ true, true, UTOOL_REG_LOC18, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC9, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "dfx_amb0_entry_max_wr_otsd" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "dfx_amb0_entry_max_rd_otsd" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb0_curr_ava_wr_latency" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dfx_amb0_curr_ava_rd_latency" },
	{ true, true, UTOOL_REG_LOC18, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC9, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "dfx_amb1_entry_max_wr_otsd" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "dfx_amb1_entry_max_rd_otsd" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_amb1_curr_ava_wr_latency" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "dfx_amb1_curr_ava_rd_latency" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_raw_pkt_q10_l2e_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_raw_pkt_q0_l2e_cnt" },
	{ true, true, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC24, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_in_raw_cnt" },
	{ true, false, UTOOL_REG_LOC20, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_in_be_cnt" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_in_imp_cnt" },
	{ true, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_in_reduce_cnt" },
	{ true, false, UTOOL_REG_LOC8, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_in_cqe_cnt" },
	{ true, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_in_ato_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_in_lsa_cnt" },
	{ true, true, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC24, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_out_raw_cnt" },
	{ true, false, UTOOL_REG_LOC20, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_out_be_cnt" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_out_imp_cnt" },
	{ true, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_out_reduce_cnt" },
	{ true, false, UTOOL_REG_LOC8, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_out_cqe_cnt" },
	{ true, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_out_ato_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_out_lsa_cnt" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_op_combine_cnt" },
	{ true, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_out_stash_vld_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rxdma_rwp_pkt_out_stash_nid_vld_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_intf_ro_dfx" },
	{ true, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC20, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_pkt_out_ato_store_cnt" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_pkt_out_be_cnt" },
	{ true, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_pkt_out_Imp_cnt" },
	{ true, false, UTOOL_REG_LOC8, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_pkt_out_reduce_cnt" },
	{ true, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_pkt_out_cas_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_pkt_out_faa_cnt" },
	{ true, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC20, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_pkt_in_ato_store_cnt" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_pkt_in_be_cnt" },
	{ true, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_pkt_in_Imp_cnt" },
	{ true, false, UTOOL_REG_LOC8, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_pkt_in_reduce_cnt" },
	{ true, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_pkt_in_cas_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_pkt_in_faa_cnt" },
	{ true, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC20, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START,
	  "rxdma_ubrx_cb_pkt_out_ato_store_cnt" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_cb_pkt_out_be_cnt" },
	{ true, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_cb_pkt_out_Imp_cnt" },
	{ true, false, UTOOL_REG_LOC8, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_cb_pkt_out_reduce_cnt" },
	{ true, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_cb_pkt_out_cas_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_cb_pkt_out_faa_cnt" },
	{ true, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC20, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START,
	  "rxdma_ubrx_cb_pkt_in_ato_store_cnt" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_cb_pkt_in_be_cnt" },
	{ true, false, UTOOL_REG_LOC12, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_cb_pkt_in_Imp_cnt" },
	{ true, false, UTOOL_REG_LOC8, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_cb_pkt_in_reduce_cnt" },
	{ true, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_cb_pkt_in_cas_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_cb_pkt_in_faa_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "txdma_ar_cnt_m1" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "txdma_r_cnt_m0" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "txdma_r_cnt_m1" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_tx_in_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "nic_tx_in_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_tx_out_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "nic_tx_out_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_c_tx_out_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_g_tx_out_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_c_tx_in_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_g_tx_in_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lsa_in_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lsa_out_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pfa_out_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mar_in_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mar_out_cnt_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "pa_out_cnt_err_g" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "memory_cnt_0" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "memory_cnt_1" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "memory_cnt_2" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "memory_cnt_3" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "p2p_bypass_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "hdr_credit_cnt_port0" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "data_credit_cnt_port0" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "hdr_credit_cnt_port2" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "data_credit_cnt_port2" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_tx_in_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "nic_tx_in_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_tx_out_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "nic_tx_out_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_c_tx_out_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_g_tx_out_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_c_tx_in_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_g_tx_in_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lsa_in_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lsa_out_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_ub_io_hdr_send_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_load_send_cnt" },

	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cfg_lsad_to_txdma_dat_cdt_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "cfg_lsad_to_txdma_hdr_cdt_num" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_alm" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_ubrx_sta" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mar_req_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "mar_ack_pkt_cnt" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "head_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cb_head_pkt_cnt" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "write_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cb_write_pkt_cnt" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "bresp_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cb_bresp_pkt_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "lsad_resp_pkt_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_load_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_abnormal_rsp_en" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_dat_ctx_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_atomic_dat_ctx_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_load_resp_incomplete_cnt" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rxdma_wr_payl_rwp_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rxdma_wr_payl_buff_pkt_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_load_resp_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_load_resp_send_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_ub_io_hdr_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_atomic_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_atomic_send_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_atomic_resp_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tx_atomic_resp_send_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cpu_seq_dat_only(lsad_chn_num0)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cpu_seq_dat_only(lsad_chn_num1)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cpu_seq_dat_only_send" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cpu_seq_dat(lsad_chn_num0)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cpu_seq_dat(lsad_chn_num1)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cpu_seq_dat_send" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cpu_seq_tx_rdat_send" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_p2p_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_p2p_send_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_spec_apl" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_spec_alced" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_sec_apl" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_sec_alced" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "rx_abnormal(lsad_rx_abnormal_num0)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "rx_abnormal(lsad_rx_abnormal_num1)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "rx_abnormal(lsad_rx_abnormal_num2)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "rx_abnormal(lsad_rx_abnormal_num3)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "rx_abnormal(lsad_rx_abnormal_num4)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "rx_abnormal(lsad_rx_abnormal_num5)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "rx_abnormal(lsad_rx_abnormal_num6)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "rx_abnormal(lsad_rx_abnormal_num7)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "rx_abnormal(lsad_rx_abnormal_num8)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "tx_abnormal(lsad_tx_abnormal_num0)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "tx_abnormal(lsad_tx_abnormal_num1)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "tx_abnormal(lsad_tx_abnormal_num2)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "tx_abnormal(lsad_tx_abnormal_num3)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "tx_abnormal(lsad_tx_abnormal_num4)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "tx_abnormal(lsad_tx_abnormal_num5)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "tx_abnormal(lsad_tx_abnormal_num6)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "tx_abnormal(lsad_tx_abnormal_num7)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "tx_abnormal(lsad_tx_abnormal_num8)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "tx_abnormal(lsad_tx_abnormal_num9)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START,
	  "tx_abnormal(lsad_tx_abnormal_num10)" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cfg_abnormal_err_rsp" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cfg_abnormal_poison" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "axim_timeout_int_src" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "master_amb_timeout" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "ctrl_err_wdata_mode" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "ctrl_err_data_wr" },
	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "mem_attr_cfg" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "mem_type_cfg" },
	{ false, true, UTOOL_REG_LOC5, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "sh_cfg" },
	{ false, true, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "abort_all" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cfg_atp_tlb_inv_all_rsp_entry" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "cfg_atp_conf_inv_all_rsp_entry" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "cfg_atp_sync_clr_all_no_rsp_entry" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "cfg_atp_sync_clr_all_stale_entry" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "cfg_atp_inv_record_mode" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "cfg_atp_apat_tlbi_vav_disable" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "cfg_atp_req_entry_rls_mode" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cfg_atp_tlbi_accurate_math_en" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "cfg_atp_tlbi_pgsz_predict_en" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "cfg_atp_range_tlbi_disable" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "cfg_dtlb_pend_match_pgsz" },
	{ false, true, UTOOL_REG_LOC19, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "master_idle" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "lkp_odr_idle" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "amb_idle" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "atp_idle" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "atp_inv_bitmap_idle" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "wdp_idle" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "p2p_idle" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "device_status0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "device_status1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "device_status2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "device_status3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "device_status4" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};


struct utool_cal_reg_cnt_dp g_utool_ba_cal_reg_table[] = {
	{ true, true, BA_PKT_STATS, UTOOL_ARRAY_SIZE(g_utool_ba_pkt_stats_field_info),
	  g_utool_ba_pkt_stats_field_info },
};

static int utool_ba_pkt_stats_parse_rpc_pkt(struct fwctl_rpc_ub_out *ba_pkt_stats_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(ba_pkt_stats_out, UTOOL_ARRAY_SIZE(g_utool_ba_pkt_stats_field_info),
			      g_utool_ba_pkt_stats_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_BA, BA_PKT_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ba pkt stats data.\n");
	}

	return ret;
}

struct utool_func_dispatch g_utool_ba_flag_mpf_table[] = {
	{ true, BA_PKT_STATS, UTOOL_CMD_QUERY_BA_PKT_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_ba_pkt_stats_parse_rpc_pkt, utool_port_create_pkt_in },
};

static void utool_ba_print_help(void)
{
	utool_err_msg("The ubctl ba command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m ba -p ${port} -f pkt_stats\n");
}

static int utool_ba_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			     struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec ba_pkt_exec = { UTOOL_CMD_QUERY_BUTT, 0, NULL };
	struct utool_cal_reg_func_param ba_cal_reg_param = {
		NULL, 0, NULL, g_utool_ba_cal_reg_table, UTOOL_ARRAY_SIZE(g_utool_ba_cal_reg_table)
	};
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;
	uint32_t i;

	for (i = 0; i < func_cnt; i++) {
		if (strcmp(param->func, func_table[i].func) == 0) {
			ba_pkt_exec.rpc_cmd = func_table[i].rpc_cmd;
			ba_pkt_exec.execute = func_table[i].execute;

			ba_cal_reg_param.data_len = &ba_pkt_exec.data_len;
			ba_cal_reg_param.user_def_data_len = func_table[i].data_len;

			ret = utool_cal_func_reg_len(param->func, &ba_cal_reg_param);
			if (ret != UTOOL_OK) {
				utool_err_msg("Failed to cal ba func %s data len.\n", param->func);
				return ret;
			}

			if (func_table[i].create_pkt_in == NULL) {
				utool_err_msg("Failed to create pkt in. Callback is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

			pkt_in = func_table[i].create_pkt_in(&pkt_in_len, param);
			if (pkt_in == NULL) {
				utool_err_msg("Failed to create pkt in.\n");
				return UTOOL_ERR_MALLOC;
			}

			ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &ba_pkt_exec);
			if (ret != UTOOL_OK) {
				utool_err_msg("Failed to execute command, ret = %d.\n", ret);
			}

			utool_destroy_pkt_in(&pkt_in);
			return ret;
		}
	}

	utool_ba_print_help();
	return UTOOL_ERR_FUNC_NOT_FOUND;
}

int utool_ba_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_ba_cmd_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F, utool_ba_cmd_func,
		  g_utool_ba_flag_mpf_table, UTOOL_ARRAY_SIZE(g_utool_ba_flag_mpf_table) },
	};
	uint32_t ba_cmd_cnt = UTOOL_ARRAY_SIZE(utool_ba_cmd_table);
	uint32_t i;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n",
			      (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < ba_cmd_cnt; i++) {
		if (param->flags == utool_ba_cmd_table[i].flags) {
			if (utool_ba_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch. Callback is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

			return utool_ba_cmd_table[i].execute(dev, param,
							     utool_ba_cmd_table[i].func_table,
							     utool_ba_cmd_table[i].func_cnt);
		}
	}

	utool_ba_print_help();

	return UTOOL_ERR_CMD_NOT_FOUND;
}
