// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <errno.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <unistd.h>

#include "../u_utool_pkt.h"
#include "../common/u_utool_error.h"
#include "u_utool_ba.h"

#define BA_PKT_STATS "pkt_stats"
#define BA_MAR "mar"
#define BA_MAR_CYC_EN "mar_cyc_en"
#define BA_MAR_PERF "mar_perf"
#define BA_ICRC "icrc"

#define BA_UB_MEM_DECODER_TABLE "ub_mem_decoder"
#define BA_MAR_INTER_SP_ROUT_TABLE "inter_sp_rout"
#define BA_MAR_INTER_MP_ROUT_TABLE "inter_mp_rout"
#define BA_MAR_INTRA_SP_ROUT_TABLE "intra_sp_rout"
#define BA_MAR_INTRA_MP_ROUT_TABLE "intra_mp_rout"
#define BA_MAR_PORT_SCNA_TABLE "port_scna"
#define BA_MAR_PORT_TABLE "port_table"
#define BA_MAR_PORT_WB_TABLE "port_wb_table"

#define UTOOL_MAR_CYC_EN_CNT 6U
#define BA_MAR_PERF_NUM_TWO 2

uint32_t g_ba_mar_perf_time = 0;

struct utool_mp_route {
	uint32_t port_id;
	uint32_t table_num;
	uint32_t index;
	uint32_t port;
};

struct utool_mar_table_name {
	char func[UBCTL_ARG_MAX_LEN];
};

struct utool_ba_mar_perf_query {
	uint32_t port_id;

	uint32_t flux_wr;
	uint32_t flux_rd;
	uint32_t flux_sum;

	uint32_t wr_cmd_cnt;
	uint32_t rd_cmd_cnt;
	uint32_t sum_cmd_cnt;

	uint32_t wlatcnt_first;
	uint32_t rlatcnt_first;
};

static struct utool_field_info g_utool_ba_pkt_stats_field_info[] = {
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "port_id" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tlb_lkup_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tlb_retried_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tlb_rsp_suc_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tlb_rsp_fault_cnt" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_ta_req_hit_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "dfx_tp_req_hit_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ba_eco_rw_reg" },
	{ true, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "p2p_type_sel_for_cqe" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "p2p_type_sel_for_payl" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "cbaw_en" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_sync_req_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "dfx_sync_resp_cnt" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_inv_req_cnt0" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "dfx_inv_req_cnt1" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_inv_req_cnt2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "dfx_inv_req_cnt3" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_inv_req_cnt4" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "dfx_inv_req_cnt5" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_inv_req_cnt6" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "dfx_inv_req_cnt7" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_rxdma_req_hit_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "dfx_txdma_req_hit_cnt" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V01, "dfx_ta_tp_dtlb_vld" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V01, "dfx_ta_tp_dtlb_pend" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V01, "dfx_rxdma_dtlb_vld" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V01, "dfx_rxdma_dtlb_pend" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V01, "dfx_txdma_dtlb_vld" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V01, "dfx_txdma_dtlb_pend" },
	{ true, true, UTOOL_LOC7, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC4, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "dfx_uimmu_first_fault_permission" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC17, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "dfx_uimmu_first_fault_va_high" },
	{ true, false, UTOOL_LOC12, UTOOL_LOC31, UTOOL_INDEX_1, UTOOL_CAP_ALL, "dfx_uimmu_first_fault_va_low" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tp_wr_req_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tp_rd_req_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_ta_wr_req_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_ta_rd_req_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_txdma_wr_req_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_txdma_rd_req_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_rxdma_wr_req_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_rxdma_rd_req_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb0_wr_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb0_rd_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb0_awack_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb0_wlast_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb0_bresp_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb0_rd_outstanding" },
	{ true, true, UTOOL_LOC7, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "amb0_rdata_ch1_bkpr" },
	{ true, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "amb0_rdata_ch0_bkpr" },
	{ true, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "amb0_awack_bkpr" },
	{ true, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "amb0_bresp_bkpr" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "amb0_wdata_bkpr" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "amb0_ar_ready" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "amb0_aw_bkpr" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb1_wr_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb1_rd_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb1_awack_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb1_wlast_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb1_bresp_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb1_rd_outstanding" },
	{ true, true, UTOOL_LOC7, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "amb1_rdata_ch1_bkpr" },
	{ true, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "amb1_rdata_ch0_bkpr" },
	{ true, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "amb1_awack_bkpr" },
	{ true, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "amb1_bresp_bkpr" },
	{ true, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "amb1_wdata_bkpr" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "amb1_ar_ready" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "amb1_aw_bkpr" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lkp_odr0_ctx0" },
	{ true, true, UTOOL_LOC25, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "lkp_odr0_ctx1" },
	{ true, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "lkp_odr0_ctx2" },
	{ true, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "lkp_odr0_ctx3" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lkp_odr0_outstanding" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "lkp_odr0_idle" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lkp_odr1_ctx0" },
	{ true, true, UTOOL_LOC25, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "lkp_odr1_ctx1" },
	{ true, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "lkp_odr1_ctx2" },
	{ true, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "lkp_odr1_ctx3" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lkp_odr1_outstanding" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "lkp_odr1_idle" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "amb0_ctx0" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "amb0_ctx2" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "amb0_idle" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "amb1_ctx0" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "amb1_ctx2" },
	{ true, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "amb1_idle" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC4, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "master_sub_icg_en" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "master_icg_en" },
	{ true, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "master_us_time_set" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "axim0_max_read_delay" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "am0_rd_max_delay_clr" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "axim0_max_write_delay" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "am0_wr_max_delay_clr" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "axim1_max_read_delay" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "am1_rd_max_delay_clr" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "axim1_max_write_delay" },
	{ true, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "am1_wr_max_delay_clr" },
	{ true, true, UTOOL_LOC18, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC9, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "dfx_amb0_entry_max_wr_otsd" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "dfx_amb0_entry_max_rd_otsd" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb0_curr_ava_wr_latency" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "dfx_amb0_curr_ava_rd_latency" },
	{ true, true, UTOOL_LOC18, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC9, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "dfx_amb1_entry_max_wr_otsd" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "dfx_amb1_entry_max_rd_otsd" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_amb1_curr_ava_wr_latency" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "dfx_amb1_curr_ava_rd_latency" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "rxdma_raw_pkt_q10_l2e_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rxdma_raw_pkt_q0_l2e_cnt" },
	{ true, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC24, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_in_raw_cnt" },
	{ true, false, UTOOL_LOC20, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_in_be_cnt" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_in_imp_cnt" },
	{ true, false, UTOOL_LOC12, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_in_reduce_cnt" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_in_cqe_cnt" },
	{ true, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_in_ato_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_in_lsa_cnt" },
	{ true, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC24, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_out_raw_cnt" },
	{ true, false, UTOOL_LOC20, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_out_be_cnt" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_out_imp_cnt" },
	{ true, false, UTOOL_LOC12, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_out_reduce_cnt" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_out_cqe_cnt" },
	{ true, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_out_ato_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_out_lsa_cnt" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_op_combine_cnt" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_out_stash_vld_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "rxdma_rwp_pkt_out_stash_nid_vld_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rxdma_intf_ro_dfx" },
	{ true, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ true, false, UTOOL_LOC20, UTOOL_LOC23, 0, UTOOL_CAP_V012, "rxdma_ubrx_pkt_out_ato_store_cnt" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_V012, "rxdma_ubrx_pkt_out_be_cnt" },
	{ true, false, UTOOL_LOC12, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rxdma_ubrx_pkt_out_imp_cnt" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_V012, "rxdma_ubrx_pkt_out_reduce_cnt" },
	{ true, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_V012, "rxdma_ubrx_pkt_out_cas_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_V012, "rxdma_ubrx_pkt_out_faa_cnt" },
	{ true, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ true, false, UTOOL_LOC20, UTOOL_LOC23, 0, UTOOL_CAP_V012, "rxdma_ubrx_pkt_in_ato_store_cnt" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_V012, "rxdma_ubrx_pkt_in_be_cnt" },
	{ true, false, UTOOL_LOC12, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rxdma_ubrx_pkt_in_imp_cnt" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_V012, "rxdma_ubrx_pkt_in_reduce_cnt" },
	{ true, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_V012, "rxdma_ubrx_pkt_in_cas_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_V012, "rxdma_ubrx_pkt_in_faa_cnt" },
	{ true, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ true, false, UTOOL_LOC20, UTOOL_LOC23, 0, UTOOL_CAP_V012, "rxdma_ubrx_cb_pkt_out_ato_store_cnt" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_V012, "rxdma_ubrx_cb_pkt_out_be_cnt" },
	{ true, false, UTOOL_LOC12, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rxdma_ubrx_cb_pkt_out_imp_cnt" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_V012, "rxdma_ubrx_cb_pkt_out_reduce_cnt" },
	{ true, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_V012, "rxdma_ubrx_cb_pkt_out_cas_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_V012, "rxdma_ubrx_cb_pkt_out_faa_cnt" },
	{ true, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ true, false, UTOOL_LOC20, UTOOL_LOC23, 0, UTOOL_CAP_V012, "rxdma_ubrx_cb_pkt_in_ato_store_cnt" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_V012, "rxdma_ubrx_cb_pkt_in_be_cnt" },
	{ true, false, UTOOL_LOC12, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rxdma_ubrx_cb_pkt_in_imp_cnt" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_V012, "rxdma_ubrx_cb_pkt_in_reduce_cnt" },
	{ true, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_V012, "rxdma_ubrx_cb_pkt_in_cas_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_V012, "rxdma_ubrx_cb_pkt_in_faa_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "txdma_ar_cnt_m1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "txdma_r_cnt_m0" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "txdma_r_cnt_m1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ub_tx_in_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "nic_tx_in_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ub_tx_out_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "nic_tx_out_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ub_c_tx_out_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ub_g_tx_out_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ub_c_tx_in_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ub_g_tx_in_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lsa_in_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lsa_out_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "pfa_out_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_in_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_out_cnt_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "pa_out_cnt_err_g" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "memory_cnt_0" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "memory_cnt_1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "memory_cnt_2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "memory_cnt_3" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "p2p_bypass_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "hdr_credit_cnt_port0" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "data_credit_cnt_port0" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "hdr_credit_cnt_port2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "data_credit_cnt_port2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ub_tx_in_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "nic_tx_in_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ub_tx_out_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "nic_tx_out_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ub_c_tx_out_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ub_g_tx_out_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ub_c_tx_in_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ub_g_tx_in_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lsa_in_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lsa_out_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rx_ub_io_hdr_send_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rx_load_send_cnt" },

	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cfg_lsad_to_txdma_dat_cdt_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "cfg_lsad_to_txdma_hdr_cdt_num" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rxdma_ubrx_alm" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rxdma_ubrx_sta" },

	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "mar_req_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "mar_ack_pkt_cnt" },

	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "head_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "cb_head_pkt_cnt" },

	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "write_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "cb_write_pkt_cnt" },

	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "bresp_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "cb_bresp_pkt_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "lsad_resp_pkt_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rx_load_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cfg_abnormal_rsp_en" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rx_dat_ctx_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rx_atomic_dat_ctx_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "tx_load_resp_incomplete_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rxdma_wr_payl_rwp_pkt_cnt" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rxdma_wr_payl_buff_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V01, "tx_load_resp_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V01, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V01, "tx_load_resp_send_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V01, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rx_ub_io_hdr_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rx_atomic_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rx_atomic_send_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V01, "tx_atomic_resp_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V01, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V01, "tx_atomic_resp_send_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V01, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "cpu_seq_dat_only(lsad_chn_num0)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "cpu_seq_dat_only(lsad_chn_num1)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "cpu_seq_dat_only_send" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "cpu_seq_dat(lsad_chn_num0)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "cpu_seq_dat(lsad_chn_num1)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cpu_seq_dat_send" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cpu_seq_tx_rdat_send" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rx_p2p_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rx_p2p_send_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "p2p_spec_apl" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "p2p_spec_alced" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "p2p_sec_apl" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "p2p_sec_alced" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rx_abnormal(lsad_rx_abnormal_num0)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rx_abnormal(lsad_rx_abnormal_num1)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rx_abnormal(lsad_rx_abnormal_num2)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rx_abnormal(lsad_rx_abnormal_num3)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rx_abnormal(lsad_rx_abnormal_num4)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rx_abnormal(lsad_rx_abnormal_num5)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rx_abnormal(lsad_rx_abnormal_num6)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rx_abnormal(lsad_rx_abnormal_num7)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "rx_abnormal(lsad_rx_abnormal_num8)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "tx_abnormal(lsad_tx_abnormal_num0)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "tx_abnormal(lsad_tx_abnormal_num1)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "tx_abnormal(lsad_tx_abnormal_num2)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "tx_abnormal(lsad_tx_abnormal_num3)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "tx_abnormal(lsad_tx_abnormal_num4)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "tx_abnormal(lsad_tx_abnormal_num5)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "tx_abnormal(lsad_tx_abnormal_num6)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "tx_abnormal(lsad_tx_abnormal_num7)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "tx_abnormal(lsad_tx_abnormal_num8)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "tx_abnormal(lsad_tx_abnormal_num9)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V012, "tx_abnormal(lsad_tx_abnormal_num10)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V012, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "cfg_abnormal_err_rsp" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cfg_abnormal_poison" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "axim_timeout_int_src" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "master_amb_timeout" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V01, "ctrl_err_wdata_mode" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC3, 0, UTOOL_CAP_V01, "reserved" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC5, 0, UTOOL_CAP_V01, "ctrl_err_data_wr" },
	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_V01, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "mem_attr_cfg" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "mem_type_cfg" },
	{ false, true, UTOOL_LOC5, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "sh_cfg" },
	{ false, true, UTOOL_LOC11, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "abort_all" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V01, "cfg_atp_tlb_inv_all_rsp_entry" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V01, "cfg_atp_conf_inv_all_rsp_entry" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V01, "cfg_atp_sync_clr_all_no_rsp_entry" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V01, "cfg_atp_sync_clr_all_stale_entry" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V01, "cfg_atp_inv_record_mode" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V01, "cfg_atp_apat_tlbi_vav_disable" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V01, "cfg_atp_req_entry_rls_mode" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V01, "cfg_atp_tlbi_accurate_math_en" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V01, "cfg_atp_tlbi_pgsz_predict_en" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V01, "cfg_atp_range_tlbi_disable" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC11, 0, UTOOL_CAP_V01, "reserved" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC18, 0, UTOOL_CAP_V01, "cfg_dtlb_pend_match_pgsz" },
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_V01, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "master_idle" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "lkp_odr_idle" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "amb_idle" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "atp_idle" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "atp_inv_bitmap_idle" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "wdp_idle" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "p2p_idle" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "device_status0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "device_status1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "device_status2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "device_status3" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "device_status4" },

	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	// opcode 0xA033
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "dfx_ccua_abort_cnt_ch0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "dfx_ta_abort_cnt_ch1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "dfx_tp_abort_cnt_ch1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "dfx_txdma_abort_cnt_ch1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "dfx_rxdma_abort_cnt_ch1" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cpu_seq_rx_rdat" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cpu_seq_rx_rdat_send" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cpu_seq_tx_rdat" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rxdma_pkt_rx_cnt(0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rxdma_pkt_rx_cnt(1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rxdma_pkt_rx_cnt(2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rxdma_pkt_rx_cnt(3)" },

	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_V01, "reserved" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC11, 0, UTOOL_CAP_V01, "rsv(0)" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V01, "rxdma_sof_sof_err(0)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V01, "rxdma_imp_2k_err(0)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC7, 0, UTOOL_CAP_V01, "rxdma_head_split_fifo_full(0)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V01, "rxdma_opcode_err(0)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V01, "rxdma_reset_err(0)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V01, "rxdma_pkt_long(0)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V01, "rxdma_fcs_err(0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V01, "rxdma_icrc_err(0)" },

	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_V01, "reserved" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC11, 0, UTOOL_CAP_V01, "rsv(1)" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V01, "rxdma_sof_sof_err(1)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V01, "rxdma_imp_2k_err(1)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC7, 0, UTOOL_CAP_V01, "rxdma_head_split_fifo_full(1)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V01, "rxdma_opcode_err(1)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V01, "rxdma_reset_err(1)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V01, "rxdma_pkt_long(1)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V01, "rxdma_fcs_err(1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V01, "rxdma_icrc_err(1)" },

	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_V01, "reserved" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC11, 0, UTOOL_CAP_V01, "rsv(2)" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V01, "rxdma_sof_sof_err(2)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V01, "rxdma_imp_2k_err(2)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC7, 0, UTOOL_CAP_V01, "rxdma_head_split_fifo_full(2)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V01, "rxdma_opcode_err(2)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V01, "rxdma_reset_err(2)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V01, "rxdma_pkt_long(2)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V01, "rxdma_fcs_err(2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V01, "rxdma_icrc_err(2)" },

	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_V01, "reserved" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC11, 0, UTOOL_CAP_V01, "rsv(3)" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V01, "rxdma_sof_sof_err(3)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V01, "rxdma_imp_2k_err(3)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC7, 0, UTOOL_CAP_V01, "rxdma_head_split_fifo_full(3)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V01, "rxdma_opcode_err(3)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V01, "rxdma_reset_err(3)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V01, "rxdma_pkt_long(3)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V01, "rxdma_fcs_err(3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V01, "rxdma_icrc_err(3)" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "inner_status" },

	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_field_info g_utool_ba_mar_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "port_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "mar_err_type" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "mar_far_type" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "mar_near_type" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "mar_without_cxt_type" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "mar_timeout_type" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "illegal_opcode" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "illegal_srcid" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "illegal_txnid" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt0_sta_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt0_sta_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt1_sta_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt1_sta_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt2_sta_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt2_sta_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt3_sta_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt3_sta_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt4_sta_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt4_sta_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt5_sta_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt5_sta_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt6_sta_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt6_sta_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt7_sta_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt7_sta_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt0_type_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt0_type_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt1_type_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt1_type_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt2_type_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt2_type_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt3_type_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt3_type_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt4_type_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt4_type_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt5_type_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt5_type_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt6_type_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt6_type_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_cxt7_type_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_cxt7_type_high" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, true, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "mar_perf_en" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "mar_perf_mode" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "mar_perf_prd" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_flux_wr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_flux_rd" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_flux_sum" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_wr_cmd_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_rd_cmd_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_sum_cmd_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_entry0_vld_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_entry0_vld_high" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_entry1_vld_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_entry1_vld_high" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_entry0_req_type_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_entry0_req_type_high" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_entry1_req_type_low" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, UTOOL_INDEX_1, UTOOL_CAP_ALL, "mar_entry1_req_type_high" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_ras_err_clr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "nor_device_status4" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "cfg_eid" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "cfg_age_en" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "cfg_age_period" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "cfg_lkp_en" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "cfg_rm" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "cfg_sl" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "cfg_ee" },
	{ false, true, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "cfg_cxt_group_pst" },
	{ false, true, UTOOL_LOC14, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "cfg_port_intlv" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "cfg_nl_intlv" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "x4_mode" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "decode_cache_en" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "cfg_lb_sel" },
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V013, "nor_rsperr_en" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V013, "timeout_fail_rsperr_en" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V013, "auth_fail_rsperr_en" },
	{ false, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_V013, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cfg_inter_rack_mask" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "cfg_inter_rack_lsb" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cfg_intra_rack_mask" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "cfg_intra_rack_lsb" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "cfg_um_entry_size0" },
	{ false, true, UTOOL_LOC22, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "cfg_um_entry_size1" },
	{ false, true, UTOOL_LOC22, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V013, "readreceipt_return_mode" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_V013, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "so_size" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "intlv_xoren" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "intlv_pos" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "sec_mode" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "linkdown_mode" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "mar_lsar_db_mode" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V013, "mar_cxt_byp_en" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_V013, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "mar_gqm_en" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "mar_reqflit_fifo_full" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "mar_rspflit_retry_fifo_full" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "mar_req_dbid_fifo0_full" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "mar_req_dbid_fifo1_full" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "mar_cxtid_fifo0_full" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "mar_cxtid_fifo1_full" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "mar_cxtid_fifo2_full" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "mar_cxtid_fifo3_full" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "mar_cxtid_age_fifo0_full" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "mar_cxtid_age_fifo1_full" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "mar_cxtid_age_fifo2_full" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "mar_cxtid_age_fifo3_full" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "mar_cxtid_wb_fifo0_full" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "mar_cxtid_wb_fifo1_full" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "mar_cxtid_wb_fifo2_full" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "mar_cxtid_wb_fifo3_full" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "mar_pkt_fifo_full" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "mar_pkt_wb_fifo_full" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "mar_odr_fifo_full" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "mar_src_fifo_full" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "mar_lcl_rsp_info_fifo_full" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "mar_rmt_rsp_info_full" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "mar_age_auth_rsp_info_fifo_full" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "mar_timeoutrsp_info_fifo_full" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "wb_hdr_fifo_full" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "wr_hdr_fifo_full" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_ALL, "ccua0_wr_cxt_full" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "ccua1_wr_cxt_full" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_ALL, "ccua0_rd_fifo_full" },
	{ false, false, UTOOL_LOC29, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "ccua1_rd_fifo_full" },
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "mar_reqflit_fifo_empty" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "mar_rspflit_retry_fifo_empty" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "mar_req_dbid_fifo0_empty" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "mar_req_dbid_fifo1_empty" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "mar_cxtid_fifo0_empty" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "mar_cxtid_fifo1_empty" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "mar_cxtid_fifo2_empty" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "mar_cxtid_fifo3_empty" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "mar_cxtid_age_fifo0_empty" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "mar_cxtid_age_fifo1_empty" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "mar_cxtid_age_fifo2_empty" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "mar_cxtid_age_fifo3_empty" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "mar_cxtid_wb_fifo0_empty" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "mar_cxtid_wb_fifo1_empty" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "mar_cxtid_wb_fifo2_empty" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "mar_cxtid_wb_fifo3_empty" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "mar_pkt_fifo_empty" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "mar_pkt_wb_fifo_empty" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "mar_odr_fifo_empty" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "mar_src_fifo_empty" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "mar_lcl_rsp_info_fifo_empty" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "mar_rmt_rsp_info_fifo_empty" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "mar_age_auth_rsp_info_fifo_empty" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "mar_timeoutrsp_info_fifo_empty" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "wb_hdr_fifo_empty" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "wr_hdr_fifo_empty" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_ALL, "ccua0_rd_fifo_empty" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "ccua1_rd_fifo_empty" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "cfg_alloc_cell_thd" },
	{ false, true, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cfg_alloc_cell_num" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "cfg_wb_alloc_cell_thd" },
	{ false, true, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "cfg_nor_ostd_cnt" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "cfg_wb_ostd_cnt" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "cfg_cbusy_leve0" },
	{ false, true, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cfg_cbusy_leve1" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "cfg_cbusy_leve2" },
	{ false, true, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "cfg_cbusy_en" },
	{ false, true, UTOOL_LOC25, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "cxtid_fifo_full_lvl" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "pkt_fifo_full_lvl" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "resflit_retry_fifo_full_lvl" },
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "dbid_nor_lvl" },
	{ false, true, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "db_nor_buf_lvl" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "entry_nor_req_lvl" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "cxtm_nor_lvl" },
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "nor_entry_pcrd_lvl" },
	{ false, true, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "wb_entry_pcrd_lvl" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "mar_cxtm_age_fifo_alful_lvl" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "mar_rsp_odr_fifo_alful_lvl" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "mar_rsp_timeout_fifo_alful_lvl" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "mar_rsp_auth_fail_fifo_alful_lvl" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "wlatcnt_first" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rlatcnt_first" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_chi_req_rcvd_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_chi_comp_rsp_sent_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_chi_retry_rsp_sent_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_chi_no_rsp_req_rcvd_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_rd_pkt_sent_to_txdma_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_rd_pkt_rsp_rcvd_from_rxdma_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_rd_pkt_rsp_sent_to_lsad_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_rd_req_rcvd_from_rxdma_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_rd_req_sent_to_txdma_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_wr_pkt_send_to_lsad_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_wr_pkt_rsp_rcvd_from_rxdma_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_wr_req_rcvd_from_rxdma_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_wr_req_sent_to_txdma_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_chi_pgnt_rsp_sent_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_chi_ccua_pgnt_rsp_sent_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_chi_ccua_req_rcvd_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_chi_ccua_comp_rsp_sent_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_chi_ccua_retry_rsp_sent_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_ccua_rd_req_sent_to_ccua_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_ccua_wr_rsp_rcvd_from_ccua_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mar_ccua_wr_req_sent_to_lsad_cnt" },
};

static struct utool_field_info g_utool_ba_mar_cyc_en_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "port_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "cnt_clr_ce" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "snap_en" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_field_info g_utool_ub_mem_decoder_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "port_id" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "table_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "index" },
	/*
	* Print format:
	* BLOCK_0:
	*     valid_0:xx
	*     mem_base_0:xx
	*     mem_limit_0:xx
	*     onepath_0:xx
	*     wr_delay_comp_0:xx
	*     reduce_delay_comp_0:xx
	*     cmo_delay_comp_0:xx
	*     so_0:xx
	*     lb_0:xx
	*     token_id_0:xx
	*     dcna_0:xx
	*     uba_base_0:xx
	*     adtroc_0:xx
	*/
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "\tBLOCK_0:\n\t\tvalid_0" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "\t\tmem_base_0" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "\t\tmem_limit_0" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "\t\tonepath_0" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "\t\twr_delay_comp_0" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "\t\treduce_delay_comp_0" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "\t\tcmo_delay_comp_0" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "\t\tso_0" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "\t\tlb_0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "\t\ttoken_id_0" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "\t\tdcna_0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, UTOOL_INDEX_1, UTOOL_CAP_ALL, "\t\tdcna_0" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "\t\tuba_base_0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC14, UTOOL_INDEX_1, UTOOL_CAP_ALL, "\t\tuba_base_0" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "\t\tadtroc_0" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "\tBLOCK_1:\n\t\tvalid_1" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "\t\tmem_base_1" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "\t\tmem_limit_1" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "\t\tonepath_1" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "\t\twr_delay_comp_1" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "\t\treduce_delay_comp_1" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "\t\tcmo_delay_comp_1" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "\t\tso_1" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "\t\tlb_1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "\t\ttoken_id_1" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "\t\tdcna_1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, UTOOL_INDEX_1, UTOOL_CAP_ALL, "\t\tdcna_1" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "\t\tuba_base_1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC14, UTOOL_INDEX_1, UTOOL_CAP_ALL, "\t\tuba_base_1" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "\t\tadtroc_1" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "\tBLOCK_2:\n\t\tvalid_2" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "\t\tmem_base_2" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "\t\tmem_limit_2" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "\t\tonepath_2" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "\t\twr_delay_comp_2" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "\t\treduce_delay_comp_2" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "\t\tcmo_delay_comp_2" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "\t\tso_2" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "\t\tlb_2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "\t\ttoken_id_2" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "\t\tdcna_2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, UTOOL_INDEX_1, UTOOL_CAP_ALL, "\t\tdcna_2" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "\t\tuba_base_2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC14, UTOOL_INDEX_1, UTOOL_CAP_ALL, "\t\tuba_base_2" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "\t\tadtroc_2" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "\tBLOCK_3:\n\t\tvalid_3" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "\t\tmem_base_3" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "\t\tmem_limit_3" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "\t\tonepath_3" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "\t\twr_delay_comp_3" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "\t\treduce_delay_comp_3" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "\t\tcmo_delay_comp_3" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "\t\tso_3" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "\t\tlb_3" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "\t\ttoken_id_3" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "\t\tdcna_3" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, UTOOL_INDEX_1, UTOOL_CAP_ALL, "\t\tdcna_3" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "\t\tuba_base_3" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC14, UTOOL_INDEX_1, UTOOL_CAP_ALL, "\t\tuba_base_3" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "\t\tadtroc_3" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rserved" },

	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_field_info g_utool_sp_rout_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "port_id" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "table_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "index" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "Port" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "valid" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_field_info g_utool_port_scna_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "port_id" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "table_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "index" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "Port_CNA" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_field_info g_utool_mar_port_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "port_id" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "table_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "index" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "Response_VL" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "Req_VL" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "valid" },
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_field_info g_utool_mar_port_wb_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "port_id" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "table_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "index" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "Req_Wb_VL" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "valid" },
	{ false, true, UTOOL_LOC5, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_field_info g_utool_ba_icrc_field_info[] = {
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_0, "rxdma_icrc_err_cnt(queue_id0)" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_0, "rxdma_icrc_err_cnt(queue_id1)" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_0, "rxdma_icrc_err_cnt(queue_id2)" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_0, "rxdma_icrc_err_cnt(queue_id3)" },
};

struct utool_cal_reg_cnt_dp g_utool_ba_cal_reg_table[] = {
	{ true, true, BA_PKT_STATS, UTOOL_ARRAY_SIZE(g_utool_ba_pkt_stats_field_info),
	  g_utool_ba_pkt_stats_field_info },
	{ true, true, BA_MAR, UTOOL_ARRAY_SIZE(g_utool_ba_mar_field_info), g_utool_ba_mar_field_info },
	{ true, false, BA_MAR_CYC_EN, UTOOL_ARRAY_SIZE(g_utool_ba_mar_cyc_en_field_info),
	  g_utool_ba_mar_cyc_en_field_info },

	{ true, false, BA_UB_MEM_DECODER_TABLE, UTOOL_ARRAY_SIZE(g_utool_ub_mem_decoder_field_info),
	  g_utool_ub_mem_decoder_field_info },
	{ true, false, BA_MAR_INTER_SP_ROUT_TABLE, UTOOL_ARRAY_SIZE(g_utool_ub_mem_decoder_field_info),
	  g_utool_ub_mem_decoder_field_info },
	{ true, false, BA_MAR_INTER_MP_ROUT_TABLE, UTOOL_ARRAY_SIZE(g_utool_ub_mem_decoder_field_info),
	  g_utool_ub_mem_decoder_field_info },
	{ true, false, BA_MAR_INTRA_SP_ROUT_TABLE, UTOOL_ARRAY_SIZE(g_utool_ub_mem_decoder_field_info),
	  g_utool_ub_mem_decoder_field_info },
	{ true, false, BA_MAR_INTRA_MP_ROUT_TABLE, UTOOL_ARRAY_SIZE(g_utool_ub_mem_decoder_field_info),
	  g_utool_ub_mem_decoder_field_info },
	{ true, false, BA_MAR_PORT_SCNA_TABLE, UTOOL_ARRAY_SIZE(g_utool_ub_mem_decoder_field_info),
	  g_utool_ub_mem_decoder_field_info },
	{ true, false, BA_MAR_PORT_TABLE, UTOOL_ARRAY_SIZE(g_utool_ub_mem_decoder_field_info),
	  g_utool_ub_mem_decoder_field_info },
	{ true, false, BA_MAR_PORT_WB_TABLE, UTOOL_ARRAY_SIZE(g_utool_ub_mem_decoder_field_info),
	  g_utool_ub_mem_decoder_field_info },
	{ true, false, BA_ICRC, UTOOL_ARRAY_SIZE(g_utool_ba_icrc_field_info),
	  g_utool_ba_icrc_field_info },
};

int utool_ba_cal_data_len(uint32_t *ba_data_len)
{
	struct utool_cal_reg_func_param ba_cal_reg_param = {
		ba_data_len, UTOOL_REG_CNT_DEFAULT, NULL,
		g_utool_ba_cal_reg_table, UTOOL_ARRAY_SIZE(g_utool_ba_cal_reg_table)
	};
	int ret = UTOOL_OK;

	if (ba_data_len == NULL) {
		utool_err_msg("Param is invalid, ba data len is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_cal_func_reg_len(UTOOL_FUNC_ALL, &ba_cal_reg_param);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate reg cnt, ret = %d.\n", ret);
	}

	return ret;
}

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

static int utool_ba_mar_parse_rpc_pkt(struct fwctl_rpc_ub_out *ba_mar_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(ba_mar_out, UTOOL_ARRAY_SIZE(g_utool_ba_mar_field_info),
			      g_utool_ba_mar_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_BA, BA_MAR));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ba mar data.\n");
	}

	return ret;
}

static int utool_ba_mar_cyc_en_parse_rpc_pkt(struct fwctl_rpc_ub_out * ba_mar_cyc_en_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(ba_mar_cyc_en_out, UTOOL_ARRAY_SIZE(g_utool_ba_mar_cyc_en_field_info),
			      g_utool_ba_mar_cyc_en_field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_BA, BA_MAR_CYC_EN));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ba mar cyc en data.\n");
	}

	return ret;
}

static int utool_mp_rout_table_parse(uint32_t *mp_rout_data, uint32_t data_len)
{
#define MP_ROUT_PORT_INDEX 3U
#define MP_ROUT_PORT_NUM 8U

	uint32_t port_num = 0;
	uint32_t i;

	if ((MP_ROUT_PORT_INDEX * sizeof(uint32_t)) >= data_len) {
		return UTOOL_ERR_PARSE;
	}

	port_num = UTOOL_EXTRACT_BITS(mp_rout_data[MP_ROUT_PORT_INDEX], UTOOL_LOC0, UTOOL_LOC7);
	utool_reg_msg("Port: ");
	if (port_num == 0) {
		utool_reg_msg("NA\n");
		return UTOOL_OK;
	}

	for (i = 0; i < MP_ROUT_PORT_NUM; i++) {
		if ((port_num & (1UL << i)) != 0) {
			utool_reg_msg("%u ", i);
		}
	}

	utool_reg_msg("\n");

	return UTOOL_OK;
}

static int utool_mp_rout_parse_rpc_pkt(struct fwctl_rpc_ub_out *mp_rout_out)
{
	int ret = UTOOL_OK;

	struct utool_mp_route *mp_rout = (struct utool_mp_route *)(mp_rout_out->data);

	utool_reg_msg("port_id: 0x%x\n", mp_rout->port_id);
	utool_reg_msg("index: 0x%x\n", mp_rout->index);

	ret = utool_mp_rout_table_parse((uint32_t *)mp_rout, mp_rout_out->data_size);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse mp rout port data.\n");
	}

	return ret;
}

static int utool_inter_mp_rout_parse_rpc_pkt(struct fwctl_rpc_ub_out *inter_sp_rout_out)
{
	utool_reg_msg("-------------------------- ba-inter_mp_rout --------------------------\n");

	return utool_mp_rout_parse_rpc_pkt(inter_sp_rout_out);
}

static int utool_intra_mp_rout_parse_rpc_pkt(struct fwctl_rpc_ub_out *intra_sp_rout_out)
{
	utool_reg_msg("-------------------------- ba-intra_mp_rout --------------------------\n");

	return utool_mp_rout_parse_rpc_pkt(intra_sp_rout_out);
}

static int utool_inter_sp_rout_parse_rpc_pkt(struct fwctl_rpc_ub_out *inter_sp_rout_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(inter_sp_rout_out, UTOOL_ARRAY_SIZE(g_utool_sp_rout_field_info),
			      g_utool_sp_rout_field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_BA, BA_MAR_INTER_SP_ROUT_TABLE));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse inter sp rout table data.\n");
	}

	return ret;
}

static int utool_intra_sp_rout_parse_rpc_pkt(struct fwctl_rpc_ub_out *intra_sp_rout_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(intra_sp_rout_out, UTOOL_ARRAY_SIZE(g_utool_sp_rout_field_info),
			      g_utool_sp_rout_field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_BA, BA_MAR_INTRA_SP_ROUT_TABLE));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse intra sp rout table data.\n");
	}

	return ret;
}

static int utool_port_scna_parse_rpc_pkt(struct fwctl_rpc_ub_out *port_scna_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(port_scna_out, UTOOL_ARRAY_SIZE(g_utool_port_scna_field_info),
			      g_utool_port_scna_field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_BA, BA_MAR_PORT_SCNA_TABLE));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse mar port scna table data.\n");
	}

	return ret;
}

static int utool_mar_port_parse_rpc_pkt(struct fwctl_rpc_ub_out *mar_port_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(mar_port_out, UTOOL_ARRAY_SIZE(g_utool_mar_port_field_info),
			      g_utool_mar_port_field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_BA, BA_MAR_PORT_TABLE));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse mar port table data.\n");
	}

	return ret;
}

static int utool_mar_port_wb_parse_rpc_pkt(struct fwctl_rpc_ub_out *mar_port_wb_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(mar_port_wb_out, UTOOL_ARRAY_SIZE(g_utool_mar_port_wb_field_info),
			      g_utool_mar_port_wb_field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_BA, BA_MAR_PORT_WB_TABLE));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse mar port wb table data.\n");
	}

	return ret;
}

static int utool_ba_icrc_parse_rpc_pkt(struct fwctl_rpc_ub_out *mar_port_wb_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(mar_port_wb_out, UTOOL_ARRAY_SIZE(g_utool_ba_icrc_field_info),
			      g_utool_ba_icrc_field_info, UTOOL_CONCAT_STR(UTOOL_MODULE_BA, BA_ICRC));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ba icrc data.\n");
	}

	return ret;
}

static int utool_ub_mem_decoder_parse_rpc_pkt(struct fwctl_rpc_ub_out *ub_mem_decoder_out)
{
#define UB_MEM_DECODER_INDEX 2U
#define UB_MEM_DECODER_ENTRY_WIDTH 4U

	uint32_t *index = ub_mem_decoder_out->data + UB_MEM_DECODER_INDEX;
	int ret = UTOOL_OK;

	*index = *index >> UB_MEM_DECODER_ENTRY_WIDTH;

	ret = utool_pkt_parse(ub_mem_decoder_out, UTOOL_ARRAY_SIZE(g_utool_ub_mem_decoder_field_info),
			      g_utool_ub_mem_decoder_field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_BA, BA_UB_MEM_DECODER_TABLE));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ub mem decoder table data.\n");
	}

	return ret;
}

static int utool_table_func_convert_num(char *func, uint32_t *table_num)
{
	struct utool_mar_table_name mar_table_name[] = {
		{ BA_MAR_INTRA_SP_ROUT_TABLE },
		{ BA_MAR_INTRA_MP_ROUT_TABLE },
		{ BA_MAR_INTER_SP_ROUT_TABLE },
		{ BA_MAR_INTER_MP_ROUT_TABLE },
		{ BA_MAR_PORT_SCNA_TABLE },
		{ BA_MAR_PORT_TABLE },
		{ BA_MAR_PORT_WB_TABLE },
		{ BA_UB_MEM_DECODER_TABLE },
	};
	uint32_t i;

	for (i = 0; i < UTOOL_ARRAY_SIZE(mar_table_name); i++) {
		if (strcmp(func, mar_table_name[i].func) == 0) {
			*table_num = i;
			return UTOOL_OK;
		}
	}

	return UTOOL_ERR;
}

static void *utool_mar_table_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_table *mar_table = NULL;
	int ret = UTOOL_OK;

	mar_table = (struct fwctl_pkt_in_table *)utool_create_pkt_in(pkt_in_len, param,
								     sizeof(struct fwctl_pkt_in_table));
	if (mar_table == NULL) {
		return NULL;
	}

	ret = utool_table_func_convert_num(param->func, &param->table_num);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to convert func num, func name = %s, ret = %d.\n", param->func, ret);
		utool_destroy_pkt_in((void **)&mar_table);
		return NULL;
	}

	mar_table->port_id = param->port;
	mar_table->table_num = param->table_num;
	mar_table->index = param->index;

	return mar_table;
}

static inline int utool_ba_mar_perf_conf_rpc_pkt(struct fwctl_rpc_ub_out *ba_conf_mar_perf_out)
{
#define BA_MAR_PERF_MS_TO_US 1000U

	UTOOL_SET_USED(ba_conf_mar_perf_out);

	(void)usleep(g_ba_mar_perf_time * BA_MAR_PERF_MS_TO_US);

	return UTOOL_OK;
}

static int utool_ba_mar_perf_obtain_data(struct utool_ba_mar_perf_query *ba_mar_perf_data,
					 uint32_t *ba_mar_perf_data_arr, uint32_t data_arr_size)
{
#define FLUX_WR_LOC 2
#define FLUX_RD_LOC 3
#define FLUX_SUM_LOC 4
#define WR_CMD_LOC 5
#define RD_CMD_LOC 6
#define SUM_CMD_LOC 7
#define WLATCNT_FIRST_LOC 8
#define RLATCNT_FIRST_LOC 9
#define BA_MAR_PERF_MIN_SIZE 10U

	if (data_arr_size < (BA_MAR_PERF_MIN_SIZE * sizeof(*ba_mar_perf_data_arr))) {
		utool_err_msg("Data arr size = %ubytes is less than the minimum %zubytes.\n",
			      data_arr_size, BA_MAR_PERF_MIN_SIZE * sizeof(*ba_mar_perf_data_arr));
		return UTOOL_ERR;
	}

	ba_mar_perf_data->port_id = ba_mar_perf_data_arr[0];
	ba_mar_perf_data->flux_wr = ba_mar_perf_data_arr[FLUX_WR_LOC];
	ba_mar_perf_data->flux_rd = ba_mar_perf_data_arr[FLUX_RD_LOC];
	ba_mar_perf_data->flux_sum = ba_mar_perf_data_arr[FLUX_SUM_LOC];

	ba_mar_perf_data->wr_cmd_cnt = ba_mar_perf_data_arr[WR_CMD_LOC];
	ba_mar_perf_data->rd_cmd_cnt = ba_mar_perf_data_arr[RD_CMD_LOC];
	ba_mar_perf_data->sum_cmd_cnt = ba_mar_perf_data_arr[SUM_CMD_LOC];

	ba_mar_perf_data->wlatcnt_first = ba_mar_perf_data_arr[WLATCNT_FIRST_LOC];
	ba_mar_perf_data->rlatcnt_first = ba_mar_perf_data_arr[RLATCNT_FIRST_LOC];

	return UTOOL_OK;
}

static void utool_ba_mar_perf_print_data(struct utool_ba_mar_perf_query *ba_mar_perf_data, double ba_mar_perf_time_s,
					 double clock_cycle_frequency_ns)
{
	uint32_t second_port_id = ba_mar_perf_data->port_id;
	uint32_t first_port_id = ba_mar_perf_data->port_id;

	utool_reg_msg("-------------------------- ba-mar_perf --------------------------\n");
	(ba_mar_perf_data->port_id % BA_MAR_PERF_NUM_TWO) != 0 ? first_port_id-- : second_port_id++;
	utool_reg_msg("port: %u + port: %u\n", first_port_id, second_port_id);

	utool_reg_msg("wr_traffic: %u\n", (uint32_t)((double)ba_mar_perf_data->flux_wr / ba_mar_perf_time_s));
	utool_reg_msg("rd_traffic: %u\n", (uint32_t)((double)ba_mar_perf_data->flux_rd / ba_mar_perf_time_s));
	utool_reg_msg("sum_traffic: %u\n", (uint32_t)((double)ba_mar_perf_data->flux_sum / ba_mar_perf_time_s));

	if (ba_mar_perf_data->wr_cmd_cnt == 0) {
		utool_reg_msg("wr_pld_avg_len: 0\n");
	} else {
		utool_reg_msg("wr_pld_avg_len: %u\n", (ba_mar_perf_data->flux_wr / ba_mar_perf_data->wr_cmd_cnt));
	}

	if (ba_mar_perf_data->rd_cmd_cnt == 0) {
		utool_reg_msg("rd_pld_avg_len: 0\n");
	} else {
		utool_reg_msg("rd_pld_avg_len: %u\n", (ba_mar_perf_data->flux_rd / ba_mar_perf_data->rd_cmd_cnt));
	}

	if (ba_mar_perf_data->sum_cmd_cnt == 0) {
		utool_reg_msg("pld_avg_len: 0\n");
	} else {
		utool_reg_msg("pld_avg_len: %u\n", (ba_mar_perf_data->flux_sum / ba_mar_perf_data->sum_cmd_cnt));
	}

	utool_reg_msg("wr_delayed: %u\n", (uint32_t)((double)ba_mar_perf_data->wlatcnt_first /
						     clock_cycle_frequency_ns));
	utool_reg_msg("rd_delayed: %u\n", (uint32_t)((double)ba_mar_perf_data->rlatcnt_first /
						     clock_cycle_frequency_ns));
}

static int utool_ba_mar_perf_query_rpc_pkt(struct fwctl_rpc_ub_out *ba_query_mar_perf_out)
{
#define BA_MAR_PERF_HZ_TO_GHZ 1e-9
#define BA_MAR_PERF_MS_TO_S 1e-3
#define CLOCK_CYCLE_IDX 1

	uint32_t *ba_mar_perf_data_arr = ba_query_mar_perf_out->data;
	uint32_t clock_cycle_frequency = ba_mar_perf_data_arr[CLOCK_CYCLE_IDX];
	struct utool_ba_mar_perf_query ba_mar_perf_data = {};
	double clock_cycle_frequency_ghz = 0.0;
	double clock_cycle_frequency_ns = 0.0;
	double ba_mar_perf_time_s = 0.0;
	int ret = UTOOL_OK;

	if (g_ba_mar_perf_time == 0) {
		utool_err_msg("Mar perf time is 0, please check input param.\n");
		return UTOOL_ERR_INVALID_CMD;
	}

	if (clock_cycle_frequency == 0) {
		utool_err_msg("Clock cycle frequency is 0.\n");
		return UTOOL_ERR_INVALID_CMD;
	}

	clock_cycle_frequency_ghz = clock_cycle_frequency * BA_MAR_PERF_HZ_TO_GHZ;
	clock_cycle_frequency_ns = 1 / clock_cycle_frequency_ghz;

	ba_mar_perf_time_s = g_ba_mar_perf_time * BA_MAR_PERF_MS_TO_S;

	ret = utool_ba_mar_perf_obtain_data(&ba_mar_perf_data, ba_mar_perf_data_arr, ba_query_mar_perf_out->data_size);
	if (ret != UTOOL_OK) {
		return ret;
	}

	utool_ba_mar_perf_print_data(&ba_mar_perf_data, ba_mar_perf_time_s, clock_cycle_frequency_ns);

	return ret;
}

static int utool_ba_mar_perf_conf_operation(struct utool_dev *dev, struct utool_cmd_param *param)
{
#define BA_MAR_PERF_CONF_LEN 24

	struct utool_pkt_exec ba_mar_perf_conf_pkt = { UTOOL_CMD_CONFIG_BA_MAR_PEFR_STATS, BA_MAR_PERF_CONF_LEN,
						       utool_ba_mar_perf_conf_rpc_pkt };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	pkt_in = utool_port_time_create_pkt_in(&pkt_in_len, param);
	if (pkt_in == NULL) {
		utool_err_msg("Failed to create pkt in.\n");
		return UTOOL_ERR_MALLOC;
	}

	ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &ba_mar_perf_conf_pkt);
	utool_destroy_pkt_in(&pkt_in);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to conf ba mar perf reg.\n");
	}

	return ret;
}

static int utool_ba_mar_perf_query_operation(struct utool_dev *dev, struct utool_cmd_param *param)
{
#define BA_MAR_PERF_QUERY_LEN 56

	struct utool_pkt_exec ba_mar_perf_query_pkt = { UTOOL_CMD_QUERY_BA_MAR_PEFR_STATS, BA_MAR_PERF_QUERY_LEN,
							utool_ba_mar_perf_query_rpc_pkt };
	uint32_t pkt_in_len;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	pkt_in = utool_port_create_pkt_in(&pkt_in_len, param);
	if (pkt_in == NULL) {
		utool_err_msg("Failed to create pkt in.\n");
		return UTOOL_ERR_MALLOC;
	}

	ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &ba_mar_perf_query_pkt);
	utool_destroy_pkt_in(&pkt_in);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ba mar perf reg.\n");
	}

	return ret;
}

struct utool_func_dispatch g_utool_ba_flag_mpf_table[] = {
	{ true, BA_PKT_STATS, UTOOL_CMD_QUERY_BA_PKT_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_ba_pkt_stats_parse_rpc_pkt, utool_port_create_pkt_in },
	{ true, BA_MAR, UTOOL_CMD_QUERY_BA_MAR, UTOOL_REG_CNT_DEFAULT,
	  utool_ba_mar_parse_rpc_pkt, utool_port_create_pkt_in },
	{ false, BA_MAR_CYC_EN, UTOOL_CMD_QUERY_BA_MAR_CYC_EN, UTOOL_REG_CNT_DEFAULT,
	  utool_ba_mar_cyc_en_parse_rpc_pkt, utool_port_create_pkt_in },
	{ false, BA_ICRC, UTOOL_CMD_QUERY_BA_ICRC, UTOOL_REG_CNT_DEFAULT,
	  utool_ba_icrc_parse_rpc_pkt, utool_port_create_pkt_in },
};

int utool_ba_parse_rpc_pkt(struct fwctl_rpc_ub_out *ba_out)
{
	int ret = UTOOL_OK;

	if (ba_out == NULL) {
		utool_err_msg("Param is invalid, ba out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_module_parse(ba_out, UTOOL_ARRAY_SIZE(g_utool_ba_flag_mpf_table), g_utool_ba_flag_mpf_table,
				 UTOOL_ARRAY_SIZE(g_utool_ba_cal_reg_table), g_utool_ba_cal_reg_table);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ba rpc pkt.\n");
	}

	return ret;
}

static void utool_ba_print_help(void)
{
	utool_err_msg("The ubctl ba command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m ba -p ${port}\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m ba -p ${port} -f pkt_stats/mar/mar_cyc_en/icrc\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m ba -p ${port} -f mar_cyc_en -e ${value}\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m ba -p ${port} -f mar_perf -t ${time}\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m ba -p ${port} -f ub_mem_decoder/inter_sp_rout/inter_mp_rout"
		      "/intra_sp_rout/intra_mp_rout/port_scna/port_table/port_wb_table -i ${index}\n");
}

static int utool_ba_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			     struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec ba_pkt_exec = { UTOOL_CMD_QUERY_MAX, 0, NULL };
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

static int utool_ba_cmd_conf(struct utool_dev *dev, struct utool_cmd_param *param,
			     struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
#define UTOOL_MAR_CYC_EN_MAX_VALUE 3U

	if (strcmp(param->func, BA_MAR_CYC_EN) == 0) {
		if (param->value > UTOOL_MAR_CYC_EN_MAX_VALUE) {
			utool_err_msg("Param value = %u is invalid, it must be in [0, %u].\n",
				      param->value, UTOOL_MAR_CYC_EN_MAX_VALUE);
			return UTOOL_ERR_INVALID_PARAM;
		}
	}

	return utool_ba_cmd_func(dev, param, func_table, func_cnt);
}

static int utool_ba_cmd_mar_perf(struct utool_dev *dev, struct utool_cmd_param *param,
				 struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
#define BA_MAR_SHM_PATH_AUTHORITY 0600
#define BA_MAR_PERF_MAX_TIME 3600U
#define UBCTL "/ubctl"

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	char shm_path[UTOOL_DEV_NAME_LEN_MAX] = {0};
	int ret = UTOOL_OK, fd = -1;

	if (strcmp(param->func, BA_MAR_PERF) != 0) {
		utool_ba_print_help();
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = snprintf(shm_path, UTOOL_DEV_NAME_LEN_MAX, UBCTL "_%u_%u_nl_%u",
		       param->chip_id, param->die_id, (param->port / BA_MAR_PERF_NUM_TWO));
	if (ret <= 0 || ret >= UTOOL_DEV_NAME_LEN_MAX) {
		utool_err_msg("Failed to format shared memory path, ret = %d, %s.\n", ret, strerror(errno));
		return UTOOL_ERR;
	}

	fd = shm_open(shm_path, O_CREAT | O_RDWR, BA_MAR_SHM_PATH_AUTHORITY);
	if (fd == -1) {
		utool_err_msg("Failed to open shm path: %s\n", strerror(errno));
		return UTOOL_ERR_OPEN_FILE;
	}

	if (flock(fd, LOCK_EX) == -1) {
		utool_err_msg("Failed to acquire lock: %s\n", strerror(errno));
		ret = UTOOL_ERR_OPEN_FILE;
		goto cleanup;
	}

	if (param->time < 1 || param->time > BA_MAR_PERF_MAX_TIME) {
		utool_err_msg("Param time = %ums is invalid, it must be in [1ms, %ums].\n",
			      param->time, BA_MAR_PERF_MAX_TIME);
		ret = UTOOL_ERR_INVALID_CMD;
	} else {
		g_ba_mar_perf_time = param->time;
		ret = utool_ba_mar_perf_conf_operation(dev, param);
		if (ret == UTOOL_OK) {
			ret = utool_ba_mar_perf_query_operation(dev, param);
		}
	}

	(void)flock(fd, LOCK_UN);
cleanup:
	(void)close(fd);
	(void)shm_unlink(shm_path);

	return ret;
}

static int utool_ba_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
			struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec ba_pkt_exec = { UTOOL_CMD_QUERY_BA, 0, NULL };
	int ret = UTOOL_OK;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	ba_pkt_exec.execute = utool_ba_parse_rpc_pkt;

	ret = utool_ba_cal_data_len(&ba_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate reg cnt of ba all, ret = %d.\n", ret);
		return ret;
	}

	ret = utool_pkt_operation_have_port(dev, param, &ba_pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	return ret;
}

static struct utool_func_dispatch *utool_ba_get_mpfi_table(uint32_t *func_cnt)
{
	static struct utool_func_dispatch utool_ba_flag_mpfi_table[] = {
		{ false, BA_UB_MEM_DECODER_TABLE, UTOOL_CMD_QUERY_BA_MAR_TABLE, UTOOL_REG_CNT_DEFAULT,
		  utool_ub_mem_decoder_parse_rpc_pkt, utool_mar_table_create_pkt_in },
		{ false, BA_MAR_INTRA_SP_ROUT_TABLE, UTOOL_CMD_QUERY_BA_MAR_TABLE, UTOOL_REG_CNT_DEFAULT,
		  utool_intra_sp_rout_parse_rpc_pkt, utool_mar_table_create_pkt_in },
		{ false, BA_MAR_INTRA_MP_ROUT_TABLE, UTOOL_CMD_QUERY_BA_MAR_TABLE, UTOOL_REG_CNT_DEFAULT,
		  utool_intra_mp_rout_parse_rpc_pkt, utool_mar_table_create_pkt_in },
		{ false, BA_MAR_INTER_SP_ROUT_TABLE, UTOOL_CMD_QUERY_BA_MAR_TABLE, UTOOL_REG_CNT_DEFAULT,
		  utool_inter_sp_rout_parse_rpc_pkt, utool_mar_table_create_pkt_in },
		{ false, BA_MAR_INTER_MP_ROUT_TABLE, UTOOL_CMD_QUERY_BA_MAR_TABLE, UTOOL_REG_CNT_DEFAULT,
		  utool_inter_mp_rout_parse_rpc_pkt, utool_mar_table_create_pkt_in },
		{ false, BA_MAR_PORT_SCNA_TABLE, UTOOL_CMD_QUERY_BA_MAR_TABLE, UTOOL_REG_CNT_DEFAULT,
		  utool_port_scna_parse_rpc_pkt, utool_mar_table_create_pkt_in },
		{ false, BA_MAR_PORT_TABLE, UTOOL_CMD_QUERY_BA_MAR_TABLE, UTOOL_REG_CNT_DEFAULT,
		  utool_mar_port_parse_rpc_pkt, utool_mar_table_create_pkt_in },
		{ false, BA_MAR_PORT_WB_TABLE, UTOOL_CMD_QUERY_BA_MAR_TABLE, UTOOL_REG_CNT_DEFAULT,
		  utool_mar_port_wb_parse_rpc_pkt, utool_mar_table_create_pkt_in },
	};

	*func_cnt = UTOOL_ARRAY_SIZE(utool_ba_flag_mpfi_table);

	return utool_ba_flag_mpfi_table;
}

int utool_ba_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_func_dispatch utool_ba_flag_mpfe_table[] = {
		{ false, BA_MAR_CYC_EN, UTOOL_CMD_CONF_BA_MAR_CYC_EN, UTOOL_REG_CNT_DEFAULT,
		  utool_ba_mar_cyc_en_parse_rpc_pkt, utool_port_enable_create_pkt_in },
	};
	struct utool_func_dispatch *utool_ba_flag_mpfi_table = NULL;
	uint32_t utool_ba_mpfi_func_cnt = 0;

	utool_ba_flag_mpfi_table = utool_ba_get_mpfi_table(&utool_ba_mpfi_func_cnt);
	struct utool_cmd_dispatch utool_ba_cmd_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F, utool_ba_cmd_func,
		  g_utool_ba_flag_mpf_table, UTOOL_ARRAY_SIZE(g_utool_ba_flag_mpf_table) },
		{ UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_E, utool_ba_cmd_conf,
		  utool_ba_flag_mpfe_table, UTOOL_ARRAY_SIZE(utool_ba_flag_mpfe_table) },
		{ UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_I, utool_ba_cmd_func,
		  utool_ba_flag_mpfi_table, utool_ba_mpfi_func_cnt },
		{ UTOOL_FLAG_M | UTOOL_FLAG_P | UTOOL_FLAG_F | UTOOL_FLAG_T, utool_ba_cmd_mar_perf, NULL, 0 },
		{ UTOOL_FLAG_M | UTOOL_FLAG_P, utool_ba_cmd, NULL, 0 },
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
