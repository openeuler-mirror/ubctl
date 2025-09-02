// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_port_info.h"

enum {
	UTOOL_QUERY_TYPE_MODULE = 0,
	UTOOL_QUERY_TYPE_DATA = 1,
};

enum {
	UTOOL_MODULE_TYPE_NOT_SET = 0,
	UTOOL_MODULE_TYPE_LINK_INFO_ETH = 1,
	UTOOL_MODULE_TYPE_MAC_INFO_ETH = 2,
	UTOOL_MODULE_TYPE_LINK_INFO_UB = 4,
	UTOOL_MODULE_TYPE_MAC_INFO_UB = 8,
};

uint16_t g_utool_module_type = UTOOL_MODULE_TYPE_NOT_SET;

enum {
	UTOOL_CFG_FEC_NOT_SET = 0,
	UTOOL_CFG_FEC_MODE0_RS = 1,
	UTOOL_CFG_FEC_MODE1_RS = 2,
	UTOOL_CFG_FEC_MODE2_RS = 3,
	UTOOL_CFG_FEC_MODE3_RS = 4,
	UTOOL_CFG_FEC_MODE4_RS = 5,
	UTOOL_CFG_FEC_MODE5_RS = 6,
	UTOOL_CFG_FEC_MODE6_RS = 7,
	UTOOL_CFG_FEC_MODE7_RS = 8,
};

enum {
	UTOOL_SPEED_UNKNOWN = 0,
	UTOOL_SPEED_LANE_200G_X2 = 1,
	UTOOL_SPEED_LANE_400G_X4 = 2,
};

enum {
	UTOOL_SPEED_ABILITY_100GBPS = 1,
	UTOOL_SPEED_ABILITY_200GBPS = 2,
	UTOOL_SPEED_ABILITY_400GBPS = 4,
	UTOOL_SPEED_ABILITY_800GBPS = 8,
};

enum {
	UTOOL_MAC_SPEED_MODE1_RATE0_4G = 0,
	UTOOL_MAC_SPEED_MODE1_RATE1_8G = 1,
	UTOOL_MAC_SPEED_MODE1_RATE2_16G = 2,
	UTOOL_MAC_SPEED_MODE1_RATE3_16G_32G = 3,
	UTOOL_MAC_SPEED_MODE1_RATE4_32G = 4,
	UTOOL_MAC_SPEED_MODE1_RATE5_32G_64G = 5,
	UTOOL_MAC_SPEED_MODE1_RATE6_64G = 6,
	UTOOL_MAC_SPEED_MODE1_RATE7_64G_128G = 7,
	UTOOL_MAC_SPEED_MODE1_RATE8_128G = 8,
	UTOOL_MAC_SPEED_MODE1_RATE9_128G_256G = 9,
	UTOOL_MAC_SPEED_MODE1_RATE10_256G = 10,
	UTOOL_MAC_SPEED_MODE1_RATE7_104G = 11,
	UTOOL_MAC_SPEED_MODE1_RATE7_112G = 12,
	UTOOL_MAC_SPEED_MODE1_RATE7_118G = 13,
};

enum {
	UTOOL_MAC_SPEED_MODE2_RATE0_2P578125G = 0,
	UTOOL_MAC_SPEED_MODE2_RATE1_10P3125G = 1,
	UTOOL_MAC_SPEED_MODE2_RATE2_25P78125G = 2,
	UTOOL_MAC_SPEED_MODE2_RATE3_26P5625G = 3,
	UTOOL_MAC_SPEED_MODE2_RATE4_53P125G = 4,
	UTOOL_MAC_SPEED_MODE2_RATE5_32G_64G = 5,
	UTOOL_MAC_SPEED_MODE2_RATE6_NA = 6,
	UTOOL_MAC_SPEED_MODE2_RATE7_64G_128G = 7,
	UTOOL_MAC_SPEED_MODE2_RATE8_106P25G = 8,
	UTOOL_MAC_SPEED_MODE2_RATE9_128G_256G = 9,
	UTOOL_MAC_SPEED_MODE2_RATE10_225G = 10,
};

enum {
	UTOOL_LINK_SDS_RATE_UNSET = 0,
	UTOOL_LINK_SDS_RATE_2P578125G = 1,
	UTOOL_LINK_SDS_RATE_4G = 2,
	UTOOL_LINK_SDS_RATE_10P3125G = 3,
	UTOOL_LINK_SDS_RATE_16G = 4,
	UTOOL_LINK_SDS_RATE_25P78125G = 5,
	UTOOL_LINK_SDS_RATE_26P5625G = 6,
	UTOOL_LINK_SDS_RATE_32G = 7,
	UTOOL_LINK_SDS_RATE_53P125G = 8,
	UTOOL_LINK_SDS_RATE_64G = 9,
	UTOOL_LINK_SDS_RATE_104G = 10,
	UTOOL_LINK_SDS_RATE_106P25G = 11,
	UTOOL_LINK_SDS_RATE_112G = 12,
	UTOOL_LINK_SDS_RATE_118G = 13,
};

enum {
	UTOOL_LINK_SDS_RATE_25G = 0,
	UTOOL_LINK_SDS_RATE_50G = 1,
	UTOOL_LINK_SDS_RATE_100G = 2,
};

enum {
	UTOOL_ETH_MODE = 0,
	UTOOL_FLEXE_MODE = 1,
	UTOOL_TRANSCODE_MODE = 2,
	UTOOL_NGSF_MODE = 3,
	UTOOL_HEE_MODE = 4,
	UTOOL_ILK_MODE = 5,
	UTOOL_FLEXO_MODE = 6,
	UTOOL_ENHANCE_ETH_MODE = 7,
};

enum {
	UTOOL_PORT_MODE_UBC = 0,
	UTOOL_PORT_MODE_SHARED = 1,
	UTOOL_PORT_MODE_UBG = 2,
	UTOOL_PORT_MODE_UNUSED = 3,
};

enum {
	UTOOL_MAC_LANES_NOT_SET = 0,
	UTOOL_MAC_LANES_X1 = 1,
	UTOOL_MAC_LANES_X2 = 2,
	UTOOL_MAC_LANES_X4 = 4,
	UTOOL_MAC_LANES_X8 = 8,
};

enum {
	UTOOL_LSTM_LINK_IDLE = 0x0,
	UTOOL_LSTM_RX_EQ = 0x1,
	UTOOL_LSTM_DETECT_WAIT = 0x2,
	UTOOL_LSTM_DETECT_CONFIRM = 0x3,
	UTOOL_LSTM_DISCOVERY_ACTIVE = 0x4,
	UTOOL_LSTM_DISCOVERY_CONFIRM = 0x5,
	UTOOL_LSTM_CONFIG_ACTIVE = 0x6,
	UTOOL_LSTM_CONFIG_CHECK = 0x7,
	UTOOL_LSTM_CONFIG_CONFIRM = 0x8,
	UTOOL_LSTM_SENT_NULL = 0x9,
	UTOOL_LSTM_LINK_ACTIVE = 0xa,
	UTOOL_LSTM_RETRAIN_ACTIVE = 0xb,
	UTOOL_LSTM_RETRAIN_CONFIRM = 0xc,
	UTOOL_LSTM_CHANGE_SPEED = 0xe,
	UTOOL_LSTM_EQ_COARSE_ACTIVE = 0x10,
	UTOOL_LSTM_EQ_PASSIVE = 0x11,
	UTOOL_LSTM_EQ_ACTIVE = 0x12,
	UTOOL_LSTM_LOOPBACK_CONFIRM = 0x13,
	UTOOL_LSTM_LOOPBACK_ACTIVE = 0x14,
	UTOOL_LSTM_LOOPBACK_EXIT = 0x15,
	UTOOL_LSTM_SEBT_EEIB = 0x16,
	UTOOL_LSTM_CHANGE_POWER = 0x17,
	UTOOL_LSTM_SENT_FLB = 0x18,
	UTOOL_LSTM_TX_LP0S_ACTIVE = 0x19,
	UTOOL_LSTM_RX_LP0S_ACTIVE = 0x1a,
	UTOOL_LSTM_RX_LP0S_WAIT_SDF = 0x1b,
	UTOOL_LSTM_EQ_COARSE_CONFIRM = 0x1e,
};

enum {
	UTOOL_DL_LINK_FSM_WAIT_INIT = 0,
	UTOOL_DL_LINK_FSM_WAIT_INIT_SUC = 1,
	UTOOL_DL_LINK_FSM_END_INIT = 2,
	UTOOL_DL_LINK_FSM_INIT_SUC = 3,
};

struct utool_port_head {
	uint32_t port_id;
	uint16_t query_type;
	uint16_t module_type;
};

#define UTOOL_LINK_PROC_ERR_STATE_SIZE 15
struct utool_mac_dfx_link_state {
	uint16_t cur_state;
	uint16_t err_state[UTOOL_LINK_PROC_ERR_STATE_SIZE];
};

struct utool_port_link_info {
	uint8_t target_speed;
	uint8_t speed_ability;
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
};

union utool_port_info {
	struct utool_port_link_info link_info;
	struct utool_port_dlphy_info dlphy_info;
};

struct utool_port_data {
	struct utool_port_head head;
	union utool_port_info info;
	uint32_t reserved;
};

struct utool_info_item {
	uint32_t key;
	const char *name;
};

struct utool_info_item g_utool_fec_table[] = {
	{ UTOOL_CFG_FEC_NOT_SET, "FEC_UNKNOWN" },
	{ UTOOL_CFG_FEC_MODE1_RS, "FEC OFF" },
	{ UTOOL_CFG_FEC_MODE2_RS, "FEC RS" },
};

struct utool_info_item g_utool_lanes_table[] = {
	{ UTOOL_MAC_LANES_NOT_SET, "unset" },
	{ UTOOL_MAC_LANES_X1, "X1" },
	{ UTOOL_MAC_LANES_X2, "X2" },
	{ UTOOL_MAC_LANES_X4, "X4" },
	{ UTOOL_MAC_LANES_X8, "X8" },
};

struct utool_data_parse_item {
	uint16_t module_type;
	int (*module_parse_func)(struct fwctl_rpc_ub_out *out);
};

static const char *utool_get_str(uint32_t val, const struct utool_info_item *table, uint32_t size, const char *none_str)
{
	const char *str = none_str;
	uint32_t i;

	for (i = 0; i < size; i++) {
		if (table[i].key == val) {
			str = table[i].name;
			break;
		}
	}

	return str;
}

static void utool_print_enum(const char *label, uint32_t val, const struct utool_info_item *table, uint32_t size,
			     const char *none_str)
{
	const char *str = utool_get_str(val, table, size, none_str);
	if (str == NULL) {
		return;
	}

	utool_reg_msg("%s: %s\n", label, str);
}

static inline void utool_print_two_type_info(const char *label, uint8_t val,
					     const char *true_str, const char *false_str)
{
	const char *str = ((val != 0) ? true_str : false_str);

	utool_reg_msg("%s: %s\n", label, str);
}

static void utool_print_speed_ability(uint8_t speed_ability)
{
	struct utool_info_item utool_speed_ability_table[] = {
		{ UTOOL_SPEED_ABILITY_100GBPS, "100Gbps" },
		{ UTOOL_SPEED_ABILITY_200GBPS, "200Gbps" },
		{ UTOOL_SPEED_ABILITY_400GBPS, "400Gbps" },
		{ UTOOL_SPEED_ABILITY_800GBPS, "800Gbps" },
	};
	uint32_t speed_ability_cnt = UTOOL_ARRAY_SIZE(utool_speed_ability_table);
	bool have_printed = false;
	uint32_t i;

	utool_reg_msg("speed ability: ");
	for (i = 0; i < speed_ability_cnt; i++) {
		if ((utool_speed_ability_table[i].key & speed_ability) != 0) {
			if (have_printed) {
				utool_reg_msg(",");
			} else {
				have_printed = true;
			}
			utool_reg_msg("%s", utool_speed_ability_table[i].name);
		}
	}
	utool_reg_msg("\n");
}

static void utool_print_cur_speed(uint8_t cur_speed)
{
	struct utool_info_item utool_cur_speed_table[] = {
		{ UTOOL_MAC_SPEED_MODE1_RATE0_4G, "data rate0" },
		{ UTOOL_MAC_SPEED_MODE1_RATE1_8G, "data rate1" },
		{ UTOOL_MAC_SPEED_MODE1_RATE2_16G, "data rate2" },
		{ UTOOL_MAC_SPEED_MODE1_RATE3_16G_32G, "data rate3" },
		{ UTOOL_MAC_SPEED_MODE1_RATE4_32G, "data rate4" },
		{ UTOOL_MAC_SPEED_MODE1_RATE5_32G_64G, "data rate5" },
		{ UTOOL_MAC_SPEED_MODE1_RATE6_64G, "data rate6" },
		{ UTOOL_MAC_SPEED_MODE1_RATE7_64G_128G, "data rate7" },
		{ UTOOL_MAC_SPEED_MODE1_RATE8_128G, "data rate8" },
		{ UTOOL_MAC_SPEED_MODE1_RATE9_128G_256G, "data rate9" },
		{ UTOOL_MAC_SPEED_MODE1_RATE10_256G, "data rate10" },
	};

	utool_print_enum("cur_speed", (uint32_t)cur_speed, utool_cur_speed_table,
			 UTOOL_ARRAY_SIZE(utool_cur_speed_table), "NA");
}

static void utool_print_dlphy_sds_rate(uint8_t sds_rate, uint8_t phy_mode_ctrl)
{
	struct utool_info_item utool_sds_rate_table1[] = {
		{ UTOOL_MAC_SPEED_MODE1_RATE0_4G, "4G" },
		{ UTOOL_MAC_SPEED_MODE1_RATE1_8G, "8G" },
		{ UTOOL_MAC_SPEED_MODE1_RATE2_16G, "16G" },
		{ UTOOL_MAC_SPEED_MODE1_RATE3_16G_32G, "16G-32G(32)" },
		{ UTOOL_MAC_SPEED_MODE1_RATE4_32G, "32G" },
		{ UTOOL_MAC_SPEED_MODE1_RATE5_32G_64G, "32G-64G(56)" },
		{ UTOOL_MAC_SPEED_MODE1_RATE6_64G, "64G" },
		{ UTOOL_MAC_SPEED_MODE1_RATE7_64G_128G, "64G_128G" },
		{ UTOOL_MAC_SPEED_MODE1_RATE8_128G, "128G" },
		{ UTOOL_MAC_SPEED_MODE1_RATE9_128G_256G, "128G-256G(128)" },
		{ UTOOL_MAC_SPEED_MODE1_RATE10_256G, "256G" },
		{ UTOOL_MAC_SPEED_MODE1_RATE7_104G, "104G" },
		{ UTOOL_MAC_SPEED_MODE1_RATE7_112G, "112G" },
		{ UTOOL_MAC_SPEED_MODE1_RATE7_118G, "118G" },
	};

	struct utool_info_item utool_sds_rate_table2[] = {
		{ UTOOL_MAC_SPEED_MODE2_RATE0_2P578125G, "2.578125G" },
		{ UTOOL_MAC_SPEED_MODE2_RATE1_10P3125G, "10.3125G" },
		{ UTOOL_MAC_SPEED_MODE2_RATE2_25P78125G, "25.78125G" },
		{ UTOOL_MAC_SPEED_MODE2_RATE3_26P5625G, "26.5625G" },
		{ UTOOL_MAC_SPEED_MODE2_RATE4_53P125G, "53.125G" },
		{ UTOOL_MAC_SPEED_MODE2_RATE5_32G_64G, "32G-64G(56.25)" },
		{ UTOOL_MAC_SPEED_MODE2_RATE6_NA, "NA" },
		{ UTOOL_MAC_SPEED_MODE2_RATE7_64G_128G, "64G-128G(112.5)" },
		{ UTOOL_MAC_SPEED_MODE2_RATE8_106P25G, "106.25G" },
		{ UTOOL_MAC_SPEED_MODE2_RATE9_128G_256G, "128G-256G(128)" },
		{ UTOOL_MAC_SPEED_MODE2_RATE10_225G, "225G" },
	};

	if (phy_mode_ctrl == 0) {
		utool_print_enum("sds_rate", (uint32_t)sds_rate, utool_sds_rate_table1,
				 UTOOL_ARRAY_SIZE(utool_sds_rate_table1), "NA");
	} else {
		utool_print_enum("sds_rate", (uint32_t)sds_rate, utool_sds_rate_table2,
				 UTOOL_ARRAY_SIZE(utool_sds_rate_table2), "NA");
	}
}

static void utool_print_sds_rate(uint8_t sds_rate)
{
	struct utool_info_item utool_sds_rate_table[] = {
		{ UTOOL_LINK_SDS_RATE_UNSET, "unset" },
		{ UTOOL_LINK_SDS_RATE_2P578125G, "2.578125G" },
		{ UTOOL_LINK_SDS_RATE_4G, "4G" },
		{ UTOOL_LINK_SDS_RATE_10P3125G, "10.3125G" },
		{ UTOOL_LINK_SDS_RATE_16G, "16G" },
		{ UTOOL_LINK_SDS_RATE_25P78125G, "25.78125G" },
		{ UTOOL_LINK_SDS_RATE_26P5625G, "26.5625G" },
		{ UTOOL_LINK_SDS_RATE_32G, "32G" },
		{ UTOOL_LINK_SDS_RATE_53P125G, "53.125G" },
		{ UTOOL_LINK_SDS_RATE_64G, "64G" },
		{ UTOOL_LINK_SDS_RATE_104G, "104G" },
		{ UTOOL_LINK_SDS_RATE_106P25G, "106.25G" },
		{ UTOOL_LINK_SDS_RATE_112G, "112G" },
		{ UTOOL_LINK_SDS_RATE_118G, "118G" },
	};

	utool_print_enum("sds_rate", (uint32_t)sds_rate, utool_sds_rate_table,
			 UTOOL_ARRAY_SIZE(utool_sds_rate_table), "NA");
}

static void utool_print_dlphy_lstm(uint8_t mac_lstm)
{
	struct utool_info_item utool_lstm_table[] = {
		{ UTOOL_LSTM_LINK_IDLE, "LINK_IDLE" },
		{ UTOOL_LSTM_RX_EQ, "RX_EQ" },
		{ UTOOL_LSTM_DETECT_WAIT, "DETECT_WAIT" },
		{ UTOOL_LSTM_DETECT_CONFIRM, "DETECT_CONFIRM" },
		{ UTOOL_LSTM_DISCOVERY_ACTIVE, "DISCOVERY_ACTIVE" },
		{ UTOOL_LSTM_DISCOVERY_CONFIRM, "DISCOVERY_CONFIRM" },
		{ UTOOL_LSTM_CONFIG_ACTIVE, "CONFIG_ACTIVE" },
		{ UTOOL_LSTM_CONFIG_CHECK, "CONFIG_CHECK" },
		{ UTOOL_LSTM_CONFIG_CONFIRM, "CONFIG_CONFIRM" },
		{ UTOOL_LSTM_SENT_NULL, "SENT_NULL" },
		{ UTOOL_LSTM_LINK_ACTIVE, "LINK_ACTIVE" },
		{ UTOOL_LSTM_RETRAIN_ACTIVE, "RETRAIN_ACTIVE" },
		{ UTOOL_LSTM_RETRAIN_CONFIRM, "RETRAIN_CONFIRM" },
		{ UTOOL_LSTM_CHANGE_SPEED, "CHANGE_SPEED" },
		{ UTOOL_LSTM_EQ_COARSE_ACTIVE, "EQ_COARSE_ACTIVE" },
		{ UTOOL_LSTM_EQ_PASSIVE, "EQ_PASSIVE" },
		{ UTOOL_LSTM_EQ_ACTIVE, "EQ_ACTIVE" },
		{ UTOOL_LSTM_LOOPBACK_CONFIRM, "LOOPBACK_CONFIRM" },
		{ UTOOL_LSTM_LOOPBACK_ACTIVE, "LOOPBACK_ACTIVE" },
		{ UTOOL_LSTM_LOOPBACK_EXIT, "LOOPBACK_EXIT" },
		{ UTOOL_LSTM_SEBT_EEIB, "SEBT_EEIB" },
		{ UTOOL_LSTM_CHANGE_POWER, "CHANGE_POWER" },
		{ UTOOL_LSTM_SENT_FLB, "SENT_FLB" },
		{ UTOOL_LSTM_TX_LP0S_ACTIVE, "TX_LP0S_ACTIVE" },
		{ UTOOL_LSTM_RX_LP0S_ACTIVE, "RX_LP0S_ACTIVE" },
		{ UTOOL_LSTM_RX_LP0S_WAIT_SDF, "RX_LP0S_WAIT_SDF" },
		{ UTOOL_LSTM_EQ_COARSE_CONFIRM, "EQ_COARSE_CONFIRM" },
	};

	utool_print_enum("lstm_state", (uint32_t)mac_lstm, utool_lstm_table, UTOOL_ARRAY_SIZE(utool_lstm_table), "NA");
}

static void utool_print_port_mode(uint8_t port_mode)
{
	struct utool_info_item utool_port_mode_table[] = {
		{ UTOOL_PORT_MODE_UBC, "PORT_MODE_UBC" },
		{ UTOOL_PORT_MODE_SHARED, "PORT_MODE_SHARED" },
		{ UTOOL_PORT_MODE_UBG, "PORT_MODE_UBG" },
		{ UTOOL_PORT_MODE_UNUSED, "PORT_MODE_UNUSED" },
	};

	utool_print_enum("port_mode", (uint32_t)port_mode, utool_port_mode_table,
			 UTOOL_ARRAY_SIZE(utool_port_mode_table), "NA");
}

static void utool_print_dl_link_fsm(uint32_t dl_link_fsm)
{
	struct utool_info_item utool_dl_link_fsm_table[] = {
		{ UTOOL_DL_LINK_FSM_WAIT_INIT, "Waiting for startup initialization (controlled by 0x400)." },
		{ UTOOL_DL_LINK_FSM_WAIT_INIT_SUC, "Waiting for the success of sending and receiving initialization packets." },
		{ UTOOL_DL_LINK_FSM_END_INIT, "Waiting for the end of initialization (controlled by 0x400)." },
		{ UTOOL_DL_LINK_FSM_INIT_SUC, "Initialization succeeded." },
	};

	utool_print_enum("dl_link_fsm", dl_link_fsm, utool_dl_link_fsm_table,
			 UTOOL_ARRAY_SIZE(utool_dl_link_fsm_table), "NA");
}

static void utool_print_target_speed(uint8_t target_speed)
{
	struct utool_info_item utool_target_speed_table[] = {
		{ UTOOL_SPEED_UNKNOWN, "unknown" },
		{ UTOOL_SPEED_LANE_200G_X2, "LANE_200G_X2" },
		{ UTOOL_SPEED_LANE_400G_X4, "LANE_400G_X4" }
	};

	utool_print_enum("target_speed", (uint32_t)target_speed, utool_target_speed_table,
			 UTOOL_ARRAY_SIZE(utool_target_speed_table), "NA");
}

static void utool_print_port_id(uint32_t port_id)
{
	static bool utool_printed_port_id = false;

	if (utool_printed_port_id) {
		return;
	}

	utool_reg_msg("port_id: 0x%x\n", port_id);
	utool_printed_port_id = true;
}

static void utool_print_eth_sds_rate(uint8_t sds_rate)
{
	struct utool_info_item utool_eth_sds_rate_table[] = {
		{ UTOOL_LINK_SDS_RATE_25G, "25G" },
		{ UTOOL_LINK_SDS_RATE_50G, "50G" },
		{ UTOOL_LINK_SDS_RATE_100G, "100G" },
	};

	utool_print_enum("sds_rate", (uint32_t)sds_rate, utool_eth_sds_rate_table,
			 UTOOL_ARRAY_SIZE(utool_eth_sds_rate_table), "NA");
}

static void utool_print_eth_dlphy_fec_info(uint8_t eth_fec)
{
	struct utool_info_item utool_eth_fec_table[] = {
		{ UTOOL_CFG_FEC_NOT_SET, "NO-FEC" },
		{ UTOOL_CFG_FEC_MODE0_RS, "BASE-R FEC" },
		{ UTOOL_CFG_FEC_MODE1_RS, "RSFEC (528, 514)" },
		{ UTOOL_CFG_FEC_MODE2_RS, "RSFEC (544, 528)" },
		{ UTOOL_CFG_FEC_MODE3_RS, "RSFEC (272, 258)" },
		{ UTOOL_CFG_FEC_MODE4_RS, "RSFEC (544, 514)" },
		{ UTOOL_CFG_FEC_MODE5_RS, "RSFEC (272, 258)" },
		{ UTOOL_CFG_FEC_MODE6_RS, "RSFEC (952, 924) + EBCH (1320, 1285)" },
		{ UTOOL_CFG_FEC_MODE7_RS, "EBCH (1320, 1285)" },
	};

	utool_print_enum("fec", (uint32_t)eth_fec, utool_eth_fec_table, UTOOL_ARRAY_SIZE(utool_eth_fec_table), "NA");
}

static void utool_print_eth_dlphy_mode_info(uint8_t phy_mode_ctrl)
{
	struct utool_info_item utool_eth_dlphy_mode_table[] = {
		{ UTOOL_ETH_MODE, "Ethernet Mode" },
		{ UTOOL_FLEXE_MODE, "FlexE Mode" },
		{ UTOOL_TRANSCODE_MODE, "Transcode Mode" },
		{ UTOOL_NGSF_MODE, "NGSF Mode" },
		{ UTOOL_HEE_MODE, "HEE Mode" },
		{ UTOOL_ILK_MODE, "ILK Mode" },
		{ UTOOL_FLEXO_MODE, "FlexO Mode" },
		{ UTOOL_ENHANCE_ETH_MODE, "Enhance Ethernet Mode" },
	};

	utool_print_enum("phy mode ctrl", (uint32_t)phy_mode_ctrl, utool_eth_dlphy_mode_table,
			 UTOOL_ARRAY_SIZE(utool_eth_dlphy_mode_table), "NA");
}

static void utool_print_eth_lane_num_info(uint8_t cur_lane_num, const char *str)
{
	struct utool_info_item utool_lane_num_table[] = {
		{ UTOOL_MAC_LANES_X1, "LANE_NUM_X1" },
		{ UTOOL_MAC_LANES_X2, "LANE_NUM_X2" },
		{ UTOOL_MAC_LANES_X4, "LANE_NUM_X4" },
	};

	utool_print_enum(str, (uint32_t)cur_lane_num, utool_lane_num_table,
			 UTOOL_ARRAY_SIZE(utool_lane_num_table), "NA");
}

static int utool_ub_port_info_parse_link_info(struct fwctl_rpc_ub_out *port_info_out)
{
	struct utool_port_data *port_info_out_data = (struct utool_port_data *)(port_info_out->data);
	struct utool_port_link_info link_info = port_info_out_data->info.link_info;
	uint32_t i;

	utool_print_port_id(port_info_out_data->head.port_id);
	utool_reg_msg("\n======================= UB PORT LINK INFO =======================\n");
	utool_print_target_speed(link_info.target_speed);
	utool_print_speed_ability(link_info.speed_ability);
	utool_print_enum("lane num", (uint32_t)link_info.lane_num, g_utool_lanes_table,
			 UTOOL_ARRAY_SIZE(g_utool_lanes_table), "NA");
	utool_print_enum("fec", (uint32_t)link_info.fec, g_utool_fec_table, UTOOL_ARRAY_SIZE(g_utool_fec_table), "NA");
	utool_print_sds_rate(link_info.sds_rate);
	utool_print_two_type_info("port usage", link_info.port_usage, "used", "unused");
	utool_print_two_type_info("port enable", link_info.port_enable, "on", "off");
	utool_print_two_type_info("port link", link_info.port_link, "link", "no link");
	utool_print_two_type_info("driver_type", link_info.driver_type, "NA", "TYPE_NONE");
	utool_print_port_mode(link_info.port_mode);
	utool_reg_msg("link down err: 0x%x\n", link_info.link_down_err);

	utool_reg_msg("link state: 0x%04x ", link_info.mac_link_state.cur_state);
	for (i = 0; i < UTOOL_ARRAY_SIZE(link_info.mac_link_state.err_state); i++) {
		utool_reg_msg("0x%04x ", link_info.mac_link_state.err_state[i]);
	}
	utool_reg_msg("\n");

	return UTOOL_OK;
}

static int utool_ub_port_info_parse_dlphy_info(struct fwctl_rpc_ub_out *port_info_out)
{
	struct utool_info_item utool_dlphy_fec_table[] = {
		{ UTOOL_CFG_FEC_NOT_SET, "No FEC" },
		{ UTOOL_CFG_FEC_MODE0_RS, "FEC Mode 0 RS (128, 120,T=2)" },
		{ UTOOL_CFG_FEC_MODE1_RS, "FEC Mode 1 RS (128, 120,T=4)" },
		{ UTOOL_CFG_FEC_MODE2_RS, "FEC Mode 2 RS (256, 240,T=8)" },
		{ UTOOL_CFG_FEC_MODE3_RS, "FEC Mode 3 RS (512, 480,T=16)" },
	};
	struct utool_port_data *port_info_out_data = (struct utool_port_data *)(port_info_out->data);
	struct utool_port_dlphy_info dlphy_info = port_info_out_data->info.dlphy_info;

	utool_print_port_id(port_info_out_data->head.port_id);
	utool_reg_msg("\n======================== UB DLPHY INFO ==========================\n");
	utool_print_enum("fec", (uint32_t)dlphy_info.fec, utool_dlphy_fec_table,
			 UTOOL_ARRAY_SIZE(utool_dlphy_fec_table), "NA");
	utool_print_two_type_info("phy_mode_ctrl", dlphy_info.phy_mode_ctrl, "Mode2", "Mode1");
	utool_print_dlphy_sds_rate(dlphy_info.sds_rate, dlphy_info.phy_mode_ctrl);
	utool_print_cur_speed(dlphy_info.cur_speed);
	utool_print_enum("cur_tx_lane_num", (uint32_t)dlphy_info.cur_tx_lane_num, g_utool_lanes_table,
			 UTOOL_ARRAY_SIZE(g_utool_lanes_table), "NA");
	utool_print_enum("cur_rx_lane_num", (uint32_t)dlphy_info.cur_rx_lane_num, g_utool_lanes_table,
			 UTOOL_ARRAY_SIZE(g_utool_lanes_table), "NA");
	utool_print_enum("init_succ_tx_lane_num", (uint32_t)dlphy_info.init_succ_tx_lane_num, g_utool_lanes_table,
			 UTOOL_ARRAY_SIZE(g_utool_lanes_table), "NA");
	utool_print_enum("init_succ_rx_lane_num", (uint32_t)dlphy_info.init_succ_rx_lane_num, g_utool_lanes_table,
			 UTOOL_ARRAY_SIZE(g_utool_lanes_table), "NA");
	utool_print_two_type_info("port_en", dlphy_info.port_en, "on", "off");
	utool_print_two_type_info("port_mode", dlphy_info.port_mode, "X2 4port", "X4 2port");
	utool_print_two_type_info("port_mode_en", dlphy_info.port_mode_en, "on", "off");
	utool_print_two_type_info("dl_link", dlphy_info.dl_link, "link", "no link");
	utool_print_two_type_info("phy_link", dlphy_info.phy_link, "link", "no link");
	utool_print_two_type_info("cur_port_type", dlphy_info.cur_port_type, "master", "slave");
	utool_print_dlphy_lstm(dlphy_info.mac_lstm);
	utool_reg_msg("decoded_fail_block_num: 0x%x\n", dlphy_info.decoded_fail_block_num);
	utool_reg_msg("fec_err: 0x%llx\n", ((uint64_t)dlphy_info.fec_err_high << 32) | dlphy_info.fec_err_low);
	utool_reg_msg("retry_cnt: 0x%x\n", dlphy_info.retry_cnt);
	utool_print_dl_link_fsm(dlphy_info.dl_link_fsm);

	return UTOOL_OK;
}

static int utool_eth_port_info_parse_link_info(struct fwctl_rpc_ub_out *port_info_out)
{
	struct utool_port_data *port_info_out_data = (struct utool_port_data *)(port_info_out->data);
	struct utool_port_link_info link_info = port_info_out_data->info.link_info;

	utool_print_port_id(port_info_out_data->head.port_id);
	utool_reg_msg("\n======================= ETH PORT LINK INFO =======================\n");
	utool_print_target_speed(link_info.target_speed);
	utool_print_speed_ability(link_info.speed_ability);
	utool_print_enum("lane num", (uint32_t)link_info.lane_num, g_utool_lanes_table,
			 UTOOL_ARRAY_SIZE(g_utool_lanes_table), "NA");
	utool_print_enum("fec", (uint32_t)link_info.fec, g_utool_fec_table, UTOOL_ARRAY_SIZE(g_utool_fec_table), "NA");
	utool_print_eth_sds_rate(link_info.sds_rate);
	utool_print_two_type_info("port usage", link_info.port_usage, "used", "unused");
	utool_print_two_type_info("port enable", link_info.port_enable, "on", "off");
	utool_print_two_type_info("port link", link_info.port_link, "link", "no link");
	utool_print_two_type_info("driver_type", link_info.driver_type, "NA", "TYPE_NONE");
	utool_print_port_mode(link_info.port_mode);
	utool_print_two_type_info("link down err", link_info.link_down_err, "NA", "LINK_DOWN_ERR_UNKNOW");

	return UTOOL_OK;
}

static int utool_eth_port_info_parse_dlphy_info(struct fwctl_rpc_ub_out *port_info_out)
{
	struct utool_port_data *port_info_out_data = (struct utool_port_data *)(port_info_out->data);
	struct utool_port_dlphy_info dlphy_info = port_info_out_data->info.dlphy_info;

	utool_print_port_id(port_info_out_data->head.port_id);
	utool_reg_msg("\n======================== ETH DLPHY INFO ==========================\n");
	utool_print_eth_dlphy_fec_info(dlphy_info.fec);
	utool_print_eth_dlphy_mode_info(dlphy_info.phy_mode_ctrl);
	utool_print_eth_sds_rate(dlphy_info.sds_rate);
	utool_print_eth_lane_num_info(dlphy_info.cur_tx_lane_num, "cur_tx_lane_num");
	utool_print_eth_lane_num_info(dlphy_info.cur_tx_lane_num, "cur_rx_lane_num");
	utool_print_two_type_info("port_en", dlphy_info.port_en, "enable", "disable");
	utool_print_two_type_info("port_mode", dlphy_info.port_mode, "X2 2port", "X4 1port");
	utool_print_two_type_info("phy_link", dlphy_info.phy_link, "link", "no link");
	utool_reg_msg("mac lstm: 0x%x\n", dlphy_info.mac_lstm);
	utool_reg_msg("decoded_fail_block_num: 0x%x\n", dlphy_info.decoded_fail_block_num);
	utool_reg_msg("fec_err: 0x%llx\n", ((uint64_t)dlphy_info.fec_err_high << 32) | dlphy_info.fec_err_low);

	return UTOOL_OK;
}

static int utool_port_info_parse_modules(struct fwctl_rpc_ub_out *port_info_out)
{
	struct utool_port_data *port_info_out_data = (struct utool_port_data *)(port_info_out->data);

	g_utool_module_type = port_info_out_data->head.module_type;

	return UTOOL_OK;
}

static int utool_port_info_cmd_get_mudules(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_pkt_exec pkt_exec = {UTOOL_CMD_QUERY_PORT_INFO, 0, NULL};
	struct fwctl_pkt_in_port_info *pkt_in = NULL;
	uint32_t pkt_in_len = 0;
	int ret = UTOOL_OK;

	pkt_exec.data_len = sizeof(struct utool_port_data);
	pkt_exec.execute = utool_port_info_parse_modules;

	pkt_in = utool_create_pkt_in(&pkt_in_len, param, sizeof(struct fwctl_pkt_in_port_info));
	if (pkt_in == NULL) {
		utool_err_msg("Failed to create pkt in.\n");
		return UTOOL_ERR_MALLOC;
	}

	pkt_in->port_id = param->port;
	pkt_in->query_type = UTOOL_QUERY_TYPE_MODULE;
	pkt_in->module_type = UTOOL_MODULE_TYPE_NOT_SET;

	ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	utool_destroy_pkt_in((void **)&pkt_in);

	return ret;
}

static int utool_port_info_cmd_get_data(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_data_parse_item data_parse_table[] = {
		{ UTOOL_MODULE_TYPE_LINK_INFO_ETH, utool_eth_port_info_parse_link_info },
		{ UTOOL_MODULE_TYPE_MAC_INFO_ETH, utool_eth_port_info_parse_dlphy_info },
		{ UTOOL_MODULE_TYPE_LINK_INFO_UB, utool_ub_port_info_parse_link_info },
		{ UTOOL_MODULE_TYPE_MAC_INFO_UB, utool_ub_port_info_parse_dlphy_info },
	};
	struct utool_pkt_exec pkt_exec = { UTOOL_CMD_QUERY_PORT_INFO, 0, NULL };
	uint32_t module_type_cnt = UTOOL_ARRAY_SIZE(data_parse_table);
	struct fwctl_pkt_in_port_info *pkt_in = NULL;
	uint32_t pkt_in_len = 0;
	int ret = UTOOL_OK;
	uint32_t i;

	pkt_exec.data_len = sizeof(struct utool_port_data);

	for (i = 0; i < module_type_cnt; i++) {
		if ((g_utool_module_type & data_parse_table[i].module_type) == 0) {
			continue;
		}

		pkt_exec.execute = data_parse_table[i].module_parse_func;

		pkt_in = utool_create_pkt_in(&pkt_in_len, param, sizeof(struct fwctl_pkt_in_port_info));
		if (pkt_in == NULL) {
			utool_err_msg("Failed to create pkt in.\n");
			return UTOOL_ERR_MALLOC;
		}

		pkt_in->port_id = param->port;
		pkt_in->query_type = UTOOL_QUERY_TYPE_DATA;
		pkt_in->module_type = data_parse_table[i].module_type;

		ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &pkt_exec);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to execute command, ret = %d.\n", ret);
			utool_destroy_pkt_in((void **)&pkt_in);
			return ret;
		}

		utool_destroy_pkt_in((void **)&pkt_in);
	}

	return UTOOL_OK;
}

static int utool_port_info_cmd(struct utool_dev *dev, struct utool_cmd_param *param)
{
	int ret = UTOOL_OK;

	ret = utool_port_info_cmd_get_mudules(dev, param);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to get mudules, ret = %d.\n", ret);
		return ret;
	}

	ret = utool_port_info_cmd_get_data(dev, param);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to get data, ret = %d.\n", ret);
	}

	return ret;
}

int utool_port_info_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	if (dev == NULL || param == NULL) {
		utool_err_msg("Param is invalid, dev==null(%d), param==null(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (param->flags != (UTOOL_FLAG_M | UTOOL_FLAG_P)) {
		utool_err_msg("The ubctl port_info command must be in the following formats:\n"
			      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m port_info -p ${port}\n");
		return UTOOL_ERR_CMD_NOT_FOUND;
	}

	return utool_port_info_cmd(dev, param);
}
