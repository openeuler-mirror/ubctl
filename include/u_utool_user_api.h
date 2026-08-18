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
#define UBCTL_UBASE_MAX_DSCP 64
#define UBCTL_UBASE_MAX_SL_NUM 16
#define UBCTL_RXDMA_QUEUE_NUM 4

struct ubctl_cmd_buf {
	unsigned short opcode;
	bool is_read;
	unsigned int data_size;
	void *data;
};

struct ubctl_icrc_info {
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

#endif
