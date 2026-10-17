#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2026, Max97k
# SPDX-License-Identifier: BSD-3-Clause
"""
自動掃描本機 S32 Design Studio 安裝路徑並更新 .cproject 中的硬編碼路徑。

用法:
  python tool/fix_s32ds_cproject_paths.py --repo <專案路徑> [--s32ds-path C:/NXP/S32DS.3.6.11]
"""
import argparse
import glob
import os
import re
import sys

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
if hasattr(sys.stderr, "reconfigure"):
    sys.stderr.reconfigure(encoding="utf-8", errors="replace")


def detect_local_s32ds():
    for drive in ["C:", "D:", "E:"]:
        matches = sorted(glob.glob(f"{drive}/NXP/S32DS*"), reverse=True)
        for m in matches:
            if os.path.isdir(m):
                return m.replace("\\", "/")
    return None


def main():
    parser = argparse.ArgumentParser(description="Fix hardcoded S32DS paths in .cproject")
    parser.add_argument("--repo", default=".", help="Path to SJA1110_MGS_gPTP_FreeRTOS root")
    parser.add_argument("--s32ds-path", default="", help="Explicit S32DS installation path")
    args = parser.parse_args()

    cproj_path = os.path.join(os.path.abspath(args.repo), ".cproject")
    if not os.path.exists(cproj_path):
        print(f"[-] 找不到 .cproject: {cproj_path}", file=sys.stderr)
        sys.exit(1)

    with open(cproj_path, "r", encoding="utf-8", newline="") as f:
        text = f.read()

    found_paths = sorted(set(re.findall(r"[A-Za-z]:/NXP/S32DS[^/\s\"]+", text)))
    print(f"[*] .cproject 目前內含的 S32DS 路徑: {found_paths}")

    target_path = args.s32ds_path.replace("\\", "/") if args.s32ds_path else detect_local_s32ds()
    if not target_path:
        print("[!] 未自動偵測到本機 S32DS 安裝目錄，請透過 --s32ds-path 指定。")
        sys.exit(0)

    print(f"[*] 使用本機 S32DS 路徑: {target_path}")
    new_text = re.sub(r"[A-Za-z]:/NXP/S32DS[^/\s\"]+", target_path, text)
    if new_text != text:
        with open(cproj_path, "w", encoding="utf-8", newline="") as f:
            f.write(new_text)
        print(f"[+] 已成功更新 {cproj_path}")
    else:
        print("[+] .cproject 路徑已與本機一致，無需修改。")


if __name__ == "__main__":
    main()
