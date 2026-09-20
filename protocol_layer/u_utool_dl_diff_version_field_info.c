// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_dl_diff_version_field_info.h"

static struct utool_field_info g_utool_dl_A1_K1_pkt_189th_field_info[] = {
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_V23, "pfa_tx_norm_long_pkt_chk_en" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_V23, "pfa_tx_norm_short_pkt_chk_en" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC29, 0, UTOOL_CAP_V23, "pfa_tx_norm_short_pkt_len" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "reserved" },
};

static struct utool_field_info g_utool_dl_A1_K1_pkt_193rd_field_info[] = {
	{ false, true, UTOOL_LOC25, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC24, 0, UTOOL_CAP_V23, "pfa_dfx_rx_drop_fifo_cnt" },
	{ false, false, UTOOL_LOC17, UTOOL_LOC17, 0, UTOOL_CAP_V23, "pfa_dfx_rx_drop_fifo_full" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC16, 0, UTOOL_CAP_V23, "pfa_dfx_rx_drop_fifo_empty" },
	{ false, true, UTOOL_LOC9, UTOOL_LOC15, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC8, 0, UTOOL_CAP_V23, "pfa_dfx_rx_data_fifo_cnt" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "pfa_dfx_rx_data_fifo_full" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "pfa_dfx_rx_data_fifo_empty" },
};

static struct utool_field_info g_utool_dl_A1_K1_pkt_194th_field_info[] = {
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC19, UTOOL_LOC19, 0, UTOOL_CAP_V23, "pfa_dfx_tx_norm_bp" },
	{ false, true, UTOOL_LOC13, UTOOL_LOC18, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_V23, "pfa_dfx_port_200g_en" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_V23, "pfa_dfx_port_400g_en" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_V23, "pfa_dfx_dl_link_state" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC9, 0, UTOOL_CAP_V23, "pfa_dfx_pkt_crc_mode" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "reserved" },
};

static struct utool_field_info g_utool_dl_A1_K1_pkt_214th_field_info[] = {
	{ false, true, UTOOL_LOC7, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_V23, "cfg_data_am_clr_seed_en" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_V23, "cfg_tsb_symbol0_scram_en" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_V23, "cfg_scram_poly_mode" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC3, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "cfg_scram_en" },
};

static struct utool_field_info g_utool_dl_A1_pkt_225th_field_info[] = {
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_2, "port_eq_redo" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_2, "port_perdorm_eq" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_2, "port_change_lane" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_2, "port_change_speed" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_2, "port_detect_ei" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_2, "port_soft_retrain" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_2, "port_dl_retrain" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_2, "port_fec_err" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_2, "port_recv_edf" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "port_deskew_overflow" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "port_asyn_buf_overflow" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "port_am_loss" },
};

static struct utool_field_info g_utool_dl_A1_pkt_229th_field_info[] = {
	{ false, true, UTOOL_LOC27, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC26, 0, UTOOL_CAP_2, "st_recv_xmode" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC23, 0, UTOOL_CAP_2, "st_ub_cnt_link_idle" },
	{ false, true, UTOOL_LOC3, UTOOL_LOC7, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_2, "st_port_en" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_2, "st_dl2mac_link_down" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_2, "st_link_rdy" },
};

static struct utool_field_info g_utool_dl_K1_pkt_179th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "pfa_dfx_tx_norm_err_pkt_in_cnt" },
};

static struct utool_field_info g_utool_dl_K1_pkt_180th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "pfa_dfx_rx_err_pkt_in_cnt" },
};

static struct utool_field_info g_utool_dl_K1_pkt_184th_field_info[] = {
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3, "pfa_dfx_tx_norm_short_pkt_cnt" },
};

static struct utool_field_info g_utool_dl_K1_pkt_185th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3, "pfa_dfx_tx_norm_long_pkt_cnt" },
};

static struct utool_field_info g_utool_dl_K1_pkt_186th_field_info[] = {
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3, "pfa_dfx_tx_norm_mode_err_pkt_cnt" },
};

static struct utool_field_info g_utool_dl_K1_pkt_187th_field_info[] = {
	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_3, "pfa_dfx_rx_short_pkt_cnt" },
};

static struct utool_field_info g_utool_dl_K1_pkt_188th_field_info[] = {
	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_3, "pfa_dfx_rx_mode_err_pkt_cnt" },
};

static struct utool_field_info g_utool_dl_A1_K1_pkt_232nd_field_info[] = {
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_V23, "muxpcs_st_of_cfg_linkdown_stall_mc" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_V23, "muxpcs_st_of_cfg_linkdown_done_mc" },
};

static struct utool_field_info g_utool_dl_A1_K1_pkt_233rd_field_info[] = {
	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_V23, "muxpcs_cfg_linkdown_stall_mc" },
};

static struct utool_field_info g_utool_dl_A1_K1_pkt_234th_field_info[] = {
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_V23, "muxpcs_cfg_linkdown_timeout_mc" },
};

static struct utool_field_info g_utool_dl_A1_K1_pkt_235th_field_info[] = {
	{ false, true, UTOOL_LOC30, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC27, UTOOL_LOC29, 0, UTOOL_CAP_V23, "cfg_rate_speed9_width" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC26, 0, UTOOL_CAP_V23, "cfg_rate_speed8_width" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC23, 0, UTOOL_CAP_V23, "cfg_rate_speed7_width" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC20, 0, UTOOL_CAP_V23, "cfg_rate_speed6_width" },
	{ false, false, UTOOL_LOC15, UTOOL_LOC17, 0, UTOOL_CAP_V23, "cfg_rate_speed5_width" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC14, 0, UTOOL_CAP_V23, "cfg_rate_speed4_width" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC11, 0, UTOOL_CAP_V23, "cfg_rate_speed3_width" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC8, 0, UTOOL_CAP_V23, "cfg_rate_speed2_width" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC5, 0, UTOOL_CAP_V23, "cfg_rate_speed1_width" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_V23, "cfg_rate_speed0_width" },
};

static struct utool_field_info g_utool_dl_A1_K1_pkt_240th_field_info[] = {
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "st_pcs_rx_am_det_pn(lane0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "st_pcs_rx_am_lane_id(lane0)" },
};

static struct utool_field_info g_utool_dl_A1_K1_pkt_241st_field_info[] = {
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "st_pcs_rx_am_det_pn(lane1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "st_pcs_rx_am_lane_id(lane1)" },
};

static struct utool_field_info g_utool_dl_A1_K1_pkt_242nd_field_info[] = {
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "st_pcs_rx_am_det_pn(lane2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "st_pcs_rx_am_lane_id(lane2)" },
};

static struct utool_field_info g_utool_dl_A1_K1_pkt_243rd_field_info[] = {
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_V23, "st_pcs_rx_am_det_pn(lane3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_V23, "st_pcs_rx_am_lane_id(lane3)" },
};

static struct utool_field_info g_utool_dl_A1_lane_1st_field_info[] = {
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_2, "retrain_link" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_2, "enter_buss_lpk_en" },
	{ false, false, UTOOL_LOC29, UTOOL_LOC29, 0, UTOOL_CAP_2, "enter_prot_lpk_en" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_2, "enter_cmp" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC27, 0, UTOOL_CAP_2, "phy_mode_ctrl" },
	{ false, true, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_2, "chg_lw_request" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC21, 0, UTOOL_CAP_2, "target_rx_link_width" },
	{ false, true, UTOOL_LOC14, UTOOL_LOC15, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC13, 0, UTOOL_CAP_2, "target_tx_link_width" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_2, "target_link_speed" },
};

static struct utool_field_info g_utool_dl_A1_K1_lane_3rd_field_info[] = {
	{ false, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_V23, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_V23, "st_md_rx_det_lane_use" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_V23, "st_md_rx_physical_lane_use" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_V23, "st_md_tx_physical_lane_use" },
};

static struct utool_field_info g_utool_dl_K1_pkt_225th_field_info[] = {
	{ false, true, UTOOL_LOC13, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC12, 0, UTOOL_CAP_3, "port_link_disable" },
	{ false, false, UTOOL_LOC11, UTOOL_LOC11, 0, UTOOL_CAP_3, "port_eq_redo" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC10, 0, UTOOL_CAP_3, "port_perdorm_eq" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC9, 0, UTOOL_CAP_3, "port_change_lane" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC8, 0, UTOOL_CAP_3, "port_change_speed" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_3, "port_detect_ei" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_3, "port_soft_retrain" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "port_dl_retrain" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "port_fec_err" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "port_recv_edf" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "port_deskew_overflow" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "port_asyn_buf_overflow" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "port_am_loss" },
};

static struct utool_field_info g_utool_dl_K1_lane_1st_field_info[] = {
	{ false, false, UTOOL_LOC31, UTOOL_LOC31, 0, UTOOL_CAP_3, "retrain_link" },
	{ false, false, UTOOL_LOC30, UTOOL_LOC30, 0, UTOOL_CAP_3, "enter_buss_lpk_en" },
	{ false, false, UTOOL_LOC29, UTOOL_LOC29, 0, UTOOL_CAP_3, "enter_prot_lpk_en" },
	{ false, false, UTOOL_LOC28, UTOOL_LOC28, 0, UTOOL_CAP_3, "enter_cmp" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC27, 0, UTOOL_CAP_3, "phy_mode_ctrl" },
	{ false, true, UTOOL_LOC23, UTOOL_LOC23, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC22, UTOOL_LOC22, 0, UTOOL_CAP_3, "chg_lw_request" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC21, 0, UTOOL_CAP_3, "target_rx_link_width" },
	{ false, true, UTOOL_LOC14, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC13, 0, UTOOL_CAP_3, "target_tx_link_width" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_3, "target_link_speed" },
};

static struct utool_field_info g_utool_dl_rsv_field_info[] = {
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_diff_version_field_info g_utool_dl_diff_version_field_info[] = {
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC175,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC176,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC181,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC182,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC183,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC189,
	  g_utool_dl_A1_K1_pkt_189th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_189th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC191,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC192,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC193,
	  g_utool_dl_A1_K1_pkt_193rd_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_193rd_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC194,
	  g_utool_dl_A1_K1_pkt_194th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_194th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC195,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC196,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC197,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC198,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC199,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC200,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC214,
	  g_utool_dl_A1_K1_pkt_214th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_214th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC225,
	  g_utool_dl_A1_pkt_225th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_pkt_225th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC229,
	  g_utool_dl_A1_pkt_229th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_pkt_229th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC232,
	  g_utool_dl_A1_K1_pkt_232nd_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_232nd_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC233,
	  g_utool_dl_A1_K1_pkt_233rd_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_233rd_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC234,
	  g_utool_dl_A1_K1_pkt_234th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_234th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC235,
	  g_utool_dl_A1_K1_pkt_235th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_235th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC236,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC240,
	  g_utool_dl_A1_K1_pkt_240th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_240th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC241,
	  g_utool_dl_A1_K1_pkt_241st_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_241st_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC242,
	  g_utool_dl_A1_K1_pkt_242nd_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_242nd_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC243,
	  g_utool_dl_A1_K1_pkt_243rd_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_243rd_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC284,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_A_1, UTOOL_LOC285,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },

	{ "dl-lane", UTOOL_ENV_VER_A_1, UTOOL_LOC1,
	  g_utool_dl_A1_lane_1st_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_lane_1st_field_info) },
	{ "dl-lane", UTOOL_ENV_VER_A_1, UTOOL_LOC3,
	  g_utool_dl_A1_K1_lane_3rd_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_lane_3rd_field_info) },

	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC175,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC176,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC179,
	  g_utool_dl_K1_pkt_179th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_K1_pkt_179th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC180,
	  g_utool_dl_K1_pkt_180th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_K1_pkt_180th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC181,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC182,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC183,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },

	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC184,
	  g_utool_dl_K1_pkt_184th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_K1_pkt_184th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC185,
	  g_utool_dl_K1_pkt_185th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_K1_pkt_185th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC186,
	  g_utool_dl_K1_pkt_186th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_K1_pkt_186th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC187,
	  g_utool_dl_K1_pkt_187th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_K1_pkt_187th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC188,
	  g_utool_dl_K1_pkt_188th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_K1_pkt_188th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC189,
	  g_utool_dl_A1_K1_pkt_189th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_189th_field_info) },

	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC190,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC191,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC192,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC193,
	  g_utool_dl_A1_K1_pkt_193rd_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_193rd_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC194,
	  g_utool_dl_A1_K1_pkt_194th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_194th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC195,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC196,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC197,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC198,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC199,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC200,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC214,
	  g_utool_dl_A1_K1_pkt_214th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_214th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC225,
	  g_utool_dl_K1_pkt_225th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_K1_pkt_225th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC232,
	  g_utool_dl_A1_K1_pkt_232nd_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_232nd_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC233,
	  g_utool_dl_A1_K1_pkt_233rd_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_233rd_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC234,
	  g_utool_dl_A1_K1_pkt_234th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_234th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC235,
	  g_utool_dl_A1_K1_pkt_235th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_235th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC236,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC240,
	  g_utool_dl_A1_K1_pkt_240th_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_240th_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC241,
	  g_utool_dl_A1_K1_pkt_241st_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_241st_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC242,
	  g_utool_dl_A1_K1_pkt_242nd_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_242nd_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC243,
	  g_utool_dl_A1_K1_pkt_243rd_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_pkt_243rd_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC284,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },
	{ "dl-pkt_stats", UTOOL_ENV_VER_K_1, UTOOL_LOC285,
	  g_utool_dl_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_rsv_field_info) },

	{ "dl-lane", UTOOL_ENV_VER_K_1, UTOOL_LOC1,
	  g_utool_dl_K1_lane_1st_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_K1_lane_1st_field_info) },
	{ "dl-lane", UTOOL_ENV_VER_K_1, UTOOL_LOC3,
	  g_utool_dl_A1_K1_lane_3rd_field_info, UTOOL_ARRAY_SIZE(g_utool_dl_A1_K1_lane_3rd_field_info) },
};

struct utool_field_info *utool_dl_cmd_diff_ver_dispatch(const char *module_func_name,
							uint32_t reg_version, uint32_t reg_info_index,
							uint32_t *replace_field_cnt)
{
	uint32_t i;

	if (module_func_name == NULL || module_func_name[0] == '\0') {
		utool_err_msg("Module func name is invalid.\n");
		return NULL;
	}

	for (i = 0; i < UTOOL_ARRAY_SIZE(g_utool_dl_diff_version_field_info); i++) {
		if (strcmp(module_func_name, g_utool_dl_diff_version_field_info[i].module_func_name) != 0) {
			continue;
		}

		if (reg_version != g_utool_dl_diff_version_field_info[i].reg_version) {
			continue;
		}

		if (reg_info_index == g_utool_dl_diff_version_field_info[i].reg_info_index) {
			*replace_field_cnt = g_utool_dl_diff_version_field_info[i].replace_field_cnt;
			return g_utool_dl_diff_version_field_info[i].replace_field_info;
		}
	}

	return NULL;
}
