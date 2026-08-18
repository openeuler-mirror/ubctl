// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "u_utool_help.h"
#include "u_utool_error.h"
#include "u_utool_common.h"

struct ubctl_module_info {
	const char *module_name;
	const char *functions;
};

static const char *ubctl_usage = "Usage:\n"
				 "  ubctl <-c ${chip_id}> <-d${ub_ctl_id}> <-m ${module}>\n"
				 "        [-f${function}] [-p ${port}] [-e${value}] [-u ${ummu_id}] [-i${index}]\n"
				 "        [-t ${time}] [-dev${device}] [-file ${file}] [-h] [ls]\n";

static const char *ubctl_options = "Options:\n"
				   "  -c $chip_id: chip id, chip id and ub ctl id  are used to find the valid device.\n\n"
				   "  -d $ub_ctl_id : ub ctl id, chip id and ub ctl id  are used to find the valid device.\n\n"
				   "  -m $module: module name, current module include:\n"
				   "             dl, nl, ta, tp, ba, qos, msgq, ummu, port_info, ubommu, upa,\n"
				   "             ecc_2b, queue, uboe, dump, fw_version,\n"
				   "             port_pkt_stats, port_link, ue, debugfs.\n\n"
				   "  -f $function: function name, different processing functions are provided for each module:";

static const struct ubctl_module_info ubctl_modules[] = {
	{"dl", "pkt_stats, lane, link_status, bit_err, bist, bist_err, link_trace, performance, rt_bandwidth, perf"},
	{"nl", "pkt_stats, abn_stats, ssu_stats, ssu_sw, ssu_oq, ssu_p2p, ssu_vl_pkt, p2p"},
	{"ta", "pkt_stats, abn_stats, wqe_processing_time"},
	{"tp", "pkt_stats, abn_stats, scc_version, scc_log, scc_debug_en, rx_bank, route_result"},
	{"ba", "pkt_stats, mar, mar_perf, ub_mem_decoder, inter_sp_rout, inter_mp_rout, intra_sp_rout, intra_mp_rout,\n"
		"                    port_scna, port_table, port_wb_table, mar_cyc_en, icrc"},
	{"msgq", "que_stats, entry"},
	{"ummu", "ummu_sync_query, ummu_sync_config"},
	{"uboe", "rxmac2txmac, txmac2rxmac, txpcs2rxpcs, prbs, prbs_err_cnt"},
	{"upa", "pkt_stats\n"}};

static const char *ubctl_parameters =
	"  -p $port: port index, indicates the physical port index.\n"
	"            The port_bitmap represents each bit as a port, used in the dl-performance\n"
	"            and rt_bandwidth command.\n"
	"            It represents port_num in the function upa-pkt_stats.\n\n"
	"  -e $value: value, used to set the value of the register.\n\n"
	"  -u $ummu_id: ummu id, it is used to search for the corresponding ummu register,\n"
	"               the value of ummu_id is the same as the number of io_die, the io_ide with\n"
	"               a smaller absolute address corresponds to a smaller ummu_id index.\n"
	"               It represents upa_num in the function upa-pkt_stats.\n\n"
	"  -i $index: entry index, indicates the index of entry,\n"
	"             it represents p2p_port_id in the function nl-p2p, ue id.\n\n"
	"  -t $time: time, used to query mar_perf statistics.\n"
	"            period, used to query port performance.\n\n"
	"  -dev $device: device name, can be entered: Bus_Num / Device_Name / NetDev_Name.\n\n"
	"  -file $file: file name, the specific file name queried by debugfs.\n\n"
	"  -h: help. display the help information, also use -h or --help or help or -help.\n\n"
	"  ls: querying information about all chip.\n";

static const char *ubctl_examples = "Examples:\n"
				    "  ubctl -m dl -p 0 -f bit_err -d 0 -c 0       query the number of bit errors by port\n\n"
				    "  ubctl -m ba -p 0 -f pkt_stats -d 0 -c 0     query BA packet statistics\n";

void utool_print_help(void)
{
	utool_reg_msg("%s\n", ubctl_usage);

	utool_reg_msg("%s\n", ubctl_options);

	for (size_t i = 0; i < sizeof(ubctl_modules) / sizeof(ubctl_modules[0]); i++) {
		utool_reg_msg("                %s: %s\n", ubctl_modules[i].module_name, ubctl_modules[i].functions);
	}

	utool_reg_msg("%s\n", ubctl_parameters);

	utool_reg_msg("%s\n", ubctl_examples);
}
