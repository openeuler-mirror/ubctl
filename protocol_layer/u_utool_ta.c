// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_ta.h"

#define TA_PKT_STATS "pkt_stats"
#define TA_ABN_STATS "abn_stats"
#define TA_WQE_TIME "wqe_processing_time"

static struct utool_field_info g_utool_ta_pkt_stats_info[] = {
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "eip_sta0" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "eip_sta1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "eip_sta2" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "eip_sta3" },
	{ true, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "eip_axi_wr_outstanding" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "tp_ae_cnt_i" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqm_ae_cnt_i" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "tqep_ae_cnt_i" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "mrd_ae_cnt_i" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqm_ce_cnt_i" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqm_vld_ce_cnt_i" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqm_ce_ovf_cnt_o" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "eip_db_error_cnt_o" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ace_discard_cnt_o" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ae_overflow_cnt_o" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ae_vld_cnt_o" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "eip_irq_cnt_inc" },

	{ true, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "mrd_db_addr_err" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "mrd_db_timeout_err" },
	{ true, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "mrd_mb_cmd_err" },
	{ true, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "mrd_mb_addr_err" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "mrd_mb_resp_err" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_db_timeout_drop_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_mb_issue_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_mb_exec_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_dsqe_issue_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_dsqe_exec_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_dsqe_drop_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_jfsdb_issue_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_jfsdb_exec_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_jfcdb_issue_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_jfcdb_exec_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_eqdb_issue_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_eqdb_exec_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_flr_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_destroy_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_db_cfg_addr_err_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_rw_addr_err_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_mb_cmd_err_cnt" },
	{ true, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "mrd_axi_wr_err_info" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "mrd_axi_rd_err_info" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lqc_ta_mrd_tp_flush_issue_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lqc_ta_mrd_ta_flush_issue_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lqc_ta_mrd_tp_flush_comp_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lqc_ta_mrd_ta_flush_comp_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lqc_ta_mrd_bypass_wqe_exec_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lqc_ta_mrd_dsqe_intr_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lqc_ta_mrd_jfsdb_intr_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lqc_ta_mrd_jfcdb_intr_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lqc_ta_mrd_eqdb_intr_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lqc_ta_mrd_ue0_npa_mb_cmd_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lqc_ta_mrd_db_sec_auth_fail_cnt" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_dsqe_db_issue_cnt" },
	{ true, true, UTOOL_LOC11, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "mrd_mb_buff_full" },
	{ true, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "mrd_mb_buff_empty" },
	{ true, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "mrd_dynamic_clk_status1" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "mrd_dynamic_clk_status0" },
	{ true, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "mrd_mb_state" },
	{ true, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "mb_cmd_inpipe_num" },
	{ true, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "axi_wr_outstanding_num" },
	{ true, true, UTOOL_LOC4, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "axi_rd_outstanding_num" },

	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_host_int_num_vld_in" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "usi_eip_int_num_vld_in" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_vld_int_num_out_w" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "usi_vld_int_num_out_req" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_eip_int_cnt_for_fun_in" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "usi_misc_int_cnt_for_fun_in" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_eip_int_cnt_for_vec_in" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "usi_ccu_int_cnt_for_vec_in" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_host_int_cnt_in" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "usi_host_int_cnt_out" },
	{ true, true, UTOOL_LOC26, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC16, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "fun_num_cnt" },
	{ true, true, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ true, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "total_num_cnt_en" },
	{ true, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "fun_num_cnt_en" },
	{ true, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "vec_num_cnt_en" },
	{ true, false, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "vec_idx_cnt" },

	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "bus_rd_err_type" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "bus_rd_err_function_num" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "bus_rd_err_jetty_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "bus_rd_err_bbidx" },

	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "bus_wr_err_type" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "bus_wr_err_function_num" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "bus_wr_err_jetty_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "bus_wr_err_bbidx" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ctx_rd_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dma_mode_0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dma_mode_1" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rx_ta_ack_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rx_rce_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rx_cqe_cnt" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "proc_err_alm" },

	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "taack_abnorm_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "taack_normal_cnt" },

	{ false, true, UTOOL_LOC27, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC26, 0, UTOOL_CAP_ALL, "taack_abnorm_tag" },

	{ false, true, UTOOL_LOC5, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "tqc_int_src4" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "tqc_int_src3" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "tqc_int_src2" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "tqc_int_src1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tqc_int_src0" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqc_ue_err_bm0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tpwqe_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "cache_rfr_wl_en" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "cache_rfr_wl" },
	{ false, true, UTOOL_LOC23, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cache_srh_wl_0" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cache_srh_bp_wl_0" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cache_srh_wl_1" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cache_srh_bp_wl_1" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cache_srh_wl_2" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cache_srh_bp_wl_2" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cache_srh_wl_3" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cache_srh_bp_wl_3" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cache_srh_wl_4" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cache_srh_bp_wl_4" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cache_srh_wl_5" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cache_srh_bp_wl_5" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cache_srh_wl_6" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cache_srh_bp_wl_6" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cache_srh_wl_7" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cache_srh_bp_wl_7" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cache_srh_wl_8" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cache_srh_bp_wl_8" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cache_srh_wl_9" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cache_srh_bp_wl_9" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cache_srh_wl_10" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cache_srh_bp_wl_10" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cache_srh_wl_11" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "cache_srh_bp_wl_11" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "credit2srh_ost_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "credit2rd_ost_cnt" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "rce2srh_ost_cnt" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rce2rd_ost_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "wqe_loop_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "conti_loop_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tp_port_handshake_state" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "rtqeb_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "wtqeb_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "mrd_bypass_en_cfg" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "mrd_bypass_busy_time_cfg" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "dfx_bypass_disable" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "statis_mode" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "jetty_num_templ" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "func_num_templ" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "statis_en" },
	{ false, true, UTOOL_LOC26, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ssn_templ" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "taack_normal_cap_mode" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "taack_abnorm_cap_mode" },
	{ false, true, UTOOL_LOC18, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC26, 0, UTOOL_CAP_ALL, "taack_normal_tag" },
	{ false, true, UTOOL_LOC27, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "taack_normal_ssn" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "taack_abnorm_ssn" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "taack_normal_clr" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "taack_abnorm_clr" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "taack_normal_header" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "taack_abnorm_header" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "tqep_rd_ost_cnt" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "cqm_rd_ost_cnt" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "rsp_rd_ost_cnt" },
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "rsp_wr_ost_cnt" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "tqc_srh_ost_cnt" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "tqc_rd_ost_cnt" },
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "bus_rd_ost_cnt" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "bus_wr_ost_cnt" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tqep_cnt_en" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "reg_tqep_idle" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "reg_tqep_cgc_idle" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "reg_tqep_wqer_idle" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "reg_tqep_sqes_idle" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "reg_tqep_saa_idle" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "reg_tqep_erpt_idle" },
	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "tm_in_fifo_cnt" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "tm_in_fifo_full" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "tm_in_fifo_empty" },
	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "tm_out_fifo_cnt" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "tm_out_fifo_full" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "tm_out_fifo_empty" },
	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "wqer_wqe_num_fifo_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "wqer_wqe_num_fifo_empty" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "wqer_wqe_num_fifo_full" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "tp_loop_fifo_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "tp_loop_fifo_empty" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "tp_loop_fifo_full" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "cqe_lkp_ctrl_en" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqm_jfc_pa_min_idx" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqm_jfc_pa_max_idx" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "gcqe_cqereq_num_cnt_2" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "gcqe_cqereq_num_cnt_1" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqm_target_normal_cqe_cnt" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "cqm_target_raw_cqe_cnt" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "cqm_target_notify_cqe_cnt" },
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "cqm_cnt_info" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "cqm_cnt_mode_en" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_ALL, "cqm_cnt_cqe_en" },
	{ false, true, UTOOL_LOC29, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cqm_stars_cqe_cnt" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cqm_se_req_cnt" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cqm_inline_wr_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqm_inline_rd_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "gcqe_cqe_err_alarm" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "gcqe_wrd_alarm" },
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqe_fifo_empty" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "cqm_ras_function_id3" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "cqm_ras_function_id4" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "cqm_cqe_handshake1" },
	{ false, true, UTOOL_LOC11, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "cqm_cqe_handshake2" },
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "cqm_cqe_handshake3" },
	{ false, true, UTOOL_LOC21, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "cqm_cqe_handshake5" },
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqc_srh_cnt_dfx2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "tqc_srh_ost_dfx0" },
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "tqc_srh_ost_dfx1" },
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "src_rdctx_ost_dfx" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "tqc_srhrsp_ost_dfx0" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "mrd_req_err" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "taack_ssn_err" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "taack_rspst_err" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "rcr_rd_ctx_err" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "taack_cache_err" },
	{ false, true, UTOOL_LOC5, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqc_ue_err_bm1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqc_ue_err_bm2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqc_ue_err_bm3" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tqeb2tqc_srh_vld" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "mrd2tqc_srh_vld" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "tqep2tqc_srh_vld" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "tqms2tqc_srh_vld" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "rsp2tqc_0srh_vld" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "tom2tqc_srh_vld(LQC_TA_TQC_SEARCH_VLD_DFX)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "tp2ta_rqm2tqc_srh_vld" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "taack2tqc_srh_vld" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "eip2tqc_srh_vld" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "rsp2tqc_1srh_vld" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tqc2tqeb_srh_rdy" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "tqc2mrd_srh_rdy" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "tqc2tqep_srh_rdy" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "tqc2tqms_srh_rdy" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "tqc2rsp_0srh_rdy" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "tqc2tom_srh_rdy(LQC_TA_TQC_SEARCH_RDY_DFX)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "ta2tp_tqc2rqm_srh_rdy" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "tqc2taack_srh_rdy" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "tqc2eip_srh_rdy" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "tqc2rsp_1srh_rdy" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tqep2tqc_rd_vld" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "tqms2tqc_rd_vld" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "rsp2tqc_rd_vld" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "cqm2tqc_rd_vld" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "tqeb2tqc_rd_vld" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "tp2ta_rqm2tqc_rd_vld" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "tom2tqc_rd_vld(LQC_TA_TQC_RW_VLD_DFX)" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "tqms2tqc_wr_vld" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "rsp2tqc_wr_vld" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "tom2tqc_wr_vld(LQC_TA_TQC_RW_VLD_DFX)" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "tqep2tqc_wr_vld" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "eip2tqc_wr_vld" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "tqc2mrd_mb_rdata_vld" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "mrd2tqc_mb_wdata_vld" },
	{ false, true, UTOOL_LOC14, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tqc2tqep_rd_rdy" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "tqc2tqms_rd_rdy" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "tqc2rsp_rd_rdy" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "tqc2cqm_rd_rdy" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "tqc2tqeb_rd_rdy" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "ta2tp_tqc2rqm_rd_rdy" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "tqc2tom_rd_rdy(LQC_TA_TQC_RW_RDY_DFX)" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "tqc2tqms_wr_rdy" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "tqc2rsp_wr_rdy" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "tqc2tom_wr_rdy(LQC_TA_TQC_RW_RDY_DFX)" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "tqc2tqep_wr_rdy" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "tqc2eip_wr_rdy" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "mrd2tqc_mb_rdata_rdy" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "tqc2mrd_mb_wdata_rdy" },
	{ false, true, UTOOL_LOC14, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "tqc_srhrsp_ost_dfx1" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "taack_timeout_rpt_mode" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "db_loop_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "timmer_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "cur_credit_cnt" },
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "retry_func_id" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "retry_jfs_num" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ctx_ci" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ctx_pi" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "retry_ptr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ctx_rty_pi" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "retry_wqe_ssn_num" },
	{ false, true, UTOOL_LOC21, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "length_0_ae_en" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "prefetch_ctx_retry" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "prefetch_ctx_normal_rd" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "prefetch_ctx_normal" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC26, 0, UTOOL_CAP_ALL, "chain_vld" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "ctx_reading_flag" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_ALL, "tqc_rd_retry_loop_flag" },
	{ false, false, UTOOL_LOC29, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "retry_conflict_loop_flag" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "tqc_rd_retry_taack_inc_err_flag" },
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqc_rd_retry_err_flag" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ost_not_enough_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "lock_buf_wr_cnt" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lock_buf_clr_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "lock_buf_clr_miss_jetty_num" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lock_buf_clr_miss" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "lock_buf_clr_miss_wqebb_idx" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lock_buf_clr_miss_func_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "lock_buf_rd_miss_jetty_num" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "lock_buf_rd_miss_req_type" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "lock_buf_rd_miss_msk_dis" },
	{ false, true, UTOOL_LOC23, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lock_buf_rd_miss" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "lock_buf_rd_miss_wqebb_idx" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lock_buf_rd_miss_func_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "cnt_en" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "tqeb_int_src" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tqep_rd_req_vld" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "tqep_rd_req_rdy" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "tqep_rd_resp_vld" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "tqep_rd_resp_rdy" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "cqm_rd_req_vld" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "cqm_rd_req_rdy" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "cqm_rd_resp_vld" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cqm_rd_resp_rdy" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "rsp_rd_req_vld" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "rsp_rd_req_rdy" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "rsp_rd_resp_vld" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "rsp_rd_resp_rdy" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "rsp_wr_req_vld" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "rsp_wr_req_rdy" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "tqep_clr_req_vld" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "tqep_clr_req_rdy" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "cqm_clr_req_vld" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "cqm_clr_req_rdy" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "tqc_srh_vld(LQC_TA_TQEB_HANDSHAKE_STATUS)" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "tqc_srh_rdy(LQC_TA_TQEB_HANDSHAKE_STATUS)" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "tqc_rd_vld(LQC_TA_TQEB_HANDSHAKE_STATUS)" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "tqc_rd_rdy(LQC_TA_TQEB_HANDSHAKE_STATUS)" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "ami_req_vld" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "ami_req_rdy" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "ami_rvld" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "ami_rrdy" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_ALL, "ami_wvld" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "ami_wrdy" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_ALL, "ami_bvld" },
	{ false, false, UTOOL_LOC29, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "ami_brdy" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "rsc_req" },
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rsc_done" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "dfx_tqep_retry_crd" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqms_int_src" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "fun_bitmap(func_bmp_num0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "fun_bitmap(func_bmp_num1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "fun_bitmap(func_bmp_num2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "fun_bitmap(func_bmp_num3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "sch_fifo_fill" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "bresp_fifo_fill" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "data_ram_addr_fifo_fill" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "aw_fifo_fill" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "rd_inf_fifo_fill" },
	{ false, true, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "wr_inf_fifo_fill" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "w_fifo_fill" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "pref_r_data_ram_fifo_fill" },
	{ false, true, UTOOL_LOC17, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "aw_fifo_full" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "w_fifo_full" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "bresp_fifo_full" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "wr_inf_fifo_full" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "rd_inf_fifo_full" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "data_ram_addr_fifo_full" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "r_fifo_full" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "r_fifo_fill" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "pref_r_data_ram_fifo_afull" },
	{ false, true, UTOOL_LOC13, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "timer_sta_0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tom_dfx_cnt_en" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tqep2tom_timer_req" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "tqc2tom_timer_req" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "tom2tqc_srh_vld(LQC_TA_TOM_VLD_DFX)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "tom2tqc_rd_vld(LQC_TA_TOM_VLD_DFX)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "tom2tqc_wr_vld(LQC_TA_TOM_VLD_DFX)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "cqm2tom_timer_req" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "tom2cqm_timeout_req" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "tom2tqms_retry_req" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "tom2timercbb_req" },
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tom2tqep_timer_ack" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "tom2tqc_timer_ack" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "tqc2tom_srh_rdy(LQC_TA_TOM_REQ_DFX)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "tqc2tom_rd_rdy(LQC_TA_TOM_REQ_DFX)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "tqc2tom_wr_rdy(LQC_TA_TOM_REQ_DFX)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "tom2cqm_timer_ack" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "cqm2tom_timeout_ack" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "tqms2tom_retry_ack" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "tom2timercbb_ack" },
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "rtqc_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "wtqc_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "rsqe_fsm_sta" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "tqms_iqm_fifo_empty_sta" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "dfx_tm_crd_ctrl" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_iqm_prv_vld(que_pri_idx0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_iqm_prv_vld(que_pri_idx1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_iqm_prv_vld(que_pri_idx2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_iqm_prv_vld(que_pri_idx3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_iqm_prv_vld(que_pri_idx4)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_iqm_prv_vld(que_pri_idx5)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_iqm_prv_vld(que_pri_idx6)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_iqm_prv_vld(que_pri_idx7)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tm_crd(que_pri_idx0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tm_crd(que_pri_idx1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tm_crd(que_pri_idx2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tm_crd(que_pri_idx3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tm_crd(que_pri_idx4)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tm_crd(que_pri_idx5)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tm_crd(que_pri_idx6)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tm_crd(que_pri_idx7)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_dqm_crd_bkp(que_pri_idx0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_dqm_crd_bkp(que_pri_idx1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_dqm_crd_bkp(que_pri_idx2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_dqm_crd_bkp(que_pri_idx3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_dqm_crd_bkp(que_pri_idx4)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_dqm_crd_bkp(que_pri_idx5)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_dqm_crd_bkp(que_pri_idx6)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_dqm_crd_bkp(que_pri_idx7)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tqms_ddr_fun_err_bmp(func_bmp_num0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tqms_ddr_fun_err_bmp(func_bmp_num1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tqms_ddr_fun_err_bmp(func_bmp_num2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dfx_tqms_ddr_fun_err_bmp(func_bmp_num3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "taack_rsc_rcved" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "cur_jetty_num" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "cur_function_id" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "cur_retry_type" },
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "cur_rc_type" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "flush_db_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rst_db_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "cqm_err_cqe_cnt" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "cqm_flush_cqe_cnt" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "cqm_tar_err_cqe_cnt" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "cqm_cqe_handshake4" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqc_srh_ost_dfx2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "db_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "wqe_rd_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "wqe_back_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ctx_data_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ctx_wr_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ctx_clr_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "rc_queue_head_only_num" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "dbell2loop_cnt" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "module_flr_done" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "module_flr_done_force" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "cqersp_rsc_done" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "jfs_srh2rsqe_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rctx_ost_cnt" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "rsqe_ost_cnt" },
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	// 0xA02C
	{ false, false, UTOOL_LOC0, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "rq_crdt_req_th" },
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "rdma_pre_sub_value" },
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "sch_roce_num_port(0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "sch_roce_num_port(1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "rq_quanta_value" },
	{ false, true, UTOOL_LOC7, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "qm_crdt_dpl_info_lock_rq" },
	{ false, true, UTOOL_LOC26, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "qm_crdt_dpl_vld_num_rq" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "q_crdt_sts_grp_id_rq" },
	{ false, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "q_crdt_sts_rq" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tm_ue_flush_done" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "sch_ue_flush_done" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "qm_crdt_dpl_vld_flush_num_rq" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tqep_tm_en" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rst_funid" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "rst_fun_en" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "rst_fun_done" },
	{ false, true, UTOOL_LOC18, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "mb_status" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "hw_run" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_2, "wqe_processing_time" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "lock_start_jetty" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC30, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lock_wqe_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "lock_end_jetty" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "lock_buf_tqep_rd_ost_cnt" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "lock_buf_cqm_rd_ost_cnt" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "lock_buf_rsp_rd_ost_cnt" },
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cqm_jetty_ae_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqm_jfc_ae_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "cqm_ae_jtnum(rx)" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "cqm_ae_jtnum(tx)" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "cqm_int_src0" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "cqm_int_src1" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "cqm_int_src2" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "cqm_int_src3" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "cqm_int_src4" },
	{ false, true, UTOOL_LOC5, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "mrd_int_src0" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "mrd_int_src1" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "mrd_int_src2" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "mrd_int_src3" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "mrd_int_src4" },
	{ false, true, UTOOL_LOC5, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "func0_31_bresp_int_src" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "func32_63_bresp_int_src" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "func64_95_bresp_int_src" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "func96_127_bresp_int_src" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tom_int_src0" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "tom_int_src1" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "tom_int_src2" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "tom_int_src3" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "tom_int_src4" },
	{ false, true, UTOOL_LOC5, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "func0_31_ae_of_int_src" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "func32_63_ae_of_int_src" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "func64_95_ae_of_int_src" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "func96_127_ae_of_int_src" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "snap_taack_cfg_jetty" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "snap_taack_cfg_func" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "snap_taack_cfg_ssn" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "snap_taack_cfg_mode" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "snap_taack_cfg_en" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "snap_taack_status" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "snap_taack_payload0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "snap_taack_payload1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "vector" },
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_data" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "vect_addr_idx" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "usi_vect_mask" },
	{ false, true, UTOOL_LOC17, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "msg_cfg_idx" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "msg_low_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "msg_up_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_dest_eid0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_dest_eid1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_dest_eid2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_dest_eid3" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "urma_ue_num" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "urma_mue_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cdma_ue_num" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "cdma_mue_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "pmu_ue_num" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "pmu_mue_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccu_ue_num" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccu_mue_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "interrupt_number" },
	{ false, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "interrupt_enable_number" },
	{ false, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "usi_int_src" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "retry_ctx_vld" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "normal_ctx_vld" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "wqe_rcv_left_cnt" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "wqe_rd_left_cnt" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "rr_result_retry_hold" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "rr_result_normal_hold" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "retry_find_cycle_flag" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "reading_flag" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "src_so_satisfy" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "wqer2cgc_retry_find_vld" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "bypass_wqe_vld" },
	{ false, true, UTOOL_LOC25, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl0" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl1" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl2" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl3" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl4" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl5" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl6" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl7" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl8" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl9" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl10" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl11" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl12" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl13" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl14" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "sl_vl15" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "gcqe_cqereq_num_cnt_3" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "gcqe_wr_ost_cnt" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cqm_timer_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqm_timeout_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC19, 0, UTOOL_CAP_V13, "cache_srh_bp_wl_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_V13, "cache_srh_wl_en" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "dfx_timer_ctrl0" },

	{ false, true, UTOOL_LOC29, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC28, 0, UTOOL_CAP_V13, "rc_wqebb_ostd_num" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC20, 0, UTOOL_CAP_V13, "jfs_wqebb_ostd_num" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC12, 0, UTOOL_CAP_V13, "adaptive_stride" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC8, 0, UTOOL_CAP_V13, "wqebb_max_ostd_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "wqebb_ostd_adaptive_en" },

	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V13, "tqep_tp_credit" },

	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "tqep_sch_jam" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V13, "tqep_sch_jam_wait_cycle" },

	{ false, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V13, "tqep_debug_block_flag" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V13, "tqep_send_go_on" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "tqep_debug_mode" },

	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V13, "pi_err_switch" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V13, "rc_wqe_type_err_switch" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V13, "inline_len_overlen_switch" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V13, "sge_num_overlen_switch" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V13, "wqe_overlen_detect_switch" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V13, "opcode_out_cap_err_detect_switch" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V13, "opcode_err_detect_switch" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V13, "ctx_err_detect_switch" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "tqeb_err_detect_switch" },

	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "tqep_so_switch" },

	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "tqep_fence_switch" },

	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_V13, "tm_in_fifo_afull_cfg" },

	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_V13, "tm_out_fifo_afull_cfg" },

	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_V13, "ae_fifo_afull_cfg" },

	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_V13, "que_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V13, "start_qid" },

	{ false, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V13, "tm_elr_vld" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "tqep_send_elr_done" },

	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_V13, "jfs_mode_is_srm" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_V13, "jfs_mode_is_raw" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC29, 0, UTOOL_CAP_V13, "opcode_reg" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_V13, "jetty_suspend" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_V13, "bypass_db" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_V13, "ctx_rd_normal_rd_err" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_V13, "retry_err" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_V13, "taack_inc_err" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_V13, "ctx_rst_flag" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_V13, "ctx_flush_flag" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_V13, "reading_left_wqe_flag" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC13, 0, UTOOL_CAP_V13, "sgmt_ost" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V13, "send_flag_tmp" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V13, "sqes2saa_ctx_vld" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V13, "cur_ctx_using" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "jetty_cycle" },

	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_V13, "db_capture_rc_type" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_V13, "db_capture_retry" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC29, 0, UTOOL_CAP_V13, "db_capture_jetty_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_V13, "db_capture_func_num" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "db_sch_capture_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "wqe_send_capture_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "wqe_send_no_empty_capture_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "db_loop_capture_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "db_wr_tqc_capture_cnt" },

	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "tqep_odr_mask_en" },

	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V13, "tqep_tqc_srh_ost_cfg" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V13, "chain_vld_high" },

	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_V13, "err_rc_type" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_V13, "err_retry_type" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC29, 0, UTOOL_CAP_V13, "err_jetty_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_V13, "err_func_num" },

	{ false, true, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC30, 0, UTOOL_CAP_V13, "func_id_loop_err" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC18, 0, UTOOL_CAP_V13, "jetty_num_loop_err" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "tp_loop_err" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "ctx_idx_vld" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "normal_rd_sch_flag" },

	{ false, true, UTOOL_LOC29, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_V13, "traffic_mode" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC27, 0, UTOOL_CAP_V13, "rcv_ssn_equal_src_ssn" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_V13, "sqes_err_flag" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_V13, "so_flag" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_V13, "so_wqe_reading_flag" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_V13, "resplit_flag" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC22, 0, UTOOL_CAP_V13, "resplit_wqe_cnt" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC19, 0, UTOOL_CAP_V13, "tawqe_buf_cnt" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC16, 0, UTOOL_CAP_V13, "tpwqe_buf_cnt" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_V13, "no_wqe_send_too_many_times" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_V13, "que_empty_send_so_wqe" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC10, 0, UTOOL_CAP_V13, "tpwqe_buf_rptr" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC7, 0, UTOOL_CAP_V13, "tpwqe_buf_wptr" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC4, 0, UTOOL_CAP_V13, "final_sge_out" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "op_read_send_flag" },

	{ false, true, UTOOL_LOC25, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_V13, "writing_ctx_flag" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_V13, "wqe_rcv_allow_loop_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_V13, "wr_done_last_sgmt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V13, "wr_done_last_sgmt_cnt_for_timer" },

	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "resplit_en" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "ctx_srh_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "ctx_srh_rsp_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "bypass_db_cnt" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V13, "raw_tpwqe_cnt" },

	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC18, 0, UTOOL_CAP_V13, "rst_fsm" },
	{ false, true, UTOOL_LOC13, UTOOL_LOC15, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_V13, "rsc2mrd_rst_done_status" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_V13, "mrd2rsc_rst_req_status" },

	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V13, "usi_ccu_int_num_vld_in" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V13, "usi_misc_int_num_vld_in" },

	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V13, "usi_int_cnt_for_vec_out" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V13, "usi_int_cnt_for_fun_out" },

	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_V13, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V13, "qs_cshap_bypass" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V13, "pri_pshap_bypass" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V13, "pri_cshap_bypass" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V13, "pg_pshap_bypass" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V13, "pg_cshap_bypass" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V13, "port_shap_bypass" },
};

static struct utool_field_info g_utool_ta_abn_stats_info[] = {
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "lqc_tache_ro" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "lqc_tache_rc" },
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC29, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "wmtp_ram_fifo_full" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_ALL, "wmtp_ram_fifo_empty" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "wm_ram_fifo_full" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_ALL, "wm_ram_fifo_empty" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "ro_ram_fifo_full" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "ro_ram_fifo_empty" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "we_ram_fifo_full" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "we_ram_fifo_empty" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "rcr_op_grant" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "rcr_rdata_array_afull" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rcr_rdata_array_empty" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "rcr_type_array_afull" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "rcr_type_array_empty" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "cqersp_array_afull" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "cqersp_array_empty" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "taack_array_afull" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "taack_array_empty" },
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC29, 0, UTOOL_CAP_ALL, "eip_array_afull" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC27, 0, UTOOL_CAP_ALL, "eip_array_empty" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "tom_array_afull" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "tom_array_empty" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "rsp_array_afull" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_ALL, "rsp_array_empty" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "tqms_array_afull" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "tqms_array_empty" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "tqep_wr_array_afull" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "tqep_wr_array_empty" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "dmae_array_clr_afull" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "dmae_array_clr_empty" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "tom_array_clr_afull" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "tom_array_clr_empty" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "rqm_array_clr_afull" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "rqm_array_clr_empty" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "tqeb_array_clr_afull" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "tqeb_array_clr_empty" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cqm_array_clr_afull" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "cqm_array_clr_empty" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "rsp_array_clr_afull" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "rsp_array_clr_empty" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "tqms_array_clr_afull" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "tqms_array_clr_empty" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "tqep_array_clr_afull" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tqep_array_clr_empty" },
	{ false, true, UTOOL_LOC22, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "rcr_srhidx_array_afull" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "rcr_srhidx_array_empty" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rfr_comb_all_full" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "rfr_comb_all_empty" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "rqm_comb_all_full" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "rqm_comb_all_empty" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "tqeb_comb_all_full" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "tqeb_comb_all_empty" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "tom_comb_all_full" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "tom_comb_all_empty" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "cqm_comb_all_full" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "cqm_comb_all_empty" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "rsp_comb_all_full" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "rsp_comb_all_empty" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "tqep_comb_all_full" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "tqep_comb_all_empty" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "tqms_comb_all_full" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tqms_comb_all_empty" },
	{ false, true, UTOOL_LOC26, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "tqms_reg_cnt_en" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "tqms_reg_cnt_clr" },
	{ false, true, UTOOL_LOC21, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "tqms_reg_cnt_ctrl" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "tqms_reg_cnt" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "tqms_vld_sta" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "tqms_rdy_sta" },
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "tqms_iqm_fifo_full_sta" },
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "tqms_tch_ring_buf_seloh" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "tqms_tch_ring_buf_pointer_sel" },
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "tqc_rdata_err_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "bus_rd_err_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "bus_wr_err_cnt" },
	{ false, true, UTOOL_LOC11, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "tpwqe_info_fifo_full" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "tpwqe_info_fifo_afull" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "tpwqe_info_fifo_empty" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "tpwqe_info_fifo_cnt" },

	{ false, true, UTOOL_LOC22, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "tqms_sch_vld" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "tqms_sch_rdy" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "tqms_loop_vld" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "tqms_loop_rdy" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "rsp_loop_req" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "rsp_loop_ack" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "tqc_srh_vld(LQC_TA_TQEP_INTERFACE)" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_ALL, "tqc_srh_rdy(LQC_TA_TQEP_INTERFACE)" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "tqc_rd_vld(LQC_TA_TQEP_INTERFACE)" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_ALL, "tqc_rd_rdy(LQC_TA_TQEP_INTERFACE)" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "tqc_wr_vld" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "tqc_wr_rdy" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "tqeb_rd_vld" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "tqeb_rd_rdy" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "tqeb_wqe_vld" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_ALL, "tqeb_wqe_rdy" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "tqeb_clr_vld" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "tqeb_clr_rdy" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "eip_req" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "eip_ack" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "tom_req" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "tom_ack" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "timer_buf_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "ctx_buf_cnt" },
	{ false, true, UTOOL_LOC25, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC24, 0, UTOOL_CAP_ALL, "wqe_err_wqe_idx" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC8, 0, UTOOL_CAP_ALL, "wqe_err_code" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "wqe_err_vld" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqeb_wqe_err_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqc_context_err_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rc_full_queue_cnt" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "last_full_queue_func" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "last_full_queue_num" },
	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "rx_cqe_cnt_mode" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC3, 0, UTOOL_CAP_ALL, "rx_rce_cnt_mode" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "rx_ta_ack_cnt_mode" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rx_cnt_cfg_func" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "rx_cnt_cfg_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ta_port_handshake_state" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "wr_ost_cnt" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "loop2rd_ost_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "loop2srh_ost_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "wrce_ost_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqe_fifo_full" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "cqm_ras_function_id1" },
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "cqm_ce_ovfl_num_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqm_ce_comp_num_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "cqm_ras_function_id2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "func0_31_ae_of_int_src_ce" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dma_mode_0(cqm)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dma_mode_1(cqm)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "split_size" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "mtu_size_compact" },
	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_func_err_info_0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_func_err_info_2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_func_err_info_3" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "tch_err_db_jfs_num" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tch_err_db_function_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "eqm_err_db_jfs_num" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "eqm_err_db_function_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "oqm_ddr_err_rd_fun" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "oqm_ddr_err_wr_fun" },
	{ false, true, UTOOL_LOC26, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "taack_timeout_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "tanak_rnr_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "jfs_pi_err_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "rce_write_bypass_req_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "rce_write_bypass_done_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "cqm_normal_cqe_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "mrd_func_err_info_1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_ALL, "eqm_err_type" },
	{ false, true, UTOOL_LOC3, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "tch_err_type" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "mrd_rdata_ram_ecc_1b_int" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_ALL, "mrd_mb_ram_ecc_1b_int" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "mrd_rdata_ram_ecc_1b_addr" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "mrd_mb_ram_ecc_1b_addr" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	// opcode 0xA032
	{ false, true, UTOOL_LOC22, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "usi_addr_sram_addr_pre_dfx" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "usi_tbl_sram_addr_dfx" },

	{ false, true, UTOOL_LOC26, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "usi_src_fun_over_dfx" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "usi_src_over_int_idx" },

	{ false, true, UTOOL_LOC17, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC16, 0, UTOOL_CAP_ALL, "usi_index_rdy_send_dfx" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "host_int_over_idx" },

	{ false, true, UTOOL_LOC22, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC21, 0, UTOOL_CAP_ALL, "ami_wr_ost_num" },
	{ false, true, UTOOL_LOC12, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "write_err_vec_idx_dfx" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tom_ue_err_bm1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tom_ue_err_bm2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tom_ue_err_bm3" },

	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tom_mue_err_bm0" },

	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "mrd2tqms_db_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "rsp2tqms_db_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tom2tqms_db_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqep2tqms_db_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqc2tqms_db_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms2tqep_sch_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms2tqep_bypass_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms2tqep_jt_rst_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms2ami_rd_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms2ami_wr_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms_jt_rst_sq_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms_jt_rst_rc_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms_jt_rst_flr_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms_tch_merge_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms_iqm_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms_oqm_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms_reg_err_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "tqms2tqc_srh_cnt" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqms2tqc_wr_clr_cnt" },
};

static struct utool_field_info g_utool_ta_wqe_time_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_1 | UTOOL_CAP_3, "wqe_processing_time" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_1 | UTOOL_CAP_3, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_1 | UTOOL_CAP_3, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_1 | UTOOL_CAP_3, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_1 | UTOOL_CAP_3, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_1 | UTOOL_CAP_3, "reserved" },
};

static struct utool_cal_reg_cnt_dp g_utool_ta_cal_reg_table[] = {
	{ true, true, TA_PKT_STATS, UTOOL_ARRAY_SIZE(g_utool_ta_pkt_stats_info), g_utool_ta_pkt_stats_info },
	{ true, true, TA_ABN_STATS, UTOOL_ARRAY_SIZE(g_utool_ta_abn_stats_info), g_utool_ta_abn_stats_info },
	{ true, false, TA_WQE_TIME, UTOOL_ARRAY_SIZE(g_utool_ta_wqe_time_info), g_utool_ta_wqe_time_info },
};

int utool_ta_cal_data_len(uint32_t *ta_data_len)
{
	struct utool_cal_reg_func_param ta_cal_reg_param = {
		ta_data_len, UTOOL_REG_CNT_DEFAULT, NULL,
		g_utool_ta_cal_reg_table, UTOOL_ARRAY_SIZE(g_utool_ta_cal_reg_table)
	};
	int ret = UTOOL_OK;

	if (ta_data_len == NULL) {
		utool_err_msg("Param is invalid, ta data len is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_cal_func_reg_len(UTOOL_FUNC_ALL, &ta_cal_reg_param);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate reg cnt, ret = %d.\n", ret);
	}

	return ret;
}

static int utool_ta_parse_pkt_stats(struct fwctl_rpc_ub_out *ta_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(ta_out, UTOOL_ARRAY_SIZE(g_utool_ta_pkt_stats_info),
			      g_utool_ta_pkt_stats_info, UTOOL_CONCAT_STR(UTOOL_MODULE_TA, TA_PKT_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ta pkt stats data.\n");
	}

	return ret;
}

static int utool_ta_parse_abn_stats(struct fwctl_rpc_ub_out *ta_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(ta_out, UTOOL_ARRAY_SIZE(g_utool_ta_abn_stats_info),
			      g_utool_ta_abn_stats_info, UTOOL_CONCAT_STR(UTOOL_MODULE_TA, TA_ABN_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to print ta abn stats data.\n");
	}

	return ret;
}

static int utool_ta_parse_wqe_time(struct fwctl_rpc_ub_out *ta_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(ta_out, UTOOL_ARRAY_SIZE(g_utool_ta_wqe_time_info),
			      g_utool_ta_wqe_time_info, UTOOL_CONCAT_STR(UTOOL_MODULE_TA, TA_WQE_TIME));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to print ta wqe time data.\n");
	}

	return ret;
}

static struct utool_func_dispatch g_utool_ta_func_table[] = {
	{ true, TA_PKT_STATS, UTOOL_CMD_QUERY_TA_PKT_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_ta_parse_pkt_stats, utool_null_create_pkt_in },
	{ true, TA_ABN_STATS, UTOOL_CMD_QUERY_TA_ABN_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_ta_parse_abn_stats, utool_null_create_pkt_in },
	{ false, TA_WQE_TIME, UTOOL_CMD_QUERY_TA_WQE_TIME, UTOOL_REG_CNT_DEFAULT,
	  utool_ta_parse_wqe_time, utool_null_create_pkt_in },
};

int utool_ta_parse_rpc_pkt(struct fwctl_rpc_ub_out *ta_out)
{
	int ret = UTOOL_OK;

	if (ta_out == NULL) {
		utool_err_msg("Param is invalid, ta out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_module_parse(ta_out, UTOOL_ARRAY_SIZE(g_utool_ta_func_table), g_utool_ta_func_table,
				 UTOOL_ARRAY_SIZE(g_utool_ta_cal_reg_table), g_utool_ta_cal_reg_table);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ta rpc pkt.\n");
	}

	return ret;
}

static void utool_ta_print_help(void)
{
	utool_err_msg("The ubctl ta command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m ta\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m ta -f pkt_stats/abn_stats/wqe_processing_time\n");
}

static int utool_ta_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			     struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_MAX, 0, NULL };
	struct utool_cal_reg_func_param ta_cal_reg_param = {
		NULL, 0, NULL, g_utool_ta_cal_reg_table, UTOOL_ARRAY_SIZE(g_utool_ta_cal_reg_table)
	};
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;
	uint32_t i;

	for (i = 0; i < func_cnt; i++) {
		if (strcmp(param->func, func_table[i].func) == 0) {
			func_pkt_exec.rpc_cmd = func_table[i].rpc_cmd;
			func_pkt_exec.execute = func_table[i].execute;

			ta_cal_reg_param.data_len = &func_pkt_exec.data_len;
			ta_cal_reg_param.user_def_data_len = func_table[i].data_len;

			ret = utool_cal_func_reg_len(param->func, &ta_cal_reg_param);
			if (ret != UTOOL_OK) {
				utool_err_msg("Failed to calculate reg cnt of ta func %s.\n", param->func);
				return ret;
			}

			if (func_table[i].create_pkt_in == NULL) {
				utool_err_msg("Failed to create ta func pkt in, callback is NULL.\n");
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
	utool_ta_print_help();

	return UTOOL_ERR_FUNC_NOT_FOUND;
}

static int utool_ta_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
			struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_TA, 0, NULL };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	func_pkt_exec.execute = utool_ta_parse_rpc_pkt;

	ret = utool_ta_cal_data_len(&func_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate data len of all, ret = %d.\n", ret);
		return ret;
	}

	pkt_in = utool_null_create_pkt_in(&pkt_in_len, param);
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

int utool_ta_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_ta_cmd_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_F, utool_ta_cmd_func,
		  g_utool_ta_func_table, UTOOL_ARRAY_SIZE(g_utool_ta_func_table) },
		{ UTOOL_FLAG_M, utool_ta_cmd,
		  g_utool_ta_func_table, UTOOL_ARRAY_SIZE(g_utool_ta_func_table) },
	};
	uint32_t ta_cmd_cnt = UTOOL_ARRAY_SIZE(utool_ta_cmd_table);
	uint32_t i = 0;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < ta_cmd_cnt; i++) {
		if (param->flags == utool_ta_cmd_table[i].flags) {
			if (utool_ta_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch. Callback is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

			return utool_ta_cmd_table[i].execute(dev, param,
							     utool_ta_cmd_table[i].func_table,
							     utool_ta_cmd_table[i].func_cnt);
		}
	}

	utool_ta_print_help();

	return UTOOL_ERR_CMD_NOT_FOUND;
}
