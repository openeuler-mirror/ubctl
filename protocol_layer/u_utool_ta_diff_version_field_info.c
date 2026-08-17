// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_ta_diff_version_field_info.h"

static struct utool_field_info g_utool_ta_A1_pkt_52nd_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_2, "mb_cmd_inpipe_num" },
};

static struct utool_field_info g_utool_ta_A1_pkt_78th_field_info[] = {
	{ false, true, UTOOL_LOC25, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC24, 0, UTOOL_CAP_2, "cache_rfr_wl" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC15, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "cache_rfr_wl_en" },
};

static struct utool_field_info g_utool_ta_A1_pkt_79th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_2, "cache_srh_bp_wl_0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "cache_srh_wl_0" },
};

static struct utool_field_info g_utool_ta_A1_pkt_80th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_2, "cache_srh_bp_wl_1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "cache_srh_wl_1" },
};

static struct utool_field_info g_utool_ta_A1_pkt_81st_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_2, "cache_srh_bp_wl_2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "cache_srh_wl_2" },
};

static struct utool_field_info g_utool_ta_A1_pkt_82nd_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_2, "cache_srh_bp_wl_3" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "cache_srh_wl_3" },
};

static struct utool_field_info g_utool_ta_A1_pkt_83rd_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_2, "cache_srh_bp_wl_4" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "cache_srh_wl_4" },
};

static struct utool_field_info g_utool_ta_A1_pkt_84th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_2, "cache_srh_bp_wl_5" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "cache_srh_wl_5" },
};

static struct utool_field_info g_utool_ta_A1_pkt_85th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_2, "cache_srh_bp_wl_6" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "cache_srh_wl_6" },
};

static struct utool_field_info g_utool_ta_A1_pkt_86th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_2, "cache_srh_bp_wl_7" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "cache_srh_wl_7" },
};

static struct utool_field_info g_utool_ta_A1_pkt_87th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_2, "cache_srh_bp_wl_8" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "cache_srh_wl_8" },
};

static struct utool_field_info g_utool_ta_A1_pkt_88th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_2, "cache_srh_bp_wl_9" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "cache_srh_wl_9" },
};

static struct utool_field_info g_utool_ta_A1_pkt_89th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_2, "cache_srh_bp_wl_10" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "cache_srh_wl_10" },
};

static struct utool_field_info g_utool_ta_A1_pkt_90th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_2, "cache_srh_bp_wl_11" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "cache_srh_wl_11" },
};

static struct utool_field_info g_utool_ta_A1_pkt_98th_field_info[] = {
	{ false, true, UTOOL_LOC27, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_2, "statis_en" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC25, 0, UTOOL_CAP_2, "func_num_templ" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC17, 0, UTOOL_CAP_2, "jetty_num_templ" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_2, "statis_mode" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_106th_field_info[] = {
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC29, 0, UTOOL_CAP_V23, "rsp_rd_ost_cnt" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC19, 0, UTOOL_CAP_V23, "rwqep_rd_ost_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_V23, "twqep_rd_ost_cnt" },
};

static struct utool_field_info g_utool_ta_A1_pkt_107th_field_info[] = {
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC29, 0, UTOOL_CAP_2, "ctx_rd_ost_cnt" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC19, 0, UTOOL_CAP_2, "ctx_srh_ost_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_2, "wwqep_wr_ost_cnt" },
};

static struct utool_field_info g_utool_ta_A1_pkt_125th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_2, "gcqe_cqe_err_alarm" },
};

static struct utool_field_info g_utool_ta_A1_pkt_126th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_2, "cqe_fifo_empty" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_129th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "cqm_cqe_handshake1" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_130th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "cqm_cqe_handshake2" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_131st_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "cqm_cqe_handshake3" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_132nd_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "cqm_cqe_handshake5" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_133rd_field_info[] = {
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC29, 0, UTOOL_CAP_V23, "tqc_srh_cnt_dfx2" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_134th_field_info[] = {
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC29, 0, UTOOL_CAP_V23, "tqc_srh_ost_dfx0" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_135th_field_info[] = {
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC29, 0, UTOOL_CAP_V23, "tqc_srh_ost_dfx1" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_136th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "src_rdctx_ost_dfx" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_142nd_field_info[] = {
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_V23, "rsp2tqc_3srh_vld" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_V23, "rsp2tqc_2srh_vld" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "rsp2tqc_1srh_vld" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "eip2tqc_srh_vld" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V23, "taack2tqc_srh_vld" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V23, "tp2ta_rqm2tqc_srh_vld" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V23,
	  "tom2tqc_srh_vld(LQC_TA_TQC_SEARCH_VLD_DFX)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V23, "rsp2tqc_0srh_vld" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V23, "tqms2tqc_srh_vld" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "tqep2tqc_srh_vld" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "mrd2tqc_srh_vld" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "tqeb2tqc_srh_vld" },
};

static struct utool_field_info g_utool_ta_A1_pkt_143rd_field_info[] = {
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_2, "tqc2rsp_3srh_rdy" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_2, "tqc2rsp_2srh_rdy" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_2, "tqc2rsp_1srh_rdy" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "tqc2eip_srh_rdy" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "tqc2taack_srh_rdy" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "ta2tp_tqc2rqm_srh_rdy" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_2, "tqc2tom_srh_rdy(LQC_TA_TQC_SEARCH_RDY_DFX)" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_2, "tqc2rsp_0srh_rdy" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_2, "tqc2tqms_srh_rdy" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "tqc2tqep_srh_rdy" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "tqc2mrd_srh_rdy" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "tqc2tqeb_srh_rdy" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_155th_field_info[] = {
	{ false, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "rdwqe_bus_ae_en" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "retry_err_ae_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "length_0_ae_en" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_164th_field_info[] = {
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "wqem_int_src" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_165th_field_info[] = {
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_V23, "rsc_done" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_V23, "rsc_req" },
	{ false, false, UTOOL_LOC29, UTOOL_LOC29, 0, UTOOL_CAP_V23, "ami_brdy" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_V23, "ami_bvld" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC27, 0, UTOOL_CAP_V23, "ami_wrdy" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_V23, "ami_wvld" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_V23, "ami_rrdy" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_V23, "ami_rvld" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_V23, "ami_req_rdy" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_V23, "ami_req_vld" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_V23, "ctx_rd_rdy" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_V23, "ctx_rd_vld" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_V23, "ctx_srh_rdy" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_V23, "ctx_srh_vld" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_V23, "rwqep_clr_req_rdy" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_V23, "rwqep_clr_req_vld" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_V23, "twqep_clr_req_rdy" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_V23, "twqep_clr_req_vld" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_V23, "wwqep_wr_req_rdy" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_V23, "wwqep_wr_req_vld" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_V23, "rsp_rd_resp_rdy" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_V23, "rsp_rd_resp_vld" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "rsp_rd_req_rdy" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "rsp_rd_req_vld" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V23, "rwqep_rd_resp_rdy" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V23, "rwqep_rd_resp_vld" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V23, "rwqep_rd_req_rdy" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V23, "rwqep_rd_req_vld" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V23, "twqep_rd_resp_rdy" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "twqep_rd_resp_vld" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "twqep_rd_req_rdy" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "twqep_rd_req_vld" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_166th_field_info[] = {
	{ false, true, UTOOL_LOC5, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC4, 0, UTOOL_CAP_V23, "dfx_tqep_retry_crd" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_216th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "cqm_cqe_handshake4" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_217th_field_info[] = {
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC29, 0, UTOOL_CAP_V23, "tqc_srh_ost_dfx2" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_228th_field_info[] = {
	{ false, true, UTOOL_LOC26, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC25, 0, UTOOL_CAP_V23, "rsqe_ost_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_V23, "rctx_ost_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "jfs_srh2rsqe_cnt" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_248th_field_info[] = {
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC29, 0, UTOOL_CAP_V23, "lock_buf_rsp_rd_ost_cnt" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC19, 0, UTOOL_CAP_V23, "lock_buf_rwqep_rd_ost_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_V23, "lock_buf_twqep_rd_ost_cnt" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_250th_field_info[] = {
	{ false, true, UTOOL_LOC23, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC22, 0, UTOOL_CAP_V23, "rx_cqm_ae_type" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_V23, "rx_cqm_ae_jtnum" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_251st_field_info[] = {
	{ false, true, UTOOL_LOC23, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC22, 0, UTOOL_CAP_V23, "tx_cqm_ae_type" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_V23, "tx_cqm_ae_jtnum" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_302nd_field_info[] = {
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "gcqe_cqereq_num_cnt_4" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "gcqe_cqereq_num_cnt_3" },
};

static struct utool_field_info g_utool_ta_A1_K1_pkt_303rd_field_info[] = {
	{ false, true, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC30, 0, UTOOL_CAP_V23, "tx_ccu_other_wr_ost_cnt" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC25, 0, UTOOL_CAP_V23, "tx_ccu_local_wr_ost_cnt" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC19, 0, UTOOL_CAP_V23, "tx_gcqe_wr_ost_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_V23, "rx_gcqe_wr_ost_cnt" },
};

static struct utool_field_info g_utool_ta_A1_K1_abn_1st_field_info[] = {
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC27, 0, UTOOL_CAP_V23, "wmtp_ram_fifo_full" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_V23, "wmtp_ram_fifo_empty" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_V23, "wm_ram_fifo_full" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_V23, "wm_ram_fifo_empty" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_V23, "ro_ram_fifo_full" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_V23, "ro_ram_fifo_empty" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_V23, "we_ram_fifo_full" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_V23, "we_ram_fifo_empty" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_V23, "rcr_op_grant" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_V23, "rcr_type_fifo_2_afull" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_V23, "rcr_type_fifo_2_empty" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_V23, "rcr_type_fifo_1_afull" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_V23, "rcr_type_fifo_1_empty" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_V23, "rcr_type_fifo_0_afull" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_V23, "rcr_type_fifo_0_empty" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "ro_rd_id_fifo_afull" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "ro_rd_id_fifo_empty" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC7, 0, UTOOL_CAP_V23, "cqersp_array_afull" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC5, 0, UTOOL_CAP_V23, "cqersp_array_empty" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC3, 0, UTOOL_CAP_V23, "taack_proc_array_afull" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_V23, "taack_proc_array_empty" },
};

static struct utool_field_info g_utool_ta_A1_K1_abn_3rd_field_info[] = {
	{ false, true, UTOOL_LOC18, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_V23, "rcr_srhidx_array_afull" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_V23, "rcr_srhidx_array_empty" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_V23, "rfr_comb_all_full" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_V23, "rfr_comb_all_empty" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_V23, "rqm_comb_all_full" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_V23, "rqm_comb_all_empty" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_V23, "tqeb_comb_all_full" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_V23, "tqeb_comb_all_empty" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_V23, "tom_comb_all_full" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "tom_comb_all_empty" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_V23, "cqm_comb_all_full" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V23, "cqm_comb_all_empty" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V23, "rsp_comb_all_full" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V23, "rsp_comb_all_empty" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_V23, "tqep_comb_all_full" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "tqep_comb_all_empty" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "tqms_comb_all_full" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "tqms_comb_all_empty" },
};

static struct utool_field_info g_utool_ta_A1_K1_abn_9th_field_info[] = {
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_V23, "ctx_rdata_err_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_V23, "bus_rd_err_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "bus_wr_err_cnt" },
};

static struct utool_field_info g_utool_ta_A1_abn_11th_field_info[] = {
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_2, "tqms_flush_vld" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_2, "tqms_flush_rdy" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_2, "tqms_sch_vld" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_2, "tqms_sch_rdy" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_2, "tqms_loop_vld" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_2, "tqms_loop_rdy" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_2, "rsp_loop_req" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_2, "rsp_loop_ack" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_2, "tqc_srh_vld" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_2, "tqc_srh_rdy" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_2, "tqc_rd_vld" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_2, "tqc_rd_rdy" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_2, "tqc_wr_vld" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_2, "tqc_wr_rdy" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_2, "tqeb_rd_vld" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "tqeb_rd_rdy" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "tqeb_wqe_vld" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "tqeb_wqe_rdy" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_2, "tqeb_clr_vld" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_2, "tqeb_clr_rdy" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_2, "eip_req" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "eip_ack" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "tom_req" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "tom_ack" },
};

static struct utool_field_info g_utool_ta_A1_K1_abn_13th_field_info[] = {
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "wqe_err_wqe_idx" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC15, 0, UTOOL_CAP_V23, "wqe_err_code" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "wqe_err_vld" },
};

static struct utool_field_info g_utool_ta_A1_K1_abn_22nd_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "cqe_fifo_full" },
};

static struct utool_field_info g_utool_ta_A1_abn_40th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_2, "tx_cqm_normal_cqe_cnt" },
};

static struct utool_field_info g_utool_ta_K1_abn_11th_field_info[] = {
	{ false, true, UTOOL_LOC26, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC25, UTOOL_LOC25, 0, UTOOL_CAP_3, "tp2ta_wqe_rdy" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC24, 0, UTOOL_CAP_3, "tqms_flush_rdy" },
	{ false, false, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_3, "tqms_sch_rdy" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_3, "tqms_loop_rdy" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC21, 0, UTOOL_CAP_3, "rsp_loop_ack" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_3, "tqc_srh_rdy(LQC_TA_TQEP_INTERFACE)" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_3, "tqc_rd_rdy(LQC_TA_TQEP_INTERFACE)" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_3, "tqc_wr_rdy" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_3, "tqeb_rd_rdy" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_3, "tqeb_wqe_rdy" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC15, 0, UTOOL_CAP_3, "tqeb_clr_rdy" },
	{ false, false, UTOOL_LOC14, UTOOL_LOC14, 0, UTOOL_CAP_3, "eip_ack" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC13, 0, UTOOL_CAP_3, "tom_ack" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_3, "tqms_flush_vld" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_3, "ta2tp_wqe_vld" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_3, "tqms_sch_vld" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_3, "tqms_loop_vld" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_3, "rsp_loop_req" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_3, "tqc_srh_vld(LQC_TA_TQEP_INTERFACE)" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_3, "tqc_rd_vld(LQC_TA_TQEP_INTERFACE)" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "tqc_wr_vld" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "tqeb_rd_vld" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "tqeb_wqe_vld" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "tqeb_clr_vld" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "eip_req" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "tom_req" },
};

static struct utool_field_info g_utool_ta_K1_abn_40th_field_info[] = {
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "tx_rsp_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "tx_cqm_normal_cqe_cnt" },
};

static struct utool_field_info g_utool_ta_K1_abn_42nd_field_info[] = {
	{ false, true, UTOOL_LOC21, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC20, 0, UTOOL_CAP_3, "tch_err_type" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_3, "eqm_err_type" },
};

static struct utool_field_info g_utool_ta_K1_pkt_78th_field_info[] = {
	{ false, true, UTOOL_LOC25, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC24, 0, UTOOL_CAP_3, "cache_rfr_wl" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "cache_rfr_wl_en" },
};

static struct utool_field_info g_utool_ta_K1_pkt_79th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_3, "cache_srh_bp_wl_0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_3, "cache_srh_wl_0" },
};

static struct utool_field_info g_utool_ta_K1_pkt_80th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_3, "cache_srh_bp_wl_1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_3, "cache_srh_wl_1" },
};

static struct utool_field_info g_utool_ta_K1_pkt_81st_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_3, "cache_srh_bp_wl_2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_3, "cache_srh_wl_2" },
};

static struct utool_field_info g_utool_ta_K1_pkt_82nd_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_3, "cache_srh_bp_wl_3" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_3, "cache_srh_wl_3" },
};

static struct utool_field_info g_utool_ta_K1_pkt_83rd_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_3, "cache_srh_bp_wl_4" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_3, "cache_srh_wl_4" },
};

static struct utool_field_info g_utool_ta_K1_pkt_84th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_3, "cache_srh_bp_wl_5" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_3, "cache_srh_wl_5" },
};

static struct utool_field_info g_utool_ta_K1_pkt_85th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_3, "cache_srh_bp_wl_6" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_3, "cache_srh_wl_6" },
};

static struct utool_field_info g_utool_ta_K1_pkt_86th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_3, "cache_srh_bp_wl_7" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_3, "cache_srh_wl_7" },
};

static struct utool_field_info g_utool_ta_K1_pkt_87th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_3, "cache_srh_bp_wl_8" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_3, "cache_srh_wl_8" },
};

static struct utool_field_info g_utool_ta_K1_pkt_88th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_3, "cache_srh_bp_wl_9" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_3, "cache_srh_wl_9" },
};

static struct utool_field_info g_utool_ta_K1_pkt_89th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_3, "cache_srh_bp_wl_10" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_3, "cache_srh_wl_10" },
};

static struct utool_field_info g_utool_ta_K1_pkt_90th_field_info[] = {
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC18, 0, UTOOL_CAP_3, "cache_srh_bp_wl_11" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_3, "cache_srh_wl_11" },
};

static struct utool_field_info g_utool_ta_K1_pkt_96th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_3, "mrd_bypass_busy_time_cfg" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "mrd_rd_at_or_wr_send_no_inline_bypass_en_cfg" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "mrd_bypass_en_cfg" },
};

static struct utool_field_info g_utool_ta_K1_pkt_98th_field_info[] = {
	{ false, true, UTOOL_LOC27, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC26, UTOOL_LOC26, 0, UTOOL_CAP_3, "statis_en" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC25, 0, UTOOL_CAP_3, "func_num_templ" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC17, 0, UTOOL_CAP_3, "jetty_num_templ" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_3, "statis_mode" },
};

static struct utool_field_info g_utool_ta_K1_pkt_125th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "gcqe_cqe_err_alarm" },
};

static struct utool_field_info g_utool_ta_K1_pkt_126th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "cqe_fifo_empty" },
};

static struct utool_field_info g_utool_ta_K1_pkt_143rd_field_info[] = {
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_3, "tqc2rsp_3srh_rdy" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_3, "tqc2rsp_2srh_rdy" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_3, "tqc2rsp_1srh_rdy" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_3, "tqc2eip_srh_rdy" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_3, "tqc2taack_srh_rdy" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_3, "ta2tp_tqc2rqm_srh_rdy" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "tqc2tom_srh_rdy" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "tqc2rsp_0srh_rdy" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "tqc2tqms_srh_rdy" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "tqc2tqep_srh_rdy" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "tqc2mrd_srh_rdy" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "tqc2tqeb_srh_rdy" },
};

static struct utool_field_info g_utool_ta_K1_pkt_147th_field_info[] = {
	{ false, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "taack_timeout_rpt_mode2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "taack_timeout_rpt_mode" },
};

static struct utool_field_info g_utool_ta_K1_pkt_215th_field_info[] = {
	{ false, false, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_3, "cqm_flush_done_cqe_cnt" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC27, 0, UTOOL_CAP_3, "cqm_tar_err_cqe_cnt" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC21, 0, UTOOL_CAP_3, "cqm_flush_cqe_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_3, "cqm_err_cqe_cnt" },
};

static struct utool_field_info g_utool_ta_K1_pkt_235th_field_info[] = {
	{ false, true, UTOOL_LOC25, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC24, 0, UTOOL_CAP_3, "qm_crdt_dpl_info_lock_rq" },
};

static struct utool_field_info g_utool_ta_K1_pkt_237th_field_info[] = {
	{ false, true, UTOOL_LOC2, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC1, 0, UTOOL_CAP_3, "q_crdt_sts_grp_id_rq" },
};

static struct utool_field_info g_utool_ta_K1_pkt_246th_field_info[] = {
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_3, "lock_wqe_en" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC30, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC19, 0, UTOOL_CAP_3, "lock_start_jetty" },
};

static struct utool_field_info g_utool_ta_rsv_field_info[] = {
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_diff_version_field_info g_utool_ta_diff_version_field_info[] = {
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC52,
	  g_utool_ta_A1_pkt_52nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_52nd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC78,
	  g_utool_ta_A1_pkt_78th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_78th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC79,
	  g_utool_ta_A1_pkt_79th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_79th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC80,
	  g_utool_ta_A1_pkt_80th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_80th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC81,
	  g_utool_ta_A1_pkt_81st_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_81st_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC82,
	  g_utool_ta_A1_pkt_82nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_82nd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC83,
	  g_utool_ta_A1_pkt_83rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_83rd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC84,
	  g_utool_ta_A1_pkt_84th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_84th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC85,
	  g_utool_ta_A1_pkt_85th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_85th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC86,
	  g_utool_ta_A1_pkt_86th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_86th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC87,
	  g_utool_ta_A1_pkt_87th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_87th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC88,
	  g_utool_ta_A1_pkt_88th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_88th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC89,
	  g_utool_ta_A1_pkt_89th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_89th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC90,
	  g_utool_ta_A1_pkt_90th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_90th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC98,
	  g_utool_ta_A1_pkt_98th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_98th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC106,
	  g_utool_ta_A1_K1_pkt_106th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_106th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC107,
	  g_utool_ta_A1_pkt_107th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_107th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC125,
	  g_utool_ta_A1_pkt_125th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_125th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC126,
	  g_utool_ta_A1_pkt_126th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_126th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC129,
	  g_utool_ta_A1_K1_pkt_129th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_129th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC130,
	  g_utool_ta_A1_K1_pkt_130th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_130th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC131,
	  g_utool_ta_A1_K1_pkt_131st_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_131st_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC132,
	  g_utool_ta_A1_K1_pkt_132nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_132nd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC133,
	  g_utool_ta_A1_K1_pkt_133rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_133rd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC134,
	  g_utool_ta_A1_K1_pkt_134th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_134th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC135,
	  g_utool_ta_A1_K1_pkt_135th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_135th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC136,
	  g_utool_ta_A1_K1_pkt_136th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_136th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC142,
	  g_utool_ta_A1_K1_pkt_142nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_142nd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC143,
	  g_utool_ta_A1_pkt_143rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_pkt_143rd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC155,
	  g_utool_ta_A1_K1_pkt_155th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_155th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC164,
	  g_utool_ta_A1_K1_pkt_164th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_164th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC165,
	  g_utool_ta_A1_K1_pkt_165th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_165th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC166,
	  g_utool_ta_A1_K1_pkt_166th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_166th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC216,
	  g_utool_ta_A1_K1_pkt_216th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_216th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC217,
	  g_utool_ta_A1_K1_pkt_217th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_217th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC228,
	  g_utool_ta_A1_K1_pkt_228th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_228th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC248,
	  g_utool_ta_A1_K1_pkt_248th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_248th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC250,
	  g_utool_ta_A1_K1_pkt_250th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_250th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC251,
	  g_utool_ta_A1_K1_pkt_251st_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_251st_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC302,
	  g_utool_ta_A1_K1_pkt_302nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_302nd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC303,
	  g_utool_ta_A1_K1_pkt_303rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_303rd_field_info) },

	{ "ta-abn_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC1,
	  g_utool_ta_A1_K1_abn_1st_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_abn_1st_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC3,
	  g_utool_ta_A1_K1_abn_3rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_abn_3rd_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC4,
	  g_utool_ta_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_rsv_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC9,
	  g_utool_ta_A1_K1_abn_9th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_abn_9th_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC11,
	  g_utool_ta_A1_abn_11th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_abn_11th_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC13,
	  g_utool_ta_A1_K1_abn_13th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_abn_13th_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC22,
	  g_utool_ta_A1_K1_abn_22nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_abn_22nd_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC40,
	  g_utool_ta_A1_abn_40th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_abn_40th_field_info) },

	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC78,
	  g_utool_ta_K1_pkt_78th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_78th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC79,
	  g_utool_ta_K1_pkt_79th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_79th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC80,
	  g_utool_ta_K1_pkt_80th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_80th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC81,
	  g_utool_ta_K1_pkt_81st_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_81st_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC82,
	  g_utool_ta_K1_pkt_82nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_82nd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC83,
	  g_utool_ta_K1_pkt_83rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_83rd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC84,
	  g_utool_ta_K1_pkt_84th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_84th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC85,
	  g_utool_ta_K1_pkt_85th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_85th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC86,
	  g_utool_ta_K1_pkt_86th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_86th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC87,
	  g_utool_ta_K1_pkt_87th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_87th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC88,
	  g_utool_ta_K1_pkt_88th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_88th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC89,
	  g_utool_ta_K1_pkt_89th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_89th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC90,
	  g_utool_ta_K1_pkt_90th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_90th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC96,
	  g_utool_ta_K1_pkt_96th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_96th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC98,
	  g_utool_ta_K1_pkt_98th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_98th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC106,
	  g_utool_ta_A1_K1_pkt_106th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_106th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC125,
	  g_utool_ta_K1_pkt_125th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_125th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC126,
	  g_utool_ta_K1_pkt_126th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_126th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC129,
	  g_utool_ta_A1_K1_pkt_129th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_129th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC130,
	  g_utool_ta_A1_K1_pkt_130th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_130th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC131,
	  g_utool_ta_A1_K1_pkt_131st_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_131st_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC132,
	  g_utool_ta_A1_K1_pkt_132nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_132nd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC133,
	  g_utool_ta_A1_K1_pkt_133rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_133rd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC134,
	  g_utool_ta_A1_K1_pkt_134th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_134th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC135,
	  g_utool_ta_A1_K1_pkt_135th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_135th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC136,
	  g_utool_ta_A1_K1_pkt_136th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_136th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC142,
	  g_utool_ta_A1_K1_pkt_142nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_142nd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC143,
	  g_utool_ta_K1_pkt_143rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_143rd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC147,
	  g_utool_ta_K1_pkt_147th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_147th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC155,
	  g_utool_ta_A1_K1_pkt_155th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_155th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC164,
	  g_utool_ta_A1_K1_pkt_164th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_164th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC165,
	  g_utool_ta_A1_K1_pkt_165th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_165th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC166,
	  g_utool_ta_A1_K1_pkt_166th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_166th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC215,
	  g_utool_ta_K1_pkt_215th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_215th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC216,
	  g_utool_ta_A1_K1_pkt_216th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_216th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC217,
	  g_utool_ta_A1_K1_pkt_217th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_217th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC228,
	  g_utool_ta_A1_K1_pkt_228th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_228th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC235,
	  g_utool_ta_K1_pkt_235th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_235th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC237,
	  g_utool_ta_K1_pkt_237th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_237th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC246,
	  g_utool_ta_K1_pkt_246th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_pkt_246th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC248,
	  g_utool_ta_A1_K1_pkt_248th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_248th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC250,
	  g_utool_ta_A1_K1_pkt_250th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_250th_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC251,
	  g_utool_ta_A1_K1_pkt_251st_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_251st_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC302,
	  g_utool_ta_A1_K1_pkt_302nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_302nd_field_info) },
	{ "ta-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC303,
	  g_utool_ta_A1_K1_pkt_303rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_pkt_303rd_field_info) },

	{ "ta-abn_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC1,
	  g_utool_ta_A1_K1_abn_1st_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_abn_1st_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC3,
	  g_utool_ta_A1_K1_abn_3rd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_abn_3rd_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC4,
	  g_utool_ta_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_rsv_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC9,
	  g_utool_ta_A1_K1_abn_9th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_abn_9th_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC11,
	  g_utool_ta_K1_abn_11th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_abn_11th_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC13,
	  g_utool_ta_A1_K1_abn_13th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_abn_13th_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC22,
	  g_utool_ta_A1_K1_abn_22nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_A1_K1_abn_22nd_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC40,
	  g_utool_ta_K1_abn_40th_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_abn_40th_field_info) },
	{ "ta-abn_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC42,
	  g_utool_ta_K1_abn_42nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ta_K1_abn_42nd_field_info) },
};

struct utool_field_info *utool_ta_cmd_diff_ver_dispatch(const char *module_func_name,
							uint32_t reg_version, uint32_t reg_info_index,
							uint32_t *replace_field_cnt)
{
	uint32_t i;

	if (module_func_name == NULL || module_func_name[0] == '\0') {
		utool_err_msg("Module func name is invalid.\n");
		return NULL;
	}

	for (i = 0; i < UTOOL_ARRAY_SIZE(g_utool_ta_diff_version_field_info); i++) {
		if (strcmp(module_func_name, g_utool_ta_diff_version_field_info[i].module_func_name) != 0) {
			continue;
		}

		if (reg_version != g_utool_ta_diff_version_field_info[i].reg_version) {
			continue;
		}

		if (reg_info_index == g_utool_ta_diff_version_field_info[i].reg_info_index) {
			*replace_field_cnt = g_utool_ta_diff_version_field_info[i].replace_field_cnt;
			return g_utool_ta_diff_version_field_info[i].replace_field_info;
		}
	}

	return NULL;
}
