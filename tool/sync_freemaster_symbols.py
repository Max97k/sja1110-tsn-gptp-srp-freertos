#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2026, Max97k
# SPDX-License-Identifier: BSD-3-Clause
"""
從編譯後的 SJA1110 ELF 檔案自動解析真實 SRAM 變數符號位址，
並更新 freemaster/sja1110_freemaster.fmcfg。

用法:
  python tool/sync_freemaster_symbols.py --elf Debug_FLASH/SJA1110_MGS_gPTP_FreeRTOS.elf --fmcfg freemaster/sja1110_freemaster.fmcfg
"""
import argparse
import json
import os
import sys

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
if hasattr(sys.stderr, "reconfigure"):
    sys.stderr.reconfigure(encoding="utf-8", errors="replace")

try:
    from elftools.elf.elffile import ELFFile
    from elftools.elf.sections import SymbolTableSection
except ImportError:
    print("[-] Error: 請先安裝 pyelftools (pip install pyelftools)", file=sys.stderr)
    sys.exit(1)

TARGET_SYMBOLS = {
    "sbGptpInitialized":              {"type": "uint", "size": 1},
    "xFreeBytesRemaining":            {"type": "uint", "size": 4},
    "xMinimumEverFreeBytesRemaining": {"type": "uint", "size": 4},
    "g_srp_selftest_done":            {"type": "uint", "size": 1},
    "g_srp_selftest_vlan_res":        {"type": "int",  "size": 4},
    "g_srp_selftest_fdb_res":         {"type": "int",  "size": 4},
    "g_srp_selftest_cbs_res":         {"type": "int",  "size": 4},
    "g_srp_run_selftest":             {"type": "uint", "size": 1},
    "g_srp_telemetry":                {"type": "uint", "size": 40},
}


def extract_symbols(elf_path):
    addrs = {}
    with open(elf_path, "rb") as f:
        elf = ELFFile(f)
        for sec in elf.iter_sections():
            if isinstance(sec, SymbolTableSection):
                for sym in sec.iter_symbols():
                    if sym.name in TARGET_SYMBOLS and sym["st_value"] != 0:
                        addrs[sym.name] = int(sym["st_value"])
    return addrs


def main():
    parser = argparse.ArgumentParser(description="Update sja1110_freemaster.fmcfg with real ELF symbol addresses")
    parser.add_argument("--elf", required=True, help="Path to compiled .elf file")
    parser.add_argument("--fmcfg", default="freemaster/sja1110_freemaster.fmcfg", help="Path to .fmcfg file")
    args = parser.parse_args()

    if not os.path.exists(args.elf):
        print(f"[-] 找不到 ELF 檔案: {args.elf}", file=sys.stderr)
        sys.exit(1)

    addrs = extract_symbols(args.elf)
    print(f"[+] 從 {args.elf} 解析到 {len(addrs)} 個符號:")
    for name, addr in sorted(addrs.items()):
        print(f"    {name:<32} -> 0x{addr:08X} ({addr})")

    with open(args.fmcfg, "r", encoding="utf-8") as f:
        cfg = json.load(f)

    variables = []
    for name, meta in TARGET_SYMBOLS.items():
        if name in addrs:
            variables.append({
                "name": name,
                "addr": addrs[name],
                "type": meta["type"],
                "size": meta["size"],
            })

    # If g_srp_telemetry struct was found, also add sub-field offsets for direct FreeMASTER ReadVariable access
    if "g_srp_telemetry" in addrs:
        base = addrs["g_srp_telemetry"]
        subfields = [
            ("g_srp_telemetry.magic",                  base + 0,  "uint", 4),
            ("g_srp_telemetry.uptime_ticks",           base + 4,  "uint", 4),
            ("g_srp_telemetry.free_heap_bytes",        base + 8,  "uint", 4),
            ("g_srp_telemetry.min_free_heap_bytes",    base + 12, "uint", 4),
            ("g_srp_telemetry.port_link_mask",         base + 16, "uint", 1),
            ("g_srp_telemetry.selftest_done",          base + 17, "uint", 1),
            ("g_srp_telemetry.active_vlan_id",         base + 18, "uint", 2),
            ("g_srp_telemetry.active_tcam_dest_ports", base + 20, "uint", 2),
            ("g_srp_telemetry.active_tcam_mac",        base + 22, "uint", 6),
            ("g_srp_telemetry.port4_cbs_slope_bps",    base + 28, "uint", 4),
            ("g_srp_telemetry.rx_mrp_packets",         base + 32, "uint", 4),
            ("g_srp_telemetry.tx_mrp_packets",         base + 36, "uint", 4),
        ]
        for sname, saddr, stype, ssize in subfields:
            variables.append({"name": sname, "addr": saddr, "type": stype, "size": ssize})

    cfg["variables"] = variables
    with open(args.fmcfg, "w", encoding="utf-8", newline="\n") as f:
        json.dump(cfg, f, indent=2)
        f.write("\n")

    print(f"[+] 已更新 {args.fmcfg} (共 {len(variables)} 筆變數映射)")


if __name__ == "__main__":
    main()
