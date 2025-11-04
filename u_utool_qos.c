// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_pkt.h"
#include "u_utool_error.h"
#include "u_utool_qos.h"

static struct utool_field_info g_utool_qos_field[] = {
	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "port_id" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp0)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp1)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp2)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp3)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp4)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp5)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp6)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp7)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp8)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp9)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp10)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp11)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp12)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp13)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp14)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "tp_axqos(grp15)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "ta_axqos(grp0)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "ta_axqos(grp1)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "ta_axqos(grp2)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "ta_axqos(grp3)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "ta_axqos(grp4)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "ta_axqos(grp5)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "ta_axqos(grp6)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "ta_axqos(grp7)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "ta_axqos(grp8)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "ta_axqos(grp9)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "ta_axqos(grp10)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp0)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp1)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp2)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp3)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp4)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp5)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp6)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp7)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp8)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp9)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp10)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp11)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp12)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp13)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp14)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "nl_axqos(grp15)" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp0)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp1)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp2)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp3)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp4)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp5)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp6)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp7)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp8)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp9)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp10)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp11)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp12)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp13)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp14)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_cmdq_axqos(grp15)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_8win_axqos(win0)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_8win_axqos(win1)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_8win_axqos(win2)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_8win_axqos(win3)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_8win_axqos(win4)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_8win_axqos(win5)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_8win_axqos(win6)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "misc_8win_axqos(win7)" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC23, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC24, UTOOL_REG_LOC27, UTOOL_FIELD_INDEX_START, "misc_msix_axqos" },
	{ false, true, UTOOL_REG_LOC28, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, true, UTOOL_REG_LOC0, UTOOL_REG_LOC10, UTOOL_FIELD_INDEX_START, "reserved" },
	{ false, false, UTOOL_REG_LOC11, UTOOL_REG_LOC14, UTOOL_FIELD_INDEX_START, "ub_memory_axqos" },
	{ false, true, UTOOL_REG_LOC15, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "reserved" },

	{ false, false, UTOOL_REG_LOC0, UTOOL_REG_LOC31, UTOOL_FIELD_INDEX_START, "tp_lsa_req_qos_ctrl" },
};

int utool_qos_cal_data_len(uint32_t *qos_data_len)
{
	uint32_t qos_reg_cnt = 0;
	int ret = UTOOL_OK;

	if (qos_data_len == NULL) {
		utool_err_msg("Param is invalid, qos data len is null.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_cal_reg_cnt(g_utool_qos_field, UTOOL_ARRAY_SIZE(g_utool_qos_field), &qos_reg_cnt);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to calculate qos reg cnt.\n");
		return ret;
	}

	*qos_data_len = qos_reg_cnt * sizeof(uint32_t);
	return UTOOL_OK;
}

int utool_qos_parse_rpc_pkt(struct fwctl_rpc_ub_out *qos_out)
{
	int ret = UTOOL_OK;

	if (qos_out == NULL) {
		utool_err_msg("Failed to parse qos rpc pkt, qos_out is NULL.\n");
		return UTOOL_ERR_INVALID_PARAM;
	}

	ret = utool_pkt_parse(qos_out, UTOOL_ARRAY_SIZE(g_utool_qos_field), g_utool_qos_field, UTOOL_MODULE_QOS);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to parse qos data.\n");
	}

	return ret;
}

static int utool_qos_cmd(struct utool_dev *dev, struct utool_cmd_param *param,
			 struct utool_func_dispatch *func_table, uint32_t func_cnt)
{
	struct utool_pkt_exec qos_pkt_exec = { UTOOL_CMD_QUERY_QOS, 0, NULL };
	int ret = UTOOL_OK;

	ret = utool_qos_cal_data_len(&qos_pkt_exec.data_len);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to cal qos reg cnt.\n");
		return ret;
	}

	qos_pkt_exec.execute = utool_qos_parse_rpc_pkt;

	ret = utool_pkt_operation_have_port(dev, param, &qos_pkt_exec);
	if (ret != UTOOL_OK) {
		utool_err_msg("Failed to execute command, ret = %d.\n", ret);
	}

	return ret;
}

int utool_qos_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param)
{
	struct utool_cmd_dispatch utool_cmd_qos_table[] = {
		{ UTOOL_FLAG_M | UTOOL_FLAG_P, utool_qos_cmd, NULL, 0 },
	};
	uint32_t cmd_qos_cnt = UTOOL_ARRAY_SIZE(utool_cmd_qos_table);
	uint32_t i = 0;

	if ((dev == NULL) || (param == NULL)) {
		utool_err_msg("Failed to dispatch qos, dev==NULL(%d), param==NULL(%d).\n", (dev == NULL), (param == NULL));
		return UTOOL_ERR_INVALID_PARAM;
	}

	for (i = 0; i < cmd_qos_cnt; i++) {
		if (param->flags == utool_cmd_qos_table[i].flags) {
			if (utool_cmd_qos_table[i].execute == NULL) {
				utool_err_msg("Failed to dispatch qos, execute is NULL.\n");
				return UTOOL_ERR_INVALID_PARAM;
			}

			return utool_cmd_qos_table[i].execute(dev, param,
							      utool_cmd_qos_table[i].func_table,
							      utool_cmd_qos_table[i].func_cnt);
		}
	}
	utool_err_msg("The ubctl qos command must be in the following formats:\n"
		      "ubctl -c ${chip_id} -d ${ub_ctl_id} -m qos -p ${port}\n");

	return UTOOL_ERR_CMD_NOT_FOUND;
}
