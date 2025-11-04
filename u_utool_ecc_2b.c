// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_ecc_2b.h"

static struct utool_field_info g_utool_ecc_2b_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_0(BA)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_1(BA)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_2(BA)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_3(BA)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_4(BA)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_5(BA)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_6(BA)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_7(BA)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC10, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "mar_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "mar_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccum_imm_b0_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccum_imm_b1_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccum_imm_b2_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccum_imm_b3_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccum_imm_b4_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccum_imm_b5_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccum_imm_b6_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccum_imm_b7_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccum_xn_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccum_gsa_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccum_lc_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccum_ckb_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccum_tifmbuf_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccum_tifcmt_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccum_tifjc_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccum_tifwbuf_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccum_tifptm_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccum_pru_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccum_sifdbuf_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccum_tifpvm_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_0(CCU)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_1(CCU)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_2(CCU)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_3(CCU)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_4(CCU)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_5(CCU)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_6(CCU)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "master_ram_ecc_2b_addr_7(CCU)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_msm_b0_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_msm_b1_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_msm_b2_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_msm_b3_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_msm_b4_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_msm_b5_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_msm_b6_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_msm_b7_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_msm_b8_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_msm_b9_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_msm_b10_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_msm_b11_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_msm_b12_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_msm_b13_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_msm_b14_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_msm_b15_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_cip_b0_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_cip_b1_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_cip_b2_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_cip_b3_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_cip_b4_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_cip_b5_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_cip_b6_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_cip_b7_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_cip_b8_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_cip_b9_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_cip_b10_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_cip_b11_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_cip_b12_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_cip_b13_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "ccua_cip_b14_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ccua_cip_b15_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "dl_retry_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC11, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC26, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC25, UTOOL_FIELD_INDEX_START, "dl_pmu_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ppp_nl_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "mrd_mb_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "mrd_rdata_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "eip_int_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "eip_db_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "eip_ba_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC10, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC9, UTOOL_FIELD_INDEX_START, "cqm_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC27, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC26, UTOOL_FIELD_INDEX_START, "tom_fifo_inf_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "tom_fifo_tl_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "tom_r_data_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "tom_rd_data_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rsp_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC26, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC25, UTOOL_FIELD_INDEX_START, "tqc_reorder_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "tqc_we_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "tqc_wm_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "tqc_ro_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tqms_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tqeb_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dm_ram_ecc_2b_addr(LQC_TA_DM)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "usi_ram_ecc_2b_addr(LQC_TA_USI)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "dm_ram_ecc_2b_addr(LQC_TA_IDEV)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "usi_ram_ecc_2b_addr(LQC_TA_RIG)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC24, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC18, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "tp_timer_fifo_inf_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC12, UTOOL_REG_LOC17, UTOOL_FIELD_INDEX_START, "tp_timer_fifo_tl_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC11, UTOOL_FIELD_INDEX_START, "tp_timer_r_data_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "tp_timer_rd_data_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "scc_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "scc_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC14, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "tqem_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "tqem_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "tqs_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tqs_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "tai_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tai_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC21, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC20, UTOOL_FIELD_INDEX_START, "extq_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "extq_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tpp_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tpp_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tpp_ram_ecc_2b_ram_id_1" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tpp_ram_ecc_2b_addr_1" },
	{ false, true, UTOOL_REG_LOC14, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC8, UTOOL_REG_LOC13, UTOOL_FIELD_INDEX_START, "tprxp_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "tprxp_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC8, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC6, UTOOL_REG_LOC7, UTOOL_FIELD_INDEX_START, "rqm_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC5, UTOOL_FIELD_INDEX_START, "rqm_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC19, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "cache_ecc_2bit_eaddr(DAM)" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "cache_ecc_2bit_err_id(DAM)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC19, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "cache_ecc_2bit_eaddr(EUM)" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "cache_ecc_2bit_err_id(EUM)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC19, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "cache_ecc_2bit_eaddr(TPCM)" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "cache_ecc_2bit_err_id(TPCM)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC19, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "cache_ecc_2bit_eaddr(TPGCM)" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "cache_ecc_2bit_err_id(TPGCM)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC19, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC5, UTOOL_REG_LOC18, UTOOL_FIELD_INDEX_START, "cache_ecc_2bit_eaddr(TPMM)" },
	{ false, false, UTOOL_REG_LOC1, UTOOL_REG_LOC4, UTOOL_FIELD_INDEX_START, "cache_ecc_2bit_err_id(TPMM)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC0, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC20, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC19, UTOOL_FIELD_INDEX_START, "lrb_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "lrb_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tp_lsa_req_ram_ecc_2b_ram_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "tp_lsa_req_ram_ecc_2b_addr" },
	{ false, false, UTOOL_REG_LOC16, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ubommu_ram_ecc_2b_addr" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC15, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
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
