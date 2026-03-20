// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <stdio.h>
#include <string.h>

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_port_link.h"

#define UTOOL_MAX_PORT_LINK_STATUS 10U
#define UTOOL_MAX_TIME_INFO_SIZE 64

struct port_link_info {
	long long time;
	uint32_t link_status;
};

struct ubctl_port_link_stats {
	uint32_t link_info_num;
	uint32_t link_up_num;
	uint32_t link_down_num;
	struct port_link_info link_info[UTOOL_MAX_PORT_LINK_STATUS];
};

static int utool_time_parse(char *buf, struct tm time)
{
#define YEAR_BASE_NUM 1900

	int ret;

	const char *ubtool_weekdays[] = {
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
	};

	const char *ubtool_months[] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};

	memset(buf, 0, UTOOL_MAX_TIME_INFO_SIZE);
	ret = snprintf(buf, UTOOL_MAX_TIME_INFO_SIZE, "%s %s %d %02d:%02d:%02d %d",
		       ubtool_weekdays[time.tm_wday],
		       ubtool_months[time.tm_mon],
		       time.tm_mday,
		       time.tm_hour, time.tm_min, time.tm_sec,
		       time.tm_year + YEAR_BASE_NUM);
	if (ret <= 0) {
		utool_err_msg("snprintf failed, ret = %d.\n", ret);
		return UTOOL_ERR;
	}

	return UTOOL_OK;
}

static int utool_port_link_print(struct ubctl_port_link_stats *data, uint32_t data_num, char *buf)
{
#define LINK_DOWN "LINK_DOWN"
#define LINK_UP "LINK_UP"
#define LINK_DOWN_FLAG 1

	time_t ker_time;
	uint32_t i;
	int ret;

	utool_reg_msg("current time        : %s\n", buf);
	utool_reg_msg("link up count       : %u\n", data->link_up_num);
	utool_reg_msg("link down count     : %u\n", data->link_down_num);
	utool_reg_msg("link change records :\n");

	for (i = 0; i < data_num; i++) {
		ker_time = (time_t)data->link_info[i].time;
		ret = utool_time_parse(buf, *(gmtime(&ker_time)));
		if (ret) {
			return ret;
		}
		utool_reg_msg("    %s    %s\n", buf,
			      (data->link_info[i].link_status == LINK_DOWN_FLAG ? LINK_DOWN : LINK_UP));
	}

	return UTOOL_OK;
}

int utool_port_link_parse_rpc_pkt(struct fwctl_rpc_ub_out *out)
{
	char buf[UTOOL_MAX_TIME_INFO_SIZE];
	struct ubctl_port_link_stats *data;
	struct timespec ts;
	int ret = UTOOL_OK;
	uint32_t data_num;
	struct tm time;

	if ((out == NULL) || (out->data_size < sizeof(struct ubctl_port_link_stats))) {
		utool_err_msg("Param is invalid, out==null(%d), data size is too small(%d).\n",
			      (out == NULL), out == NULL ? 0 : 1);
		return UTOOL_ERR_INVALID_PARAM;
	}

	clock_gettime(CLOCK_REALTIME, &ts);
	localtime_r(&ts.tv_sec, &time);
	ret = utool_time_parse(buf, time);
	if (ret) {
		return ret;
	}
	data = (struct ubctl_port_link_stats *)out->data;
	data_num = data->link_info_num;
	if (data_num > UTOOL_MAX_PORT_LINK_STATUS) {
		utool_err_msg("the volume of data is excessive, data num = %u\n", data_num);
		return UTOOL_ERR_INVALID_PARAM;
	}

	return utool_port_link_print(data, data_num, buf);
}

static int utool_port_link_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
			       struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec port_link_pkt_exec = { UTOOL_CMD_QUERY_PORT_LINK_STATS, 0, utool_port_link_parse_rpc_pkt };
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	UTOOL_SET_USED(func_table);
	UTOOL_SET_USED(func_cnt);

	port_link_pkt_exec.data_len = sizeof(struct ubctl_port_link_stats);

	pkt_in = utool_port_create_pkt_in(&pkt_in_len, param);
	if (pkt_in == NULL) {
		utool_err_msg("Failed to create pkt in.\n");
		return UTOOL_ERR_MALLOC;
	}

	ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, &port_link_pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	utool_destroy_pkt_in(&pkt_in);

	return ret;
}

int utool_port_link_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_cmd_port_link_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_P, utool_port_link_cmd, NULL, 0 },
	};
	uint32_t cmd_port_link_cnt = UTOOL_ARRAY_SIZE(utool_cmd_port_link_table);
	uint32_t i;

	if ((dev == NULL) || (param == NULL)) {
		utool_err_msg("Failed to dispatch port link, dev==NULL(%d), param==NULL(%d).\n",
			      (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < cmd_port_link_cnt; i++) {
		if (param->flags == utool_cmd_port_link_table[i].flags) {
			if (utool_cmd_port_link_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch port_link, execute is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

		return utool_cmd_port_link_table[i].execute(dev, param,
							    utool_cmd_port_link_table[i].func_table,
							    utool_cmd_port_link_table[i].func_cnt);
		}
	}
	utool_err_msg("The ubctl query port link status command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m port_link -p {port_id}\n");

	return UTOOL_ERR_CMD_NOT_FOUND;
}
