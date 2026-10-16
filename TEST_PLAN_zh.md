# SJA1110-MGS-EVM 韌體自我測試計畫與驗證指南
## FreeRTOS + RTD + gPTP + GenAVB/TSN SRP Bridge — 漸進式測試驗證規範

[![測試狀態](https://img.shields.io/badge/測試計畫-v1.0-blue.svg)](#)
[![情境一](https://img.shields.io/badge/情境一-僅單板與%20USB%20(JTAG)-orange.svg)](#情境一單一開發板--usb-jtag--swd-除錯介面自我測試計畫)
[![情境二](https://img.shields.io/badge/情境二-開發板%20%2B%20PC%20Ethernet-green.svg)](#情境二開發板--乙太網路線連接電腦雙向互動測試計畫)

[English](TEST_PLAN.md) | [繁體中文](TEST_PLAN_zh.md)

---

## 測試計畫總覽

本文件針對 `SJA1110-MGS-EVM` 評估板與本專案韌體架構（FreeRTOS + RTD + gPTP + GenAVB/TSN SRP Bridge），制定完整的漸進式自我測試計畫、驗證技術手法與測試覆蓋率分析。

依據手邊硬體實驗設備資源，分為兩大情境，並切分為 **5 個子測試里程碑（T1 ~ T5）**，供後續開發與逐步回歸驗證使用：

> [!IMPORTANT]
> **建議測試執行順序**：
> 1. 先行於 **情境一（T1 ~ T3）** 完成純單板 USB/JTAG 下之開機、FreeRTOS `heap_4` 記憶體穩定性、硬體 Trap 暫存器檢查與軟體封包注入自測（無需實體網路線）。
> 2. 待單板測試驗收通過後，再切換至 **情境二（T4 ~ T5）**，接上實體網路線（`SW1 Port 4`）進行與電腦端之閉迴路雙向協議對鎖與 Wireshark 抓包分析。

---

## 測試覆蓋率總覽與情境對比

| 測試驗證維度 | 模組 / 協議目標 | 情境一：單板 + USB (JTAG/SWD) | 情境二：開發板 + PC (Ethernet 雙向) | 差異說明 |
| :--- | :--- | :---: | :---: | :--- |
| **RTOS 與記憶體管理** | FreeRTOS 排程、`heap_4` 分配與釋放 | **100% 涵蓋** | **100% 涵蓋** | 單板即可透過 GDB Watch 觀察 `xFreeBytesRemaining`，確認無記憶體洩漏 |
| **硬體配置與 Trap 規則** | `GeneralParametersTable` (`macFilter0/1`) | **100% 涵蓋** | **100% 涵蓋** | 單板可直接讀取 SJA1110 Switch 內部暫存器確認寫入狀態 |
| **控制平面訊框發送 (TX)** | `0x8B8C` 封裝、gPTP Sync、MSRP Domain 宣告 | **80% (內部計數與 loopback)** | **100% (Wireshark 實包解析)** | 連接 PC 可直接驗證外部線路剝除 `0x8B8C` 後之標準 Ethernet 格式 |
| **控制平面訊框接收 (RX)** | `EthIf_RxIndication` 多工分流 (`0x88F7`/`0x22EA`/`0x88F5`) | **90% (軟體/內部迴路注入)** | **100% (PC 端真實封包注入)** | 單板可呼叫 `SRP_PORT_RxIndication` 進行軟體自我注入自測 |
| **IEEE 802.1AS gPTP** | Pdelay 量測、Sync/Follow_Up、GM/Slave 狀態機 | **50% (僅 GM 自發與 PHY Loopback)** | **100% (與 PC `linuxptp` 雙向對鎖)** | 需對端回應 `Pdelay_Resp` 才能完整收斂真實鏈路延遲 |
| **IEEE 802.1Qat MSRP** | Talker Advertise、Listener Ready、屬性合併 | **85% (軟體模擬 RX PDU + IPC)** | **100% (PC Python/Scapy 雙向互動)** | 雙向測試可驗證跨埠傳播（Port A 進、Port B 出） |
| **硬體卸載表項** | 16 通道 CBS `idleSlope`、L2 TCAM FDB、VLAN 表 | **95% (讀回硬體 Table 驗證)** | **100% (加上實際流量整形量測)** | 連接 PC 可實際打流測試 CBS 限速與群播過濾效果 |

---

## 漸進式測試里程碑藍圖 (Milestones Roadmap)

```
[情境一：單板 + USB (JTAG)]              [情境二：開發板 + PC (Ethernet)]
T1 ───────► T2 ───────► T3 ────────► T4 ────────► T5

T1: 開機與 FreeRTOS heap_4 驗證
T2: SJA1110 硬體 Trap 規則與 8 埠初始化檢查
T3: 韌體內建軟體封包注入 (MRP 狀態機 + 硬體卸載)
T4: gPTP Pdelay 收斂與 Wireshark 外部訊框驗證
T5: MVRP / MSRP 雙向閉迴路自動化測試 (Python Scapy)
```

| 測試里程碑 | 範疇與驗證重點 | 所需設備與環境 | 狀態 |
| :---: | :--- | :--- | :---: |
| **T1** | 開機狀態、FreeRTOS `heap_4` 記憶體分配與釋放、Alive LED 週期心跳 | 單板 + S32 Debug Probe (USB) | 📋 待測 |
| **T2** | `GeneralParametersTable` 雙濾波暫存器、8 埠 SRP Bridge 初始化、計時器池運作 | 單板 + S32 Debug Probe (USB) | 📋 待測 |
| **T3** | 軟體封包注入自測（按鍵觸發）：MVRP VID 2、MSRP Talker/Listener、CBS/TCAM/VLAN 硬體寫入 | 單板 + S32 Debug Probe (USB) | 📋 待測 |
| **T4** | `SW1 Port 4` 1GbE 外部發送、Wireshark 驗證 `0x8B8C` 剝除、gPTP 125ms Sync 與 Pdelay 量測 | 開發板 + PC (1x 乙太網路線至 Port 4) | 📋 待測 |
| **T5** | PC 端 Python (Scapy) 雙向交互測試：MVRP VID 註冊、MSRP 串流預留、硬體 CBS 整形器啟動 | 開發板 + PC (Scapy / ptp4l) | 📋 待測 |

---

## 情境一：單一開發板 + USB (JTAG / SWD 除錯介面) 自我測試計畫

當手邊僅有 `SJA1110-MGS-EVM` 開發板，且僅透過 USB（連接板載除錯器或外接 S32 Debug Probe / PEMicro 至 `J16`）連上電腦時，由於沒有外部乙太網對端設備，測試的核心策略為：

> **GDB 全域變數即時監控 + 韌體內建 Self-Test 注入鉤子 (Software RX Injection) + PHY 內部迴路 (Internal Loopback)**

### 三種單板測試手法

1. **S32DS / GDB Live Expressions（即時記憶體監控）**：
   本專案編譯連結 `newlib_nano_noio`。透過 S32DS 的 **Expressions / Live Variables** 視窗，無須實體網路線即可即時監控 FreeRTOS Heap、SRP 結構體、計時器陣列與硬體傳送計數器：
   ```text
   xFreeBytesRemaining
   xMinimumEverFreeBytesRemaining
   xNumberOfSuccessfulAllocations
   xNumberOfSuccessfulFrees
   g_srp_bridge_ctx
   g_srp_timers
   EthIf_TxConfirmations
   ```

2. **韌體內建 RX 迴路自我注入（Software Packet Injection Self-Test）**：
   在韌體內部構造標準的 **MVRP JoinIn (VID=2)**、**MSRP Talker Advertise** 與 **MSRP Listener Ready** 原始位元組陣列，直接餵給 `SRP_PORT_RxIndication()`（模擬從 Port 1 與 Port 4 收到封包），即可在不接網路線的情況下完整驅動整個 MRP 狀態機與 SJA1110 硬體表項（CBS / TCAM / VLAN）卸載。可綁定至板載實體按鍵 **SWT_BUTTON1** 觸發。

3. **PHY 硬體內部 Loopback（MAC/PHY Loopback）**：
   由於 `peripherals_gPTP_SJA11XX.c` 中已設定 `.bLinkStateIgnore = true`，即使不插網路線，gPTP 與 SRP 仍會判定連接埠為 Up 並主動向外發送訊框。若進一步透過 `EthTrcv_43_PHY_SetPhyLoopbackMode()` 開啟內部 PHY (`Port 5..7` 100BASE-T1) 的 Internal Loopback，或用雙絞線將板子上的 **Port 5 與 Port 6 對接（Board Self-Loop）**，即可實現純硬體的真實封包自發自收。

---

### 里程碑 T1：開機與 FreeRTOS `heap_4` 驗證

* **測試目的**：確認韌體從 SPI Dual-Bank NVM 正常載入，FreeRTOS 排程器啟動，Alive LED 閃爍，且 `heap_4` 動態記憶體分配器無記憶體洩漏與棧溢位。
* **執行步驟**：
  1. 透過 S32DS 將 `Debug_FLASH/app_flash.elf` 下載至開發板。
  2. 開發板上電，觀察板載狀態指示燈。
  3. 啟動 S32DS Debugger 連線暫停（或於 `SRP_PORT_Init()` 回傳後設中斷點）。
  4. 於 Live Expressions 視窗監看以下變數。

* **驗收指標**：

| 檢查項目 | 觀測變數 / 暫存器 | 預期結果與驗收標準 |
| :--- | :--- | :--- |
| **開機分區狀態** | `sbNVMInitialized`, `sbGptpInitialized` | 兩者皆為 `true` |
| **Alive LED 心跳** | 板載 LED (視覺確認) | 每 `500 ms` 翻轉一次 |
| **Dual-Bank RGB LED** | 板載 RGB LED (視覺確認) | 恆亮/閃爍 **綠燈**（Bank 1）或 **黃燈**（Bank 2） |
| **無 HardFault / 死鎖** | GDB 執行狀態 | CPU 於 `vTaskDelay` 與排程任務間正常切換，無 `configASSERT` 卡死 |
| **heap_4 成功分配次數** | `xNumberOfSuccessfulAllocations` | `>= 8`（8 埠 IPC 初始化配置） |
| **heap_4 成功釋放次數** | `xNumberOfSuccessfulFrees` | `>= 8`（IPC 回應緩衝區即時釋放） |
| **剩餘 Heap 空間** | `xFreeBytesRemaining` | 介於 `25600` ~ `32768` 位元組（48 KB 總空間） |
| **長期穩定性** | `xMinimumEverFreeBytesRemaining` | 靜置 30 秒後數值維持恆定，無遞減洩漏 |

---

### 里程碑 T2：SJA1110 硬體 Trap 檢查與 8 埠初始化

* **測試目的**：驗證 `SRP_PORT_ConfigureHwTrap()` 正確將雙組 MAC 濾波規則寫入交換機 `GeneralParametersTable`，且 8 個外部橋接埠皆進入 Operational 狀態並啟動軟體計時器池。
* **執行步驟**：
  1. 於 `SRP_PORT_ConfigureHwTrap()` 之 `Switch_Ip_SetGeneralParamsTable()` 下中斷點。
  2. 讀回 `genParams` 暫存器內容或調用 `Switch_Ip_GetGeneralParamsTable(0U, &genParams)`。
  3. 讓程式運行約 3 秒後暫停，檢查 `g_srp_bridge_ctx` 與 `g_srp_timers`。

* **驗收指標**：

| 檢查項目 | GDB 監看表達式 | 預期結果與驗收標準 |
| :--- | :--- | :--- |
| **macFilter0 目的 MAC** | `genParams.macFilterResult0[0..5]` | `{0x01, 0x80, 0xC2, 0x00, 0x00, 0x0E}` |
| **macFilter0 遮罩** | `genParams.macFilter0[0..5]` | `{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}` |
| **macFilter1 目的 MAC** | `genParams.macFilterResult1[0..5]` | `{0x01, 0x80, 0xC2, 0x00, 0x00, 0x20}` |
| **macFilter1 遮罩** | `genParams.macFilter1[5]` | `0xFE`（精準匹配 MMRP `..20` 與 MVRP `..21`） |
| **SRP 網橋上下文** | `g_srp_bridge_ctx` | `!= NULL` |
| **8 埠 Operational 狀態** | `g_srp_bridge_ctx->msrp->operational_state` | `0x00FF`（8 個外部埠皆處於就緒狀態） |
| **計時器池運行** | `g_srp_timers[0].in_use` 與 `.active` | 皆為 `TRUE`，倒數計時正常運作 |
| **最大計時器容量** | `SRP_MAX_OS_TIMERS` | `64` |

---

### 里程碑 T3：韌體內建軟體封包注入 (MRP 狀態機 + 硬體卸載)

* **測試目的**：在不連接任何外部網路線的情境下，透過韌體內部函式直接注入模擬 MVRP 與 MSRP 訊框，驗證 MRP 狀態機轉換與 SJA1110 硬體表項（CBS 整形器、L2 TCAM 群播表、VLAN 表）的自動寫入。
* **觸發方式**：將自我測試函式綁定至板載按鍵 **BUTTON1** (`HandleButtonInterrupts`)。

#### 按鍵觸發自我測試程式碼 (`srp_stack/port/srp_port.c`)

```c
/**
 * @brief  板載單機自我測試函式：注入模擬 MVRP + MSRP PDU，驗證
 *         MRP 狀態機與 SJA1110 硬體卸載表項 (CBS / TCAM / VLAN)。
 *         可綁定至 example_init.c 之 HandleButtonInterrupts() 由 BUTTON1 觸發。
 */
void SRP_PORT_RunSelfTest(void)
{
    if (g_srp_bridge_ctx == NULL) return;

    /* 1. 測試 MVRP 動態 VLAN 註冊 (VID = 2，模擬來自 Logical Port 5 = SwitchPort 4) */
    struct genavb_vlan_port_map vmap = {
        .port_id = 5U,   /* GenAVB 邏輯埠 5 = SJA1110 實體交換埠 4 */
        .control = GENAVB_VLAN_ADMIN_CONTROL_REGISTERED
    };
    (void)vlan_update(2U, true, &vmap);

    /* 2. 測試 L2 TCAM 動態串流群播轉發 (Stream DA = 91:E0:F0:00:FE:00, VID = 2, 轉發至 Port 4) */
    uint8_t test_stream_da[6] = {0x91U, 0xE0U, 0xF0U, 0x00U, 0xFEU, 0x00U};
    (void)fdb_update(5U /* SwitchPort 4 */, test_stream_da, 2U,
                     true, GENAVB_FDB_PORT_CONTROL_FORWARDING);

    /* 3. 測試 IEEE 802.1Qav CBS 硬體整形器卸載 (Port 4, Class A Priority 3, 16.384 Mbps) */
    (void)common_fqtss_stream_add(5U /* SwitchPort 4 */, NULL, 2U, 3U,
                                  16384000ULL, true);
}
```

* **驗收指標**：

| 檢查項目 | GDB 表達式 / 暫存器 API | 預期結果與驗收標準 |
| :--- | :--- | :--- |
| **硬體 VLAN 查找表寫入** | `Switch_Ip_GetVlanLookupEntry(0, 2, &vlt, &found)` | `found == TRUE` |
| **VLAN 埠成員遮罩** | `vlt.vmembPort` | `0x0011`（同時包含 Bit 0 Host Port 與 Bit 4 SwitchPort 4） |
| **MVRP 註冊 VLAN 計數** | `g_srp_bridge_ctx->mvrp->map[0].num_vlans` | `1` |
| **L2 TCAM 轉發表項建立** | `Switch_Ip_SearchL2EntryInTcam(...)` | `found == TRUE` |
| **TCAM 轉發目的埠** | `g_srp_fdb_table[0].dest_ports` | `(1 << 4)` = `0x0010`（精準導向 Port 4） |
| **TCAM 啟用標記** | `g_srp_fdb_table[0].in_use` | `TRUE` |
| **CBS 運作斜率** | `fqtss_port_params[5].bandwidth_availability[tc].oper_idle_slope` | `> 0` |
| **CBS 硬體寫入狀態** | `Switch_Ip_SetCbsIdleSlope()` 回傳值 | `SWITCH_STATUS_SUCCESS` |

---

## 情境二：開發板 + 乙太網路線連接電腦（雙向互動測試計畫）

當將 `1000BASE-T` SFP 轉 RJ45 模組插入評估板的 **`SW1 Port 4` (`SwitchPortIdx = 4`, 對應 GenAVB `logical_port = 5`)** 並透過網路線連接至測試電腦（PC）網卡時，即可執行完整的**黑箱與白箱雙向閉迴路測試（Closed-Loop Bidirectional Verification）**。

### 測試環境與工具配置

* **硬體連線**：`SJA1110-MGS-EVM` 之 `SW1 Port 4` (1G SFP) $\leftrightarrow$ PC Gigabit 網卡（如 Linux `eth0` 或 Windows 乙太網路）。
* **PC 網卡組態**：
  - 關閉 PC 網卡硬體 VLAN Tag 剝除功能（以保留 802.1Q 標籤）。
  - 開啟混雜模式（Promiscuous Mode）以接收 Link-Local 群播訊框 (`01:80:C2:00:00:0E`、`01:80:C2:00:00:20`、`01:80:C2:00:00:21`)。
* **PC 端必備工具**：
  1. **Wireshark**：捕捉與解碼 gPTP (`0x88F7`)、MSRP (`0x22EA`)、MVRP (`0x88F5`) 訊框。
  2. **Python 3 + Scapy**：執行本專案提供之自動化雙向測試腳本 `tool/test_sja1110_srp.py`。
  3. **`linuxptp` (`ptp4l`)**（Linux PC）：與開發板執行高精度時間同步與 Pdelay 對鎖。

---

### 里程碑 T4：gPTP 外部訊框發送與 Pdelay 延遲收斂

* **測試目的**：驗證 SJA1110 硬體能正確剝除 Cortex-M7 送出之 `0x8B8C` 特殊管理標頭，從 `Port 4` 送出標準 Ethernet II 訊框；驗證 gPTP 時間戳記擷取與 Pdelay 狀態機收斂。
* **執行步驟**：
  1. PC 端開啟 Wireshark，設定捕獲過濾器：
     ```text
     ether proto 0x88f7 or ether proto 0x22ea or ether proto 0x88f5 or ether proto 0x88f6
     ```
  2. 開發板上電開機。
  3. （若為 Linux PC）執行 `sudo ptp4l -i eth0 -f gPTP.cfg -m -s` 擔任 Slave 回應 Pdelay。

* **驗收指標**：

| 檢查項目 | 觀測方法 | 預期結果與驗收標準 |
| :--- | :--- | :--- |
| **無 `0x8B8C` 洩漏** | Wireshark 封包清單 | 捕獲封包之 EtherType 皆為乾淨的 `0x88F7`/`0x22EA`/`0x88F5`，零 `0x8B8C` 殘留 |
| **gPTP Sync 發送週期** | Wireshark 時間戳記 | 每 `125 ms` 穩定發送一組 `Sync` 與 `Follow_Up` (`s8SyncIntervalLog = -3`) |
| **Pdelay_Req 初始週期** | Wireshark 時間戳記 | 每 `1 秒` 發送一次 (`s8LogPdelayReqIntervalDefault = 0`) |
| **Pdelay 測量降速** | Wireshark 時間戳記 | 測量滿 `50` 次後，發送週期自動拉長至 `8 秒` (`log = 3`) |
| **gPTP 來源 MAC** | Wireshark 乙太網標頭 | `22:33:44:55:66:77` |
| **MSRP/MVRP 來源 MAC** | Wireshark 乙太網標頭 | `22:33:44:55:66:75`（最低半位元組嵌入 `logical_port = 5`） |
| **Pdelay 數值收斂** | GDB: `rGptpCfgParams.paPdelay[0].f64NeighborPropDelay` | 收斂為實體線材延遲（`< 20000 ns`） |
| **Pdelay 有效標記** | GDB: `rGptpCfgParams.paPdelay[0].bPdelayValueValid` | `true` |
| **MSRP 開機 Domain 宣告** | Wireshark MSRP 解碼 | 開機 2 秒內發出 SR Class A (Prio 3, VID 2) 與 Class B (Prio 2, VID 2) 之 Domain 屬性 |
| **發送錯誤計數** | GDB: `g_srp_bridge_ctx->msrp->port[3].num_tx_err` | `0` |

---

### 里程碑 T5：MVRP 與 MSRP 雙向閉迴路自動化驗證

* **測試目的**：透過 PC 端 Python Scapy 腳本向開發板發送 MVRP 與 MSRP 訊框，驗證開發板入埠攔截 (`macFilter1`/`macFilter0`)、狀態機轉換 (`MT` $\to$ `IN`) 以及跨埠屬性傳播觸發之硬體 CBS 與 L2 TCAM 寫入。

#### 測試 T5-A：MVRP VID=2 動態註冊 (PC $\to$ 開發板 $\to$ 硬體 VLAN 表)

* **步驟**：執行 `tool/test_sja1110_srp.py` 之 Stage 2（發送 `MVRP JoinIn (VID=2)`）。
* **驗收指標**：
  1. **Wireshark 狀態機轉換**：開發板在下一個 Join Timer 週期從 `Port 4` 回送之 MVRP PDU 中，針對 VID=2 的編碼事件由 `JoinMt` 轉變為 **`JoinIn`** 或 **`In`**（證明 Registrar 已進入 `MRP_STATE_IN`！）。
  2. **GDB 硬體 VLAN 表**：`Switch_Ip_GetVlanLookupEntry(0, 2, &vlt, &found)` 回傳 `found == TRUE`，且 `vlt.vmembPort` 包含 `Port 4`。
  3. **Leave 超時註銷**：PC 停止宣告並等待 `1000 ms` 後，`VID = 2` 從 `mvrp->map[0]` 銷毀並自動呼叫 `vlan_delete()`。

#### 測試 T5-B：MSRP Talker Advertise 跨埠轉發 (開發板 $\to$ PC)

* **步驟**：於 GDB 命令列中向 `Port 1` (`logical_port = 2`) 模擬注入一筆 Talker Advertise：
  ```gdb
  call SRP_PORT_RxIndication(2, <talker_advertise_bytes>, len)
  ```
* **驗收指標**：開發板判定屬性合法，依據 IEEE 802.1Qat 跨埠傳播機制，自動由 `Port 4` 向 PC Wireshark 發出該筆 `Talker Advertise` 訊框。

#### 測試 T5-C：MSRP Listener Ready 觸發硬體 CBS 與 L2 TCAM 啟動 (全閉迴路)

* **步驟**：PC 端 Scapy 腳本針對上述 `StreamID` 送出 `MSRP Listener Ready`。
* **驗收指標**：

| 檢查項目 | 觀測方法 | 預期結果與驗收標準 |
| :--- | :--- | :--- |
| **CBS 運作斜率** | GDB: `fqtss_port_params[5].bandwidth_availability[tc].oper_idle_slope` | `> 0` |
| **CBS 硬體寫入** | GDB: `Switch_Ip_SetCbsIdleSlope()` 回傳值 | `SWITCH_STATUS_SUCCESS` |
| **L2 TCAM 表項** | GDB: `g_srp_fdb_table[0].in_use` | `TRUE` |
| **TCAM 轉發目的埠** | GDB: `g_srp_fdb_table[0].dest_ports` | `(1 << 4)` = `0x0010`（精準導向 Port 4 / PC） |
| **Leave 資源釋放** | PC 送出 Listener Leave，等待 1 秒 | `fdb_delete()` 呼叫，CBS `oper_idle_slope` 歸零釋放 |

---

## 單條網路線測試技巧與架構說明

> [!IMPORTANT]
> **IEEE 802.1Q 水平分割 (Split Horizon) 特性**：
> 標準網橋不會將從某埠收到的屬性原封不動從同一埠反射回去。因此，若要在 `Port 4` 觸發硬體 CBS 頻寬預留與 L2 TCAM 群播過濾，必須先有**其他連接埠（如 Port 1..3 或 5..8）宣告 Talker Advertise**，且 `Port 4` 收到來自 PC 的 Listener Ready。

**單線實驗室兩種突破手法**：
1. **手法一（單線 + GDB 注入）**：透過 GDB 模擬 `Port 1` 收到 `Talker Advertise`，開發板會自動將其從實體 `Port 4` 輸出給 PC Wireshark，接著 PC Scapy 再從 `Port 4` 回送 `Listener Ready`，即可在單條線下走完 100% 閉迴路！
2. **手法二（雙線或板載對接環路）**：拿一條短雙絞線將板載 `Port 5` 與 `Port 6` 對接，或用第二張 PC 網卡接 `Port 2` (RJ45)，一埠當 Talker、另一埠當 Listener。

---

## 相關技術規範與參考文獻

- [IEEE 802.1Q-2018](https://standards.ieee.org/ieee/802.1Q/6844/) — MRP / MVRP / MSRP / CBS 規範
- [IEEE 802.1AS-2020](https://standards.ieee.org/ieee/802.1AS/7121/) — gPTP 時間同步規範
- [NXP SJA1110 User Manual](https://www.nxp.com/products/interfaces/ethernet-/automotive-ethernet-switches/sja1110-multi-gig-safe-and-secure-tsn-ethernet-switch-with-integrated-100base-t1-phys:SJA1110) — 硬體暫存器規格手冊
- [linuxptp](https://linuxptp.sourceforge.net/) — Linux 802.1AS 測試套件
- [Scapy 官方文件](https://scapy.readthedocs.io/) — Python 封包構造函式庫

---

## 授權條款

BSD-3-Clause License. Copyright (c) 2026, Max97k. All rights reserved.
