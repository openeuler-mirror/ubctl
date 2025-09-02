// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <inttypes.h>

#include "u_utool_error.h"
#include "u_utool_pkt.h"

static void utool_delete_substr(char *str, const char *substr)
{
	uint32_t substr_len = 0;
	uint32_t str_len = 0;
	uint32_t pos = 0;
	uint32_t i = 0;

	str_len = (uint32_t)strlen(str);
	substr_len = (uint32_t)strlen(substr);
	if (str_len < substr_len) {
		return;
	}

	while (strstr(str, substr) != NULL) {
		pos = strstr(str, substr) - str;
		for (i = pos; i < str_len - substr_len; ++i) {
			str[i] = str[i + substr_len];
		}
		str_len -= substr_len;
		str[str_len] = '\0';
	}
}

int utool_cal_reg_cnt(struct utool_field_info *field_info, uint32_t field_cnt, uint32_t *reg_cnt)
{
	uint32_t count = 0;
	uint32_t i = 0;

	if ((field_info == NULL) || (reg_cnt == NULL)) {
		utool_err_msg("Failed to get reg_cnt, field_info==NULL(%d), reg_cnt==NULL(%d).\n",
			      (field_info == NULL), (reg_cnt == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < field_cnt; i++) {
		if (field_info[i].end == UTOOL_REG_LOC31) {
			count++;
		}
	}

	*reg_cnt = count;

	return UTOOL_OK;
}

static int utool_parse_param_check(struct fwctl_rpc_ub_out *out, struct utool_field_info *field_info,
				   const char *module_func_name)
{
	if ((out == NULL) || (field_info == NULL) || (module_func_name == NULL)) {
		utool_err_msg("Failed to parse pkt, param is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if ((out->data_size == 0) || (out->data == NULL)) {
		utool_err_msg("Failed to parse pkt, param is invalid data_size==0(%d), data==NULL(%d).\n",
			      (out->data_size == 0), (out->data == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

static void utool_data_merge(bool is_high_before, uint64_t *data, uint64_t field_data,
			     uint32_t field_count, uint32_t len)
{
	uint64_t merge_field_data = field_data;
	uint64_t merge_data = *data;

	if (!is_high_before) {
		merge_field_data = merge_field_data << field_count;
	} else {
		merge_data = merge_data << len;
	}

	*data = merge_data | merge_field_data;
}

static void utool_reg_name_deal(char *reg_name)
{
#define SUBSTR_LOW "_low"
#define SUBSTR_HIGH "_high"

	if (strstr(reg_name, SUBSTR_LOW) != NULL) {
		utool_delete_substr(reg_name, SUBSTR_LOW);
	}

	if (strstr(reg_name, SUBSTR_HIGH) != NULL) {
		utool_delete_substr(reg_name, SUBSTR_HIGH);
	}
}

static inline void utool_pkt_print(bool is_reserved, const char *reg_name, uint64_t merge_data)
{
	if (!is_reserved) {
		utool_reg_msg("%s: 0x%llx\n", reg_name, merge_data);
	}
}

static int utool_cal_func_reg_len_check(const char *func_name, struct utool_cal_reg_func_param *cal_reg_param)
{
	if (func_name == NULL || cal_reg_param == NULL) {
		utool_err_msg("Param is invalid, input is null;");
		return UTOOL_ERR_INVALID_PARAM;
	}

	if ((cal_reg_param->data_len == NULL) || (cal_reg_param->utool_cal_reg_table == NULL) ||
	    (cal_reg_param->func_cnt == 0)) {
		utool_err_msg("Param is invalid, length==NULL(%d), table==NULL(%d), count==0(%d).\n",
			      (cal_reg_param->data_len == NULL), (cal_reg_param->utool_cal_reg_table == NULL),
			      (cal_reg_param->func_cnt == 0));
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

int utool_cal_func_reg_len(const char *func_name, struct utool_cal_reg_func_param *cal_reg_param)
{
	struct utool_cal_reg_cnt_dp *reg_table = NULL;
	uint32_t func_reg_cnt = 0, total_reg_cnt = 0;
	int ret = UTOOL_OK;
	uint32_t i;

	ret = utool_cal_func_reg_len_check(func_name, cal_reg_param);
	if (ret != UTOOL_OK) {
		return ret;
	}

	reg_table = cal_reg_param->utool_cal_reg_table;
	for (i = 0; i < cal_reg_param->func_cnt; i++) {
		if (!reg_table[i].is_read_reg) {
			if (strcmp(reg_table[i].func, func_name) == 0) {
				*cal_reg_param->data_len = cal_reg_param->user_def_data_len;
				return UTOOL_OK;
			}
			continue;
		}

		ret = utool_cal_reg_cnt(reg_table[i].field_info,
								reg_table[i].field_cnt, &func_reg_cnt);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to calculate reg cnt, func name = %s, ret = %d.\n",
				      reg_table[i].func, ret);
			return ret;
		}

		if (strcmp(reg_table[i].func, TP_RX_BANK) == 0) {
			func_reg_cnt *= UBCTL_TP_RX_BANK_NUM;
		}

		if (strcmp(reg_table[i].func, func_name) == 0) {
			if (cal_reg_param->offset_data_len != NULL) {
				*cal_reg_param->offset_data_len = total_reg_cnt * sizeof(uint32_t);
			}
			*cal_reg_param->data_len = func_reg_cnt * sizeof(uint32_t);
			return UTOOL_OK;
		}

		if (reg_table[i].is_dump) {
			total_reg_cnt += func_reg_cnt;
		}
	}

	utool_err_msg("Unknown func name: %s.\n", func_name);

	return UTOOL_ERR_INVALID_CMD;
}

static int utool_module_parse_input_check(struct fwctl_rpc_ub_out *out,
					  uint32_t func_table_cnt, struct utool_func_dispatch *func_table,
					  uint32_t cal_reg_table_cnt, struct utool_cal_reg_cnt_dp *cal_reg_table)
{
	if ((out == NULL) || (func_table == NULL) || (cal_reg_table == NULL)) {
		utool_err_msg("Param is invalid, out==null(%d), func_table==NULL(%d), cal_reg_table==NULL(%d).\n",
			      (out == NULL), (func_table == NULL), (cal_reg_table == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	if ((func_table_cnt == 0) || (cal_reg_table_cnt == 0)) {
		utool_err_msg("Param is invalid, func_table_cnt==0(%d), cal_reg_table_cnt==0(%d).\n",
			      (func_table_cnt == 0), (cal_reg_table_cnt == 0));
		return UTOOL_ERR_INVALID_PARAM;
	}

	if ((out->data_size == 0) || (out->data == NULL)) {
		utool_err_msg("Failed to split module, param is invalid data_size==0(%d), data==NULL(%d).\n",
			      (out->data_size == 0), (out->data == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

int utool_module_parse(struct fwctl_rpc_ub_out *out,
		       uint32_t func_table_cnt, struct utool_func_dispatch *func_table,
		       uint32_t cal_reg_table_cnt, struct utool_cal_reg_cnt_dp *cal_reg_table)
{
	struct utool_cal_reg_func_param cal_reg_param = { NULL, 0, NULL, cal_reg_table, cal_reg_table_cnt };
	struct fwctl_rpc_ub_out *func_pkt_out = NULL;
	uint32_t func_pkt_out_max_len = 0;
	uint32_t offset_data_len = 0;
	uint32_t func_data_len = 0;
	void *pos_index = NULL;
	int ret = UTOOL_OK;
	uint32_t i = 0;

	if (utool_module_parse_input_check(out, func_table_cnt, func_table, cal_reg_table_cnt,
					   cal_reg_table) != UTOOL_OK) {
		return UTOOL_ERR_INVALID_PARAM;
	}

	cal_reg_param.data_len = &func_data_len;
	cal_reg_param.offset_data_len = &offset_data_len;

	func_pkt_out_max_len = (uint32_t)(out->data_size + sizeof(struct fwctl_rpc_ub_out));
	func_pkt_out = (struct fwctl_rpc_ub_out *)UTOOL_MALLOC(func_pkt_out_max_len);
	if (func_pkt_out == NULL) {
		utool_err_msg("Failed to malloc space for func data.\n");
		return UTOOL_ERR_MALLOC;
	}
	func_pkt_out->retval = 0;

	for (i = 0; i < func_table_cnt; i++) {
		if (!func_table[i].is_dump) {
			continue;
		}

		memset(func_pkt_out, 0x0, func_pkt_out_max_len);

		ret = utool_cal_func_reg_len(func_table[i].func, &cal_reg_param);
		if (ret != UTOOL_OK || func_data_len == 0) {
			utool_err_msg("Failed to cal func %s reg cnt.\n", func_table[i].func);
			break;
		}

		func_pkt_out->data_size = func_data_len;

		pos_index = (void *)((uint8_t *)(out->data) + offset_data_len);
		memcpy(func_pkt_out->data, pos_index, func_pkt_out->data_size);

		if (func_table[i].execute == NULL) {
			utool_err_msg("The func %s's excute is NULL.\n", func_table[i].func);
			ret = UTOOL_ERR;
			break;
		}

		ret = func_table[i].execute(func_pkt_out);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to parse all pkt, %s parse is error, ret = %d.\n",
				      func_table[i].func, ret);
			break;
		}
	}

	UTOOL_FREE(func_pkt_out);

	return ret;
}

int utool_pkt_parse(struct fwctl_rpc_ub_out *out, uint32_t field_cnt, struct utool_field_info *field_info,
		    const char *module_func_name)
{
	uint32_t field_count = 0, count = 0, reg_cnt = 0;
	uint32_t data, len, i, j = 0;
	uint64_t merge_data = 0;

	if (utool_parse_param_check(out, field_info, module_func_name) != UTOOL_OK) {
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (utool_cal_reg_cnt(field_info, field_cnt, &reg_cnt) != UTOOL_OK) {
		return UTOOL_ERR_CAL_REG_CNT;
	}

	utool_reg_msg("-------------------------- %s --------------------------\n", module_func_name);
	for (i = 0; i < reg_cnt; i++) {
		for (; j < field_cnt; j++) {
			if (count >= UTOOL_REG_MAX_LEN) {
				count = 0;
				break;
			}

			if (field_info[j].end < field_info[j].start) {
				utool_err_msg("Failed to parse pkt, start is bigger than end.\n");
				return UTOOL_ERR_PARSE;
			}

			len = field_info[j].end - field_info[j].start + 1;

			if (len > UTOOL_REG_MAX_LEN) {
				utool_err_msg("Failed to parse pkt, length of field is bigger than 32.\n");
				return UTOOL_ERR_PARSE;
			} else if (len == UTOOL_REG_MAX_LEN) {
				data = out->data[i];
			} else {
				data = UTOOL_EXTRACT_BITS(out->data[i], field_info[j].start, field_info[j].end);
			}

			count += len;

			utool_data_merge(field_info[j].is_high_before, &merge_data, (uint64_t)data, field_count, len);
			field_count += len;
			utool_reg_name_deal(field_info[j].reg_name);

			/* print the last data */
			if ((j + 1) >= field_cnt) {
				utool_pkt_print(field_info[j].is_reserved, field_info[j].reg_name, merge_data);
				break;
			}

			if (field_info[j + 1].index != UTOOL_FIELD_INDEX_START) {
				continue;
			}

			utool_pkt_print(field_info[j].is_reserved, field_info[j].reg_name, merge_data);

			field_count = 0;
			merge_data = 0;
		}
	}

	return UTOOL_OK;
}

static int utool_operation_param_check(struct utool_dev *dev, void *pkt_in,
				       struct utool_pkt_exec *pkt_exec)
{
	if ((dev == NULL) || (pkt_in == NULL) || (pkt_exec == NULL)) {
		utool_err_msg("Failed to build pkt, dev==NULL(%d), pkt_in==NULL(%d), pkt_exec==NULL(%d).\n",
			      (dev == NULL), (pkt_in == NULL), (pkt_exec == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	if (pkt_exec->execute == NULL) {
		utool_err_msg("Failed to build pkt, pkt_exec execute is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

static void utool_fill_in_data(void *pkt_in, uint32_t pkt_in_len, struct fwctl_rpc_ub_in *rpc_in,
			       struct utool_pkt_exec *pkt_exec)
{
	rpc_in->rpc_cmd = (uint32_t)pkt_exec->rpc_cmd;
	rpc_in->data_size = pkt_in_len;
	rpc_in->version = UTOOL_VERSION;

	memcpy(rpc_in->data, pkt_in, pkt_in_len);
}

int utool_pkt_operation(struct utool_dev *dev, void *pkt_in, uint32_t pkt_in_len, struct utool_pkt_exec *pkt_exec)
{
	struct fwctl_rpc_ub_out *pkt_out = NULL;
	struct fwctl_rpc_ub_in *in = NULL;
	uint32_t pkt_out_len = 0;
	uint32_t in_len = 0;
	int ret = UTOOL_OK;

	if (utool_operation_param_check(dev, pkt_in, pkt_exec) != UTOOL_OK) {
		return UTOOL_ERR_INVALID_PARAM;
	}

	in_len = (uint32_t)(sizeof(struct fwctl_rpc_ub_in) + pkt_in_len);
	in = (struct fwctl_rpc_ub_in *)UTOOL_MALLOC(in_len);
	if (in == NULL) {
		utool_err_msg("Failed to malloc space for in.\n");
		return UTOOL_ERR_MALLOC;
	}

	utool_fill_in_data(pkt_in, pkt_in_len, in, pkt_exec);

	do {
		pkt_out_len = (uint32_t)(sizeof(struct fwctl_rpc_ub_out) + pkt_exec->data_len);
		pkt_out = (struct fwctl_rpc_ub_out *)UTOOL_MALLOC(pkt_out_len);
		if (pkt_out == NULL) {
			utool_err_msg("Failed to malloc space for pkt_out.\n");
			ret = UTOOL_ERR_MALLOC;
			break;
		}
		memset(pkt_out, 0x0, pkt_out_len);

		ret = utool_cmd_exec(dev, in, in_len, pkt_out, &pkt_out_len);
		if (pkt_out->retval != 0) {
			ret = UTOOL_ERR_IOCTL;
			break;
		}

		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to execute cmd, utool_cmd_exec, ret = %d\n", ret);
			break;
		}

		if ((pkt_out->data_size != pkt_exec->data_len) &&
			(pkt_exec->rpc_cmd != UTOOL_CMD_QUERY_IO_DIE_PORT_INFO)) {
			utool_err_msg("Failed to get pkt_out data, datasize is err, pkt out data_size = %u, data len = %u.\n",
				      pkt_out->data_size, pkt_exec->data_len);
			ret = UTOOL_ERR;
			break;
		}

		ret = pkt_exec->execute(pkt_out);
	} while (0);

	UTOOL_FREE(pkt_out);
	UTOOL_FREE(in);

	return ret;
}

void utool_destroy_pkt_in(void **pkt_in)
{
	UTOOL_FREE(*pkt_in);
}

static int utool_create_param_check(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	if ((pkt_in_len == NULL) || (param == NULL)) {
		utool_err_msg("Failed to create pkt in, pkt_in_len == NULL(%d), param == NULL(%d).\n",
			      (pkt_in_len == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	return UTOOL_OK;
}

void *utool_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param, size_t struct_size)
{
	void *pkt_in = NULL;

	if (utool_create_param_check(pkt_in_len, param) != UTOOL_OK) {
		return NULL;
	}

	pkt_in = UTOOL_MALLOC(struct_size);
	if (pkt_in == NULL) {
		utool_err_msg("Failed to malloc pkt in.\n");
		return NULL;
	}
	memset(pkt_in, 0x0, struct_size);
	*pkt_in_len = struct_size;
	return pkt_in;
}

void *utool_null_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	uint32_t *rsv;

	rsv = (uint32_t *)utool_create_pkt_in(pkt_in_len, param, sizeof(uint32_t));
	if (rsv == NULL) {
		return NULL;
	}

	*rsv = 0;
	return rsv;
}

void *utool_port_enable_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_port_enable *pkt_in_port_enable;
	uint32_t data_size = sizeof(struct fwctl_pkt_in_port_enable);

	pkt_in_port_enable = (struct fwctl_pkt_in_port_enable *)utool_create_pkt_in(pkt_in_len, param, data_size);
	if (pkt_in_port_enable == NULL) {
		return NULL;
	}

	pkt_in_port_enable->port_id = param->port;
	pkt_in_port_enable->enable = (uint8_t)param->value;
	return pkt_in_port_enable;
}

void *utool_enable_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_enable *pkt_in_enable;

	pkt_in_enable = utool_create_pkt_in(pkt_in_len, param, sizeof(struct fwctl_pkt_in_enable));
	if (pkt_in_enable == NULL) {
		return NULL;
	}

	pkt_in_enable->enable = param->value;
	return pkt_in_enable;
}

void *utool_index_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_index *pkt_in_index;

	pkt_in_index = utool_create_pkt_in(pkt_in_len, param, sizeof(struct fwctl_pkt_in_index));
	if (pkt_in_index == NULL) {
		return NULL;
	}

	pkt_in_index->index = param->index;
	return pkt_in_index;
}

void *utool_port_time_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_port_time *pkt_in_port_time;

	pkt_in_port_time = utool_create_pkt_in(pkt_in_len, param, sizeof(struct fwctl_pkt_in_port_time));
	if (pkt_in_port_time == NULL) {
		return NULL;
	}

	pkt_in_port_time->port_id = param->port;
	pkt_in_port_time->time = param->time;

	return pkt_in_port_time;
}

void *utool_port_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_port *pkt_in_port;

	pkt_in_port = (struct fwctl_pkt_in_port *)utool_create_pkt_in(pkt_in_len, param, sizeof(struct fwctl_pkt_in_port));
	if (pkt_in_port == NULL) {
		return NULL;
	}

	pkt_in_port->port_id = param->port;
	return pkt_in_port;
}

int utool_pkt_operation_have_port(struct utool_dev *dev, struct utool_cmd_param *param, struct utool_pkt_exec *pkt_exec)
{
	uint32_t pkt_in_len = 0;
	void *pkt_in = NULL;
	int ret = UTOOL_OK;

	if ((dev == NULL) || (param == NULL) || (pkt_exec == NULL)) {
		utool_err_msg("Failed to check param, dev==NULL(%d), param==NULL(%d), pkt_exec==NULL(%d).\n",
			      (dev == NULL), (param == NULL), (pkt_exec == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	pkt_in = utool_port_create_pkt_in(&pkt_in_len, param);
	if (pkt_in == NULL) {
		utool_err_msg("Failed to create pkt in.\n");
		return UTOOL_ERR_MALLOC;
	}

	ret = utool_pkt_operation(dev, pkt_in, pkt_in_len, pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	utool_destroy_pkt_in(&pkt_in);
	return ret;
}
