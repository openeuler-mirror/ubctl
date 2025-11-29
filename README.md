# 📌 Introduction

The ubctl command-line tool is part of the UB (Unified Bus) system, designed to query public function configurations, module statuses, statistical data, and firmware information. Built on the open-source fwctl framework, it interacts with hardware through the kernel module ub_fwctl to provide read-only query functionality (the current version does not support configuration modifications). As an essential component of the UB system's DFX (Maintenance Information) function, ubctl supports low-level debugging, operation and maintenance, and fault analysis.

## Terms and Abbreviations

The terms and Abbreviations in [UnifiedBus™ (UB) Base Specification](https://www.unifiedbus.com/zh/docs/UB-Base-Specification-2.0-preview-zh).

# 📦 Architecture and Components
## 1. core component

User-mode tools ubctl:

    Provide a command-line interface to communicate with the kernel module by calling the /dev/fwctl/fwctlNN device file.

Kernel module ub_fwctl:

    Register to the fwctl open-source framework, interface with the ubase framework via the auxiliary bus as an auxiliary device,and interact with the hardware interface using the command queue mechanism.

## 2. Driver dependency

The ub_fwctl.ko depends on ubase.ko and fwctl.ko,while there is no dependency between ubase.ko and fwctl.ko.

# 🛠 Installation and Preparation
## 1. Kernel module loading

### Prerequisites
Ensure that ubase.ko and fwctl.ko have been loaded before loading ub_fwctl.ko:

    insmod ubase.ko
    insmod fwctl.ko
    insmod ub_fwctl.ko

Verify device node:

    ls -l /dev/fwctl/fwctlNN

## 2. User-mode tool compilation

Enter the user-mode code directory:

    cd path/to/ubctl/user

Create an empty folder:

    mkdir tmp
    cd tmp

Compile the tool:

    cmake ../
    make -j15

Copy to system path:

    cp ubctl /usr/bin/

### Installing and uninstalling

If you want to install the ubctl user-mode tool you can:

    rpm -ivh ubctlxx.aarch64.rpm

Uninstall ubctl tool:

    rpm -e ubctl

# 🧩 code structure
## user-mode code

    ├─ README.md                  # current document
    ├─ CMakeLists.txt             # user-mode build file
    ├─ u_utool_*.(c|h)            # core functional module
    ├─ u_utool_main.c             # main program entry
    ├─ u_utool_dispatch.c         # command Dispatcher
    ├─ u_utool_fwctl.c            # device communication logic
    ├─ u_utool_io_die.c           # chip information inquiry
    └── ...                       # other functional modules

# 🚀 Function and Usage

Support querying the following types of registers：
- Support querying information about UB links.
- Support querying Quality of Service-related memory access information.
- Support querying the status of the Link port.
- Support querying Data Link layer message statistics.
- Support querying Network Link layer message statistics.
- Support querying Bus Adapter layer message statistics.
- Support querying TP (Transport) layer packet statistics.
- Support querying Transaction layer packet statistics.
- Support dumping all the aforementioned registers.
- For specific functions, please refer to ubctl -h.

Function Implementation Scheme:

    1. ub_fwctl registers to the fwctl framework.

    2. As an auxiliary device, ub_fwctl connects to ubase via the auxiliary bus. It utilizes the command queue (cmdq) of the PMU IDEV to invoke the firmware programming interface for register read and write operations.

    3. ubctl provides a command-line interface for user interaction. During startup, ubctl opens the ubctl device file, assembles the corresponding data structure based on user input, and invokes an ioctl call to enter kernel mode. Upon receiving a command from ubctl, ub_fwctl first validates the command's legitimacy. And then, it communicates with the firmware by calling the cmdq access interface provided by ubase. The firmware returns the register access result via cmdq to ub_fwctl, which subsequently passes the data back to user space. Finally, upon termination, ubctl closes the previously opened device file.

# ⚠️ Notice

- The ```/dev/fwctl/fwctlNN``` will be automatically created after the fwctl.ko and ub_fwctl.ko drivers are loaded.

- Permission control:

    The driver is needed to be loaded with root privilege, and the ubctl are executable only by root.

# 📝 Example command

    ubctl <-c ${chip_id}> <-d ${ub_ctl_id}> <-m ${module}> [-f ${function}]
    [-p ${port}] [-e ${value}] [-u ${ummu_id}] [-i ${index}] [-t ${time}]
    [-h] [ls]

1.Query all chip information:

    ubctl ls

2.Query ba layer packet statistics:

    ubctl -c ${chip_id} -d ${ub_ctl_id} -m ba -f pkt_stats

3.Query the help information for ubctl:

    ubctl help/--help/-help/-h

# 📦 Version and compatibility

Kernel version: openeuler 24.03 SP3 (requires support for the fwctl framework).

# 📄 Connection and contribution

Issue feedback: Submit an issue in the openeuler community.

# 📌 Copyright Notice

Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
This software is provided on an "as is" basis, without warranties of any kind, either express or implied, including but not limited to non-infringement, merchantability or fit for a particular purpose.
