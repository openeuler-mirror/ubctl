// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_port_pkt.h"

static struct utool_field_info g_utool_uboe_pkt_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "is_uboe_port" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_ipv4_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_ipv6_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ipv4_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ipv6_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_compact_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_umoc_ctph_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_umoc_ntph_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_mem_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unknown_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "drop_ind_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "err_ind_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_host_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_imp_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_mar_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_link_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_noc_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "route_err_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "out_err_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "length_err_cnt(rx)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_busi_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_busi_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_send_ack_flit" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_send_ack_flit" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_ipv4_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_ipv6_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ipv4_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ipv6_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_compact_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_umoc_ctph_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_umoc_ntph_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_mem_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unknown_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "drop_ind_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "err_ind_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lpbk_ind_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "out_err_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "length_err_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_busi_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_busi_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_recv_ack_flit" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_recv_ack_flit" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "retry_req_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "retry_req_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "retry_ack_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "retry_ack_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "crc_error_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "crc_error_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "core_mib_rxpausepkts" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "core_mib_rxpausepkts" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "core_mib_txpausepkts" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "core_mib_txpausepkts" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "core_mib_rxpfcpkts" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "core_mib_rxpfcpkts" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "core_mib_txpfcpkts" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "core_mib_txpfcpkts" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "core_mib_rxbadpkts" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "core_mib_rxbadpkts" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "core_mib_txbadpkts" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "core_mib_txbadpkts" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "core_mib_rxbadoctets" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "core_mib_rxbadoctets" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "core_mib_txbadoctets" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "core_mib_txbadoctets" },
};

static struct utool_field_info g_utool_ub_pkt_field_info[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "is_uboe_port" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_ipv4_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_ipv6_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ipv4_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ipv6_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_compact_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_umoc_ctph_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_umoc_ntph_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_mem_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unknown_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "drop_ind_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "err_ind_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_host_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_imp_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_mar_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_link_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "to_noc_pkt_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "route_err_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "out_err_cnt(rx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "length_err_cnt(rx)" },
	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_busi_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_busi_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "rx_send_ack_flit" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "rx_send_ack_flit" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_ipv4_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_ipv6_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ipv4_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unic_ipv6_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_compact_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_umoc_ctph_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_umoc_ntph_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "ub_mem_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "unknown_pkt_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "drop_ind_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "err_ind_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "lpbk_ind_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "out_err_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "length_err_cnt(tx)" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_busi_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_busi_flit_num" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tx_recv_ack_flit" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "tx_recv_ack_flit" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "retry_req_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "retry_req_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "retry_ack_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "retry_ack_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "crc_error_sum" },
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_1, "crc_error_sum" },
};

static int utool_port_pkt_cal_data_len(uint32_t *port_data_len)
{
	uint32_t port_reg_cnt = 0;
	int ret = UTOOL_OK;

	if (port_data_len == NULL) {
		utool_err_msg("Param is invalid, port data len is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_cal_reg_cnt(g_utool_uboe_pkt_field_info,
				UTOOL_ARRAY_SIZE(g_utool_uboe_pkt_field_info), &port_reg_cnt);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate port pkt stats reg cnt.\n");
		return ret;
	}

	*port_data_len = port_reg_cnt * sizeof(uint32_t);
	return UTOOL_OK;
}

static int utool_port_pkt_parse_rpc_pkt(struct fwctl_rpc_ub_out *port_out)
{
#define UTOOL_WHETHER_UBOE_IDX 1

	int ret = UTOOL_OK;

	if (port_out == NULL) {
		utool_err_msg("Failed to parse port pkt stats rpc pkt, port out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (port_out->data[UTOOL_WHETHER_UBOE_IDX]) {
		ret = utool_pkt_parse(port_out,
				      UTOOL_ARRAY_SIZE(g_utool_uboe_pkt_field_info),
				      g_utool_uboe_pkt_field_info, UTOOL_MODULE_PORT_PKT_STATS);
	} else {
		ret = utool_pkt_parse(port_out,
				      UTOOL_ARRAY_SIZE(g_utool_ub_pkt_field_info),
				      g_utool_ub_pkt_field_info, UTOOL_MODULE_PORT_PKT_STATS);
	}
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse port pkt stats data.\n");
	}

	return ret;
}

static int utool_port_pkt_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
			      struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec port_pkt_exec = { UTOOL_CMD_QUERY_PORT_PKT_STATS, 0, NULL };
	int ret = UTOOL_OK;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	ret = utool_port_pkt_cal_data_len(&port_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to cal port pkt stats reg cnt.\n");
		return ret;
	}

	port_pkt_exec.execute = utool_port_pkt_parse_rpc_pkt;

	ret = utool_pkt_operation_have_port(dev, param, &port_pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	return ret;
}

int utool_port_pkt_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_port_pkt_cmd_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_P, utool_port_pkt_cmd, NULL, 0 }
	};
	uint32_t port_pkt_cmd_cnt = UTOOL_ARRAY_SIZE(utool_port_pkt_cmd_table);
	uint32_t i = 0;

	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < port_pkt_cmd_cnt; i++) {
		if (param->flags == utool_port_pkt_cmd_table[i].flags) {
			if (utool_port_pkt_cmd_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch. Callback is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

		return utool_port_pkt_cmd_table[i].execute(dev, param, utool_port_pkt_cmd_table[i].func_table,
							   utool_port_pkt_cmd_table[i].func_cnt);
		}
	}

	utool_err_msg("The ubctl port_pkt_stats command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m port_pkt_stats -p ${port}\n");

	return UTOOL_ERR_CMD_NOT_FOUND;
}
