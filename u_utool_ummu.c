// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_ummu.h"

#define UMMU_FUNC_REG_COUNT 4U

#define UMMU_SYNC_QUERY "ummu_sync_query"
#define UMMU_SYNC_CONFIG "ummu_sync_config"

static struct utool_field_info g_utool_ummu_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "KCMD:\n\tdfx_kcmd_status" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_kcmd_err_status" },

	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "CMD_CTRL:\n\tdfx_snp_err_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_4" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_5" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_6" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_7" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_8" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_9" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_10" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_11" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_12" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_13" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_14" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_entry_status_15" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_snp_status" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_ctrl_status1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cmd_ctrl_status2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tsync_timeout_info" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdvm_req_receive_cnt" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdvm_req_send_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_dvm_receive_info0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_dvm_receive_info1" },

	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "UCMD:\n\tcache_rd_bresp_err_qid" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tcache_wr_bresp_err_qid" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tcplq_wr_bresp_err_qid" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tuieq_wr_bresp_err_qid" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tarb_q_vld_0" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tarb_q_del_cur_sts_0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tarb_q_id_0" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tarb_q_vld_1" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tarb_q_del_cur_sts_1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tarb_q_id_1" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tarb_q_vld_2" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tarb_q_del_cur_sts_2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tarb_q_id_2" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tarb_q_vld_3" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tarb_q_del_cur_sts_3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tarb_q_id_3" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tarb_q_vld_4" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tarb_q_del_cur_sts_4" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tarb_q_id_4" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tarb_q_vld_5" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tarb_q_del_cur_sts_5" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tarb_q_id_5" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tarb_q_vld_6" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tarb_q_del_cur_sts_6" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tarb_q_id_6" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tlink_table_len" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "\tcur_state" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tlink_table_head_qid" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tlink_table_tail_qid" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC17, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tcfg_wr_state" },
	{ false, false, UTOOL_REG_LOC7, UTOOL_REG_LOC16, UTOOL_FIELD_INDEX_START, "\tmax_use_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC6, UTOOL_FIELD_INDEX_START, "\tmax_clr_cnt" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tlqc_cache_ro" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tlqc_cache_rc" },
	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "\tucmd_indirect_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tucmd_indirect_data" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "\trst_srh_alarm" },
	{ false, true, UTOOL_REG_LOC2, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "\tempty_rd" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "\tfull_wr" },

	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "EVENT:\n\tdfx_nonstall_drop_cnt" },
	{ false, true, UTOOL_REG_LOC2, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "\tevent_que_int_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "\tglb_err_int_en" },
	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "\tpmcg_ovf_int_en" },
	{ false, true, UTOOL_REG_LOC2, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "\tubif_usi_mask" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "\tuieq_usi_mask" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC15, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\ttect_mode_sel" },
	{ false, false, UTOOL_REG_LOC14, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "\tprivate_tlb" },
	{ false, false, UTOOL_REG_LOC13, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "\tbad_dsteid_record" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\te2h" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "\ttable_sh_t" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "\ttable_oc_t" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\ttable_ic_t" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "\tqueue_sh_t" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "\tqueue_oc_t" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "\tqueue_ic_t" },
	{ false, true, UTOOL_REG_LOC2, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "\teid_matt_bypass_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "\ttid_matt_bypass_en" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\ttect_fmt" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "\ttect_split" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "\ttect_log2size" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tav" },
	{ false, false, UTOOL_REG_LOC30, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "\tv" },
	{ false, false, UTOOL_REG_LOC29, UTOOL_REG_LOC29, UTOOL_FIELD_INDEX_START, "\tue" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC28, UTOOL_FIELD_INDEX_START, "\ter" },
	{ false, false, UTOOL_REG_LOC27, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "\tof" },
	{ false, false, UTOOL_REG_LOC26, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "\tmv" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC25, UTOOL_FIELD_INDEX_START, "\tce" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tde" },
	{ false, false, UTOOL_REG_LOC22, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "\tpn" },
	{ false, false, UTOOL_REG_LOC20, UTOOL_REG_LOC21, UTOOL_FIELD_INDEX_START, "\tuet" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tierr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tserr" },
	{ false, true, UTOOL_REG_LOC12, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "\tfaultcode" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START, "\treason" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "\tfault" },
	{ false, false, UTOOL_REG_LOC30, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tfpas" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC29, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tevent_que_ovflg" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tevent_que_wr_wrap" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tevent_que_wr_idx" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tevent_que_ovflg_resp" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tevent_que_rd_wrap" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tevent_que_rd_idx" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "UBIF:\n\tubif_dfx0" },
	{ false, true, UTOOL_REG_LOC3, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START, "\tubif_fault_rsp_buf_full_write" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "\tubif_fault_rsp_buf_empty_read" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "\tubif_fault_rsp_buf_wr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tubif_dsteid_dfx" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tubif_sync_dfx" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tubif_kv_cache_ns_nse_mismatch_tect_tag" },
	{ false, true, UTOOL_REG_LOC5, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC4, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START,
	  "\tubif_kv_cache_ns_nse_mismatch_tect_tag_nse" },
	{ false, false, UTOOL_REG_LOC3, UTOOL_REG_LOC3, UTOOL_FIELD_INDEX_START,
	  "\tubif_kv_cache_ns_nse_mismatch_tect_tag_ns" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC2, UTOOL_FIELD_INDEX_START,
	  "\tubif_kv_cache_ns_nse_mismatch_dsteid_nse" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START,
	  "\tubif_kv_cache_ns_nse_mismatch_dsteid_ns" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START,
	  "\tubif_kv_cache_ns_nse_mismatch_vld" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tubif_kv_cache_ns_nse_mismatch_dsteid0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tubif_kv_cache_ns_nse_mismatch_dsteid1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tubif_kv_cache_ns_nse_mismatch_dsteid2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tubif_kv_cache_ns_nse_mismatch_dsteid3" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "TBU:\n\tdfx_tbu_tlb_lkup_proc" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tlb_tbu_stat" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tdfx_tlb_fault_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_plb_lkup_proc" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_plb_tbu_stat" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tdfx_plb_fault_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_invld_mg_info" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_state" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_perm_err_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tummu_tbu_dfx0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tummu_tbu_dfx1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[0][0]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[0][1]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[0][2]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[0][3]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[0][4]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[0][5]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[0][6]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[0][7]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[0][8]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[0][9]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[0][10]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[0][11]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[0][12]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[0][13]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[0][14]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[0][15]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[1][0]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[1][1]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[1][2]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[1][3]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[1][4]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[1][5]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[1][6]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[1][7]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[1][8]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[1][9]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[1][10]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[1][11]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[1][12]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[1][13]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[1][14]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[1][15]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[2][0]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[2][1]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[2][2]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[2][3]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[2][4]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[2][5]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[2][6]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[2][7]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[2][8]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[2][9]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[2][10]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[2][11]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[2][12]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[2][13]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[2][14]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[2][15]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[3][0]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[3][1]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[3][2]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[3][3]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[3][4]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[3][5]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[3][6]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[3][7]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[3][8]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[3][9]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[3][10]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[3][11]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[3][12]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[3][13]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[3][14]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[3][15]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[4][0]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[4][1]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[4][2]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[4][3]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[4][4]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[4][5]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[4][6]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[4][7]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[4][8]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[4][9]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[4][10]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[4][11]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[4][12]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[4][13]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[4][14]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[4][15]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[5][0]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[5][1]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[5][2]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[5][3]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[5][4]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[5][5]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[5][6]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[5][7]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[5][8]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[5][9]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[5][10]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[5][11]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[5][12]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[5][13]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[5][14]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[5][15]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[6][0]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[6][1]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[6][2]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[6][3]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[6][4]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[6][5]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[6][6]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[6][7]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[6][8]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[6][9]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[6][10]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[6][11]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[6][12]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[6][13]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[6][14]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[6][15]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[7][0]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[7][1]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[7][2]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[7][3]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[7][4]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[7][5]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[7][6]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[7][7]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[7][8]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_tbu_rab_entry_info_0_[7][9]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[7][10]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[7][11]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[7][12]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[7][13]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[7][14]" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "\tdfx_tbu_rab_entry_info_0_[7][15]" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "TCU:\n\tdfx_ptw_queue_probe_stat_0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_4" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_5" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_6" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_7" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_8" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_9" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_10" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_11" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_12" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_13" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_14" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_15" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_16" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_17" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_18" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_19" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_20" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_21" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_22" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_23" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_24" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_25" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_26" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_27" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_28" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_29" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_30" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_31" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_32" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_33" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_34" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_35" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_36" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_37" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_38" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_39" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_40" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_41" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_42" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_43" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_44" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_45" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_46" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_ptw_queue_probe_stat_47" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_4" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_5" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_6" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_7" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_8" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_9" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_10" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_11" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_12" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_13" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_14" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_15" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_16" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_17" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_18" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_19" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_20" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_21" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_22" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_23" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_24" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_25" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_26" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_27" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_28" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_29" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_30" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_31" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_32" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_33" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_34" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_35" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_36" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_37" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_38" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_pptw_queue_probe_stat_39" },

	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "CFG:\n\tl2_plb_ecc_err_cnt" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tl2_tlb_ecc_err_cnt" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tkcmd_s_ecc_err_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tkcmd_ns_ecc_err_cnt" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tubif_table_p_ecc_err_cnt" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tubif_table_a_ecc_err_cnt" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "\tubif_ue_idx_ecc_err_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tcontext_ecc_err_cnt" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_cfgbus_status" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START,
	  "GPC:\n\tdfx_gpc_queue_probe_stat_0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_4" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_5" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_6" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_7" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_8" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_9" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_10" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_11" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_12" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_13" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_14" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tdfx_gpc_queue_probe_stat_15" },

	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START,
	  "SKY:\n\tdfx_sky_queue_empty_full_sp_0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_0" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_1" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_2" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_3" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_4" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_4" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_5" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_5" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_6" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_6" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_7" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_7" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_8" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_8" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_9" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_9" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_10" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_10" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_11" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_11" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_12" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_12" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_13" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_13" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_14" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_14" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_15" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_15" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_16" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_16" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_17" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_17" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_18" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_18" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_19" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_19" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_20" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_20" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_21" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_21" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_22" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_22" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_23" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_23" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_24" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_24" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_25" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_25" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_26" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_26" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_27" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_27" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_28" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_28" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_29" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_29" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_30" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_30" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_31" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_31" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_32" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_32" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_33" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_33" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_34" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_34" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_35" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_35" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_36" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_36" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_37" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_37" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_38" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_38" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_39" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_39" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_40" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_40" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_41" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_41" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_42" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_42" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_43" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_43" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_44" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_44" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_45" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_45" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_46" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_46" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_47" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_47" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_48" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_48" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_49" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_49" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_50" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_50" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_51" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_51" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_52" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_52" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_53" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_53" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_54" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_54" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_55" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_55" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_56" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_56" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_57" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_57" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_58" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_58" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_59" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_59" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_60" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_60" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_61" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_61" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_62" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_62" },
	{ false, true, UTOOL_REG_LOC13, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC12, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_empty_full_sp_63" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "\tdfx_sky_queue_valud_num_sp_63" },

	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "MCMD:\n\tmcmd_que_en_0" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_ack_0" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_wrap_0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_idx_0" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_1" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_ack_1" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_wrap_1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_idx_1" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_2" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_ack_2" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_wrap_2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_idx_2" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_3" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_ack_3" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_wrap_3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_idx_3" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_4" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_ack_4" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_wrap_4" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_idx_4" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_5" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_ack_5" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_wrap_5" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_idx_5" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_6" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_ack_6" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_wrap_6" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_idx_6" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_7" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_ack_7" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_wrap_7" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_wr_idx_7" },

	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_resp_0" },
	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_reason_0" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_0" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_wrap_0" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_idx_0" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_resp_1" },
	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_reason_1" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_1" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_wrap_1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_idx_1" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_resp_2" },
	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_reason_2" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_2" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_wrap_2" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_idx_2" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_resp_3" },
	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_reason_3" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_3" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_wrap_3" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_idx_3" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_resp_4" },
	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_reason_4" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_4" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_wrap_4" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_idx_4" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_resp_5" },
	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_reason_5" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_5" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_wrap_5" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_idx_5" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_resp_6" },
	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_reason_6" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_6" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_wrap_6" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_idx_6" },
	{ false, false, UTOOL_REG_LOC31, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "\tmcmd_que_en_resp_7" },
	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC30, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_reason_7" },
	{ false, false, UTOOL_REG_LOC23, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "\tmcmd_que_err_7" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC22, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC19, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_wrap_7" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "\tmcmd_que_rd_idx_7" },

	{ false, true, UTOOL_REG_LOC6, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "UMMU_EN:\n\tmapt_en" },
	{ false, false, UTOOL_REG_LOC2, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "\tvmid_wildcard_t" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC1, UTOOL_FIELD_INDEX_START, "\teventq_en" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "\tummu_en" },

	{ false, true, UTOOL_REG_LOC1, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "OTHER:\n\tsync_timeout_open" },
};

static int utool_ummu_func_query_config_parse_rpc_pkt(struct fwctl_rpc_ub_out *ummu_out)
{
	uint32_t *data = NULL;

	if (ummu_out == NULL) {
		utool_err_msg("Param is invalid, ummu out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	data = (uint32_t *)(ummu_out->data);
	utool_info_msg("Ubctl query or config register(sync_timeout_open) succeeded, value = %u.\n", *data);

	return UTOOL_OK;
}

static void utool_ummu_print_help(void)
{
	utool_err_msg("The ubctl ummu command must be in the following formats:\n"
		      "ubctl -m ummu -u ummu_id\n"
		      "ubctl -m ummu -u ummu_id -f ummu_sync_query\n"
		      "ubctl -m ummu -u ummu_id -f ummu_sync_config -e ${value}\n");
}

static int utool_ummu_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			       struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_BUTT, 0, NULL };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;
	uint32_t i;

	if ((strcmp(param->func, UMMU_SYNC_CONFIG) == 0) && (param->value > 1)) {
		utool_err_msg("Ummu config value is invalid, must be 0 or 1.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < func_cnt; i++) {
		if (strcmp(param->func, func_table[i].func) == 0) {
			func_pkt_exec.rpc_cmd = func_table[i].rpc_cmd;
			func_pkt_exec.execute = func_table[i].execute;
			func_pkt_exec.data_len = func_table[i].data_len;

			if (func_table[i].create_pkt_in == NULL) {
				utool_err_msg("Create pkt in function is NULL.\n");
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
	utool_ummu_print_help();

	return UTOOL_ERR_FUNC_NOT_FOUND;
}

int utool_ummu_parse_rpc_pkt(struct fwctl_rpc_ub_out *ummu_out)
{
	int ret = UTOOL_OK;

	if (ummu_out == NULL) {
		utool_err_msg("Param is invalid, ummu out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_pkt_parse(ummu_out, UTOOL_ARRAY_SIZE(g_utool_ummu_field_info),
			      g_utool_ummu_field_info, UTOOL_MODULE_UMMU);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ummu register data.\n");
	}

	return ret;
}

static int utool_ummu_cal_data_len(uint32_t *data_len)
{
	uint32_t reg_cnt = 0;
	int ret = UTOOL_OK;

	ret = utool_cal_reg_cnt(g_utool_ummu_field_info, UTOOL_ARRAY_SIZE(g_utool_ummu_field_info), &reg_cnt);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate ummu reg cnt.\n");
		return ret;
	}

	*data_len = reg_cnt * sizeof(uint32_t);
	return UTOOL_OK;
}

static int utool_ummu_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
			  struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_UMMU_ALL, 0, NULL };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	func_pkt_exec.execute = utool_ummu_parse_rpc_pkt;

	ret = utool_ummu_cal_data_len(&func_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Ummu cmd failed to calculate ummu reg cnt, ret = %d.\n", ret);
		return ret;
	}

	pkt_in = utool_ummu_value_create_pkt_in(&pkt_in_len, param);
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

int utool_ummu_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	static struct utool_func_dispatch utool_ummu_flag_mufe_table[] = {
		{ false, UMMU_SYNC_CONFIG, UTOOL_CMD_CONFIG_UMMU_SYNC, UMMU_FUNC_REG_COUNT,
		  utool_ummu_func_query_config_parse_rpc_pkt, utool_ummu_value_create_pkt_in },
	};
	static struct utool_func_dispatch utool_ummu_flag_muf_table[] = {
		{ false, UMMU_SYNC_QUERY, UTOOL_CMD_QUERY_UMMU_SYNC, UMMU_FUNC_REG_COUNT,
		  utool_ummu_func_query_config_parse_rpc_pkt, utool_ummu_value_create_pkt_in },
	};
	struct utool_cmd_dispatch utool_ummu_cmd_table[] = {
		{
			UTOOL_FLAG_M | UTOOL_FLAG_U | UTOOL_FLAG_F | UTOOL_FLAG_E,
			utool_ummu_cmd_func, utool_ummu_flag_mufe_table, UTOOL_ARRAY_SIZE(utool_ummu_flag_mufe_table)
		}, {
			UTOOL_FLAG_M | UTOOL_FLAG_U | UTOOL_FLAG_F,
			utool_ummu_cmd_func, utool_ummu_flag_muf_table, UTOOL_ARRAY_SIZE(utool_ummu_flag_muf_table)
		}, {
			UTOOL_FLAG_M | UTOOL_FLAG_U, utool_ummu_cmd, NULL, 0
		}
	};
	uint32_t ummu_cmd_cnt = UTOOL_ARRAY_SIZE(utool_ummu_cmd_table);
	uint32_t i;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < ummu_cmd_cnt; i++) {
		if (param->flags == utool_ummu_cmd_table[i].flags) {
			if (utool_ummu_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch. Callback is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

			return utool_ummu_cmd_table[i].execute(dev, param,
							       utool_ummu_cmd_table[i].func_table,
							       utool_ummu_cmd_table[i].func_cnt);
		}
	}

	utool_ummu_print_help();

	return UTOOL_ERR_CMD_NOT_FOUND;
}
