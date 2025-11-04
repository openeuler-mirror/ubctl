/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_DISPATCH_H__
#define __U_UTOOL_DISPATCH_H__

#include "u_utool_common.h"

int utool_transform_str(char *param, uint32_t *value);
int utool_cmd_select(struct utool_dev *dev);
int utool_parse_command(int argc, char **argv);
const struct utool_cmd_param *utool_get_cmd_param(void);

#endif
