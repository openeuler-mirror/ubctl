// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_ecc_2b.h"

static struct utool_field_info g_utool_ecc_2b_field_info[] = {
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "port_id" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_0(BA)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_1(BA)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_2(BA)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_3(BA)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_4(BA)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_5(BA)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_6(BA)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_7(BA)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC10, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "mar_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "mar_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccum_imm_b0_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccum_imm_b1_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccum_imm_b2_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccum_imm_b3_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccum_imm_b4_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccum_imm_b5_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccum_imm_b6_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccum_imm_b7_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccum_xn_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccum_gsa_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccum_lc_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccum_ckb_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccum_tifmbuf_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccum_tifcmt_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccum_tifjc_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccum_tifwbuf_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccum_tifptm_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccum_pru_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccum_sifdbuf_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccum_tifpvm_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_0(CCU)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_1(CCU)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_2(CCU)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_3(CCU)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_4(CCU)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_5(CCU)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_6(CCU)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "master_ram_ecc_2b_addr_7(CCU)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_msm_b0_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_msm_b1_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_msm_b2_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_msm_b3_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_msm_b4_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_msm_b5_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_msm_b6_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_msm_b7_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_msm_b8_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_msm_b9_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_msm_b10_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_msm_b11_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_msm_b12_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_msm_b13_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_msm_b14_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_msm_b15_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_cip_b0_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_cip_b1_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_cip_b2_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_cip_b3_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_cip_b4_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_cip_b5_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_cip_b6_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_cip_b7_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_cip_b8_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_cip_b9_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_cip_b10_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_cip_b11_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_cip_b12_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_cip_b13_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "ccua_cip_b14_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ccua_cip_b15_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC27, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC26, 0, UTOOL_CAP_ALL, "dl_retry_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC11, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC10, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC26, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "dl_pmu_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ppp_nl_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "mrd_mb_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "mrd_rdata_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "eip_int_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "eip_db_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "eip_ba_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC9, 0, UTOOL_CAP_ALL, "cqm_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC27, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC26, 0, UTOOL_CAP_ALL, "tom_fifo_inf_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "tom_fifo_tl_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "tom_r_data_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "tom_rd_data_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "rsp_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC26, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC25, 0, UTOOL_CAP_ALL, "tqc_reorder_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "tqc_we_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "tqc_wm_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "tqc_ro_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqms_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tqeb_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dm_ram_ecc_2b_addr(LQC_TA_DM)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_ram_ecc_2b_addr(LQC_TA_USI)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "dm_ram_ecc_2b_addr(LQC_TA_IDEV)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "usi_ram_ecc_2b_addr(LQC_TA_RIG)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC23, 0, UTOOL_CAP_ALL, "tp_timer_fifo_inf_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC17, 0, UTOOL_CAP_ALL, "tp_timer_fifo_tl_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC11, 0, UTOOL_CAP_ALL, "tp_timer_r_data_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "tp_timer_rd_data_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "scc_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "scc_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC14, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "tqem_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "tqem_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "tqs_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "tqs_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "tai_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "tai_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC21, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC20, 0, UTOOL_CAP_ALL, "extq_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "extq_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tpp_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tpp_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tpp_ram_ecc_2b_ram_id_1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tpp_ram_ecc_2b_addr_1" },
	{ false, true, UTOOL_LOC14, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC13, 0, UTOOL_CAP_ALL, "tprxp_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "tprxp_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC7, 0, UTOOL_CAP_ALL, "rqm_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_ALL, "rqm_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "cache_ecc_2bit_eaddr(DAM)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "cache_ecc_2bit_err_id(DAM)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "cache_ecc_2bit_eaddr(EUM)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "cache_ecc_2bit_err_id(EUM)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "cache_ecc_2bit_eaddr(TPCM)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "cache_ecc_2bit_err_id(TPCM)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "cache_ecc_2bit_eaddr(TPGCM)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "cache_ecc_2bit_err_id(TPGCM)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC19, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC18, 0, UTOOL_CAP_ALL, "cache_ecc_2bit_eaddr(TPMM)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC4, 0, UTOOL_CAP_ALL, "cache_ecc_2bit_err_id(TPMM)" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_ALL, "lrb_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "lrb_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "tp_lsa_req_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "tp_lsa_req_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "ubommu_ram_ecc_2b_addr" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_ALL, "reserved" },

	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_field_info g_utool_ecc_2b_A1_9th_field_info[] = {
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_2, "mar_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_2, "mar_ram_ecc_2b_addr" },
};

static struct utool_field_info g_utool_ecc_2b_A1_52nd_field_info[] = {
	{ false, false, UTOOL_LOC27, UTOOL_LOC31, 0, UTOOL_CAP_2, "tom_w_data_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC26, 0, UTOOL_CAP_2, "tom_fifo_inf_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC17, 0, UTOOL_CAP_2, "tom_fifo_tl_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC11, 0, UTOOL_CAP_2, "tom_r_data_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_2, "tom_rd_data_ram_ecc_2b_addr" },
};

static struct utool_field_info g_utool_ecc_2b_A1_54th_field_info[] = {
	{ false, true, UTOOL_LOC27, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC26, 0, UTOOL_CAP_2, "tqc_we_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC17, 0, UTOOL_CAP_2, "tqc_wm_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC8, 0, UTOOL_CAP_2, "tqc_ro_ram_ecc_2b_addr" },
};

static struct utool_field_info g_utool_ecc_2b_A1_56th_field_info[] = {
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_2, "wqem_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_2, "wqem_ram_ecc_1b_addr" },
};

static struct utool_field_info g_utool_ecc_2b_A1_61st_field_info[] = {
	{ false, true, UTOOL_LOC29, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC28, 0, UTOOL_CAP_2, "tp_timer_w_data_ram_ecc_1b_addr" },
	{ false, false, UTOOL_LOC18, UTOOL_LOC23, 0, UTOOL_CAP_2, "tp_timer_fifo_inf_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC12, UTOOL_LOC17, 0, UTOOL_CAP_2, "tp_timer_fifo_tl_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC11, 0, UTOOL_CAP_2, "tp_timer_r_data_ram_ecc_2b_addr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_2, "tp_timer_rd_data_ram_ecc_2b_addr" },
};

static struct utool_field_info g_utool_ecc_2b_A1_71st_field_info[] = {
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC9, UTOOL_LOC14, 0, UTOOL_CAP_2, "tprxp_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC8, 0, UTOOL_CAP_2, "tprxp_ram_ecc_2b_addr" },
};

static struct utool_field_info g_utool_ecc_2b_A1_72nd_field_info[] = {
	{ false, true, UTOOL_LOC15, UTOOL_LOC31, 0, UTOOL_CAP_2, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC14, 0, UTOOL_CAP_2, "rqm_ram_ecc_2b_addr_new" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC7, 0, UTOOL_CAP_2, "rqm_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_2, "rqm_ram_ecc_2b_addr" },
};

static struct utool_field_info g_utool_ecc_2b_rsv_field_info[] = {
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_ALL, "reserved" },
};

static struct utool_diff_version_field_info g_utool_ecc_2b_diff_version_field_info[] = {
	{ "ecc_2b", UTOOL_ENV_VER_A_1, UTOOL_LOC9,
	  g_utool_ecc_2b_A1_9th_field_info, UTOOL_ARRAY_SIZE(g_utool_ecc_2b_A1_9th_field_info) },
	{ "ecc_2b", UTOOL_ENV_VER_A_1, UTOOL_LOC52,
	  g_utool_ecc_2b_A1_52nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ecc_2b_A1_52nd_field_info) },
	{ "ecc_2b", UTOOL_ENV_VER_A_1, UTOOL_LOC54,
	  g_utool_ecc_2b_A1_54th_field_info, UTOOL_ARRAY_SIZE(g_utool_ecc_2b_A1_54th_field_info) },
	{ "ecc_2b", UTOOL_ENV_VER_A_1, UTOOL_LOC56,
	  g_utool_ecc_2b_A1_56th_field_info, UTOOL_ARRAY_SIZE(g_utool_ecc_2b_A1_56th_field_info) },
	{ "ecc_2b", UTOOL_ENV_VER_A_1, UTOOL_LOC61,
	  g_utool_ecc_2b_A1_61st_field_info, UTOOL_ARRAY_SIZE(g_utool_ecc_2b_A1_61st_field_info) },
	{ "ecc_2b", UTOOL_ENV_VER_A_1, UTOOL_LOC63,
	  g_utool_ecc_2b_rsv_field_info, UTOOL_ARRAY_SIZE(g_utool_ecc_2b_rsv_field_info) },
	{ "ecc_2b", UTOOL_ENV_VER_A_1, UTOOL_LOC71,
	  g_utool_ecc_2b_A1_71st_field_info, UTOOL_ARRAY_SIZE(g_utool_ecc_2b_A1_71st_field_info) },
	{ "ecc_2b", UTOOL_ENV_VER_A_1, UTOOL_LOC72,
	  g_utool_ecc_2b_A1_72nd_field_info, UTOOL_ARRAY_SIZE(g_utool_ecc_2b_A1_72nd_field_info) },
};

int utool_ecc_2b_cal_data_len(uint32_t *ecc_2b_data_len)
{
	uint32_t ecc_2b_reg_cnt = 0;
	int ret = UTOOL_OK;

	if (ecc_2b_data_len == NULL) {
		utool_err_msg("Param is invalid, ecc 2b data len is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_cal_reg_cnt(g_utool_ecc_2b_field_info, UTOOL_ARRAY_SIZE(g_utool_ecc_2b_field_info),
				&ecc_2b_reg_cnt);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate reg cnt, ret = %d.\n", ret);
		return ret;
	}

	*ecc_2b_data_len = ecc_2b_reg_cnt * sizeof(uint32_t);

	return UTOOL_OK;
}

int utool_ecc_2b_parse_rpc_pkt(struct fwctl_rpc_ub_out *ecc_2b_out)
{
	int ret = UTOOL_OK;

	if (ecc_2b_out == NULL) {
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_pkt_parse(ecc_2b_out, UTOOL_ARRAY_SIZE(g_utool_ecc_2b_field_info), g_utool_ecc_2b_field_info,
			      UTOOL_MODULE_ECC_2B);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse ecc_2b pkt stats data.\n");
	}

	return ret;
}

static int utool_ecc_2b_cmd(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_ECC_2B, 0, NULL };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	func_pkt_exec.execute = utool_ecc_2b_parse_rpc_pkt;

	ret = utool_ecc_2b_cal_data_len(&func_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate data len of all, ret = %d.\n", ret);
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

int utool_ecc_2b_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (param->flags != (UTOOL_FLAG_M | UTOOL_FLAG_P)) {
		utool_err_msg("The ubctl ecc_2b command must be in the following formats:\n"
			      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m ecc_2b -p ${port}\n");
		return UTOOL_ERR_CMD_NOT_FOUND;
	}

	return utool_ecc_2b_cmd(dev, param);
}

struct utool_field_info *utool_ecc_2b_cmd_diff_ver_dispatch(const char *module_func_name,
							uint32_t reg_version, uint32_t reg_info_index,
							uint32_t *replace_field_cnt)
{
	uint32_t i;

	if (module_func_name == NULL || module_func_name[0] == '\0') {
		utool_err_msg("Module func name is invalid.\n");
		return NULL;
	}

	for (i = 0; i < UTOOL_ARRAY_SIZE(g_utool_ecc_2b_diff_version_field_info); i++) {
		if (strcmp(module_func_name, g_utool_ecc_2b_diff_version_field_info[i].module_func_name) != 0) {
			continue;
		}

		if (reg_version != g_utool_ecc_2b_diff_version_field_info[i].reg_version) {
			continue;
		}

		if (reg_info_index == g_utool_ecc_2b_diff_version_field_info[i].reg_info_index) {
			*replace_field_cnt = g_utool_ecc_2b_diff_version_field_info[i].replace_field_cnt;
			return g_utool_ecc_2b_diff_version_field_info[i].replace_field_info;
		}
	}

	return NULL;
}
