/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_ECC_2B_H__
#define __U_UTOOL_ECC_2B_H__

#include "../common/u_utool_fwctl.h"
#include "../common/u_utool_common.h"

int utool_ecc_2b_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param);
int utool_ecc_2b_cal_data_len(uint32_t *ecc_2b_data_len);
int utool_ecc_2b_parse_rpc_pkt(struct fwctl_rpc_ub_out *ecc_2b_out);
struct utool_field_info *utool_ecc_2b_cmd_diff_ver_dispatch(const char *module_func_name,
							    uint32_t reg_version, uint32_t reg_info_index,
							    uint32_t *replace_field_cnt);

#endif
