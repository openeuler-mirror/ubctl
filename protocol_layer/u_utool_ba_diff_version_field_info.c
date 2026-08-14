// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_ba_diff_version_field_info.h"

static struct utool_field_info g_utool_ba_A1_K1_pkt_14th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "dfx_ta_tp_dtlb_vld" },
};

static struct utool_field_info g_utool_ba_A1_K1_pkt_15th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "dfx_rxdma_dtlb_vld" },
};

static struct utool_field_info g_utool_ba_A1_K1_pkt_16th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "dfx_txdma_dtlb_vld" },
};

static struct utool_field_info g_utool_ba_A1_K1_pkt_139th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "tx_load_resp_cnt" },
};

static struct utool_field_info g_utool_ba_A1_K1_pkt_140th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "tx_load_resp_send_cnt" },
};

static struct utool_field_info g_utool_ba_A1_K1_pkt_144th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "tx_atomic_resp_cnt" },
};

static struct utool_field_info g_utool_ba_A1_K1_pkt_145th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "tx_atomic_resp_send_cnt" },
};

static struct utool_field_info g_utool_ba_A1_K1_pkt_183rd_field_info[] = {
	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC5, 0, UTOOL_CAP_V23, "ctrl_err_data_wr" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC3, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "ctrl_err_wstrb_all_set" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "ctrl_err_wdata_mode" },
};

static struct utool_field_info g_utool_ba_A1_K1_pkt_185th_field_info[] = {
	{ false, true, UTOOL_LOC27, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC26, 0, UTOOL_CAP_V23, "cfg_uat_dtlb_pend_match_pgsz" },
	{ false, true, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC18, 0, UTOOL_CAP_V23, "cfg_dtlb_pend_match_pgsz" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC11, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "cfg_atp_range_tlbi_disable" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "cfg_atp_tlbi_pgsz_predict_en" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V23, "cfg_atp_tlbi_accurate_math_en" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V23, "cfg_atp_req_entry_rls_mode" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V23, "cfg_atp_apat_tlbi_vav_disable" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V23, "cfg_atp_inv_record_mode" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V23, "cfg_atp_sync_clr_all_stale_entry" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "cfg_atp_sync_clr_all_no_rsp_entry" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "cfg_atp_conf_inv_all_rsp_entry" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "cfg_atp_tlb_inv_all_rsp_entry" },
};

static struct utool_field_info g_utool_ba_A1_pkt_211th_field_info[] = {
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "pkt_align_err(0)" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "pkt_len_err(0)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "hdr_len_err(0)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_2, "rxdma_sof_sof_err(0)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_2, "rxdma_imp_2k_err(0)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_2, "rxdma_opcode_err(0)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "rxdma_pkt_long(0)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "rxdma_fcs_err(0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "rxdma_icrc_err(0)" },
};

static struct utool_field_info g_utool_ba_A1_pkt_212th_field_info[] = {
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "pkt_align_err(1)" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "pkt_len_err(1)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "hdr_len_err(1)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_2, "rxdma_sof_sof_err(1)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_2, "rxdma_imp_2k_err(1)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_2, "rxdma_opcode_err(1)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "rxdma_pkt_long(1)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "rxdma_fcs_err(1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "rxdma_icrc_err(1)" },
};

static struct utool_field_info g_utool_ba_A1_pkt_213th_field_info[] = {
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "pkt_align_err(2)" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "pkt_len_err(2)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "hdr_len_err(2)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_2, "rxdma_sof_sof_err(2)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_2, "rxdma_imp_2k_err(2)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_2, "rxdma_opcode_err(2)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "rxdma_pkt_long(2)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "rxdma_fcs_err(2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "rxdma_icrc_err(2)" },
};

static struct utool_field_info g_utool_ba_A1_pkt_214th_field_info[] = {
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "pkt_align_err(3)" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "pkt_len_err(3)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "hdr_len_err(3)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_2, "rxdma_sof_sof_err(3)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_2, "rxdma_imp_2k_err(3)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_2, "rxdma_opcode_err(3)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "rxdma_pkt_long(3)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "rxdma_fcs_err(3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "rxdma_icrc_err(3)" },
};

static struct utool_field_info g_utool_ba_A1_mar_66th_field_info[] = {
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "todef_rsperr_en" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "todefok_rsperr_en" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_2, "timeout_rsperr_en" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_2, "illegal_access_rsperr_en" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_2, "rsw_size_illegal_rsperr_en" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "auth_fail_rsperr_en" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "timeout_fail_rsperr_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "nor_rsperr_en" },
};

static struct utool_field_info g_utool_ba_A1_mar_71st_field_info[] = {
	{ false, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "order_readreceipt_return_mode" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "readreceipt_return_mode" },
};

static struct utool_field_info g_utool_ba_A1_mar_77th_field_info[] = {
	{ false, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "cfg_mar_entry_bypass_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "mar_cxt_byp_en" },
};

static struct utool_field_info g_utool_ba_K1_pkt_146th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "cpu_seq_dat_only_chn0" },
};

static struct utool_field_info g_utool_ba_K1_pkt_147th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "cpu_seq_dat_only_chn1" },
};

static struct utool_field_info g_utool_ba_K1_pkt_149th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "cpu_seq_dat_chn0" },
};

static struct utool_field_info g_utool_ba_K1_pkt_150th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "cpu_seq_dat_chn1" },
};

static struct utool_field_info g_utool_ba_K1_pkt_153rd_field_info[] = {
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "rx_p2p_cnt1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "rx_p2p_cnt" },
};

static struct utool_field_info g_utool_ba_K1_pkt_154th_field_info[] = {
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "rx_p2p_send_cnt1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "rx_p2p_send_cnt" },
};

static struct utool_field_info g_utool_ba_K1_pkt_155th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "p2p_spec_apl" },
};

static struct utool_field_info g_utool_ba_K1_pkt_157th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "p2p_sec_apl" },
};

static struct utool_field_info g_utool_ba_K1_pkt_159th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "rx_abnormal0" },
};

static struct utool_field_info g_utool_ba_K1_pkt_160th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "rx_abnormal1" },
};

static struct utool_field_info g_utool_ba_K1_pkt_161st_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "rx_abnormal2" },
};

static struct utool_field_info g_utool_ba_K1_pkt_162nd_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "rx_abnormal3" },
};

static struct utool_field_info g_utool_ba_K1_pkt_163rd_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "rx_abnormal4" },
};

static struct utool_field_info g_utool_ba_K1_pkt_164th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "rx_abnormal5" },
};

static struct utool_field_info g_utool_ba_K1_pkt_165th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "rx_abnormal6" },
};

static struct utool_field_info g_utool_ba_K1_pkt_166th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "rx_abnormal7" },
};

static struct utool_field_info g_utool_ba_K1_pkt_167th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "rx_abnormal8" },
};

static struct utool_field_info g_utool_ba_K1_pkt_168th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "tx_abnormal0" },
};

static struct utool_field_info g_utool_ba_K1_pkt_169th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "tx_abnormal1" },
};

static struct utool_field_info g_utool_ba_K1_pkt_170th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "tx_abnormal2" },
};

static struct utool_field_info g_utool_ba_K1_pkt_171st_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "tx_abnormal3" },
};

static struct utool_field_info g_utool_ba_K1_pkt_172nd_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "tx_abnormal4" },
};

static struct utool_field_info g_utool_ba_K1_pkt_173rd_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "tx_abnormal5" },
};

static struct utool_field_info g_utool_ba_K1_pkt_174th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "tx_abnormal6" },
};

static struct utool_field_info g_utool_ba_K1_pkt_175th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "tx_abnormal7" },
};

static struct utool_field_info g_utool_ba_K1_pkt_176th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "tx_abnormal8" },
};

static struct utool_field_info g_utool_ba_K1_pkt_177th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "tx_abnormal9" },
};

static struct utool_field_info g_utool_ba_K1_pkt_178th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "tx_abnormal10" },
};

static struct utool_field_info g_utool_ba_K1_pkt_211th_field_info[] = {
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved(0)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_3, "pkt_align_err_3_0(0)" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_3, "pkt_len_err_3_0(0)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_3, "hdr_len_err_3_0(0)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "rxdma_sof_sof_err_3_0(0)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "rxdma_imp_2k_err_3_0(0)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "rxdma_opcode_err_3_0(0)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "rxdma_pkt_long_3_0(0)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "rxdma_fcs_err_3_0(0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "rxdma_icrc_err_3_0(0)" },
};

static struct utool_field_info g_utool_ba_K1_pkt_212th_field_info[] = {
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved(1)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_3, "pkt_align_err_3_0(1)" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_3, "pkt_len_err_3_0(1)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_3, "hdr_len_err_3_0(1)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "rxdma_sof_sof_err_3_0(1)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "rxdma_imp_2k_err_3_0(1)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "rxdma_opcode_err_3_0(1)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "rxdma_pkt_long_3_0(1)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "rxdma_fcs_err_3_0(1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "rxdma_icrc_err_3_0(1)" },
};

static struct utool_field_info g_utool_ba_K1_pkt_213th_field_info[] = {
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved(2)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_3, "pkt_align_err_3_0(2)" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_3, "pkt_len_err_3_0(2)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_3, "hdr_len_err_3_0(2)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "rxdma_sof_sof_err_3_0(2)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "rxdma_imp_2k_err_3_0(2)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "rxdma_opcode_err_3_0(2)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "rxdma_pkt_long_3_0(2)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "rxdma_fcs_err_3_0(2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "rxdma_icrc_err_3_0(2)" },
};

static struct utool_field_info g_utool_ba_K1_pkt_214th_field_info[] = {
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved(3)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_3, "pkt_align_err_3_0(3)" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_3, "pkt_len_err_3_0(3)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_3, "hdr_len_err_3_0(3)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "rxdma_sof_sof_err_3_0(3)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "rxdma_imp_2k_err_3_0(3)" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "rxdma_opcode_err_3_0(3)" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "rxdma_pkt_long_3_0(3)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "rxdma_fcs_err_3_0(3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "rxdma_icrc_err_3_0(3)" },
};

static struct utool_field_info g_utool_ba_rsv_field_info[] = {
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_diff_version_field_info g_utool_ba_diff_version_field_info[] = {
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC14,
	  g_utool_ba_A1_K1_pkt_14th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_14th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC15,
	  g_utool_ba_A1_K1_pkt_15th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_15th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC16,
	  g_utool_ba_A1_K1_pkt_16th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_16th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC139,
	  g_utool_ba_A1_K1_pkt_139th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_139th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC140,
	  g_utool_ba_A1_K1_pkt_140th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_140th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC144,
	  g_utool_ba_A1_K1_pkt_144th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_144th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC145,
	  g_utool_ba_A1_K1_pkt_145th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_145th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC183,
	  g_utool_ba_A1_K1_pkt_183rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_183rd_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC185,
	  g_utool_ba_A1_K1_pkt_185th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_185th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC211,
	  g_utool_ba_A1_pkt_211th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_pkt_211th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC212,
	  g_utool_ba_A1_pkt_212th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_pkt_212th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC213,
	  g_utool_ba_A1_pkt_213th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_pkt_213th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC214,
	  g_utool_ba_A1_pkt_214th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_pkt_214th_field_info) },

	{ "ba-mar", UTOOL_ENV_VER_A_1, UTOOL_LOC66,
	  g_utool_ba_A1_mar_66th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_mar_66th_field_info) },
	{ "ba-mar", UTOOL_ENV_VER_A_1, UTOOL_LOC71,
	  g_utool_ba_A1_mar_71st_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_mar_71st_field_info) },
	{ "ba-mar", UTOOL_ENV_VER_A_1, UTOOL_LOC77,
	  g_utool_ba_A1_mar_77th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_mar_77th_field_info) },

	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC14,
	  g_utool_ba_A1_K1_pkt_14th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_14th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC15,
	  g_utool_ba_A1_K1_pkt_15th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_15th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC16,
	  g_utool_ba_A1_K1_pkt_16th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_16th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC78,
	  g_utool_ba_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_rsv_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC83,
	  g_utool_ba_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_rsv_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC84,
	  g_utool_ba_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_rsv_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC85,
	  g_utool_ba_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_rsv_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC86,
	  g_utool_ba_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_rsv_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC128,
	  g_utool_ba_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_rsv_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC129,
	  g_utool_ba_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_rsv_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC130,
	  g_utool_ba_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_rsv_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC131,
	  g_utool_ba_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_rsv_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC132,
	  g_utool_ba_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_rsv_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC139,
	  g_utool_ba_A1_K1_pkt_139th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_139th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC140,
	  g_utool_ba_A1_K1_pkt_140th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_140th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC144,
	  g_utool_ba_A1_K1_pkt_144th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_144th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC145,
	  g_utool_ba_A1_K1_pkt_145th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_145th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC146,
	  g_utool_ba_K1_pkt_146th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_146th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC147,
	  g_utool_ba_K1_pkt_147th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_147th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC149,
	  g_utool_ba_K1_pkt_149th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_149th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC150,
	  g_utool_ba_K1_pkt_150th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_150th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC153,
	  g_utool_ba_K1_pkt_153rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_153rd_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC154,
	  g_utool_ba_K1_pkt_154th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_154th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC155,
	  g_utool_ba_K1_pkt_155th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_155th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC157,
	  g_utool_ba_K1_pkt_157th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_157th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC159,
	  g_utool_ba_K1_pkt_159th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_159th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC160,
	  g_utool_ba_K1_pkt_160th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_160th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC161,
	  g_utool_ba_K1_pkt_161st_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_161st_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC162,
	  g_utool_ba_K1_pkt_162nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_162nd_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC163,
	  g_utool_ba_K1_pkt_163rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_163rd_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC164,
	  g_utool_ba_K1_pkt_164th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_164th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC165,
	  g_utool_ba_K1_pkt_165th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_165th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC166,
	  g_utool_ba_K1_pkt_166th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_166th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC167,
	  g_utool_ba_K1_pkt_167th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_167th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC168,
	  g_utool_ba_K1_pkt_168th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_168th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC169,
	  g_utool_ba_K1_pkt_169th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_169th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC170,
	  g_utool_ba_K1_pkt_170th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_170th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC171,
	  g_utool_ba_K1_pkt_171st_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_171st_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC172,
	  g_utool_ba_K1_pkt_172nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_172nd_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC173,
	  g_utool_ba_K1_pkt_173rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_173rd_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC174,
	  g_utool_ba_K1_pkt_174th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_174th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC175,
	  g_utool_ba_K1_pkt_175th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_175th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC176,
	  g_utool_ba_K1_pkt_176th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_176th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC177,
	  g_utool_ba_K1_pkt_177th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_177th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC178,
	  g_utool_ba_K1_pkt_178th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_178th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC183,
	  g_utool_ba_A1_K1_pkt_183rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_183rd_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC185,
	  g_utool_ba_A1_K1_pkt_185th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_A1_K1_pkt_185th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC211,
	  g_utool_ba_K1_pkt_211th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_211th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC212,
	  g_utool_ba_K1_pkt_212th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_212th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC213,
	  g_utool_ba_K1_pkt_213th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_213th_field_info) },
	{ "ba-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC214,
	  g_utool_ba_K1_pkt_214th_field_info, UTOOL_ARRAY_SIZE(g_utool_ba_K1_pkt_214th_field_info) },
};

struct utool_field_info *utool_ba_cmd_diff_ver_dispatch(const char *module_func_name,
							uint32_t reg_version, uint32_t reg_info_index,
							uint32_t *replace_field_cnt)
{
	uint32_t i;

	if (module_func_name == NULL || module_func_name[0] == '\0') {
		utool_err_msg("Module func name is invalid.\n");
		return NULL;
	}

	for (i = 0; i < UTOOL_ARRAY_SIZE(g_utool_ba_diff_version_field_info); i++) {
		if (strcmp(module_func_name, g_utool_ba_diff_version_field_info[i].module_func_name) != 0) {
			continue;
		}

		if (reg_version != g_utool_ba_diff_version_field_info[i].reg_version) {
			continue;
		}

		if (reg_info_index == g_utool_ba_diff_version_field_info[i].reg_info_index) {
			*replace_field_cnt = g_utool_ba_diff_version_field_info[i].replace_field_cnt;
			return g_utool_ba_diff_version_field_info[i].replace_field_info;
		}
	}

	return NULL;
}
