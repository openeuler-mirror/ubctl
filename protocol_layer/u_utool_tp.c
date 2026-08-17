// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_tp_basic_field_info.h"
#include "u_utool_tp_ex_field_info.h"
#include "u_utool_tp.h"

#define TP_PKT_STATS "pkt_stats"
#define TP_ABN_STATS "abn_stats"
#define TP_ROUTE_RESULT "route_result"
#define TP_SCC_VERSION "scc_version"
#define TP_SCC_LOG "scc_log"
#define TP_SCC_DEBUG "scc_debug_en"

#define UTOOL_SCC_LOG_DIR_PATH "/var/log/ubtool/operation_logs/"
#define UTOOL_SCC_LOG_FILE_PATH_MAX_LEN 256U
#define UTOOL_SCC_LOG_NAME_MAX_LEN 128U
#define UTOOL_SZ_1M 0x100000
#define UTOOL_SCC_LOG_CNT UTOOL_SZ_1M
#define UTOOL_SCC_CNT 24U
#define UTOOL_SCC_LOG_FILE_AUTHORITY 0440
#define UTOOL_SCC_LOG_PATH_AUTHORITY 0550
#define UTOOL_START_YEAR 1900

struct utool_type_trans {
	char type_base;
	uint32_t type_size;
};

struct utool_cal_reg_table_dp {
	uint32_t func_cnt;
	struct utool_cal_reg_cnt_dp *reg_table;
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_33rd_field_info[] = {
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "tpp_trans_lsa_pktn_ba4" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_V23, "pipe0_twp2tpp_nic_pktn_inc" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "tai2tpp_flush_sge_num" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_195th_field_info[] = {
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_V23, "flush_cqe_collect_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "flush_collect_cnt" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_225th_field_info[] = {
	{ false, false, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_V23, "pipe1_twp2tpp_pktn_inc" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC19, 0, UTOOL_CAP_V23, "pipe0_twp2tpp_pktn_inc" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "pipe1_twp2tpp_nic_pktn_inc" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_236th_field_info[] = {
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "rxdma_head_ub_pkt_cnt2" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "rxdma_head_ub_pkt_cnt0" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_382nd_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "req_in_cnt" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_383rd_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "req_rcvd_cnt" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_384th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "req_retry_cnt" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_385th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "req_rd_cnt" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_386th_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_V23, "rsp_compdbid_cnt" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_456th_field_info[] = {
	{ false, false, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_V23, "dfx_tp_lsa_req_status0" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "dfx_tp_lsa_req_err_status0" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_555th_field_info[] = {
	{ false, false, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_V23, "scc_token_retry_cnt" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_V23, "ppp_bonding_rsp_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_V23, "ppp_bonding_req_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "twp_cnp_rls_sge_cnt_bk0" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_556th_field_info[] = {
	{ false, false, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_V23, "tpp_rls_sge_cnt" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_V23, "tpp_alloc_sge_rslt_cnt" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_V23, "tqs_alloc_sge_req_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "twp_cnp_rls_sge_cnt_bk1" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_587th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_V23, "cfg_abnormal_data_rsp_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "cfg_abnormal_rsp_en" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_656th_field_info[] = {
	{ false, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_V23, "rxdma_head_srh_tpc_cnt" },
};

static struct utool_field_info g_utool_tp_A1_K1_pkt_657th_field_info[] = {
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC19, 0, UTOOL_CAP_V23, "rxdma_head_srh_jfs_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_V23, "rxdma_head_srh_jetty_cnt" },
};

static struct utool_field_info g_utool_tp_K1_pkt_438th_field_info[] = {
	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "rqm_ami_icg_en" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "jfr_cache_icg_en" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "jtg_cache_icg_en" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "jfr_cache_cbb_icg_en" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "jtg_cache_cbb_icg_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "get_jfr_clk_icg_en" },
};

static struct utool_field_info g_utool_tp_K1_pkt_528th_field_info[] = {
	{ false, false, UTOOL_LOC27, UTOOL_LOC31, 0, UTOOL_CAP_3, "sxc_ctrl_cfg" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC26, 0, UTOOL_CAP_3, "scc_idx_fifo_wl" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC23, 0, UTOOL_CAP_3, "scc_core_byp_ctrl" },
	{ false, false, UTOOL_LOC20, UTOOL_LOC20, 0, UTOOL_CAP_3, "scc_merge_en" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_3, "scc_ack_fast_drop_en" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC18, 0, UTOOL_CAP_3, "scc_dynamic_cg_en" },
	{ false, false, UTOOL_LOC13, UTOOL_LOC17, 0, UTOOL_CAP_3, "tpn_lock_cnp_weight" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_3, "scc_debug_en" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_3, "flr_mcu_sel" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_3, "scc_ctx_size_mode" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_3, "mcu_sel_mode" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC5, 0, UTOOL_CAP_3, "hash_sel_bit" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "hash_sel_mode" },
};

static struct utool_field_info g_utool_tp_rsv_field_info[] = {
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_diff_version_field_info g_utool_tp_diff_version_field_info[] = {
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC33,
	  g_utool_tp_A1_K1_pkt_33rd_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_33rd_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC195,
	  g_utool_tp_A1_K1_pkt_195th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_195th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC225,
	  g_utool_tp_A1_K1_pkt_225th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_225th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC236,
	  g_utool_tp_A1_K1_pkt_236th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_236th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC382,
	  g_utool_tp_A1_K1_pkt_382nd_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_382nd_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC383,
	  g_utool_tp_A1_K1_pkt_383rd_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_383rd_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC384,
	  g_utool_tp_A1_K1_pkt_384th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_384th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC385,
	  g_utool_tp_A1_K1_pkt_385th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_385th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC386,
	  g_utool_tp_A1_K1_pkt_386th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_386th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC448,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC449,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC450,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC451,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC452,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC453,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC454,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC455,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC456,
	  g_utool_tp_A1_K1_pkt_456th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_456th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC555,
	  g_utool_tp_A1_K1_pkt_555th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_555th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC556,
	  g_utool_tp_A1_K1_pkt_556th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_556th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC587,
	  g_utool_tp_A1_K1_pkt_587th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_587th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC621,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC622,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC656,
	  g_utool_tp_A1_K1_pkt_656th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_656th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC657,
	  g_utool_tp_A1_K1_pkt_657th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_657th_field_info) },

	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC33,
	  g_utool_tp_A1_K1_pkt_33rd_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_33rd_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC195,
	  g_utool_tp_A1_K1_pkt_195th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_195th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC225,
	  g_utool_tp_A1_K1_pkt_225th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_225th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC236,
	  g_utool_tp_A1_K1_pkt_236th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_236th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC246,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC247,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC248,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC249,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC250,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC251,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC252,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC253,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC254,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC255,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC256,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC257,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC258,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC266,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC267,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC268,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC269,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC270,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC271,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC272,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC273,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC274,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC275,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC276,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC277,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC278,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC286,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC287,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC288,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC289,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC290,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC291,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC292,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC293,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC294,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC295,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC296,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC297,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC298,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC299,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC307,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC308,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC309,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC310,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC311,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC312,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC313,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC314,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC315,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC316,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC332,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC333,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC334,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC335,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC336,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC337,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC382,
	  g_utool_tp_A1_K1_pkt_382nd_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_382nd_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC383,
	  g_utool_tp_A1_K1_pkt_383rd_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_383rd_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC384,
	  g_utool_tp_A1_K1_pkt_384th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_384th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC385,
	  g_utool_tp_A1_K1_pkt_385th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_385th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC386,
	  g_utool_tp_A1_K1_pkt_386th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_386th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC438,
	  g_utool_tp_K1_pkt_438th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_K1_pkt_438th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC448,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC449,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC450,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC451,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC452,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC453,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC454,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC456,
	  g_utool_tp_A1_K1_pkt_456th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_456th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC528,
	  g_utool_tp_K1_pkt_528th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_K1_pkt_528th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC555,
	  g_utool_tp_A1_K1_pkt_555th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_555th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC556,
	  g_utool_tp_A1_K1_pkt_556th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_556th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC587,
	  g_utool_tp_A1_K1_pkt_587th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_587th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC621,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC622,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC656,
	  g_utool_tp_A1_K1_pkt_656th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_656th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC657,
	  g_utool_tp_A1_K1_pkt_657th_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_A1_K1_pkt_657th_field_info) },
	{ "tp-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC663,
	  g_utool_tp_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_tp_rsv_field_info) },
};

static struct utool_cal_reg_table_dp *utool_tp_get_cal_reg_table(void)
{
#define INDEX0 0
#define INDEX1 1
#define INDEX2 2
#define INDEX3 3

	static struct utool_cal_reg_cnt_dp utool_tp_cal_reg_table[] = {
		{ true, true, TP_PKT_STATS, 0, NULL },
		{ true, true, TP_ROUTE_RESULT, 0, NULL },
		{ true, true, TP_RX_BANK, 0, NULL },
		{ true, true, TP_ABN_STATS, 0, NULL },
		{ false, false, TP_SCC_VERSION, 0, NULL },
		{ false, false, TP_SCC_LOG, 0, NULL },
		{ false, false, TP_SCC_DEBUG, 0, NULL },
	};
	static struct utool_cal_reg_table_dp cal_reg_table_dp = {};

	struct utool_field_info_dp *pkt_stats_field_info = NULL;
	struct utool_field_info_dp *abn_stats_field_info = NULL;
	struct utool_field_info_dp *route_result_field_info = NULL;
	struct utool_field_info_dp *rx_bank_field_info = NULL;

	pkt_stats_field_info = utool_tp_get_field_info_by_name(TP_PKT_STATS_FIELD_INFO);
	abn_stats_field_info = utool_tp_get_ex_field_info_by_name(TP_ABN_STATS_FIELD_INFO);
	route_result_field_info = utool_tp_get_ex_field_info_by_name(TP_TX_ROUTE_FIELD_INFO);
	rx_bank_field_info = utool_tp_get_ex_field_info_by_name(TP_RX_BANK_FIELD_INFO);
	if ((pkt_stats_field_info == NULL) || (abn_stats_field_info == NULL) || (route_result_field_info == NULL) ||
	    (rx_bank_field_info == NULL)) {
		utool_err_msg("Failed to get field info.\n");
		return NULL;
	}

	utool_tp_cal_reg_table[INDEX0].field_cnt = pkt_stats_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX0].field_info = pkt_stats_field_info->field_info;
	utool_tp_cal_reg_table[INDEX1].field_cnt = route_result_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX1].field_info = route_result_field_info->field_info;
	utool_tp_cal_reg_table[INDEX2].field_cnt = rx_bank_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX2].field_info = rx_bank_field_info->field_info;
	utool_tp_cal_reg_table[INDEX3].field_cnt = abn_stats_field_info->field_cnt;
	utool_tp_cal_reg_table[INDEX3].field_info = abn_stats_field_info->field_info;

	cal_reg_table_dp.func_cnt = UTOOL_ARRAY_SIZE(utool_tp_cal_reg_table);
	cal_reg_table_dp.reg_table = utool_tp_cal_reg_table;

	return &cal_reg_table_dp;
}

int utool_tp_cal_data_len(uint32_t *tp_data_len)
{
	struct utool_cal_reg_func_param tp_cal_reg_param = { tp_data_len, UTOOL_REG_CNT_DEFAULT, NULL, NULL, 0 };
	struct utool_cal_reg_table_dp *cal_reg_table_dp = NULL;
	int ret = UTOOL_OK;

	if (tp_data_len == NULL) {
		utool_err_msg("Param is invalid, tp data len is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	cal_reg_table_dp = utool_tp_get_cal_reg_table();
	if (cal_reg_table_dp == NULL) {
		utool_err_msg("Failed to get cal reg table.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	tp_cal_reg_param.utool_cal_reg_table = cal_reg_table_dp->reg_table;
	tp_cal_reg_param.func_cnt = cal_reg_table_dp->func_cnt;

	ret = utool_cal_func_reg_len(UTOOL_FUNC_ALL, &tp_cal_reg_param);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate reg cnt, ret = %d.\n", ret);
		return ret;
	}

	return UTOOL_OK;
}

static int utool_tp_parse_pkt_stats(struct fwctl_rpc_ub_out *tp_pkt_stats_out)
{
	struct utool_field_info_dp *pkt_stats_field_info = NULL;
	int ret = UTOOL_OK;

	pkt_stats_field_info = utool_tp_get_field_info_by_name(TP_PKT_STATS_FIELD_INFO);
	if (pkt_stats_field_info == NULL) {
		utool_err_msg("Failed to get pkt stats field info.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_pkt_parse(tp_pkt_stats_out, pkt_stats_field_info->field_cnt, pkt_stats_field_info->field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_TP, TP_PKT_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse tp pkt stats data.\n");
	}

	return ret;
}

static int utool_tp_parse_abn_stats(struct fwctl_rpc_ub_out *tp_abn_stats_out)
{
	struct utool_field_info_dp *abn_stats_field_info = NULL;
	int ret = UTOOL_OK;

	abn_stats_field_info = utool_tp_get_ex_field_info_by_name(TP_ABN_STATS_FIELD_INFO);
	if (abn_stats_field_info == NULL) {
		utool_err_msg("Failed to get abn stats field info.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_pkt_parse(tp_abn_stats_out, abn_stats_field_info->field_cnt, abn_stats_field_info->field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_TP, TP_ABN_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse tp abn stats data.\n");
	}

	return ret;
}

static int utool_tp_parse_route_result(struct fwctl_rpc_ub_out *tp_route_result_out)
{
	struct utool_field_info_dp *route_result_field_info = NULL;
	int ret = UTOOL_OK;

	route_result_field_info = utool_tp_get_ex_field_info_by_name(TP_TX_ROUTE_FIELD_INFO);
	if (route_result_field_info == NULL) {
		utool_err_msg("Failed to get route result field info.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_pkt_parse(tp_route_result_out, route_result_field_info->field_cnt, route_result_field_info->field_info,
			      UTOOL_CONCAT_STR(UTOOL_MODULE_TP, TP_ROUTE_RESULT));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse tp route result data.\n");
		return ret;
	}

	return UTOOL_OK;
}

static int utool_tp_parse_rx_bank(struct fwctl_rpc_ub_out *tp_pkt_out)
{
	struct utool_field_info_dp *rx_bank1_field_info = NULL;
	struct utool_field_info_dp *rx_bank2_field_info = NULL;
	struct utool_field_info_dp *rx_bank_field_info = NULL;
	struct fwctl_rpc_ub_out *out_temp = NULL;
	uint32_t data_size = 0;
	void *out_data = NULL;
	int ret = UTOOL_OK;
	int i;

	rx_bank_field_info = utool_tp_get_ex_field_info_by_name(TP_RX_BANK_FIELD_INFO);
	rx_bank1_field_info = utool_tp_get_ex_field_info_by_name(TP_RX_BANK_FIELD_INFO_BANK1);
	rx_bank2_field_info = utool_tp_get_ex_field_info_by_name(TP_RX_BANK_FIELD_INFO_BANK2);
	if ((rx_bank_field_info == NULL) || (rx_bank1_field_info == NULL) || (rx_bank2_field_info == NULL)) {
		utool_err_msg("Failed to get rx bank field info.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	struct utool_field_info *field_info[] = { rx_bank_field_info->field_info,
						  rx_bank1_field_info->field_info,
						  rx_bank2_field_info->field_info };
	uint32_t field_cnts[] = { rx_bank_field_info->field_cnt,
				  rx_bank1_field_info->field_cnt,
				  rx_bank2_field_info->field_cnt };

	data_size = tp_pkt_out->data_size / UBCTL_TP_RX_BANK_NUM;
	out_temp = (struct fwctl_rpc_ub_out *)UTOOL_MALLOC(sizeof(struct fwctl_rpc_ub_out) + data_size);
	if (out_temp == NULL) {
		utool_err_msg("Failed to malloc rpc out mem.\n");
		return UTOOL_ERR_MALLOC;
	}

	out_data = (void *)(tp_pkt_out->data);
	out_temp->retval = tp_pkt_out->retval;
	out_temp->data_size = data_size;
	out_temp->env_version = tp_pkt_out->env_version;
	for (i = 0; i < UBCTL_TP_RX_BANK_NUM; i++) {
		memcpy(out_temp->data, out_data, data_size);
		ret = utool_pkt_parse(out_temp, field_cnts[i], field_info[i], UTOOL_CONCAT_STR(UTOOL_MODULE_TP, TP_RX_BANK));
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to parse tp rx bank data.\n");
			break;
		}
		out_data += data_size;
	}
	UTOOL_FREE(out_temp);

	return ret;
}

static int utool_get_rand_str(char *str, int length)
{
#define TYPE_NUMBER 0
#define TYPE_UPPERCASE 1
#define TYPE_LOWERCASE 2
#define RANDOM_CHAR_TYPE_NUM 3U
#define RANDOM_NUM 2
#define TYPE_NUMBER_LEN 10
#define TYPE_UPPERCASE_LEN 26
#define TYPE_LOWERCASE_LEN 26
#define URANDOM_PATH "/dev/urandom"

	struct utool_type_trans type_arr[RANDOM_CHAR_TYPE_NUM] = {
		[TYPE_NUMBER] = {'0', TYPE_NUMBER_LEN},
		[TYPE_UPPERCASE] = {'A', TYPE_UPPERCASE_LEN},
		[TYPE_LOWERCASE] = {'a', TYPE_LOWERCASE_LEN},
	};
	uint32_t utool_rands[RANDOM_NUM] = {};
	uint32_t type;
	int fd, i, j;
	int size;

	fd = open(URANDOM_PATH, O_RDONLY);
	if (fd < 0) {
		utool_err_msg("Failed to open urand, errno is %d.\n", errno);
		return UTOOL_ERR_OPEN_FILE;
	}

	for (i = 0; i < (length - 1); i++) {
		for (j = 0; j < RANDOM_NUM; j++) {
			size = read(fd, &utool_rands[j], sizeof(uint32_t));
			if (size < 0) {
				utool_err_msg("Failed to read random, errno is %d.\n", errno);
				close(fd);
				return UTOOL_ERR_READ_FILE;
			}
		}

		type = utool_rands[0] % RANDOM_CHAR_TYPE_NUM;
		str[i] = type_arr[type].type_base + utool_rands[1] % type_arr[type].type_size;
	}

	close(fd);

	return UTOOL_OK;
}

static int utool_generate_file_name(char *file_name, uint32_t file_name_len, const char *prefix)
{
#define RANDOM_STR_LENGTH 7

	char str_rand[RANDOM_STR_LENGTH] = {};
	time_t time_seconds = time(0);
	struct tm timeinfo = {};
	int ret = UTOOL_OK;

	ret = utool_get_rand_str(str_rand, RANDOM_STR_LENGTH);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to get random string.\n");
		return ret;
	}

	if (localtime_r(&time_seconds, &timeinfo) == NULL) {
		utool_err_msg("Failed to get local time, errno = %d.\n", errno);
		return UTOOL_ERR;
	}

	ret = snprintf(file_name, file_name_len, "%s_%d_%d_%d_%d_%d_%d_%s.log", prefix,
		       timeinfo.tm_year + UTOOL_START_YEAR, timeinfo.tm_mon + 1, timeinfo.tm_mday,
		       timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, str_rand);
	if (ret <= 0 || ret >= (int)file_name_len) {
		utool_err_msg("Failed to generate file name, errno = %d, ret = %d.\n", errno, ret);
		return UTOOL_ERR;
	}

	return UTOOL_OK;
}

static int utool_tp_parse_scc_version(struct fwctl_rpc_ub_out *tp_scc_version_out)
{
	uint32_t *scc_version = NULL;

	scc_version = tp_scc_version_out->data;
	utool_reg_msg("scc_version: 0x%x\n", *scc_version);

	return UTOOL_OK;
}

static int utool_is_dir_exists(const char *file_path)
{
	struct stat st = {};
	int ret = UTOOL_ERR;

	if (stat(file_path, &st) == 0) {
		ret = (S_ISDIR(st.st_mode) != 0) ? UTOOL_OK : UTOOL_ERR;
	}

	return ret;
}

static int utool_mkdir(const char *path, mode_t mode)
{
	if (utool_is_dir_exists(path) == UTOOL_OK) {
		return UTOOL_OK;
	}

	if (mkdir(path, mode) < 0) {
		return UTOOL_ERR;
	}

	return UTOOL_OK;
}

static int utool_mkdir_p(const char *path, mode_t mode)
{
	char file_path[UTOOL_SCC_LOG_FILE_PATH_MAX_LEN];
	char *p = NULL;
	uint32_t len;
	int ret = 0;

	ret = snprintf(file_path, sizeof(file_path), "%s", path);
	if (ret <= 0 || ret >= (int)sizeof(file_path)) {
		utool_err_msg("Failed to get tmp file path, errno = %d, ret = %d.\n", errno, ret);
		return UTOOL_ERR;
	}

	len = strlen(file_path);
	if (file_path[len - 1] == '/') {
		file_path[len - 1] = '\0';
	}

	for (p = file_path + 1; *p != '\0'; p++) {
		if (*p == '/') {
			*p = '\0';
			if (utool_mkdir(file_path, mode) != UTOOL_OK) {
				return UTOOL_ERR;
			}
			*p = '/';
		}
	}

	if (utool_mkdir(file_path, mode) != UTOOL_OK) {
		return UTOOL_ERR;
	}
	return UTOOL_OK;
}

static int utool_tp_parse_scc_log(struct fwctl_rpc_ub_out *tp_scc_log_out)
{
#define TP_SCC_STR "scc"

	static char file_path[UTOOL_SCC_LOG_FILE_PATH_MAX_LEN] = {};
	static char file_name[UTOOL_SCC_LOG_NAME_MAX_LEN] = {};
	char *data = (char *)(tp_scc_log_out->data);
	int ret = UTOOL_OK;
	FILE *fp = NULL;

	if (file_path[0] == 0 && file_name[0] == 0) {
		if (utool_is_dir_exists(UTOOL_SCC_LOG_DIR_PATH) != UTOOL_OK) {
			ret = utool_mkdir_p(UTOOL_SCC_LOG_DIR_PATH, UTOOL_SCC_LOG_PATH_AUTHORITY);
			if (ret != 0) {
				utool_err_msg("Failed to mkdir file path, ret = %d.\n", ret);
				return UTOOL_ERR;
			}
		}

		ret = utool_generate_file_name(file_name, UTOOL_SCC_LOG_NAME_MAX_LEN, TP_SCC_STR);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to generate file name.\n");
			return ret;
		}

		ret = snprintf(file_path, sizeof(file_path), UTOOL_SCC_LOG_DIR_PATH"%s", file_name);
		if (ret <= 0 || ret >= (int)sizeof(file_path)) {
			utool_err_msg("Failed to create log file, errno = %d, ret = %d.\n", errno, ret);
			return UTOOL_ERR;
		}
	}

	fp = fopen(file_path, "a+");
	if (fp == NULL) {
		utool_err_msg("Failed to open file, errno = %d.\n", errno);
		return UTOOL_ERR_OPEN_FILE;
	}

	if (fwrite(data, sizeof(char), tp_scc_log_out->data_size, fp) <= 0) {
		utool_err_msg("Failed to write file, errno = %d.\n", errno);
		(void)chmod(file_path, UTOOL_SCC_LOG_FILE_AUTHORITY);
		(void)fclose(fp);
		return UTOOL_ERR_WRITE_FILE;
	}

	(void)chmod(file_path, UTOOL_SCC_LOG_FILE_AUTHORITY);
	(void)fclose(fp);

	return UTOOL_OK;
}

static int utool_tp_parse_scc_debug(struct fwctl_rpc_ub_out *tp_scc_debug_out)
{
	uint32_t *scc_debug = tp_scc_debug_out->data;

	utool_reg_msg("scc_debug_en: 0x%x\n", *scc_debug);

	return UTOOL_OK;
}

static int utool_scc_loop_call(struct utool_dev *dev, void *pkt_in, uint32_t pkt_in_len,
			       struct utool_cmd_param *param, struct utool_pkt_exec *pkt_exec)
{
#define UTOOL_SCC_NUM 2

	struct fwctl_pkt_in_index *ptr_pkt_in = (struct fwctl_pkt_in_index *)pkt_in;
	int ret = UTOOL_OK;
	uint32_t i;

	for (i = 0; i < UTOOL_SCC_NUM; i++) {
		ptr_pkt_in->index = i;
		ret = utool_pkt_operation(dev, ptr_pkt_in, pkt_in_len, pkt_exec);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to execute %s cmd, ret = %d.\n", param->func, ret);
			return ret;
		}
	}

	return ret;
}

static struct utool_func_dispatch g_utool_tp_mf_table[] = {
	{ true, TP_PKT_STATS, UTOOL_CMD_QUERY_TP_PKT_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_pkt_stats, utool_null_create_pkt_in },
	{ true, TP_ROUTE_RESULT, UTOOL_CMD_QUERY_TP_TX_ROUTE, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_route_result, utool_null_create_pkt_in },
	{ true, TP_RX_BANK, UTOOL_CMD_QUERY_TP_RX_BANK, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_rx_bank, utool_null_create_pkt_in },
	{ false, TP_SCC_VERSION, UTOOL_CMD_QUERY_SCC_VERSION, UTOOL_SCC_CNT,
	  utool_tp_parse_scc_version, utool_index_create_pkt_in },
	{ false, TP_SCC_LOG, UTOOL_CMD_QUERY_SCC_LOG, UTOOL_SCC_LOG_CNT,
	  utool_tp_parse_scc_log, utool_index_create_pkt_in },
	{ false, TP_SCC_DEBUG, UTOOL_CMD_QUERY_SCC_DEBUG_EN, UTOOL_SCC_CNT,
	  utool_tp_parse_scc_debug, utool_null_create_pkt_in },
};

static struct utool_func_dispatch g_utool_tp_func_table[] = {
	{ true, TP_PKT_STATS, UTOOL_CMD_QUERY_TP_PKT_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_pkt_stats, utool_null_create_pkt_in },
	{ true, TP_ROUTE_RESULT, UTOOL_CMD_QUERY_TP_TX_ROUTE, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_route_result, utool_null_create_pkt_in },
	{ true, TP_RX_BANK, UTOOL_CMD_QUERY_TP_RX_BANK, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_rx_bank, utool_null_create_pkt_in },
	{ true, TP_ABN_STATS, UTOOL_CMD_QUERY_TP_ABN_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_tp_parse_abn_stats, utool_port_create_pkt_in },
	{ false, TP_SCC_VERSION, UTOOL_CMD_QUERY_SCC_VERSION, UTOOL_SCC_CNT,
	  utool_tp_parse_scc_version, utool_index_create_pkt_in },
	{ false, TP_SCC_LOG, UTOOL_CMD_QUERY_SCC_LOG, UTOOL_SCC_LOG_CNT,
	  utool_tp_parse_scc_log, utool_index_create_pkt_in },
	{ false, TP_SCC_DEBUG, UTOOL_CMD_QUERY_SCC_DEBUG_EN, UTOOL_SCC_CNT,
	  utool_tp_parse_scc_debug, utool_null_create_pkt_in },
};

int utool_tp_parse_rpc_pkt(struct fwctl_rpc_ub_out *tp_out)
{
	struct utool_cal_reg_table_dp *cal_reg_table_dp = NULL;
	int ret = UTOOL_OK;

	if (tp_out == NULL) {
		utool_err_msg("Param is invalid, tp out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	cal_reg_table_dp = utool_tp_get_cal_reg_table();
	if (cal_reg_table_dp == NULL) {
		utool_err_msg("Failed to get cal reg table.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_module_parse(tp_out, UTOOL_ARRAY_SIZE(g_utool_tp_func_table), g_utool_tp_func_table,
				 cal_reg_table_dp->func_cnt, cal_reg_table_dp->reg_table);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse tp rpc pkt.\n");
	}

	return ret;
}

static void utool_tp_print_help(void)
{
	utool_err_msg("The ubctl tp command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m tp -p ${port}\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m tp -f pkt_stats/route_result/rx_bank/"
		      "scc_version/scc_log/scc_debug_en\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m tp -f abn_stats -p ${port}\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m tp -f scc_debug_en -e ${value}\n");
}

static int utool_handle_matched_func(struct utool_dev *dev, struct utool_cmd_param *param,
				     struct utool_func_dispatch *func_entry,
				     struct utool_cal_reg_func_param *tp_cal_reg_param)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_MAX, 0, NULL };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret;

	func_pkt_exec.rpc_cmd = func_entry->rpc_cmd;
	func_pkt_exec.execute = func_entry->execute;
	tp_cal_reg_param->user_def_data_len = func_entry->data_len;

	ret = utool_cal_func_reg_len(param->func, tp_cal_reg_param);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to cal tp func %s reg cnt.\n", param->func);
		return ret;
	}

	func_pkt_exec.data_len = *tp_cal_reg_param->data_len;
	if (func_entry->create_pkt_in == NULL) {
		utool_err_msg("Failed to create tp func pkt in. Callback is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	pkt_in = func_entry->create_pkt_in(&pkt_in_len, param);
	if (pkt_in == NULL) {
		utool_err_msg("Failed to create pkt in.\n");
		return UTOOL_ERR_MALLOC;
	}

	if (strcmp(func_entry->func, TP_SCC_LOG) == 0) {
		ret = utool_scc_loop_call(dev, pkt_in, pkt_in_len, param, &func_pkt_exec);
		if (ret == UTOOL_OK) {
			utool_info_msg("Succeed to query scc log.\n");
		}
	} else {
		ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &func_pkt_exec);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to execute command, ret = %d.\n", ret);
		}
	}

	utool_destroy_pkt_in(&pkt_in);
	return ret;
}

static int utool_tp_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			     struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_cal_reg_table_dp *cal_reg_table_dp = utool_tp_get_cal_reg_table();
	struct utool_cal_reg_func_param tp_cal_reg_param = {};
	uint32_t data_len = 0;
	uint32_t i;

	if (cal_reg_table_dp == NULL) {
		utool_err_msg("Failed to get cal reg table.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	tp_cal_reg_param.utool_cal_reg_table = cal_reg_table_dp->reg_table;
	tp_cal_reg_param.func_cnt = cal_reg_table_dp->func_cnt;
	tp_cal_reg_param.data_len = &data_len;

	for (i = 0; i < func_cnt; i++) {
		if (strcmp(param->func, func_table[i].func) == 0) {
			return utool_handle_matched_func(dev, param, &func_table[i], &tp_cal_reg_param);
		}
	}

	utool_tp_print_help();
	return UTOOL_ERR_FUNC_NOT_FOUND;
}

static int utool_tp_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
			struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_TP, 0, NULL };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	func_pkt_exec.execute = utool_tp_parse_rpc_pkt;

	ret = utool_tp_cal_data_len(&func_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate reg cnt of all, ret = %d.\n", ret);
		return ret;
	}

	pkt_in = utool_port_create_pkt_in(&pkt_in_len, param);
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

int utool_tp_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	static struct utool_func_dispatch utool_tp_flag_mfe_table[] = {
		{ false, TP_SCC_DEBUG, UTOOL_CMD_CONF_SCC_DEBUG_EN, UTOOL_SCC_CNT,
		  utool_tp_parse_scc_debug, utool_enable_create_pkt_in },
	};
	static struct utool_func_dispatch utool_tp_flag_mfp_table[] = {
		{ true, TP_ABN_STATS, UTOOL_CMD_QUERY_TP_ABN_STATS, UTOOL_REG_CNT_DEFAULT,
		  utool_tp_parse_abn_stats, utool_port_create_pkt_in },
	};
	struct utool_cmd_dispatch utool_tp_cmd_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_F, utool_tp_cmd_func,
		  g_utool_tp_mf_table, UTOOL_ARRAY_SIZE(g_utool_tp_mf_table) },
		{ UTOOL_FLAG_M | UTOOL_FLAG_F | UTOOL_FLAG_P, utool_tp_cmd_func,
		  utool_tp_flag_mfp_table, UTOOL_ARRAY_SIZE(utool_tp_flag_mfp_table) },
		{ UTOOL_FLAG_M | UTOOL_FLAG_F | UTOOL_FLAG_E, utool_tp_cmd_func,
		  utool_tp_flag_mfe_table, UTOOL_ARRAY_SIZE(utool_tp_flag_mfe_table) },
		{ UTOOL_FLAG_M | UTOOL_FLAG_P, utool_tp_cmd, NULL, 0 },
	};
	uint32_t tp_cmd_cnt = UTOOL_ARRAY_SIZE(utool_tp_cmd_table);
	uint32_t i = 0;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < tp_cmd_cnt; i++) {
		if (param->flags == utool_tp_cmd_table[i].flags) {
			if (utool_tp_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch, execute is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}
			return utool_tp_cmd_table[i].execute(dev, param,
							     utool_tp_cmd_table[i].func_table,
							     utool_tp_cmd_table[i].func_cnt);
		}
	}

	utool_tp_print_help();

	return UTOOL_ERR_CMD_NOT_FOUND;
}

struct utool_field_info *utool_tp_cmd_diff_ver_dispatch(const char *module_func_name,
							uint32_t reg_version, uint32_t reg_info_index,
							uint32_t *replace_field_cnt)
{
	uint32_t i;

	if (module_func_name == NULL || module_func_name[0] == '\0') {
		utool_err_msg("Module func name is invalid.\n");
		return NULL;
	}

	for (i = 0; i < UTOOL_ARRAY_SIZE(g_utool_tp_diff_version_field_info); i++) {
		if (strcmp(module_func_name, g_utool_tp_diff_version_field_info[i].module_func_name) != 0) {
			continue;
		}

		if (reg_version != g_utool_tp_diff_version_field_info[i].reg_version) {
			continue;
		}

		if (reg_info_index == g_utool_tp_diff_version_field_info[i].reg_info_index) {
			*replace_field_cnt = g_utool_tp_diff_version_field_info[i].replace_field_cnt;
			return g_utool_tp_diff_version_field_info[i].replace_field_info;
		}
	}

	return NULL;
}
