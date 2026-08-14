// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "../common/u_utool_error.h"
#include "../u_utool_pkt.h"
#include "u_utool_upa.h"

#define UPA_PKT_STATS "pkt_stats"

static struct utool_field_info g_utool_upa_pkt_stats_info[] = {
	// opcode:0xA039
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_num" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "port_num" },
	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "upa_bway_txreq_req_recycle_cnt_clr" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "upa_bway_txreq_req_drop_cnt_clr" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "upa_bway_txreq_req_send_cnt_clr" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "upa_bway_txreq_req_in_cnt_clr" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_bway_txreq_req_in_norm_cnt_clr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_bway_txreq_cnt_clr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_bway_txreq_req_in_norm_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_bway_txreq_req_in_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_bway_txreq_req_send_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_bway_txreq_req_drop_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_bway_txreq_req_recycle_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_bway_txreq_req_out_cnt" },
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC23, 0, UTOOL_CAP_3, "upa_dfx_nl_crdt_num" },
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC23, 0, UTOOL_CAP_3, "upa_dfx_nl_req_crdt_num" },
	{ false, true, UTOOL_LOC6, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC5, 0, UTOOL_CAP_3, "upa_dfx_nl_crdt_timout_st" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_tx_dl_req_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_tx_dl_dat_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_tx_dl_rsp_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_tx_dl_req_drop_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_tx_dl_dat_all_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_tx_dl_dat_drop_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_tx_dl_rsp_drop_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_tx_dl_flit_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_req_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_dat_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_rsp_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_req_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_dat_pkt_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_rsp_pkt_cnt" },

	// opcode:0xA03A
	{ false, true, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC7, UTOOL_LOC7, 0, UTOOL_CAP_3, "upa_dfx_rxsnp_lcrd_full" },
	{ false, false, UTOOL_LOC6, UTOOL_LOC6, 0, UTOOL_CAP_3, "upa_dfx_rxsnp_lcrd_empty" },
	{ false, false, UTOOL_LOC5, UTOOL_LOC5, 0, UTOOL_CAP_3, "upa_dfx_rxrsp_lcrd_full" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC4, 0, UTOOL_CAP_3, "upa_dfx_rxrsp_lcrd_empty" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "upa_dfx_rxreq_lcrd_full" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "upa_dfx_rxreq_lcrd_empty" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_rxdat_lcrd_full" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_rxdat_lcrd_empty" },
	{ false, true, UTOOL_LOC29, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC28, 0, UTOOL_CAP_3, "upa_sky_rxbuf_rxsnp_crd_cnt" },
	{ false, true, UTOOL_LOC21, UTOOL_LOC23, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC20, 0, UTOOL_CAP_3, "upa_sky_rxbuf_rxrsp_crd_cnt" },
	{ false, true, UTOOL_LOC13, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC12, 0, UTOOL_CAP_3, "upa_sky_rxbuf_rxdat_crd_cnt" },
	{ false, true, UTOOL_LOC5, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC4, 0, UTOOL_CAP_3, "upa_sky_rxbuf_rxreq_crd_cnt" },
	{ false, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "upa_dfx_rxbuf_order_bank_cnt_en" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_rxbuf_order_bank_cnt_clr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_rxbuf_order_bank_cnt_rd" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_req_in_cnt(upa_dfx_rxbuf_order_bank_cnt_id0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_vld_cnt(upa_dfx_rxbuf_order_bank_cnt_id0)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_req_in_cnt(upa_dfx_rxbuf_order_bank_cnt_id1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_vld_cnt(upa_dfx_rxbuf_order_bank_cnt_id1)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_req_in_cnt(upa_dfx_rxbuf_order_bank_cnt_id2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_vld_cnt(upa_dfx_rxbuf_order_bank_cnt_id2)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_req_in_cnt(upa_dfx_rxbuf_order_bank_cnt_id3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_vld_cnt(upa_dfx_rxbuf_order_bank_cnt_id3)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_block_cnt(upa_dfx_rxbuf_order_bank_cnt_id0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_rls_cnt(upa_dfx_rxbuf_order_bank_cnt_id0)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_block_cnt(upa_dfx_rxbuf_order_bank_cnt_id1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_rls_cnt(upa_dfx_rxbuf_order_bank_cnt_id1)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_block_cnt(upa_dfx_rxbuf_order_bank_cnt_id2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_rls_cnt(upa_dfx_rxbuf_order_bank_cnt_id2)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_block_cnt(upa_dfx_rxbuf_order_bank_cnt_id3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC15, 0, UTOOL_CAP_3,
	  "upa_dfx_rxbuf_order_bank_rls_cnt(upa_dfx_rxbuf_order_bank_cnt_id3)" },
	{ false, true, UTOOL_LOC13, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC12, 0, UTOOL_CAP_3, "upa_dfx_sky2axi_rxreq_fifo_cnt" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_sky2axi_rxreq_fifo_empty" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_sky2axi_rxreq_fifo_full" },
	{ false, true, UTOOL_LOC13, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC12, 0, UTOOL_CAP_3, "upa_dfx_sky2axi_rxdat_fifo_cnt" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_sky2axi_rxdat_fifo_empty" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_sky2axi_rxdat_fifo_full" },
	{ false, true, UTOOL_LOC13, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC12, 0, UTOOL_CAP_3, "upa_dfx_sky2axi_rxrsp_fifo_cnt" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_sky2axi_rxrsp_fifo_empty" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_sky2axi_rxrsp_fifo_full" },
	{ false, true, UTOOL_LOC13, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC12, 0, UTOOL_CAP_3, "upa_dfx_sky2axi_rxsnp_fifo_cnt" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_sky2axi_rxsnp_fifo_empty" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_sky2axi_rxsnp_fifo_full" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_sky_rxreq_prefetchtgt_drop_cnt" },
	{ false, true, UTOOL_LOC13, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC12, 0, UTOOL_CAP_3, "upa_dfx_so_outstanding_sameid" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_so_outstanding_sameid_rpt" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_bway_txreq_timeout_check_en" },
	{ false, true, UTOOL_LOC17, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC16, 0, UTOOL_CAP_3, "upa_bway_txreq_queue_dat_addr" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_bway_txreq_queue_dat_rd" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_bway_txreq_queue_dat_data" },
	{ false, true, UTOOL_LOC17, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC16, 0, UTOOL_CAP_3, "upa_bway_txreq_mem_cmd_addr" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_bway_txreq_mem_cmd_rd_done" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_bway_txreq_mem_cmd_rd" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_bway_txreq_mem_cmd_data(bway_txreq_mem_cmd_id0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_bway_txreq_mem_cmd_data(bway_txreq_mem_cmd_id1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_bway_txreq_mem_cmd_data(bway_txreq_mem_cmd_id2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_bway_txreq_mem_cmd_data(bway_txreq_mem_cmd_id3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_bway_txreq_mem_cmd_data(bway_txreq_mem_cmd_id4)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_bway_txreq_mem_cmd_data(bway_txreq_mem_cmd_id5)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_bway_txreq_mem_cmd_data(bway_txreq_mem_cmd_id6)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_bway_txreq_mem_cmd_data(bway_txreq_mem_cmd_id7)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_bway_txreq_mem_cmd_data(bway_txreq_mem_cmd_id8)" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dat_id_cnt_com_3" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_3, "upa_dat_id_cnt_com_2" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_3, "upa_dat_id_cnt_com_1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3, "upa_dat_id_cnt_com_0" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dat_id_cnt_rsv_vc_3" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_3, "upa_dat_id_cnt_rsv_vc_2" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_3, "upa_dat_id_cnt_rsv_vc_1" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3, "upa_dat_id_cnt_rsv_vc_0" },
	{ false, true, UTOOL_LOC10, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC9, 0, UTOOL_CAP_3, "upa_bway_txreq_retry_bank_choose" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_bway_txreq_retry_status_clr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_bway_txreq_retry_status(upa_bway_txreq_retry_status_id0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_bway_txreq_retry_status(upa_bway_txreq_retry_status_id1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_bway_txreq_retry_status(upa_bway_txreq_retry_status_id2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_bway_txreq_retry_status(upa_bway_txreq_retry_status_id3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_recv_reqdat_flit(dat_flit_num0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_recv_reqdat_flit(dat_flit_num1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_recv_reqdat_flit(dat_flit_num2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_recv_reqdat_flit(dat_flit_num3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_recv_reqdat_flit(dat_flit_num4)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_recv_reqdat_flit(dat_flit_num5)" },
	{ false, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "upa_dfx_bway_wrdat_err_rpt_vld" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_bway_wrdat_err_rpt_clr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_bway_wrdat_err_rpt_mode" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_bway_wrdat_err_rpt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_bway_wrdat_err_rpt_flit(bway_wrdat_poison_rpt_flit_id0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_bway_wrdat_err_rpt_flit(bway_wrdat_poison_rpt_flit_id1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_bway_wrdat_err_rpt_flit(bway_wrdat_poison_rpt_flit_id2)" },
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC8, 0, UTOOL_CAP_3, "upa_rps_dfx_entry_idx(rps_bank_num0)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_rps_dfx_clr(rps_bank_num0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_rps_dfx_mode(rps_bank_num0)" },
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC8, 0, UTOOL_CAP_3, "upa_rps_dfx_entry_idx(rps_bank_num1)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_rps_dfx_clr(rps_bank_num1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_rps_dfx_mode(rps_bank_num1)" },
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC8, 0, UTOOL_CAP_3, "upa_rps_dfx_entry_idx(rps_bank_num2)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_rps_dfx_clr(rps_bank_num2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_rps_dfx_mode(rps_bank_num2)" },
	{ false, true, UTOOL_LOC9, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC8, 0, UTOOL_CAP_3, "upa_rps_dfx_entry_idx(rps_bank_num3)" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_rps_dfx_clr(rps_bank_num3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_rps_dfx_mode(rps_bank_num3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_ghost_num(rps_bank_num0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_ghost_num(rps_bank_num1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_ghost_num(rps_bank_num2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_ghost_num(rps_bank_num3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_timeout_num(rps_bank_num0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_timeout_num(rps_bank_num1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_timeout_num(rps_bank_num2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_timeout_num(rps_bank_num3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_err_infoh(rps_bank_num0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_err_infoh(rps_bank_num1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_err_infoh(rps_bank_num2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_err_infoh(rps_bank_num3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_err_infol(rps_bank_num0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_err_infol(rps_bank_num1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_err_infol(rps_bank_num2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_err_infol(rps_bank_num3)" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC27, 0, UTOOL_CAP_3, "upa_dfx_rps_entry_roundid(rps_bank_num0)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC20, 0, UTOOL_CAP_3, "upa_dfx_rps_entry_fsm(rps_bank_num0)" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_rps_bank_idle(rps_bank_num0)" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC27, 0, UTOOL_CAP_3, "upa_dfx_rps_entry_roundid(rps_bank_num1)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC20, 0, UTOOL_CAP_3, "upa_dfx_rps_entry_fsm(rps_bank_num1)" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_rps_bank_idle(rps_bank_num1)" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC27, 0, UTOOL_CAP_3, "upa_dfx_rps_entry_roundid(rps_bank_num2)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC20, 0, UTOOL_CAP_3, "upa_dfx_rps_entry_fsm(rps_bank_num2)" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_rps_bank_idle(rps_bank_num2)" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC21, UTOOL_LOC27, 0, UTOOL_CAP_3, "upa_dfx_rps_entry_roundid(rps_bank_num3)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC20, 0, UTOOL_CAP_3, "upa_dfx_rps_entry_fsm(rps_bank_num3)" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_rps_bank_idle(rps_bank_num3)" },
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_3, "upa_txdat_buf_used_num_port1(sky_txreq_bank_id0)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_3, "upa_txdat_buf_used_num_port0(sky_txreq_bank_id0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3, "upa_txdat_buf_idle_num(sky_txreq_bank_id0)" },
	{ false, true, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_3, "upa_txdat_buf_used_num_port1(sky_txreq_bank_id1)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_3, "upa_txdat_buf_used_num_port0(sky_txreq_bank_id1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3, "upa_txdat_buf_idle_num(sky_txreq_bank_id1)" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3, "upa_txrsp_buf_idle_num(sky_txreq_bank_id0)" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3, "upa_txrsp_buf_idle_num(sky_txreq_bank_id1)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_3, "upa_txdat_buf_used_num_vc1(sky_txreq_bank_id0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3, "upa_txdat_buf_used_num_vc0(sky_txreq_bank_id0)" },
	{ false, true, UTOOL_LOC16, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_3, "upa_txdat_buf_used_num_vc1(sky_txreq_bank_id1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3, "upa_txdat_buf_used_num_vc0(sky_txreq_bank_id1)" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_txdat_buf_used_num_port1_vc1(sky_txreq_bank_id0)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_3,
	  "upa_txdat_buf_used_num_port1_vc0(sky_txreq_bank_id0)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_3,
	  "upa_txdat_buf_used_num_port0_vc1(sky_txreq_bank_id0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3,
	  "upa_txdat_buf_used_num_port0_vc0(sky_txreq_bank_id0)" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_txdat_buf_used_num_port1_vc1(sky_txreq_bank_id1)" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC23, 0, UTOOL_CAP_3,
	  "upa_txdat_buf_used_num_port1_vc0(sky_txreq_bank_id1)" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_3,
	  "upa_txdat_buf_used_num_port0_vc1(sky_txreq_bank_id1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC7, 0, UTOOL_CAP_3,
	  "upa_txdat_buf_used_num_port0_vc0(sky_txreq_bank_id1)" },
	{ false, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "upa_dfx_sky_txdat_err_rpt_vld" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_sky_txdat_err_rpt_clr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_sky_txdat_err_rpt_mode" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_sky_txdat_err_rpt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_sky_txdat_err_rpt_flit(sky_txdat_err_rpt_flit_id0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_sky_txdat_err_rpt_flit(sky_txdat_err_rpt_flit_id1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_sky_txdat_err_rpt_flit(sky_txdat_err_rpt_flit_id2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_sky_txdat_err_rpt_flit(sky_txdat_err_rpt_flit_id3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_sky_txdat_err_rpt_flit(sky_txdat_err_rpt_flit_id4)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_sky_txdat_err_rpt_flit(sky_txdat_err_rpt_flit_id5)" },
	{ false, true, UTOOL_LOC3, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC2, UTOOL_LOC2, 0, UTOOL_CAP_3, "upa_dfx_sky_txrsp_err_rpt_vld" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_sky_txrsp_err_rpt_clr" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_sky_txrsp_err_rpt_mode" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_sky_txrsp_err_rpt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_sky_txrsp_err_rpt_flit(sky_txrsp_err_rpt_flit_id0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_sky_txrsp_err_rpt_flit(sky_txrsp_err_rpt_flit_id1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3,
	  "upa_dfx_sky_txrsp_err_rpt_flit(sky_txrsp_err_rpt_flit_id2)" },
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_3, "upa_dfx_axi2sky_txreq_fifo_cnt" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_axi2sky_txreq_fifo_empty" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_axi2sky_txreq_fifo_full" },
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_3, "upa_dfx_axi2sky_txdat_fifo_cnt" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_axi2sky_txdat_fifo_empty" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_axi2sky_txdat_fifo_full" },
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_3, "upa_dfx_axi2sky_txrsp_fifo_cnt" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_axi2sky_txrsp_fifo_empty" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_axi2sky_txrsp_fifo_full" },
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_3, "upa_dfx_axi2sky_txsnp_fifo_cnt" },
	{ false, true, UTOOL_LOC2, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC1, UTOOL_LOC1, 0, UTOOL_CAP_3, "upa_dfx_axi2sky_txsnp_fifo_empty" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_dfx_axi2sky_txsnp_fifo_full" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC3, UTOOL_LOC3, 0, UTOOL_CAP_3, "upa_dfx_rx_hbps_req_fifo_not_empty" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC2, 0, UTOOL_CAP_3, "upa_dfx_rx_hbps_dat_fifo_not_empty" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC24, UTOOL_LOC27, 0, UTOOL_CAP_3, "upa_sky_txbuf_txsnp_crd_cnt" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC23, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_3, "upa_sky_txbuf_txrsp_crd_cnt" },
	{ false, true, UTOOL_LOC12, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_3, "upa_sky_txbuf_txdat_crd_cnt" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_3, "upa_sky_txbuf_txreq_crd_cnt" },
	{ false, true, UTOOL_LOC20, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC19, 0, UTOOL_CAP_3, "upa_dfx_bway_txdat_idle" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_3, "upa_dfx_txdat_fifo_full" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_3, "upa_dfx_txdat_fifo_empty" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_upa2dl_crdt_num" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_3, "upa_dfx_txsche_hbps_fifo_full" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_3, "upa_dfx_txsche_hbps_fifo_empty" },
	{ false, true, UTOOL_LOC8, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_3, "upa_dfx_txsche_lbps_fifo_full" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_3, "upa_dfx_txsche_lbps_fifo_empty" },
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_3, "upa_dfx_nl2upatx_port_bp" },
	{ false, true, UTOOL_LOC28, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC16, UTOOL_LOC27, 0, UTOOL_CAP_3, "upa_dfx_nl_crdt_vld" },
	{ false, true, UTOOL_LOC12, UTOOL_LOC15, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC11, 0, UTOOL_CAP_3, "upa_dfx_nl_crdt_rdy" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_3, "upa_dfx_bway_txsch_idle" },
	{ false, true, UTOOL_LOC1, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC0, 0, UTOOL_CAP_3, "upa_data_mem_ecc_err_en" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_skyros_txreq_flit_count" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_skyros_rxdat_comp_flit_count" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_skyros_txrsp_flit_count" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_skyros_txdat_flit_count" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_skyros_rxreq_flit_count" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_skyros_rxrsp_flit_count" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_skyros_rxsnp_flit_count" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_skyros_rxdat_flit_count" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_vl_pkt_cnt(vc_num0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_vl_pkt_cnt(vc_num1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_vl_pkt_cnt(vc_num2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_vl_pkt_cnt(vc_num3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_vl_pkt_cnt(vc_num4)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_vl_pkt_cnt(vc_num5)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_vl_pkt_cnt(vc_num6)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_vl_pkt_cnt(vc_num7)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_vl_pkt_cnt(vc_num8)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_vl_pkt_cnt(vc_num9)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_vl_pkt_cnt(vc_num10)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_dl_vl_pkt_cnt(vc_num11)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_vl_pkt_cnt(vc_num0)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_vl_pkt_cnt(vc_num1)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_vl_pkt_cnt(vc_num2)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_vl_pkt_cnt(vc_num3)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_vl_pkt_cnt(vc_num4)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_vl_pkt_cnt(vc_num5)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_vl_pkt_cnt(vc_num6)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_vl_pkt_cnt(vc_num7)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_vl_pkt_cnt(vc_num8)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_vl_pkt_cnt(vc_num9)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_vl_pkt_cnt(vc_num10)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rx_nl_vl_pkt_cnt(vc_num11)" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_sky_txreq_comp_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_bwy_txreq_comp_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_rd_data_cnt" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC31, 0, UTOOL_CAP_3, "upa_dfx_rps_comp_cnt" },
	{ false, true, UTOOL_LOC12, UTOOL_LOC31, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC8, UTOOL_LOC11, 0, UTOOL_CAP_3, "upa_link_up" },
	{ false, true, UTOOL_LOC4, UTOOL_LOC7, 0, UTOOL_CAP_3, "reserved" },
	{ false, false, UTOOL_LOC0, UTOOL_LOC3, 0, UTOOL_CAP_3, "upa_link_idle" },
};

static struct utool_cal_reg_cnt_dp g_utool_upa_cal_reg_table[] = {
	{ true, false, UPA_PKT_STATS, UTOOL_ARRAY_SIZE(g_utool_upa_pkt_stats_info), g_utool_upa_pkt_stats_info },
};

static int utool_upa_parse_pkt_stats(struct fwctl_rpc_ub_out *upa_out)
{
	int ret = UTOOL_OK;

	ret = utool_pkt_parse(upa_out, UTOOL_ARRAY_SIZE(g_utool_upa_pkt_stats_info),
			      g_utool_upa_pkt_stats_info, UTOOL_CONCAT_STR(UTOOL_MODULE_UPA, UPA_PKT_STATS));
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse upa pkt stats data.\n");
	}

	return ret;
}

static struct utool_func_dispatch g_utool_upa_func_table[] = {
	{ false, UPA_PKT_STATS, UTOOL_CMD_QUERY_UPA_PKT_STATS, UTOOL_REG_CNT_DEFAULT,
	  utool_upa_parse_pkt_stats, utool_upa_port_create_pkt_in },
};

static void utool_upa_print_help(void)
{
	utool_err_msg("The ubctl upa command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m upa -f pkt_stats -u ${upa_num} -p ${port_num}\n");
}

static int utool_upa_check_param(struct utool_cmd_param *param)
{
#define UTOOL_UPA_PORT_NUM_MAX_VALUE 3U
#define UTOOL_UPA_NUM_MAX_VALUE 1U

	if (strcmp(param->func, UPA_PKT_STATS) == 0) {
		if (param->port > UTOOL_UPA_PORT_NUM_MAX_VALUE) {
			utool_err_msg("Param port_num = %u is invalid, it must be in [0, %u].\n",
				      param->port, UTOOL_UPA_PORT_NUM_MAX_VALUE);
			return UTOOL_ERR_INVALID_PARAM;
		}
		if (param->ummu_id > UTOOL_UPA_NUM_MAX_VALUE) {
			utool_err_msg("Param upa_num = %u is invalid, it must be in [0, %u].\n",
				      param->ummu_id, UTOOL_UPA_NUM_MAX_VALUE);
			return UTOOL_ERR_INVALID_PARAM;
		}
	}

	return UTOOL_OK;
}

static int utool_upa_cmd_func(struct utool_dev *dev, struct utool_cmd_param *param,
			      struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec func_pkt_exec = { UTOOL_CMD_QUERY_MAX, 0, NULL };
	struct utool_cal_reg_func_param upa_cal_reg_param = {
		NULL, 0, NULL, g_utool_upa_cal_reg_table, UTOOL_ARRAY_SIZE(g_utool_upa_cal_reg_table)
	};
	uint32_t pkt_in_len = 0;
	void *pkt_in;
	uint32_t i;
	int ret;

	ret = utool_upa_check_param(param);
	if (ret != UTOOL_OK) {
		return ret;
	}

	for (i = 0; i < func_cnt; i++) {
		if (strcmp(param->func, func_table[i].func) == 0) {
			func_pkt_exec.rpc_cmd = func_table[i].rpc_cmd;
			func_pkt_exec.execute = func_table[i].execute;

			upa_cal_reg_param.data_len = &func_pkt_exec.data_len;
			upa_cal_reg_param.user_def_data_len = func_table[i].data_len;

			ret = utool_cal_func_reg_len(param->func, &upa_cal_reg_param);
			if (ret != UTOOL_OK) {
				utool_err_msg("Failed to calculate reg cnt of upa func %s.\n", param->func);
				return ret;
			}

			if (func_table[i].create_pkt_in == NULL) {
				utool_err_msg("Failed to create upa func pkt in, callback is NULL.\n");
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
	utool_upa_print_help();

	return UTOOL_ERR_FUNC_NOT_FOUND;
}

int utool_upa_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_upa_cmd_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_F | UTOOL_FLAG_U | UTOOL_FLAG_P, utool_upa_cmd_func,
		  g_utool_upa_func_table, UTOOL_ARRAY_SIZE(g_utool_upa_func_table) },
	};
	uint32_t upa_cmd_cnt = UTOOL_ARRAY_SIZE(utool_upa_cmd_table);
	uint32_t i;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < upa_cmd_cnt; i++) {
		if (param->flags == utool_upa_cmd_table[i].flags) {
			if (utool_upa_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch. Callback is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

			return utool_upa_cmd_table[i].execute(dev, param,
							      utool_upa_cmd_table[i].func_table,
							      utool_upa_cmd_table[i].func_cnt);
		}
	}

	utool_upa_print_help();

	return UTOOL_ERR_CMD_NOT_FOUND;
}
