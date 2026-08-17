#ifndef __UTOOL_CREATE_PKT_IN_H__
#define __UTOOL_CREATE_PKT_IN_H__

#include <stdint.h>
#include "u_utool_error.h"
#include "u_utool_common.h"

#define UBOE_LOOPBACK_MAC_OUTER "rxmac2txmac"
#define UBOE_LOOPBACK_MAC_INNER "txmac2rxmac"
#define UBOE_LOOPBACK_PCS_INNER "txpcs2rxpcs"
#define UBOE_PRBS_EN "prbs"
#define UBOE_PRBS_RESULT "prbs_err_cnt"

enum utool_loopback_mode {
	UTOOL_RXMAC2TXMAC = 0,
	UTOOL_TXMAC2RXMAC,
	UTOOL_TXPCS2RXPCS,
};

struct fwctl_pkt_in_port_index {
	uint32_t port_id;
	uint32_t index;
};

struct fwctl_pkt_in_port_enable {
	uint32_t port_id;
	uint8_t enable;
};

struct fwctl_pkt_in_port_info {
	uint32_t port_id;
	uint16_t query_type;
	uint16_t module_type;
};

struct fwctl_pkt_in_prbs {
	uint32_t port_id;
	uint32_t enable;
	uint32_t query_prbs_err_cnt;
};

struct fwctl_pkt_in_loopback {
	uint32_t port_id;
	enum utool_loopback_mode loopback_mode;
	uint32_t enable;
};

struct fwctl_pkt_in_vl {
	uint32_t port_id;
	uint32_t enable;
	uint32_t vl_num;
};

struct fwctl_pkt_in_ue_info {
	uint32_t ue_id;
};

struct fwctl_pkt_in_upa_port {
	uint32_t upa_num;
	uint32_t port_num;
};

void *utool_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param, size_t struct_size);
void *utool_null_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);
void *utool_port_enable_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);
void *utool_enable_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);
void *utool_index_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);
void *utool_port_time_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);
void *utool_time_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);
void *utool_prbs_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);
void *utool_loopback_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);
void *utool_ummu_value_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);
void *utool_port_index_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);
void *utool_port_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);
void *utool_vl_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);
void *utool_upa_port_create_pkt_in(uint32_t *pkt_in_len, struct utool_cmd_param *param);

#endif /* __UTOOL_CREATE_PKT_IN_H__ */
