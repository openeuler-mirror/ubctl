// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_ta.h"

#define TA_PKT_STATS "pkt_stats"

static struct utool_field_info g_utool_ta_pkt_stats_info[] = {
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "eip_sta0" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "eip_sta1" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "eip_sta2" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "eip_sta3" },
	{ true, true, UTOOL_REG_LOC10, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "eip_axi_wr_outstanding" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tp_ae_cnt_i" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cqm_ae_cnt_i" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tqep_ae_cnt_i" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "mrd_ae_cnt_i" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cqm_ce_cnt_i" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cqm_vld_ce_cnt_i" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cqm_ce_ovf_cnt_o" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "eip_db_error_cnt_o" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ace_discard_cnt_o" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ae_overflow_cnt_o" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ae_vld_cnt_o" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "eip_irq_cnt_inc" },

	{ true, true, UTOOL_REG_LOC10, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "mrd_db_addr_err" },
	{ true, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "mrd_db_timeout_err" },
	{ true, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "mrd_mb_cmd_err" },
	{ true, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "mrd_mb_addr_err" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "mrd_mb_resp_err" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_db_timeout_drop_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_mb_issue_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_mb_exec_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_dsqe_issue_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_dsqe_exec_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_dsqe_drop_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_jfsdb_issue_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_jfsdb_exec_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_jfcdb_issue_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_jfcdb_exec_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_eqdb_issue_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_eqdb_exec_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_flr_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_destroy_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_db_cfg_addr_err_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_rw_addr_err_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_mb_cmd_err_cnt" },
	{ true, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "mrd_axi_wr_err_info" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "mrd_axi_rd_err_info" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lqc_ta_mrd_tp_flush_issue_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lqc_ta_mrd_ta_flush_issue_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lqc_ta_mrd_tp_flush_comp_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lqc_ta_mrd_ta_flush_comp_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lqc_ta_mrd_bypass_wqe_exec_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lqc_ta_mrd_dsqe_intr_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lqc_ta_mrd_jfsdb_intr_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lqc_ta_mrd_jfcdb_intr_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lqc_ta_mrd_eqdb_intr_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lqc_ta_mrd_ue0_npa_mb_cmd_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lqc_ta_mrd_db_sec_auth_fail_cnt" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "mrd_dsqe_db_issue_cnt" },
	{ true, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "mrd_mb_buff_full" },
	{ true, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "mrd_mb_buff_empty" },
	{ true, true, UTOOL_REG_LOC2, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "mrd_dynamic_clk_status1" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "mrd_dynamic_clk_status0" },
	{ true, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "mrd_mb_state" },
	{ true, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "mb_cmd_inpipe_num" },
	{ true, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "axi_wr_outstanding_num" },
	{ true, true, UTOOL_REG_LOC4, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "axi_rd_outstanding_num" },

	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "usi_host_int_num_vld_in" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "usi_eip_int_num_vld_in" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "usi_vld_int_num_out_w" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "usi_vld_int_num_out_req" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "usi_eip_int_cnt_for_fun_in" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "usi_misc_int_cnt_for_fun_in" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "usi_eip_int_cnt_for_vec_in" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "usi_ccu_int_cnt_for_vec_in" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "usi_host_int_cnt_in" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "usi_host_int_cnt_out" },
	{ true, true, UTOOL_REG_LOC26, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC16, UTOOL_REG_LOC25, UTOOL_FIELD_INDEX_START, "fun_num_cnt" },
	{ true, true, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ true, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "total_num_cnt_en" },
	{ true, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "fun_num_cnt_en" },
	{ true, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "vec_num_cnt_en" },
	{ true, false, UTOOL_REG_LOC0, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "vec_idx_cnt" },

	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "bus_rd_err_type" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "bus_rd_err_function_num" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "bus_rd_err_jetty_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "bus_rd_err_bbidx" },

	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "bus_wr_err_type" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "bus_wr_err_function_num" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "bus_wr_err_jetty_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "bus_wr_err_bbidx" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ctx_rd_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dma_mode_0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dma_mode_1" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_ta_ack_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_rce_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rx_cqe_cnt" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "proc_err_alm" },

	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "taack_abnorm_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "taack_normal_cnt" },

	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "taack_abnorm_tag" },

	{ false, true, UTOOL_REG_LOC5, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "tqc_int_src4" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "tqc_int_src3" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "tqc_int_src2" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "tqc_int_src1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "tqc_int_src0" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tqc_ue_err_bm0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tpwqe_cnt" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cache_rfr_wl_en" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "cache_rfr_wl" },
	{ false, true, UTOOL_REG_LOC23, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cache_srh_wl_0" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cache_srh_bp_wl_0" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cache_srh_wl_1" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cache_srh_bp_wl_1" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cache_srh_wl_2" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cache_srh_bp_wl_2" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cache_srh_wl_3" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cache_srh_bp_wl_3" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cache_srh_wl_4" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cache_srh_bp_wl_4" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cache_srh_wl_5" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cache_srh_bp_wl_5" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cache_srh_wl_6" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cache_srh_bp_wl_6" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cache_srh_wl_7" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cache_srh_bp_wl_7" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cache_srh_wl_8" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cache_srh_bp_wl_8" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cache_srh_wl_9" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cache_srh_bp_wl_9" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cache_srh_wl_10" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cache_srh_bp_wl_10" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cache_srh_wl_11" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "cache_srh_bp_wl_11" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "credit2srh_ost_cnt" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "credit2rd_ost_cnt" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "rce2srh_ost_cnt" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rce2rd_ost_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "wqe_loop_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "conti_loop_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tp_port_handshake_state" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rtqeb_cnt" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "wtqeb_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "mrd_bypass_en_cfg" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "mrd_bypass_busy_time_cfg" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "dfx_bypass_disable" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "statis_mode" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "jetty_num_templ" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC24, UTOOL_FIELD_INDEX_START, "func_num_templ" },
	{ false, false, UTOOL_REG_LOC25, UTOOL_REG_LOC25, UTOOL_FIELD_INDEX_START, "statis_en" },
	{ false, true, UTOOL_REG_LOC26, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ssn_templ" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "taack_normal_cap_mode" },
	{ false, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "taack_abnorm_cap_mode" },
	{ false, true, UTOOL_REG_LOC18, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "taack_normal_tag" },
	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "taack_normal_ssn" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "taack_abnorm_ssn" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "taack_normal_clr" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "taack_abnorm_clr" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "taack_normal_header" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "taack_abnorm_header" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "tqep_rd_ost_cnt" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "cqm_rd_ost_cnt" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC29, UTOOL_FIELD_INDEX_START, "rsp_rd_ost_cnt" },
	{ false, true, UTOOL_REG_LOC30, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "rsp_wr_ost_cnt" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "tqc_srh_ost_cnt" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC29, UTOOL_FIELD_INDEX_START, "tqc_rd_ost_cnt" },
	{ false, true, UTOOL_REG_LOC30, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "bus_rd_ost_cnt" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "bus_wr_ost_cnt" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "tqep_cnt_en" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "reg_tqep_idle" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "reg_tqep_cgc_idle" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "reg_tqep_wqer_idle" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "reg_tqep_sqes_idle" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "reg_tqep_saa_idle" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "reg_tqep_erpt_idle" },
	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "tm_in_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "tm_in_fifo_full" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "tm_in_fifo_empty" },
	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "tm_out_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "tm_out_fifo_full" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "tm_out_fifo_empty" },
	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "wqer_wqe_num_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "wqer_wqe_num_fifo_empty" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "wqer_wqe_num_fifo_full" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "tp_loop_fifo_cnt" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "tp_loop_fifo_empty" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "tp_loop_fifo_full" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cqe_lkp_ctrl_en" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cqm_jfc_pa_min_idx" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cqm_jfc_pa_max_idx" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "gcqe_cqereq_num_cnt_2" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "gcqe_cqereq_num_cnt_1" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cqm_target_normal_cqe_cnt" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "cqm_target_raw_cqe_cnt" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC29, UTOOL_FIELD_INDEX_START, "cqm_target_notify_cqe_cnt" },
	{ false, true, UTOOL_REG_LOC30, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC25, UTOOL_FIELD_INDEX_START, "cqm_cnt_info" },
	{ false, false, UTOOL_REG_LOC26, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "cqm_cnt_mode_en" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC28, UTOOL_FIELD_INDEX_START, "cqm_cnt_cqe_en" },
	{ false, true, UTOOL_REG_LOC29, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cqm_stars_cqe_cnt" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cqm_se_req_cnt" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cqm_inline_wr_cnt" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cqm_inline_rd_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "gcqe_cqe_err_alarm" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "gcqe_wrd_alarm" },
	{ false, true, UTOOL_REG_LOC30, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "cqe_fifo_empty" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cqm_ras_function_id3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cqm_ras_function_id4" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "cqm_cqe_handshake1" },
	{ false, true, UTOOL_REG_LOC11, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "cqm_cqe_handshake2" },
	{ false, true, UTOOL_REG_LOC19, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "cqm_cqe_handshake3" },
	{ false, true, UTOOL_REG_LOC21, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "cqm_cqe_handshake5" },
	{ false, true, UTOOL_REG_LOC12, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tqc_srh_cnt_dfx2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "tqc_srh_ost_dfx0" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "tqc_srh_ost_dfx1" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "src_rdctx_ost_dfx" },
	{ false, true, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "tqc_srhrsp_ost_dfx0" },
	{ false, true, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "mrd_req_err" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "taack_ssn_err" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "taack_rspst_err" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "rcr_rd_ctx_err" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "taack_cache_err" },
	{ false, true, UTOOL_REG_LOC5, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tqc_ue_err_bm1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tqc_ue_err_bm2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tqc_ue_err_bm3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "tqeb2tqc_srh_vld" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "mrd2tqc_srh_vld" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "tqep2tqc_srh_vld" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "tqms2tqc_srh_vld" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "rsp2tqc_0srh_vld" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5,
	  UTOOL_FIELD_INDEX_START, "tom2tqc_srh_vld(LQC_TA_TQC_SEARCH_VLD_DFX)" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "tp2ta_rqm2tqc_srh_vld" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "taack2tqc_srh_vld" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "eip2tqc_srh_vld" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "rsp2tqc_1srh_vld" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "tqc2tqeb_srh_rdy" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "tqc2mrd_srh_rdy" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "tqc2tqep_srh_rdy" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "tqc2tqms_srh_rdy" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "tqc2rsp_0srh_rdy" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START,
	  "tqc2tom_srh_rdy(LQC_TA_TQC_SEARCH_RDY_DFX)" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "ta2tp_tqc2rqm_srh_rdy" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "tqc2taack_srh_rdy" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "tqc2eip_srh_rdy" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "tqc2rsp_1srh_rdy" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "tqep2tqc_rd_vld" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "tqms2tqc_rd_vld" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "rsp2tqc_rd_vld" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "cqm2tqc_rd_vld" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "tqeb2tqc_rd_vld" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "tp2ta_rqm2tqc_rd_vld" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START,
	  "tom2tqc_rd_vld(LQC_TA_TQC_RW_VLD_DFX)" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "tqms2tqc_wr_vld" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "rsp2tqc_wr_vld" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START,
	  "tom2tqc_wr_vld(LQC_TA_TQC_RW_VLD_DFX)" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "tqep2tqc_wr_vld" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "eip2tqc_wr_vld" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "tqc2mrd_mb_rdata_vld" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "mrd2tqc_mb_wdata_vld" },
	{ false, true, UTOOL_REG_LOC14, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "tqc2tqep_rd_rdy" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "tqc2tqms_rd_rdy" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "tqc2rsp_rd_rdy" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "tqc2cqm_rd_rdy" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "tqc2tqeb_rd_rdy" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "ta2tp_tqc2rqm_rd_rdy" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START,
	  "tqc2tom_rd_rdy(LQC_TA_TQC_RW_RDY_DFX)" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "tqc2tqms_wr_rdy" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "tqc2rsp_wr_rdy" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START,
	  "tqc2tom_wr_rdy(LQC_TA_TQC_RW_RDY_DFX)" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "tqc2tqep_wr_rdy" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "tqc2eip_wr_rdy" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "mrd2tqc_mb_rdata_rdy" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "tqc2mrd_mb_wdata_rdy" },
	{ false, true, UTOOL_REG_LOC14, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "tqc_srhrsp_ost_dfx1" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "taack_timeout_rpt_mode" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "db_loop_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "timmer_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "cur_credit_cnt" },
	{ false, true, UTOOL_REG_LOC9, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "retry_func_id" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "retry_jfs_num" },
	{ false, true, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ctx_ci" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ctx_pi" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "retry_ptr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ctx_rty_pi" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "retry_wqe_ssn_num" },
	{ false, true, UTOOL_REG_LOC21, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "length_0_ae_en" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "prefetch_ctx_retry" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "prefetch_ctx_normal_rd" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "prefetch_ctx_normal" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "chain_vld" },
	{ false, false, UTOOL_REG_LOC27, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "ctx_reading_flag" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC28, UTOOL_FIELD_INDEX_START, "tqc_rd_retry_loop_flag" },
	{ false, false, UTOOL_REG_LOC29, UTOOL_REG_LOC29, UTOOL_FIELD_INDEX_START, "retry_conflict_loop_flag" },
	{ false, false, UTOOL_REG_LOC30, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "tqc_rd_retry_taack_inc_err_flag" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tqc_rd_retry_err_flag" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ost_not_enough_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "lock_buf_wr_cnt" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lock_buf_clr_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "lock_buf_clr_miss_jetty_num" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lock_buf_clr_miss" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "lock_buf_clr_miss_wqebb_idx" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lock_buf_clr_miss_func_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "lock_buf_rd_miss_jetty_num" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "lock_buf_rd_miss_req_type" },
	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "lock_buf_rd_miss_msk_dis" },
	{ false, true, UTOOL_REG_LOC23, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lock_buf_rd_miss" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "lock_buf_rd_miss_wqebb_idx" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lock_buf_rd_miss_func_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cnt_en" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "tqeb_int_src" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "tqep_rd_req_vld" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "tqep_rd_req_rdy" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "tqep_rd_resp_vld" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "tqep_rd_resp_rdy" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "cqm_rd_req_vld" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "cqm_rd_req_rdy" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "cqm_rd_resp_vld" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "cqm_rd_resp_rdy" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "rsp_rd_req_vld" },
	{ false, false, UTOOL_REG_LOC9, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "rsp_rd_req_rdy" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "rsp_rd_resp_vld" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "rsp_rd_resp_rdy" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "rsp_wr_req_vld" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "rsp_wr_req_rdy" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tqep_clr_req_vld" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tqep_clr_req_rdy" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "cqm_clr_req_vld" },
	{ false, false, UTOOL_REG_LOC17, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "cqm_clr_req_rdy" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC18,
	 UTOOL_FIELD_INDEX_START, "tqc_srh_vld(LQC_TA_TQEB_HANDSHAKE_STATUS)" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19,
	 UTOOL_FIELD_INDEX_START, "tqc_srh_rdy(LQC_TA_TQEB_HANDSHAKE_STATUS)" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC20,
	 UTOOL_FIELD_INDEX_START, "tqc_rd_vld(LQC_TA_TQEB_HANDSHAKE_STATUS)" },
	{ false, false, UTOOL_REG_LOC21, UTOOL_REG_LOC21,
	 UTOOL_FIELD_INDEX_START, "tqc_rd_rdy(LQC_TA_TQEB_HANDSHAKE_STATUS)" },
	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "ami_req_vld" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "ami_req_rdy" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC24, UTOOL_FIELD_INDEX_START, "ami_rvld" },
	{ false, false, UTOOL_REG_LOC25, UTOOL_REG_LOC25, UTOOL_FIELD_INDEX_START, "ami_rrdy" },
	{ false, false, UTOOL_REG_LOC26, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "ami_wvld" },
	{ false, false, UTOOL_REG_LOC27, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "ami_wrdy" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC28, UTOOL_FIELD_INDEX_START, "ami_bvld" },
	{ false, false, UTOOL_REG_LOC29, UTOOL_REG_LOC29, UTOOL_FIELD_INDEX_START, "ami_brdy" },
	{ false, false, UTOOL_REG_LOC30, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "rsc_req" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rsc_done" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "dfx_tqep_retry_crd" },
	{ false, true, UTOOL_REG_LOC4, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tqms_int_src" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "fun_bitmap(func_bmp_num0)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "fun_bitmap(func_bmp_num1)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "fun_bitmap(func_bmp_num2)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "fun_bitmap(func_bmp_num3)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "sch_fifo_fill" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "bresp_fifo_fill" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "data_ram_addr_fifo_fill" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC25, UTOOL_FIELD_INDEX_START, "aw_fifo_fill" },
	{ false, false, UTOOL_REG_LOC26, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "rd_inf_fifo_fill" },
	{ false, true, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "wr_inf_fifo_fill" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "w_fifo_fill" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "pref_r_data_ram_fifo_fill" },
	{ false, true, UTOOL_REG_LOC17, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "aw_fifo_full" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "w_fifo_full" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "bresp_fifo_full" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "wr_inf_fifo_full" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "rd_inf_fifo_full" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "data_ram_addr_fifo_full" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "r_fifo_full" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "r_fifo_fill" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "pref_r_data_ram_fifo_afull" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "timer_sta_0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "tom_dfx_cnt_en" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "tqep2tom_timer_req" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "tqc2tom_timer_req" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "tom2tqc_srh_vld(LQC_TA_TOM_VLD_DFX)" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "tom2tqc_rd_vld(LQC_TA_TOM_VLD_DFX)" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "tom2tqc_wr_vld(LQC_TA_TOM_VLD_DFX)" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "cqm2tom_timer_req" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "tom2cqm_timeout_req" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "tom2tqms_retry_req" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "tom2timercbb_req" },
	{ false, true, UTOOL_REG_LOC9, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "tom2tqep_timer_ack" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "tom2tqc_timer_ack" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "tqc2tom_srh_rdy(LQC_TA_TOM_REQ_DFX)" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "tqc2tom_rd_rdy(LQC_TA_TOM_REQ_DFX)" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "tqc2tom_wr_rdy(LQC_TA_TOM_REQ_DFX)" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "tom2cqm_timer_ack" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "cqm2tom_timeout_ack" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "tqms2tom_retry_ack" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC8, UTOOL_FIELD_INDEX_START, "tom2timercbb_ack" },
	{ false, true, UTOOL_REG_LOC9, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rtqc_cnt" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "wtqc_cnt" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rsqe_fsm_sta" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tqms_iqm_fifo_empty_sta" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "dfx_tm_crd_ctrl" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_iqm_prv_vld(que_pri_idx0)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_iqm_prv_vld(que_pri_idx1)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_iqm_prv_vld(que_pri_idx2)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_iqm_prv_vld(que_pri_idx3)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_iqm_prv_vld(que_pri_idx4)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_iqm_prv_vld(que_pri_idx5)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_iqm_prv_vld(que_pri_idx6)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_iqm_prv_vld(que_pri_idx7)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tm_crd(que_pri_idx0)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tm_crd(que_pri_idx1)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tm_crd(que_pri_idx2)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tm_crd(que_pri_idx3)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tm_crd(que_pri_idx4)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tm_crd(que_pri_idx5)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tm_crd(que_pri_idx6)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_tm_crd(que_pri_idx7)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_dqm_crd_bkp(que_pri_idx0)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_dqm_crd_bkp(que_pri_idx1)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_dqm_crd_bkp(que_pri_idx2)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_dqm_crd_bkp(que_pri_idx3)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_dqm_crd_bkp(que_pri_idx4)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_dqm_crd_bkp(que_pri_idx5)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_dqm_crd_bkp(que_pri_idx6)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dfx_dqm_crd_bkp(que_pri_idx7)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "dfx_tqms_ddr_fun_err_bmp(func_bmp_num0)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "dfx_tqms_ddr_fun_err_bmp(func_bmp_num1)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "dfx_tqms_ddr_fun_err_bmp(func_bmp_num2)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "dfx_tqms_ddr_fun_err_bmp(func_bmp_num3)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "taack_rsc_rcved" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "cur_jetty_num" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC29, UTOOL_FIELD_INDEX_START, "cur_function_id" },
	{ false, false, UTOOL_REG_LOC30, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "cur_retry_type" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "cur_rc_type" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "flush_db_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rst_db_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "cqm_err_cqe_cnt" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "cqm_flush_cqe_cnt" },
	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "cqm_tar_err_cqe_cnt" },
	{ false, true, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "cqm_cqe_handshake4" },
	{ false, true, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tqc_srh_ost_dfx2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "db_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "wqe_rd_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "wqe_back_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ctx_data_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ctx_wr_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ctx_clr_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rc_queue_head_only_num" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "dbell2loop_cnt" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "module_flr_done" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "module_flr_done_force" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "cqersp_rsc_done" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "jfs_srh2rsqe_cnt" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "rctx_ost_cnt" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "rsqe_ost_cnt" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
};

static struct utool_cal_reg_cnt_dp g_utool_ta_cal_reg_table[] = {
	{ true, true, TA_PKT_STATS, UTOOL_ARRAY_SIZE(g_utool_ta_pkt_stats_info), g_utool_ta_pkt_stats_info },
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

static struct utool_func_dispatch g_utool_ta_func_table[] = {
	{ true, TA_PKT_STATS, UTOOL_CMD_QUERY_TA_PKT_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_ta_parse_pkt_stats, utool_null_create_pkt_in },
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
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m ta -f pkt_stats\n");
}

static int utool_ta_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			     struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_BUTT, 0, NULL };
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
				utool_err_msg("Failed to create ta func pkt in, create pkt in is NULL.\n");
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
