# NXP SJA1110 車載 TSN 交換機韌體：基於 FreeRTOS 之 IEEE 802.1AS gPTP 與 IEEE 802.1Qat SRP (MSRP / MVRP / MMRP) 網橋實作

[![Target: NXP SJA1110](https://img.shields.io/badge/Target-NXP%20SJA1110%20(Silicon%20E)-005a9c.svg)](https://www.nxp.com/products/interfaces/ethernet-/automotive-ethernet-switches/sja1110-multi-gig-safe-and-secure-tsn-ethernet-switch-with-integrated-100base-t1-phys:SJA1110)
[![Core: Arm Cortex-M7](https://img.shields.io/badge/Core-Arm%C2%AE%20Cortex%C2%AE--M7%20%40%20200MHz-blue.svg)](https://www.arm.com/products/silicon-ip-cpu/cortex-m/cortex-m7)
[![RTOS: FreeRTOS 11.1](https://img.shields.io/badge/RTOS-FreeRTOS%2011.1.0-brightgreen.svg)](https://www.freertos.org)
[![RTD: 0.9.0 (AUTOSAR 4.4)](https://img.shields.io/badge/RTD-0.9.0%20(AUTOSAR%C2%AE%204.4)-orange.svg)](https://www.nxp.com)
[![TSN: IEEE 802.1AS + 802.1Qat + 802.1Qav](https://img.shields.io/badge/TSN-802.1AS%20gPTP%20%7C%20802.1Qat%20SRP%20%7C%20802.1Qav%20CBS-purple.svg)](https://1.ieee802.org/tsn/)
[![Toolchain: GCC 9.2](https://img.shields.io/badge/Toolchain-GCC%209.2%20(arm--none--eabi)-brightgreen.svg)](https://gcc.gnu.org)
[![License: BSD-3-Clause](https://img.shields.io/badge/License-BSD--3--Clause-blue.svg)](LICENSE)

[English](README.md) | 繁體中文 | [自我測試與驗證計畫 (T1–T5)](TEST_PLAN_zh.md)

---

本專案為專為 **恩智浦半導體 (NXP Semiconductors®) SJA1110-MGS-EVM 評估板 (`SCH-94089 REV A`)** 所設計的車載時間敏感網路（Time-Sensitive Networking, TSN）乙太網交換機參考韌體。硬體核心採用內建 **Arm® Cortex®-M7** 微控制器與多埠 `100BASE-T1` / `SGMII` / `RGMII` 交換矩陣的 **NXP SJA1110** 安全車載 TSN 交換晶片。

本韌體在 **FreeRTOS** 即時作業系統與 **NXP Real Time Drivers (RTD / AUTOSAR 4.4 Eth + EthSwt)** 基礎之上，同時整合 **IEEE 802.1AS gPTP 高精度時間同步協議棧** 與移植自 **NXP GenAVB/TSN** 的 **IEEE 802.1Qat 串流預留協議棧 (SRP: MSRP, MVRP, MMRP)** 網橋模式 (`is_bridge = 1`，並保留 Endpoint/IPC 擴充框架)。系統深度調用 SJA1110 硬體交換引擎，實現 **特殊管理訊框 (`0x8B8C`) 入埠攔截與指定埠發送**、**IEEE 802.1Qav 信用整形器 (CBS) 硬體頻寬卸載**、**1024 筆 L2 TCAM 轉發表動態群播過濾**，以及 **硬體 VLAN 查找表動態註冊**。

---

## 核心特性 (Key Features)

* **雙協議車載 TSN 控制平面 (IEEE 802.1AS + IEEE 802.1Qat)**：於單一 Cortex-M7 核心上同步運行 IEEE 802.1AS 廣義精確時間同步協議 (`gptp_stack`，支援 Grand Master 與 Bridge 時間同步) 以及 IEEE 802.1Qat 串流預留協議 (`srp_stack`，優先實作 8 埠 TSN Bridge 模式 `is_bridge = 1`，並完整保留 Endpoint 狀態機框架)。
* **完整 MRP 狀態機家族 (IEEE 802.1Q-2018 Clause 10 & 35)**：
  * **MSRP (`0x22EA`)**：多重串流註冊協議，支援 Talker Advertise、Talker Failed、Listener Ready / Asking Failed / Ready Failed 屬性合併宣告、累積延遲計算，以及各實體埠 SR Class A 與 Class B 頻寬核算。
  * **MVRP (`0x88F5`)**：多重 VLAN 註冊協議，於 8 個外部交換埠間動態傳播與註冊 SR VLAN 成員資格。
  * **MMRP (`0x88F6`)**：多重 MAC 註冊協議，具備硬體入埠攔截 (`macFilter1`) 與 L2 訊框分流介面（狀態機保留為 Stub 預留；動態串流群播轉發由 MSRP Listener Ready 直接觸發 `fdb_update` 完成）。
  * **標準 MRP 申請者 / 註冊者 / LeaveAll 計時器**：完整實作 IEEE 802.1Q 狀態轉換表（`VO`, `VP`, `VN`, `AN`, `AA`, `QA`, `LA`, `AO`, `QO`, `AP`, `QP`, `LO` 與 `IN`, `LV`, `MT`），由確定性 FreeRTOS 軟體計時器池 (`os_timer`) 驅動。
* **SJA1110 硬體管理訊框 (`0x8B8C`) 攔截與指定埠定向發送管線**：
  * **入埠硬體攔截 (Ingress Trap)**：配置 SJA1110 `GeneralParametersTable` 雙組 MAC 濾波器（`macFilter0` = `01:80:C2:00:00:0E` 攔截 gPTP 與 MSRP；`macFilter1` = `01:80:C2:00:00:20` 搭配遮罩 `FF:FF:FF:FF:FF:FE` 同時攔截 MMRP `01:80:C2:00:00:20` 與 MVRP `01:80:C2:00:00:21`），自動附加含來源埠號 (`SwitchPortIdx 1..8`) 之 `0x8B8C` 標頭並上送內部 Host Port 0。
  * **出埠定向注入 (Directed Egress TX)**：透過 `EthSwt_43_SJA11XX_SetMgmtInfo` 與 `EthSwt_43_SJA11XX_EthTxProcessFrame` 封裝 `0x8B8C` 管理標頭，將各埠獨立產生的 MRP PDU 精準由指定外部交換埠 (`SwitchPortIdx 1..8`) 發出，繞過一般 L2 廣播泛洪。
* **IEEE 802.1Qav 信用整形器 (CBS / FQTSS) 硬體頻寬卸載**：當 MSRP 完成串流預留後，自動將核准之 `idle_slope` (bps) 透過 `Switch_Ip_SetCbsIdleSlope()` 與 `Switch_Ip_DisableCbs()` 寫入 SJA1110 硬體 CBS 整形器（共 16 組硬體整形通道）。
* **動態 L2 TCAM 轉發表與硬體 VLAN 表卸載**：
  * 動態操作 SJA1110 內建 1024 筆容量之 L2 Address Lookup TCAM (`Switch_Ip_SearchL2EntryInTcam`, `Switch_Ip_UpdateTcamEntry`, `Switch_Ip_SJA11XX_setL2AddressLookupTableControl`)，將音視訊/控制串流精準轉發至已註冊 Listener 之實體連接埠。
  * 動態更新 SJA1110 硬體 VLAN 查找表 (`Switch_Ip_GetVlanLookupEntry`, `Switch_Ip_UpdateVlanLookupEntry`)，並自動維持內部 Host Port 0 之管理權限。
* **雙分區安全升級架構 (Dual-Bank Bootloader)**：支援主引導分區搭配雙應用分區（Bank 1 綠燈 / Bank 2 黃燈），確保車規韌體更新失敗時具備自動回滾保護。

---

## 硬體架構與交換埠映射 (`SJA1110-MGS-EVM`)

### SJA1110 9 埠交換矩陣映射表

SJA1110 內部包含 1 個微控制器主機連接埠 (`Port 0`) 與 8 個外部乙太網交換埠 (`Port 1..8`)。在 `srp_stack` 網橋配置中，8 個外部交換埠與 GenAVB/TSN 邏輯埠號 (`logical_port 2..9`) 一對一映射：

| SJA1110 硬體埠號 | GenAVB `logical_port` | SRP 網橋埠索引 | xMII 介面與速率 | 實體收發器 / 連接器 | TSN 網橋角色 |
| :---: | :---: | :---: | :---: | :--- | :--- |
| **`PORT_0`** | `0` (Host EP) | N/A (內部 CPU) | Internal MII (`100M`) | 內部 Cortex-M7 主機 (`22:33:44:55:66:77`) | 控制平面攔截與注入 (`0x8B8C`) |
| **`PORT_1`** | `2` | Bridge Port `0` | SGMII (`1000 Mbps`) | 外部 SGMII PHY / 連接器 | TSN 網橋埠 (gPTP + SRP + CBS) |
| **`PORT_2`** | `3` | Bridge Port `1` | RGMII (`1000 Mbps`) | 外部 RGMII Gigabit PHY | TSN 網橋埠 (gPTP + SRP + CBS) |
| **`PORT_3`** | `4` | Bridge Port `2` | SGMII (`100 Mbps`) | 外部 SGMII 連接埠 | TSN 網橋埠 (gPTP + SRP + CBS) |
| **`PORT_4`** | `5` | Bridge Port `3` | SGMII (`1000 Mbps`) | **SW1 Port 4 SFP 光纖/電口模組座** (`1G`) | 主要測試與上行 TSN 連接埠 |
| **`PORT_5`** | `6` | Bridge Port `4` | MII (`100 Mbps`) | 晶片內建 `100BASE-T1` 車規 PHY | 車載雙絞線 T1 網橋埠 |
| **`PORT_6`** | `7` | Bridge Port `5` | MII (`100 Mbps`) | 晶片內建 `100BASE-T1` 車規 PHY | 車載雙絞線 T1 網橋埠 |
| **`PORT_7`** | `8` | Bridge Port `6` | MII (`100 Mbps`) | 晶片內建 `100BASE-T1` 車規 PHY | 車載雙絞線 T1 網橋埠 |
| **`PORT_8`** | `9` | Bridge Port `7` | MII (`100 Mbps`) | 晶片內建 `100BASE-T1` 車規 PHY | 車載雙絞線 T1 網橋埠 |

### 評估板指撥開關與跳線配置 (`SJA1110-MGS-EVM`)

| 硬體項目 | 設定位置 / 狀態 | 功能說明 |
| :--- | :---: | :--- |
| **指撥開關 `SW7`** | `ON` (其餘皆為 `OFF`) | 選擇 `SJA1110 BOOT_OPTION1` (由外部 SPI Flash 啟動) |
| **跳線帽 (Jumpers)** | `J58: 1-2`, `J61: 1-2`, `J77: 1-2` | 電源、時脈與收發器路由設定（其餘未列出跳線保持開路） |
| **除錯介面** | `J16` (10-pin Cortex Debug) | 連接 S32 Debug Probe / PEMicro / J-Link 進行燒錄與單步除錯 |
| **SFP 上行測試埠** | `SW1 Port 4` (`PORT_4`) | 插入支援 1Gb/s 自動協商之 SFP 轉 RJ45 模組連接至測試 PC |
| **GPIO 擴充晶片** | `PCAL9722` (透過 `LPSPI`) | 控制板載狀態 LED、讀取按鍵中斷與 PHY/PMIC 狀態 |

---

## 系統架構與韌體處理流程 (System Architecture & Pipeline)

```
                         ┌────────────────────────────────────────────────────────┐
                         │        外部乙太網交換埠 (SwitchPortIdx 1..8)           │
                         │   100BASE-T1 (Ports 5-8) | RGMII (Port 2) | SGMII (1,4)│
                         └──────────────┬──────────────────────────┬──────────────┘
                                        │ 入埠 L2 控制訊框         ▲ 指定埠定向出埠訊框
                                        ▼                          │ + 硬體 CBS 流量整形
        ┌──────────────────────────────────────────────────────────┴───────────────────────────────┐
        │                          NXP SJA1110 硬體交換矩陣 (Switch Fabric)                        │
        │  ┌───────────────────────────────────────┐   ┌────────────────────────────────────────┐  │
        │  │ GeneralParametersTable 硬體 MAC 濾波  │   │ 資料平面硬體卸載引擎 (Hardware Offload)│  │
        │  │ • Filter0: 01:80:C2:00:00:0E          │   │ • 16 通道 IEEE 802.1Qav CBS 信用整形器 │  │
        │  │   (攔截 gPTP 0x88F7 與 MSRP 0x22EA)   │   │   (Switch_Ip_SetCbsIdleSlope)          │  │
        │  │ • Filter1: 01:80:C2:00:00:20 / FFFE   │   │ • 1024 筆 L2 TCAM 硬體位址查找表       │  │
        │  │   (攔截 MMRP 0x88F6 與 MVRP 0x88F5)   │   │   (動態串流群播轉發埠遮罩)             │  │
        │  └───────────────────┬───────────────────┘   │ • 4096-VID 硬體 VLAN 查找表            │  │
        └──────────────────────┼───────────────────────┴───────────────────▲───────────────────────┘
                               │ 內部 Host Port 0 (附加 0x8B8C 管理標頭)   │ SPI / APB Switch_Ip API
                               ▼                                           │
        ┌──────────────────────────────────────────────────────────────────┼───────────────────────┐
        │                   Arm® Cortex®-M7 @ 200 MHz (FreeRTOS + RTD)     │                       │
        │                                                                  │                       │
        │  ┌────────────────────────────────────────────────────────────┐  │                       │
        │  │ EthIf_RxIndication() & EthSwt_43_SJA11XX_EthRxProcessFrame │  │                       │
        │  │ 解析來源實體埠號 SwitchPortIdx (1..8) 並剝除 0x8B8C 標頭   │  │                       │
        │  └──────────────┬─────────────────────────────┬───────────────┘  │                       │
        │                 │ EtherType 0x88F7            │ EtherType 0x22EA / 0x88F5 / 0x88F6       │
        │                 ▼                             ▼                  │                       │
        │  ┌──────────────────────────┐   ┌─────────────────────────────┐  │                       │
        │  │ gPTPTask (Prio 3, 2ms)   │   │ SRP_PORT_Periodic()         │  │                       │
        │  │ • IEEE 802.1AS GM/Bridge │   │ • MSRP 串流頻寬預留狀態機   ├──┘                       │
        │  │ • Eth_Main 與 Eth_Poll   ├──►│ • MVRP 動態 VLAN 註冊狀態機 │                          │
        │  │ • 硬體時間戳記校正       │   │ • FQTSS 頻寬計算與 CBS 觸發 │                          │
        │  └──────────────────────────┘   └─────────────────────────────┘                          │
        └──────────────────────────────────────────────────────────────────────────────────────────┘
```

### TSN 控制平面協議多工分流表

| 協議名稱 | IEEE 國際標準 | EtherType | 目的群播 MAC 位址 | SJA1110 硬體攔截規則 | FreeRTOS 處理任務 |
| :--- | :--- | :---: | :---: | :--- | :--- |
| **gPTP** | IEEE 802.1AS-2020 | `0x88F7` | `01:80:C2:00:00:0E` | `DPI Entry #0/#1` + `macFilter0` | `gPTPTask` (`GPTP_PORT_RxIndication`) |
| **MSRP** | IEEE 802.1Qat / 802.1Q-2018 Cl. 35 | `0x22EA` | `01:80:C2:00:00:0E` | `macFilter0` (與 gPTP 共用目的 MAC) | `gPTPTask` (`g_srp_rx_ring` -> `SRP_PORT_Periodic`) |
| **MVRP** | IEEE 802.1Q-2018 Cl. 11 | `0x88F5` | `01:80:C2:00:00:21` | `macFilter1` (`Mask: FF:FF:FF:FF:FF:FE`) | `gPTPTask` (`g_srp_rx_ring` -> `SRP_PORT_Periodic`) |
| **MMRP** | IEEE 802.1Q-2018 Cl. 10 | `0x88F6` | `01:80:C2:00:00:20` | `macFilter1` (`Res : 01:80:C2:00:00:20`) | `gPTPTask` (`g_srp_rx_ring` -> `SRP_PORT_Periodic`) |

---

## 專案開發里程碑與驗收指標 (Milestones & Acceptance Criteria)

本專案規劃為 5 個核心工程里程碑（同步建立於 GitHub Milestones 進行追蹤）：

| 里程碑 | 核心階段名稱 | 關鍵模組路徑 | 驗收指標 (Acceptance Criteria) | 狀態 |
| :---: | :--- | :--- | :--- | :---: |
| **M1** | **SRP 協議棧核心與 FreeRTOS OSAL 基礎層建立** | `srp_stack/srp/`, `srp_stack/common/`, `srp_stack/include/` | 完成 8 埠網橋映射 (`logical_port 2..9`)、FreeRTOS `os_timer` 與記憶體抽象層、保留 Endpoint 擴充框架 | ✅ 已完成 (`v1.0.0-m1`) |
| **M2** | **SJA1110 管理訊框 (`0x8B8C`) 攔截與指定埠收發管線** | `srp_stack/port/srp_port.c`, `src/EthIf.c` | 雙硬體濾波器 (`macFilter0` + `macFilter1` 遮罩 `FFFE`)、RX 多工分流 (`0x22EA`/`0x88F5`/`0x88F6`)、指定埠定向發送 | ✅ 已完成 (`v1.0.1-m2`) |
| **M3** | **交換機硬體卸載整合 (CBS 整形器、L2 TCAM 與 VLAN 表)** | `srp_stack/port/srp_port.c`, `RTD/src/Switch_Ip_*.c` | 16 通道 CBS `idleSlope` 硬體整形、1024 筆 L2 TCAM 動態群播剪枝、4096-VID 硬體 VLAN 表動態更新 | ✅ 已完成 (`v1.0.2-m3`) |
| **M4** | **FreeRTOS 雙協議棧共整合、建置與實機驗證** | `src/main.c`, `generate/include/FreeRTOSConfig.h`, `.cproject` | GCC 零錯誤編譯、產出 Dual-Bank NVM 映像檔、gPTP 與 MSRP/MVRP 零衝突協同運作 | ✅ 已完成 (`v1.0.3-m4`) |
| **M5** | **TSN Endpoint 端點模式 (`is_bridge = 0`) 與本地 IPC 擴充** | `srp_stack/srp/`, `srp_stack/port/` | 啟用內部 Host Port 0 本地端 Talker/Listener 串流宣告 API (`IPC_MEDIA_STACK_MSRP`) | 📋 已規劃 (`v1.1.0-m5`) |

### 各里程碑詳細技術指標與成果驗收

#### Milestone 1：SRP 協議棧核心與 FreeRTOS OSAL 基礎層建立 (`v1.0.0-m1`)
- **GenAVB/TSN 核心狀態機移植**：完整抽離 IEEE 802.1Qat / 802.1Q-2018 Clause 10, 11, 34, 35 狀態機（`mrp.c`, `msrp.c`, `mvrp.c`, `mmrp.c`, `srp.c`, `srp_entry.h`, `fqtss.c`, `timer.c`, `sr_class.c`, `qos.c`, `managed_objects.c`, `random.c`）。
- **SJA1110 8 埠網橋拓撲對齊**：設定 `CFG_MAX_NUM_PORT = 8`、`CFG_BR_DEFAULT_NUM_PORTS = 8`、`CFG_BR_LOGICAL_PORT_LIST = {2, 3, 4, 5, 6, 7, 8, 9}`，一對一映射至 SJA1110 實體交換埠 `SwitchPortIdx 1..8`；設定 `CFG_TRAFFIC_CLASS_MAX = 8` 與 `CFG_SR_CLASS_MAX = 2`（支援 SR Class A 8 kHz 與 Class B 4 kHz）。
- **FreeRTOS OSAL 抽象層實作**：完成 `os_malloc`/`os_free` (`pvPortMalloc`/`vPortFree`)、單調奈秒/毫秒時鐘 (`xTaskGetTickCount`)，基於 Tick 驅動之確定性軟體計時器池 (`g_srp_timers`, `SRP_MAX_OS_TIMERS = 64`)，以及支援區塊合併回收之 FreeRTOS `heap_4` 動態記憶體配置器。
- **網橋優先與架構可擴充性**：預設啟用 Bridge 模式 (`is_bridge = 1`)，同時完整保留 Endpoint 實例 (`msrp_ep` / `mvrp_ep`) 與 IPC 介面供 Milestone 5 擴充。

#### Milestone 2：SJA1110 管理訊框 (`0x8B8C`) 攔截與指定埠收發管線 (`v1.0.1-m2`)
- **雙通道硬體 MAC 濾波攔截 (`GeneralParametersTable`)**：
  - `macFilter0` (`01:80:C2:00:00:0E`, 遮罩 `FF:FF:FF:FF:FF:FF`)：同時攔截 IEEE 802.1AS gPTP (`0x88F7`) 與 IEEE 802.1Qat MSRP (`0x22EA`) 訊框並上送內部 Host Port 0。
  - `macFilter1` (`01:80:C2:00:00:20`, 遮罩 `FF:FF:FF:FF:FF:FE`, `sendFollowUpTs1 = FALSE`)：利用最低位元遮罩同時攔截 IEEE 802.1Q MMRP (`01:80:C2:00:00:20`, `0x88F6`) 與 MVRP (`01:80:C2:00:00:21`, `0x88F5`) 訊框並附上來源 `SwitchPortIdx` 標頭。
- **零干擾 RX 多工分流 (`EthIf_RxIndication`)**：維持 `0x88F7` 直接進入 `GPTP_MsgReceive()` 零延遲路徑，並將 `0x22EA` / `0x88F5` / `0x88F6` 轉換為 `logical_port = SwitchPortIdx + 1` 送入 `g_srp_rx_ring` 環形佇列。
- **指定實體埠定向發送 (`net_tx`)**：串接 `Eth_ProvideTxBuffer` $\to$ `EthSwt_43_SJA11XX_SetMgmtInfo` $\to$ `EthSwt_43_SJA11XX_EthTxProcessFrame` $\to$ `Eth_Transmit` $\to$ `Eth_TxConfirmation`，確保在單一 TX Buffer Descriptor (`BufferCount = 1U`) 配置下發送後立即釋放緩衝區。

#### Milestone 3：交換機硬體卸載整合 (CBS 整形器、L2 TCAM 與 VLAN 表) (`v1.0.2-m3`)
- **IEEE 802.1Qav 信用整形器 (CBS) 硬體卸載**：將 `fqtss.c` 之 `clock_st_psfp_cbs_config()` 對接至 SJA1110 驅動；當 `idle_slope > 0` 時呼叫 `Switch_Ip_SetCbsIdleSlope(0U, swt_port, tc, idle_slope)`，當 `idle_slope == 0` 時呼叫 `Switch_Ip_DisableCbs(0U, swt_port, tc)` 釋放硬體整形器。
- **1024 筆 L2 TCAM 動態群播過濾**：將 `fdb_update()` / `fdb_delete()` 對接至 `Switch_Ip_SearchL2EntryInTcam()` 與 `Switch_Ip_UpdateTcamEntry()`，將 GenAVB `logical_port` 狀態映射為硬體 `SwitchPortIdx` 轉發遮罩 (`destPorts`)，防止未預留頻寬埠口遭串流泛洪。
- **4096-VID 硬體 VLAN 查找表卸載**：將 `vlan_update()` / `vlan_delete()` 對接至 `Switch_Ip_GetVlanLookupEntry()` 與 `Switch_Ip_UpdateVlanLookupEntry()`，動態更新各埠 `vlanDomain` 與 `tagPort` 並確保 `Switch_Ip_Port0` (Host CPU) 維持成員權限。

#### Milestone 4：FreeRTOS 雙協議棧共整合、建置與實機驗證 (`v1.0.3-m4`)
- **確定性協同多任務排程**：
  - `gPTPTask` (`Priority 3`, 2 ms 週期, `2048` words 堆疊)：於單一任務迴圈內依序協同執行 `GPTP_TimerPeriodic()`、`Eth_Main()`、`Eth_Poll()`、`SRP_PORT_Periodic()` 與 `FLASH_Write_Poll()`，徹底避免單一 ENET TX Buffer Descriptor (`ringSize = 1U`) 與 `Switch_Ip` 硬體存取之跨執行緒鎖競爭。
  - `gpioHandleTask` (`Priority 2`, 20 ms 週期)：定期輪詢 SJA1110 板載 PHY、SFP、PMIC 與按鍵 GPIO 中斷旗標。
  - `aliveLEDTimer` (`Priority 3`, 500 ms FreeRTOS 軟體計時器, `512` words 計時器任務堆疊)：定期翻轉板載 Alive LED 指示燈。
- **RTOS 資源擴充**：於 `FreeRTOSConfig.h` 將 `configTOTAL_HEAP_SIZE` 擴充至 `49152` (48 KB，搭配支援記憶體釋放合併之 `heap_4` 分配器)，並啟用 `configUSE_TIMERS = 1`。
- **實機編譯與 Wireshark 封包驗收**：完成 S32DS GCC 零錯誤編譯、Dual-Bank SPI NVM 映像檔產出，並於 `SW1 Port 4` (1G SFP) 驗證 gPTP 與 MSRP/MVRP 控制訊框同步收發。

#### Milestone 5：TSN Endpoint 端點模式 (`is_bridge = 0`) 與本地 IPC 擴充 (`v1.1.0-m5`)
- **內部主機端點串流宣告**：啟用預留之 `msrp_ep` / `mvrp_ep` 狀態機實例，將 `ipc_tx()` / `ipc_rx()` 對接至 FreeRTOS Message Queue，支援 Cortex-M7 本地端應用任務直接發起 Talker Advertise 或 Listener Ready 宣告。

---

## 專案目錄結構 (Project Structure)

```
.
├── board/                              # SJA1110 硬體接腳、交換矩陣靜態配置與板級驅動
├── FreeRTOS/                           # FreeRTOS v11.1.0 核心、heap_4 記憶體管理與 Cortex-M7 移植層
├── generate/                           # S32 Configuration Tools (MEX) 產生之 RTD 配置檔
│   └── include/FreeRTOSConfig.h        # FreeRTOS 排程器、Heap (48 KB) 與軟體計時器配置
├── gptp_stack/                         # IEEE 802.1AS gPTP 高精度時間同步協議棧
│   ├── gptp_core/                      # gPTP 核心狀態機 (Pdelay, Sync, FollowUp, BMCA)
│   └── port/gptp_port.c                # SJA1110 Eth/EthSwt 訊框收發與硬體時鐘轉接層
├── include/                            # 應用層標頭檔 (example_init.h, gptp_cbk.h)
├── Project_Settings/                   # 鏈結腳本 (Flash/RAM)、啟動代碼、除錯器設定
├── RTD/                                # NXP Real Time Drivers (Eth, EthSwt, Switch_Ip, Spi, Gpt)
├── src/                                # 主程式與系統整合原始碼
│   ├── main.c                          # Dual-bank 啟動檢查、NVM 快取、FreeRTOS 任務建立 (gPTPTask, gpioHandleTask)
│   ├── EthIf.c                         # 0x8B8C 交換機管理訊框分流器 (gPTP + MSRP/MVRP/MMRP)
│   ├── example_init.c                  # SJA1110 交換機與 PHY 初始化、中斷處理與 RGB LED 控制
│   └── gptp_cbk.c                      # gPTP Domain 選擇、時間同步與時鐘更新回呼函式
├── srp_stack/                          # IEEE 802.1Qat 串流預留協議棧 (SRP Stack)
│   ├── common/                         # FQTSS 頻寬核算、計時器池、SR Class 與 QoS 定義
│   │   ├── fqtss.c                     # Credit-Based Shaper (CBS) 頻寬累加與硬體卸載觸發
│   │   ├── sr_class.c                  # SR Class A (8 kHz) 與 Class B (4 kHz) 參數定義
│   │   ├── srp.c                       # SRP 協議 PDU 結構定義
│   │   └── timer.c                     # 封裝 FreeRTOS xTimer 之通用計時器管理層
│   ├── include/                        # GenAVB/TSN 公用標頭檔與 FreeRTOS OSAL 轉接層
│   │   ├── genavb/                     # 公用 API 標頭檔 (config.h, srp.h, fdb.h, vlan.h, qos.h)
│   │   ├── common/                     # 協議棧內部標頭檔 (fqtss.h, timer.h, managed_objects.h)
│   │   ├── os/                         # 作業系統抽象層 (stdlib.h, clock.h, timer.h, net.h)
│   │   └── osal/                       # 系統型別與編譯器屬性定義 (sys_types.h)
│   ├── port/                           # SJA1110 硬體抽象與轉接層
│   │   ├── srp_port.h                  # SJA1110 SRP Bridge 介面與 RX 訊框佇列結構
│   │   └── srp_port.c                  # 0x8B8C 定向收發、CBS 卸載、L2 TCAM FDB、VLAN 與 FreeRTOS 任務
│   └── srp/                            # IEEE 802.1Q MRP / MSRP / MVRP / MMRP 核心狀態機
│       ├── mrp.c                       # MRP Applicant、Registrar 與 LeaveAll 通用狀態機
│       ├── msrp.c                      # IEEE 802.1Qat MSRP Talker/Listener/Bridge 處理邏輯
│       ├── mvrp.c                      # IEEE 802.1Q MVRP 動態 VLAN 註冊狀態機
│       ├── mmrp.c                      # IEEE 802.1Q MMRP 動態 MAC 註冊狀態機
│       └── srp_entry.c                 # 頂層 srp_init() 與 srp_exit() 入口函式
├── tool/                               # Dual-Bank Flash 與 SPI NVM 映像檔後處理腳本
│   ├── createDBImage.py                # 產出雙分區應用韌體映像檔
│   └── createNvmImage.py               # 產出 SJA1110 SPI NVM 開機映像檔
├── SJA1110-MGS_gPTP_FreeRTOS.mex       # S32 Configuration Tools 硬體外設專案檔
├── README.md                           # 英文技術規格書與說明文件
└── README_zh.md                        # 繁體中文技術規格書與說明文件
```

---

## 建置與燒錄指南 (Build & Flashing)

### 環境需求
* **NXP S32 Design Studio for S32 Platform** (v3.6.11)，含 `arm-none-eabi-gcc` (GCC 9.2 / 10.2) 工具鏈與 **SJA1110 Reference Applications / RTD**。
* **Python 3.8+**，並安裝 `pyelftools` 與 `pycryptodomex`（供建置後腳本 `tool/createDBImage.py` 與 `tool/createNvmImage.py` 打包雙分區映像檔使用）：
  ```powershell
  pip install pyelftools pycryptodomex
  ```

### 方式 A：透過命令列建置 (Headless GNU Make)
```powershell
# 1. 設定 S32DS 建置工具與 ARM GCC 編譯器環境變數
$env:PATH = "C:\NXP\S32DS.3.6.11\S32DS\build_tools\msys32\usr\bin;C:\NXP\S32DS.3.6.11\S32DS\build_tools\gcc_v9.2\gcc-9.2-arm32-eabi\bin;" + $env:PATH

# 2. 進入 Debug_FLASH 或 Debug_RAM 目錄執行編譯
cd Debug_FLASH
make -j8 all
```

### 方式 B：透過 S32 Design Studio IDE 建置與除錯
1. 開啟 **S32 Design Studio**，選擇 **File $\to$ Import $\to$ General $\to$ Existing Projects into Workspace** 匯入本專案。
2. 若有修改 `.mex` 硬體配置，請切換至 **Peripherals** 視圖並點擊 **Update Code**。
3. 選擇 **Debug_FLASH**（或 **Debug_RAM**）建置組態，點擊 **Project $\to$ Build Project**。
4. 將除錯探針連接至評估板 `J16` (10-pin JTAG Cortex Debug 接頭)，開啟對應之 Debug Configuration 並點擊 **Debug** 下載執行。

---

## 網路驗證與 Wireshark 封包分析 (Validation)

> [!NOTE]
> **實機測試進度**：
> - **情境一（單板 JTAG，里程碑 T1–T3）**：已於 `SJA1110-MGS-EVM` 目標板 **100% 驗證通過 (PASS)**！實測 FreeRTOS `heap_4` 剩餘 19.5 KB 零洩漏、8 埠 SRP Bridge 正常排程運作、MVRP VID 2 表項、L2 TCAM 串流轉發、IEEE 802.1Qav CBS 硬體頻寬整形器寫入全數成功。
> - **情境二（雙向網路線，里程碑 T4–T5）**：自動化 Python Scapy 腳本與 Wireshark 配置已就緒，接上實體網路線至 `SW1 Port 4` 即可執行外部雙向閉迴路測試。
>
> 詳細步驟、GDB 監看變數、開機自測與按鍵注入機制，請參閱完整的 **[自我測試計畫 (TEST_PLAN_zh.md)](TEST_PLAN_zh.md)** ([English Test Plan](TEST_PLAN.md))。

1. 將 `1000BASE-T` SFP 光電轉換模組插入 `SJA1110-MGS-EVM` 評估板之 **SW1 Port 4 (`PORT_4`)**，並透過乙太網路線連接至測試電腦或 TSN 端點設備。
2. 於電腦端開啟 **Wireshark** 並設定捕捉過濾器：
   ```text
   ether proto 0x88f7 or ether proto 0x22ea or ether proto 0x88f5 or ether proto 0x88f6
   ```
3. **預期觀測之 TSN 控制平面封包**：
   * **IEEE 802.1AS gPTP (`0x88F7`, 目的 MAC `01:80:C2:00:00:0E`)**：每 `125 ms` 週期性發送之 Grand Master `Sync` 與 `Follow_Up` 時間同步訊框，以及 `Pdelay_Req` / `Pdelay_Resp` 鏈路延遲量測訊框。
   * **IEEE 802.1Qat MSRP (`0x22EA`, 目的 MAC `01:80:C2:00:00:0E`)**：SR Class A (Priority 3 / VID 2) 與 SR Class B (Priority 2 / VID 2) 之 `Domain` 屬性宣告、週期性 `LeaveAll` 事件，以及跨交換埠 (`Port 1..8`) 之 `Talker Advertise` / `Listener Ready` 串流預留屬性傳播。
   * **IEEE 802.1Q MVRP (`0x88F5`, 目的 MAC `01:80:C2:00:00:21`)**：動態 VLAN 註冊與 LeaveAll 宣告訊框。
4. **板載 LED 狀態指示**：
   * **Alive LED**：由 `Eth_Task` 週期性閃爍，指示 FreeRTOS 排程器與交換機輪詢正常運作。
   * **RGB LED**：每當配置埠發送訊框時閃爍 **綠燈**（由 Bank 1 正常啟動）或 **黃燈**（由備援 Bank 2 啟動）。

---

## 參考文獻與國際標準 (References & Technical Standards)

1. **[1]** IEEE Std 802.1Q-2018, *IEEE Standard for Local and Metropolitan Area Networks—Bridges and Bridged Networks* (Clause 10: MMRP, Clause 11: MVRP, Clause 34: FQTSS/CBS, Clause 35: MSRP).
2. **[2]** IEEE Std 802.1Qat-2010, *IEEE Standard for Local and Metropolitan Area Networks—Virtual Bridged Local Area Networks Amendment 14: Stream Reservation Protocol (SRP)*.
3. **[3]** IEEE Std 802.1Qav-2009, *IEEE Standard for Local and Metropolitan Area Networks—Virtual Bridged Local Area Networks Amendment 12: Forwarding and Queuing Enhancements for Time-Sensitive Streams*.
4. **[4]** IEEE Std 802.1AS-2020, *IEEE Standard for Local and Metropolitan Area Networks—Timing and Synchronization for Time-Sensitive Applications*.
5. **[5]** NXP Semiconductors, *SJA1110 Multi-Gig Safe and Secure TSN Ethernet Switch User Manual & Data Sheet*, Silicon Revision E.
6. **[6]** NXP Semiconductors, *GenAVB/TSN Stack Architecture and API Reference Manual*, Real-Time Edge Software.

---

## 授權條款 (License)

BSD-3-Clause License. Copyright (c) 2026, Max97k. All rights reserved.
本專案中部分 SRP 與 gPTP 協議棧原始碼衍生自 NXP Semiconductors 以 BSD-3-Clause 授權條款發布之參考軟體。
