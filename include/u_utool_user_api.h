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

int ubctl_user_comm_api(uint32_t chip_id, uint32_t die_id, uint32_t ubctl_cmd,
			struct ubctl_cmd_buf *in, struct ubctl_cmd_buf *out);
int ubctl_query_icrc_api(uint32_t chip_id, uint32_t die_id, uint32_t port_id, struct ubctl_icrc_info *data);

#endif
