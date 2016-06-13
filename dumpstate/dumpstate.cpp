/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <dumpstate.h>
#include <dumpstate_google.h>

void dumpstate_board()
{
    dump_file("INTERRUPTS", "/proc/interrupts");
    dump_file("RPM Stats", "/d/rpm_stats");
    dump_file("Power Management Stats", "/d/rpm_master_stats");
    run_command("SUBSYSTEM TOMBSTONES", 5, SU_PATH, "root", "ls", "-l", "/data/tombstones/ramdump", NULL);
    dump_file("BAM DMUX Log", "/d/ipc_logging/bam_dmux/log");
    dump_file("SMD Log", "/d/ipc_logging/smd/log");
    dump_file("SMD PKT Log", "/d/ipc_logging/smd_pkt/log");
    dump_file("IPC Router Log", "/d/ipc_logging/ipc_router/log");
    run_command("ION HEAPS", 5, SU_PATH, "root", "/system/bin/sh", "-c", "for d in $(ls -d /d/ion/*); do for f in $(ls $d); do echo --- $d/$f; cat $d/$f; done; done", NULL);
    dump_file("dmabuf info", "/d/dma_buf/bufinfo");
    dump_file("Battery Type", "/sys/class/power_supply/bms/battery_type");
    run_command("Temperatures", 5, SU_PATH, "root", "/system/bin/sh", "-c", "for f in emmc_therm msm_therm pa_therm0 xo_therm ; do echo -n \"$f : \" ; cat /sys/class/hwmon/hwmon2/device/$f ; done ; for f in `ls /sys/class/thermal` ; do type=`cat /sys/class/thermal/$f/type` ; temp=`cat /sys/class/thermal/$f/temp` ; echo \"$type: $temp\" ; done", NULL);
    dump_file("dmesg-ramoops-0", "/sys/fs/pstore/dmesg-ramoops-0");
    dump_file("dmesg-ramoops-1", "/sys/fs/pstore/dmesg-ramoops-1");
    dump_file("LITTLE cluster time-in-state", "/sys/devices/system/cpu/cpu0/cpufreq/stats/time_in_state");
    run_command("LITTLE cluster cpuidle", 5, SU_PATH, "root", "/system/bin/sh", "-c", "for d in $(ls -d /sys/devices/system/cpu/cpu0/cpuidle/state*); do echo \"$d: `cat $d/name` `cat $d/desc` `cat $d/time` `cat $d/usage`\"; done", NULL);
    dump_file("big cluster time-in-state", "/sys/devices/system/cpu/cpu4/cpufreq/stats/time_in_state");
    run_command("big cluster cpuidle", 5, SU_PATH, "root", "/system/bin/sh", "-c", "for d in $(ls -d /sys/devices/system/cpu/cpu4/cpuidle/state*); do echo \"$d: `cat $d/name` `cat $d/desc` `cat $d/time` `cat $d/usage`\"; done", NULL);

    // Dump Google-specific info.
    dumpstate_google();
};
