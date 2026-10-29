/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2026 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_API_H__
#define __U_UTOOL_API_H__

#include <stdbool.h>
#include <stdint.h>

#define UBCTL_USER_CMD_COMM 0x0001
#define UBCTL_QUERY_DSCP_CMD_COMM 0x0002
#define UBCTL_QUERY_SL_VL_MAP_CMD_COMM 0x0003
#define UBCTL_QUERY_CAPS_CMD_COMM 0x0004
#define UBCTL_QUERY_AEQC_CMD_COMM 0x0005
#define UBCTL_QUERY_CEQC_CMD_COMM 0x0006
#define UBCTL_LS_CMD_COMM 0x0007
#define UBCTL_QUERY_PORT_INFO_CMD_COMM 0x0008
#define UBCTL_QUERY_PERFORMANCE_CMD_COMM 0x0009
#define UBCTL_QUERY_RT_BANDWIDTH_CMD_COMM 0x000A
#define UBCTL_QUERY_PORT_PKT_STATS_COMM 0x000B
#define UBCTL_QUERY_FW_VERSION_COMM 0x000C
#define UBCTL_QUERY_PORT_LINK_COMM 0x000D
#define UBCTL_CONFIG_PERF_START_COMM 0x00E
#define UBCTL_QUERY_PERF_COMM 0x00F
#define UBCTL_CONFIG_PERF_END_COMM 0x0010
#define UBCTL_CONFIG_RXMAC2TXMAC_COMM 0x0011
#define UBCTL_QUERY_RXMAC2TXMAC_COMM 0x0012
#define UBCTL_CONFIG_TXMAC2RXMAC_COMM 0x0013
#define UBCTL_QUERY_TXMAC2RXMAC_COMM 0x0014
#define UBCTL_CONFIG_TXPCS2RXPCS_COMM 0x0015
#define UBCTL_QUERY_TXPCS2RXPCS_COMM 0x0016
#define UBCTL_CONFIG_SSU_VL_PKT_COMM 0x0017
#define UBCTL_QUERY_SSU_VL_PKT_COMM 0x0018

#define UBCTL_UBASE_MAX_DSCP 64
#define UBCTL_UBASE_MAX_SL_NUM 16
#define UBCTL_RXDMA_QUEUE_NUM 4
#define UTOOL_LINK_PROC_ERR_STATE_SIZE 15
#define UTOOL_API_MAX_PORT_LINK_STATUS 10U

struct ubctl_cmd_buf {
	unsigned short opcode;
	bool is_read;
	unsigned int data_size;
	void *data;
};

struct ubctl_icrc_info {
	uint32_t port_id;
	uint32_t data[UBCTL_RXDMA_QUEUE_NUM];
};

struct ubctl_ubase_dbg_dscp_vl_map {
	uint8_t hw_vl[UBCTL_UBASE_MAX_DSCP];
};

struct ubctl_ubase_dbg_sl_vl_map {
	uint8_t hw_vl[UBCTL_UBASE_MAX_SL_NUM];
};

struct ubctl_ubase_dbg_caps_info {
	uint16_t aeq_num;
	uint16_t ceq_num;
	uint16_t aeq_ctx_size;
	uint16_t ceq_ctx_size;
	uint16_t die_id;
	uint16_t io_port_logic_id;
};

struct fwctl_port_info_api_struct {
	uint32_t port_id;
	uint32_t link_status;
	uint32_t link_state_info;
	uint32_t port_type;
	uint32_t reserved[2];
};

struct fwctl_io_die_info_api_struct {
	uint32_t port_count;
	uint32_t chip_id;
	uint32_t die_id;
	uint32_t reserved[3];
	struct fwctl_port_info_api_struct port_info[];
};

struct utool_port_head {
	uint32_t port_id;
	uint16_t query_type;
	uint16_t module_type;
};

struct utool_mac_dfx_link_state {
	uint16_t cur_state;
	uint16_t err_state[UTOOL_LINK_PROC_ERR_STATE_SIZE];
};

struct utool_port_link_info {
	uint8_t target_speed;
	uint8_t speed_ability_old;
	uint8_t lane_num;
	uint8_t fec;
	uint8_t sds_rate;
	uint8_t port_usage : 1;
	uint8_t port_enable : 1;
	uint8_t port_link : 1;
	uint8_t reserved_0 : 5;
	uint8_t driver_type;
	uint8_t port_mode;
	uint32_t link_down_err;
	struct utool_mac_dfx_link_state mac_link_state;
	uint32_t speed_ability;
};

struct utool_port_dlphy_info {
	uint8_t fec;
	uint8_t phy_mode_ctrl;
	uint8_t sds_rate;
	uint8_t cur_speed;
	uint8_t cur_tx_lane_num : 4;
	uint8_t cur_rx_lane_num : 4;
	uint8_t init_succ_tx_lane_num : 4;
	uint8_t init_succ_rx_lane_num : 4;
	uint8_t port_en : 1;
	uint8_t port_mode : 2;
	uint8_t port_mode_en : 1;
	uint8_t dl_link : 1;
	uint8_t phy_link : 1;
	uint8_t cur_port_type : 1;
	uint8_t reserved_0 : 1;
	uint8_t mac_lstm;
	uint32_t decoded_fail_block_num;
	uint32_t fec_err_low;
	uint32_t retry_cnt;
	uint32_t dl_link_fsm;
	uint32_t fec_err_high;
	uint16_t port_cna;
	uint16_t sds_lpbk_en_bitmap;
	uint32_t clock_freq;
	uint8_t opposite_valid;
	uint8_t opposite;
	uint8_t media_type_valid;
	uint8_t media_type;
};

struct utool_api_rt_bandwidth_info {
	uint32_t port_id;
	uint32_t is_valid;
	uint64_t tx_bandwidth;
	uint64_t rx_bandwidth;
};

union utool_port_info {
	struct utool_port_link_info link_info;
	struct utool_port_dlphy_info dlphy_info;
};

struct utool_port_data {
	struct utool_port_head head;
	union utool_port_info info;
};

enum {
	UTOOL_MODULE_TYPE_NOT_SET = 0,
	UTOOL_MODULE_TYPE_LINK_INFO_ETH = 1,
	UTOOL_MODULE_TYPE_MAC_INFO_ETH = 2,
	UTOOL_MODULE_TYPE_LINK_INFO_UB = 4,
	UTOOL_MODULE_TYPE_MAC_INFO_UB = 8,
};

struct ubctl_port_pkt_stats_data {
	uint32_t port_id;
	uint32_t is_uboe_port;
	uint32_t ub_ipv4_pkt_cnt_rx;
	uint32_t ub_ipv6_pkt_cnt_rx;
	uint32_t unic_ipv4_pkt_cnt_rx;
	uint32_t unic_ipv6_pkt_cnt_rx;
	uint32_t ub_compact_pkt_cnt_rx;
	uint32_t ub_umoc_ctph_cnt_rx;
	uint32_t ub_umoc_ntph_cnt_rx;
	uint32_t ub_mem_pkt_cnt_rx;
	uint32_t unknown_pkt_cnt_rx;
	uint32_t drop_ind_cnt_rx;
	uint32_t err_ind_cnt_rx;
	uint32_t to_host_pkt_cnt_rx;
	uint32_t to_imp_pkt_cnt_rx;
	uint32_t to_mar_pkt_cnt_rx;
	uint32_t to_link_pkt_cnt_rx;
	uint32_t to_noc_pkt_cnt_rx;
	uint32_t route_err_cnt_rx;
	uint32_t out_err_cnt_rx;
	uint32_t length_err_cnt_rx;
	uint32_t reserved_0;
	uint32_t rx_busi_flit_num_low;
	uint32_t rx_busi_flit_num_high;
	uint32_t rx_send_ack_flit_low;
	uint32_t rx_send_ack_flit_high;
	uint32_t ub_ipv4_pkt_cnt_tx;
	uint32_t ub_ipv6_pkt_cnt_tx;
	uint32_t unic_ipv4_pkt_cnt_tx;
	uint32_t unic_ipv6_pkt_cnt_tx;
	uint32_t ub_compact_pkt_cnt_tx;
	uint32_t ub_umoc_ctph_cnt_tx;
	uint32_t ub_umoc_ntph_cnt_tx;
	uint32_t ub_mem_pkt_cnt_tx;
	uint32_t unknown_pkt_cnt_tx;
	uint32_t drop_ind_cnt_tx;
	uint32_t err_ind_cnt_tx;
	uint32_t lpbk_ind_cnt_tx;
	uint32_t out_err_cnt_tx;
	uint32_t length_err_cnt_tx;
	uint32_t tx_busi_flit_num_low;
	uint32_t tx_busi_flit_num_high;
	uint32_t tx_recv_ack_flit_low;
	uint32_t tx_recv_ack_flit_high;

	uint32_t retry_req_sum_low;
	uint32_t retry_req_sum_high;
	uint32_t retry_ack_sum_low;
	uint32_t retry_ack_sum_high;
	uint32_t crc_error_sum_low;
	uint32_t crc_error_sum_high;
	uint32_t core_mib_rxpausepkts_low;
	uint32_t core_mib_rxpausepkts_high;
	uint32_t core_mib_txpausepkts_low;
	uint32_t core_mib_txpausepkts_high;
	uint32_t core_mib_rxpfcpkts_low;
	uint32_t core_mib_rxpfcpkts_high;
	uint32_t core_mib_txpfcpkts_low;
	uint32_t core_mib_txpfcpkts_high;
	uint32_t core_mib_rxbadpkts_low;
	uint32_t core_mib_rxbadpkts_high;
	uint32_t core_mib_txbadpkts_low;
	uint32_t core_mib_txbadpkts_high;
	uint32_t core_mib_rxbadoctets_low;
	uint32_t core_mib_rxbadoctets_high;
	uint32_t core_mib_txbadoctets_low;
	uint32_t core_mib_txbadoctets_high;
};

struct utool_dl_perf_stats {
	uint32_t valid : 1,
		 reserved_0 : 7,
		 port_id : 8,
		 reserved_1 : 16;
	uint32_t tx_port_bw;
	uint32_t rx_port_bw;
	uint32_t tx_vl_bw_0;
	uint32_t tx_vl_bw_1;
	uint32_t tx_vl_bw_2;
	uint32_t tx_vl_bw_3;
	uint32_t tx_vl_bw_4;
	uint32_t tx_vl_bw_5;
	uint32_t tx_vl_bw_6;
	uint32_t tx_vl_bw_7;
	uint32_t tx_vl_bw_8;
	uint32_t tx_vl_bw_9;
	uint32_t tx_vl_bw_10;
	uint32_t tx_vl_bw_11;
	uint32_t tx_vl_bw_12;
	uint32_t tx_vl_bw_13;
	uint32_t tx_vl_bw_14;
	uint32_t tx_vl_bw_15;

	uint32_t rx_vl_bw_0;
	uint32_t rx_vl_bw_1;
	uint32_t rx_vl_bw_2;
	uint32_t rx_vl_bw_3;
	uint32_t rx_vl_bw_4;
	uint32_t rx_vl_bw_5;
	uint32_t rx_vl_bw_6;
	uint32_t rx_vl_bw_7;
	uint32_t rx_vl_bw_8;
	uint32_t rx_vl_bw_9;
	uint32_t rx_vl_bw_10;
	uint32_t rx_vl_bw_11;
	uint32_t rx_vl_bw_12;
	uint32_t rx_vl_bw_13;
	uint32_t rx_vl_bw_14;
	uint32_t rx_vl_bw_15;

	uint32_t tx_max_port_bw;
	uint32_t rx_max_port_bw;
};

struct utool_port_time_api_in_data {
	uint32_t port_id;
	uint32_t time;
};

struct utool_port_value_api_in_data {
	uint32_t port_id;
	uint32_t value;
};

struct utool_port_time_value_api_in_data {
	uint32_t port_id;
	uint32_t time;
	uint32_t value;
};

struct ubctl_fw_version_data {
	uint32_t fw_version;
	uint32_t reserved[5];
};

struct utool_api_port_link_info {
	long long time;
	uint32_t link_status;
};

struct ubctl_api_port_link_stats {
	uint32_t link_info_num;
	uint32_t link_up_num;
	uint32_t link_down_num;
	struct utool_api_port_link_info link_info[UTOOL_API_MAX_PORT_LINK_STATUS];
};

enum utool_api_loopback_mode {
	UTOOL_API_RXMAC2TXMAC = 0,
	UTOOL_API_TXMAC2RXMAC,
	UTOOL_API_TXPCS2RXPCS,
};

struct utool_api_loopback {
	uint32_t port_id;
	enum utool_api_loopback_mode loopback_mode;
	uint32_t enable;
};

struct utool_api_ssu_vl_pkt_config {
	uint32_t port_id;
	uint32_t enable;
	uint32_t vl_num;
};

struct ssu_vl_pkt_info_CAP_V01 {
	uint32_t port_id;
	uint32_t enable_flag;
	uint32_t ssu_rx_in_dfx_vl_sel : 4;
	uint32_t ssu_tx_in_dfx_vl_sel : 4;
	uint32_t ssu_rx_out_dfx_vl_sel : 4;
	uint32_t ssu_tx_out_dfx_vl_sel : 4;
	uint32_t reserved : 16;
	uint32_t rx_packet_in_vl_cnt;
	uint32_t tx_packet_in_vl_cnt;
	uint32_t rx_packet_out_vl_cnt;
	uint32_t tx_packet_out_vl_cnt;
};

struct ssu_vl_pkt_info_CAP_2 {
	uint32_t port_id;
	uint32_t enable_flag;
	uint32_t ssu_rx_in_dfx_vl_sel : 4;
	uint32_t ssu_tx_in_dfx_vl_sel : 4;
	uint32_t ssu_rx_out_dfx_vl_sel : 4;
	uint32_t ssu_tx_out_dfx_vl_sel : 4;
	uint32_t reserved_0 : 16;
	uint32_t tx_packet_in_sf_vl_cnt;
	uint32_t rx_packet_in_sf_vl_cnt;
	uint32_t tx_packet_in_bps_vl_cnt;
	uint32_t rx_packet_in_bps_vl_cnt;

	uint32_t ssu_rx_0_out_dfx_vl_sel : 4;
	uint32_t ssu_rx_1_out_dfx_vl_sel : 4;
	uint32_t ssu_rx_2_out_dfx_vl_sel : 4;
	uint32_t ssu_tx_0_out_dfx_vl_sel : 4;
	uint32_t ssu_tx_1_out_dfx_vl_sel : 4;
	uint32_t ssu_tx_2_out_dfx_vl_sel : 4;
	uint32_t reserved_1 : 8;

	uint32_t ssu_rx_0_in_sf_dfx_vl_sel : 4;
	uint32_t ssu_rx_1_in_sf_dfx_vl_sel : 4;
	uint32_t ssu_rx_2_in_sf_dfx_vl_sel : 4;
	uint32_t ssu_tx_0_in_sf_dfx_vl_sel : 4;
	uint32_t ssu_tx_1_in_sf_dfx_vl_sel : 4;
	uint32_t ssu_tx_2_in_sf_dfx_vl_sel : 4;
	uint32_t reserved_2 : 8;

	uint32_t ssu_rx_0_in_bps_dfx_vl_sel : 4;
	uint32_t ssu_rx_1_in_bps_dfx_vl_sel : 4;
	uint32_t ssu_rx_2_in_bps_dfx_vl_sel : 4;
	uint32_t ssu_tx_0_in_bps_dfx_vl_sel : 4;
	uint32_t ssu_tx_1_in_bps_dfx_vl_sel : 4;
	uint32_t ssu_tx_2_in_bps_dfx_vl_sel : 4;
	uint32_t reserved_3 : 8;
};

struct ssu_vl_pkt_info_CAP_3 {
	uint32_t port_id;
	uint32_t enable_flag;
	uint32_t ssu_rx_in_dfx_vl_sel : 4;
	uint32_t ssu_tx_in_dfx_vl_sel : 4;
	uint32_t ssu_rx_out_dfx_vl_sel : 4;
	uint32_t ssu_tx_out_dfx_vl_sel : 4;
	uint32_t reserved_0 : 16;
	uint32_t tx_packet_in_vl_cnt0;
	uint32_t rx_packet_in_vl_cnt0;
	uint32_t ssu_rx_0_out_dfx_vl_sel : 4;
	uint32_t ssu_rx_1_out_dfx_vl_sel : 4;
	uint32_t ssu_rx_2_out_dfx_vl_sel : 4;
	uint32_t ssu_tx_0_out_dfx_vl_sel : 4;
	uint32_t ssu_tx_1_out_dfx_vl_sel : 4;
	uint32_t ssu_tx_2_out_dfx_vl_sel : 4;
	uint32_t reserved_1 : 8;

	uint32_t ssu_rx_0_in_sf_dfx_vl_sel : 4;
	uint32_t ssu_rx_1_in_sf_dfx_vl_sel : 4;
	uint32_t ssu_rx_2_in_sf_dfx_vl_sel : 4;
	uint32_t ssu_tx_0_in_sf_dfx_vl_sel : 4;
	uint32_t ssu_tx_1_in_sf_dfx_vl_sel : 4;
	uint32_t ssu_tx_2_in_sf_dfx_vl_sel : 4;
	uint32_t reserved_2 : 8;

	uint32_t ssu_rx_0_in_bps_dfx_vl_sel : 4;
	uint32_t ssu_rx_1_in_bps_dfx_vl_sel : 4;
	uint32_t ssu_rx_2_in_bps_dfx_vl_sel : 4;
	uint32_t ssu_tx_0_in_bps_dfx_vl_sel : 4;
	uint32_t ssu_tx_1_in_bps_dfx_vl_sel : 4;
	uint32_t ssu_tx_2_in_bps_dfx_vl_sel : 4;
	uint32_t reserved_3 : 8;
};

union ssu_vl_pkt_info_CAP_VERSION {
	struct ssu_vl_pkt_info_CAP_V01 ssu_vl_pkt_info_CAP_V01;
	struct ssu_vl_pkt_info_CAP_2 ssu_vl_pkt_info_CAP_2;
	struct ssu_vl_pkt_info_CAP_3 ssu_vl_pkt_info_CAP_3;
};

struct ssu_vl_pkt_info {
	uint32_t env_version;
	union ssu_vl_pkt_info_CAP_VERSION ssu_vl_pkt_info_CAP;
};

int ubctl_user_comm_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
			struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out);
int ubctl_query_ubase_info_api(const char *dev_name, uint32_t ubctl_cmd,
			       void *buf, uint32_t buf_size);
int ubctl_query_dscp_vl_api(const char *dev_name, uint32_t ubctl_cmd,
			    struct ubctl_ubase_dbg_dscp_vl_map *data);
int ubctl_query_sl_vl_map_api(const char *dev_name, uint32_t ubctl_cmd,
			      struct ubctl_ubase_dbg_sl_vl_map *data);
int ubctl_query_caps_info_api(const char *dev_name, uint32_t ubctl_cmd,
			      struct ubctl_ubase_dbg_caps_info *data);
int ubctl_query_icrc_api(uint32_t chip_id, uint32_t die_id, uint32_t port_id, struct ubctl_icrc_info *data);
int ubctl_query_comm_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
			 struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out);

#endif
