// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_io_die.h"

#define UTOOL_MAX_IO_DIE_PORT_NUM 20

static uint32_t g_ubctl_id = 0;

static int utool_display_io_die_info(struct fwctl_io_die_info *data)
{
	struct fwctl_port_info *port_info = data->port_info;
	uint32_t port_num = data->port_count;
	uint32_t i;

	utool_reg_msg("ubctl_id: %u\n", g_ubctl_id++);
	utool_reg_msg("\tchip_id: %u\n", data->chip_id);
	utool_reg_msg("\tdie_id: %u\n", data->die_id);
	utool_reg_msg("\tport_count: %u\n", port_num);

	if (port_num == 0 || port_num > UTOOL_MAX_IO_DIE_PORT_NUM) {
		utool_err_msg("Port num is invalid.\n");
		return UTOOL_ERR;
	}

	for (i = 0; i < port_num; i++) {
		utool_reg_msg("\t\tport_id: 0x%x\n", port_info->port_id);
		utool_reg_msg("\t\tport_type: %s\n", port_info->port_type ? "ub" : "eth");
		utool_reg_msg("\t\tlink_status: %s\n", port_info->link_status ? "up" : "down");
		port_info++;
	}
	return UTOOL_OK;
}

int utool_io_die_cmd(struct utool_dev *dev, struct utool_cmd_param *param)
{
#define UTOOL_MAX_IO_DIE_PORT_REG_LEN (sizeof(struct fwctl_port_info) * \
				       UTOOL_MAX_IO_DIE_PORT_NUM + \
				       sizeof(struct fwctl_io_die_info))
	struct utool_pkt_exec tp_pkt_exec = {
		UTOOL_CMD_QUERY_IO_DIE_PORT_INFO, UTOOL_MAX_IO_DIE_PORT_REG_LEN,
		utool_io_die_parse_rpc_pkt
	};
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	if ((dev == NULL) || (param == NULL)) {
		utool_err_msg("Param is invalid.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	pkt_in = utool_null_create_pkt_in(&pkt_in_len, param);
	if (pkt_in == NULL) {
		utool_err_msg("Failed to create pkt in.\n");
		return UTOOL_ERR_MALLOC;
	}
	ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &tp_pkt_exec);
	utool_destroy_pkt_in(&pkt_in);

	return ret;
}

int utool_io_die_parse_rpc_pkt(struct fwctl_rpc_ub_out *out)
{
	struct fwctl_io_die_info *data = NULL;

	if ((out == NULL) || (out->data_size < sizeof(struct fwctl_io_die_info))) {
		utool_err_msg("Param is invalid, out==null(%d), data size is too small(%d).\n",
			      (out == NULL), out == NULL ? 0 : 1);
		return UTOOL_ERR_INVALID_PARAM;
	}

	data = (struct fwctl_io_die_info *)out->data;

	if (out->data_size != sizeof(struct fwctl_io_die_info) + data->port_count * sizeof(struct fwctl_port_info)) {
		utool_err_msg("out data is invalid, data size = %u, port count = %u", out->data_size, data->port_count);
		return UTOOL_ERR_PARSE;
	}

	return utool_display_io_die_info(data);
}

uint32_t utool_get_ubctl_id(void)
{
	return g_ubctl_id;
}
