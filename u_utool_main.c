// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <ctype.h>
#include <stddef.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

#include "./common/u_utool_error.h"
#include "./common/u_utool_common.h"
#include "./feature/u_utool_io_die.h"
#include "u_utool_dispatch.h"
#include "u_utool_pkt.h"

static void utool_help(void)
{
	utool_info_msg("Usage: ubctl <-c ${chip_id}> <-d ${ub_ctl_id}> <-m ${module}>\n"
		       "       [-f ${function}] [-p ${port}] [-e ${value}] [-u ${ummu_id}] [-i ${index}]\n"
		       "       [-t ${time}] [-dev ${device}] [-file ${file}] [-h] [ls]\n\n"
		       "options:\n\n"
		       "  -c $chip_id: chip id, chip id and ub ctl id  are used to find the valid device.\n\n"
		       "  -d $ub_ctl_id : ub ctl id, chip id and ub ctl id  are used to find the valid device.\n\n"
		       "  -m $module: module name, current module include: dl, nl, ta, tp, ba, qos, msgq,\n\n"
		       "              ummu, port_info, ubommu, ecc_2b, queue, uboe, dump,\n"
		       "              port_pkt_stats, fw_version, port_link, debugfs.\n\n"
		       "  -f $function: function name, different processing functions are provided for each module.\n"
		       "                dl: pkt_stats, lane, link_status, bit_err, bist, bist_err, link_trace,\n"
		       "                    performance, rt_bandwidth, perf\n"
		       "                nl: pkt_stats, abn_stats, ssu_stats, ssu_sw, ssu_oq, ssu_p2p, ssu_vl_pkt\n"
		       "                ta: pkt_stats, abn_stats, wqe_processing_time\n"
		       "                tp: pkt_stats, abn_stats, scc_version, scc_log, scc_debug_en, rx_bank,\n"
		       "                    route_result\n"
		       "                ba: pkt_stats, mar, mar_perf, ub_mem_decoder, inter_sp_rout, inter_mp_rout,\n"
		       "                    intra_sp_rout, intra_mp_rout, port_scna, port_table, port_wb_table,\n"
		       "                    mar_cyc_en\n"
		       "                msgq: que_stats, entry\n"
		       "                ummu: ummu_sync_query, ummu_sync_config\n"
		       "                uboe: rxmac2txmac, txmac2rxmac, txpcs2rxpcs, prbs, prbs_err_cnt\n\n"
		       "  -p $port: port index, indicates the physical port index,\n"
		       "            The port_bitmap represents each bit as a port, used in the dl-performance\n"
		       "            and rt_bandwidth command.\n\n"
		       "  -e $value: value, used to set the value of the register.\n\n"
		       "  -u $ummu_id: ummu id, it is used to search for the corresponding ummu register,\n"
		       "               the value of ummu_id is the same as the number of io_die, the io_ide with\n"
		       "               a smaller absolute address corresponds to a smaller ummu_id index.\n\n"
		       "  -i $index: entry index, indicates the index of entry.\n\n"
		       "  -t $time: time, used to query mar_perf statistics.\n"
		       "            period, used to query port performance.\n\n"
		       "  -dev $device: device name, can be entered: Bus_Num / Device_Name / NetDev_Name.\n\n"
		       "  -file $file: file name, the specific file name queried by debugfs.\n\n"
		       "  -h: help. display the help information, also use -h or --help or help or -help.\n\n"
		       "  ls: querying information about all chip.\n\n"
		       "example:\n\n"
		       "   ubctl -m dl -p 0 -f bit_err -d 0 -c 0       query the number of bit errors by port\n\n"
		       "   ubctl -m ba -p 0 -f pkt_stats -d 0 -c 0     query BA packet statistics\n\n");
}

static int utool_check_arg(int argc, char **argv)
{
	char *argv_ptr = NULL;
	char argv_value = ' ';
	size_t argv_len = 0;
	size_t j = 0;
	int i = 0;

	for (i = 1; i < argc; i++) {
		if (strchr(argv[i], '\0') == NULL) {
			utool_err_msg("The input parameter is not string.\n");
			return UTOOL_ERR;
		}

		argv_len = strlen(argv[i]);
		if (argv_len > UBCTL_FILE_NAME_MAX_LEN) {
			utool_err_msg("The input param length = %zubytes is bigger than maximum %ubytes.\n",
				      argv_len, UBCTL_FILE_NAME_MAX_LEN);
			return UTOOL_ERR;
		}

		argv_ptr = argv[i];
		for (j = 0; j < argv_len; j++) {
			argv_value = argv_ptr[j];
			if ((isalnum(argv_value) == 0) && argv_value != '_' && argv_value != '-') {
				utool_err_msg("The input parameter is illegal string.\n");
				return UTOOL_ERR;
			}
		}
	}

	return UTOOL_OK;
}

static int utool_main_parse_sub(int argc, char **argv, struct utool_dev *dev)
{
#define UBCTL_ARG_MIN_NUM 2

	int ret = UTOOL_OK;

	do {
		if (argc < UBCTL_ARG_MIN_NUM) {
			ret = UTOOL_ERR_INVALID_PARAM;
			break;
		}

		ret = utool_check_arg(argc, argv);
		if (ret != UTOOL_OK) {
			break;
		}

		if (strcmp(argv[1], "ls") == 0) {
			return utool_open_dev_step(dev, 0, 0, UTOOL_DEV_STEP_LS);
		}

		if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0) ||
		    (strcmp(argv[1], "help") == 0) || (strcmp(argv[1], "-help") == 0)) {
			ret = UTOOL_ERR_HELP;
			break;
		}

		ret = utool_parse_command(argc, argv);
		if (ret != UTOOL_OK) {
			utool_err_msg("Failed to parse command.\n");
			break;
		}
	} while (0);

	if (ret != UTOOL_OK) {
		utool_help();
	}

	return ret;
}

int main(int argc, char *argv[])
{
	const struct utool_cmd_param *cmd_param = NULL;
	struct utool_dev dev = {};
	int ret = UTOOL_OK;

	ret = utool_main_parse_sub(argc, argv, &dev);
	if (ret != UTOOL_OK) {
		return ret == UTOOL_OK_LS ? UTOOL_OK : ret;
	}

	cmd_param = utool_get_cmd_param();
	if (cmd_param == NULL) {
		utool_err_msg("Failed to get cmd param.\n");
		return UTOOL_ERR;
	}

	if (cmd_param->module_id == UTOOL_MODULE_NAME_UMMU) {
		ret = utool_open_dev_step(&dev, 0, 0, UTOOL_DEV_STEP_UMMU);
	} else if (cmd_param->module_id == UTOOL_MODULE_NAME_DEBUGFS) {
		dev.fd = UTOOL_INVALID_FD; // debugfs does not need to open dev.
	} else {
		ret = utool_open_dev_step(&dev, cmd_param->chip_id, cmd_param->die_id,
					  UTOOL_DEV_STEP_SCAN);
	}

	if (ret != UTOOL_OK) {
		return ret;
	}

	ret = utool_cmd_select(&dev);

	utool_close(&dev);

	return ret;
}
