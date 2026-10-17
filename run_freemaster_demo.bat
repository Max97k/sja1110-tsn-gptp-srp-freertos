@echo off
:: Copyright (c) 2026, Max97k
:: SPDX-License-Identifier: BSD-3-Clause
title SJA1110 TSN and gPTP FreeRTOS - Live Dashboard Launcher
echo ===============================================================================
echo     NXP SJA1110 Automotive TSN Switch + FreeRTOS + IEEE 802.1AS gPTP
echo     FreeMASTER and Live Wireshark Packet Stream Interactive Dashboard
echo ===============================================================================
echo.

cd /d "%~dp0freemaster"

:: 1. Clean up any previous server on port 8091 or 8090
echo [*] Checking and freeing server ports 8091 and 8090...
for /f "tokens=5" %%a in ('netstat -aon 2^>nul ^| findstr ":8091\>"') do taskkill /F /PID %%a >nul 2>&1
for /f "tokens=5" %%a in ('netstat -aon 2^>nul ^| findstr ":8090\>"') do taskkill /F /PID %%a >nul 2>&1
taskkill /F /IM fmlite.exe >nul 2>&1
ping 127.0.0.1 -n 2 >nul

:: 2. Launch FreeMASTER Lite server in background on Port 8090 if installed
if exist "C:\NXP\FreeMASTER Lite 1.5.1\FreeMASTER Lite\fmlite.exe" (
    echo [*] Starting FreeMASTER Lite RPC server on Port 8090...
    start "FreeMASTER_Lite" /B "C:\NXP\FreeMASTER Lite 1.5.1\FreeMASTER Lite\fmlite.exe" --no-node_red --no-open_path sja1110_freemaster.fmcfg
    ping 127.0.0.1 -n 2 >nul
)

:: 3. Launch Python Telemetry and Wireshark Packet Bridge Server on Port 8091
echo [*] Launching Hardware Telemetry and Wireshark Packet Bridge on Port 8091...
start "SJA1110_Telemetry_Server" /B python telemetry_bridge.py
ping 127.0.0.1 -n 3 >nul

:: 4. Automatically open web dashboard in default browser (Single Window)
echo [*] Opening Live Interactive Dashboard in default browser...
start "" "http://127.0.0.1:8091/index.html"

echo.
echo ===============================================================================
echo [V] Dashboard is LIVE and STREAMING!
echo.
echo     * Web Dashboard URL:   http://127.0.0.1:8091/index.html
echo     * WebSocket Stream:    ws://127.0.0.1:8091/ws
echo     * FreeMASTER Lite:     http://127.0.0.1:8090/
echo.
echo If your browser did not pop up automatically, please open the URL above manually.
echo Keep this window open during your demo. Press any key to stop all services.
echo ===============================================================================
pause >nul

echo [*] Shutting down services...
for /f "tokens=5" %%a in ('netstat -aon 2^>nul ^| findstr ":8091\>"') do taskkill /F /PID %%a >nul 2>&1
for /f "tokens=5" %%a in ('netstat -aon 2^>nul ^| findstr ":8090\>"') do taskkill /F /PID %%a >nul 2>&1
taskkill /F /IM fmlite.exe >nul 2>&1
echo [OK] All services stopped.
