#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "u_utool_error.h"
#include "u_utool_create_pkt_in.h"

void *utool_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param, size_t struct_size)
{
	void *pkt_in;

	if ((pkt_in_len == NULL) || (param == NULL)) {
		utool_err_msg("Failed to create pkt in, pkt_in_len == NULL or param == NULL.\n");
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
	uint32_t *rsv = (uint32_t *)utool_create_pkt_in(pkt_in_len, param, sizeof(uint32_t));
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

	if (param->value > UINT8_MAX) {
		utool_err_msg("The value parameter is out of range.\n");
		return NULL;
	}

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

	pkt_in_enable = (struct fwctl_pkt_in_enable *)utool_create_pkt_in(pkt_in_len, param,
									  sizeof(struct fwctl_pkt_in_enable));
	if (pkt_in_enable == NULL) {
		return NULL;
	}

	pkt_in_enable->enable = param->value;
	return pkt_in_enable;
}

void *utool_index_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_index *pkt_in_index;

	pkt_in_index = (struct fwctl_pkt_in_index *)utool_create_pkt_in(pkt_in_len, param,
									sizeof(struct fwctl_pkt_in_index));
	if (pkt_in_index == NULL) {
		return NULL;
	}

	pkt_in_index->index = param->index;
	return pkt_in_index;
}

void *utool_port_time_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_port_time *pkt_in_port_time;

	pkt_in_port_time = (struct fwctl_pkt_in_port_time *)utool_create_pkt_in(pkt_in_len, param,
										sizeof(struct fwctl_pkt_in_port_time));
	if (pkt_in_port_time == NULL) {
		return NULL;
	}

	pkt_in_port_time->port_id = param->port;
	pkt_in_port_time->time = param->time;

	return pkt_in_port_time;
}

void *utool_time_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_time *pkt_in_time;

	pkt_in_time = (struct fwctl_pkt_in_time *)utool_create_pkt_in(pkt_in_len, param,
								      sizeof(struct fwctl_pkt_in_time));
	if (pkt_in_time == NULL) {
		return NULL;
	}

	pkt_in_time->time = param->time;

	return pkt_in_time;
}

void *utool_prbs_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
#define UBCTL_PRBS_ERR_CNT_VAL 1U

	uint32_t data_size = sizeof(struct fwctl_pkt_in_prbs);
	struct fwctl_pkt_in_prbs *pkt_in_prbs;

	pkt_in_prbs = (struct fwctl_pkt_in_prbs *)utool_create_pkt_in(pkt_in_len, param, data_size);
	if (pkt_in_prbs == NULL) {
		return NULL;
	}

	pkt_in_prbs->port_id = param->port;
	pkt_in_prbs->query_prbs_err_cnt = UBCTL_PRBS_ERR_CNT_VAL;

	return pkt_in_prbs;
}

void *utool_loopback_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_loopback *pkt_in_loopback;

	pkt_in_loopback = (struct fwctl_pkt_in_loopback *)utool_create_pkt_in(pkt_in_len, param,
									      sizeof(struct fwctl_pkt_in_loopback));
	if (pkt_in_loopback == NULL) {
		return NULL;
	}

	if (strcmp(param->func, UBOE_LOOPBACK_PCS_INNER) == 0) {
		pkt_in_loopback->loopback_mode = UTOOL_TXPCS2RXPCS;
	} else if (strcmp(param->func, UBOE_LOOPBACK_MAC_INNER) == 0) {
		pkt_in_loopback->loopback_mode = UTOOL_TXMAC2RXMAC;
	} else {
		pkt_in_loopback->loopback_mode = UTOOL_RXMAC2TXMAC;
	}

	pkt_in_loopback->port_id = param->port;
	pkt_in_loopback->enable = param->value;

	return pkt_in_loopback;
}

void *utool_ummu_value_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_ummuid_value *pkt_in_ummu_value;

	pkt_in_ummu_value = (struct fwctl_pkt_in_ummuid_value *)utool_create_pkt_in(
		pkt_in_len, param, sizeof(struct fwctl_pkt_in_ummuid_value));
	if (pkt_in_ummu_value == NULL) {
		return NULL;
	}

	pkt_in_ummu_value->ummu_id = param->ummu_id;
	pkt_in_ummu_value->value = param->value;

	return pkt_in_ummu_value;
}

void *utool_port_index_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_port_index *pkt_in_port_index;

	pkt_in_port_index = (struct fwctl_pkt_in_port_index *)utool_create_pkt_in(
		pkt_in_len, param, sizeof(struct fwctl_pkt_in_port_index));
	if (pkt_in_port_index == NULL) {
		return NULL;
	}

	pkt_in_port_index->port_id = param->port;
	pkt_in_port_index->index = param->index;

	return pkt_in_port_index;
}

void *utool_port_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_port *pkt_in_port;

	pkt_in_port = (struct fwctl_pkt_in_port *)utool_create_pkt_in(pkt_in_len, param,
								      sizeof(struct fwctl_pkt_in_port));
	if (pkt_in_port == NULL) {
		return NULL;
	}

	pkt_in_port->port_id = param->port;
	return pkt_in_port;
}

void *utool_vl_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
#define UBCTL_CONF_SSU_VL_FLAG 1U

	struct fwctl_pkt_in_vl *pkt_in_vl;

	pkt_in_vl = (struct fwctl_pkt_in_vl *)utool_create_pkt_in(pkt_in_len, param, sizeof(struct fwctl_pkt_in_vl));
	if (pkt_in_vl == NULL) {
		return NULL;
	}

	pkt_in_vl->port_id = param->port;
	pkt_in_vl->enable = UBCTL_CONF_SSU_VL_FLAG;
	pkt_in_vl->vl_num = param->value;

	return pkt_in_vl;
}

void *utool_upa_port_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param)
{
	struct fwctl_pkt_in_upa_port *pkt_in_upa_port;

	pkt_in_upa_port = (struct fwctl_pkt_in_upa_port *)utool_create_pkt_in(pkt_in_len, param,
									      sizeof(struct fwctl_pkt_in_upa_port));
	if (pkt_in_upa_port == NULL) {
		return NULL;
	}

	pkt_in_upa_port->upa_num = param->ummu_id;
	pkt_in_upa_port->port_num = param->port;

	return pkt_in_upa_port;
}
