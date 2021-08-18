#pragma once
#include <esp_err.h>
#include "esp_gap_ble_api.h"
typedef enum {
  ESP_BT_MODE_IDLE = 0x00,       /*!< Bluetooth is not running */
  ESP_BT_MODE_BLE = 0x01,        /*!< Run BLE mode */
  ESP_BT_MODE_CLASSIC_BT = 0x02, /*!< Run Classic BT mode */
  ESP_BT_MODE_BTDM = 0x03,       /*!< Run dual mode */
} esp_bt_mode_t;

typedef struct {
  /*
   * Following parameters can be configured runtime, when call esp_bt_controller_init()
   */
  uint16_t controller_task_stack_size; /*!< Bluetooth controller task stack size */
  uint8_t controller_task_prio;        /*!< Bluetooth controller task priority */
  uint8_t hci_uart_no;                 /*!< If use UART1/2 as HCI IO interface, indicate UART number */
  uint32_t hci_uart_baudrate;          /*!< If use UART1/2 as HCI IO interface, indicate UART baudrate */
  uint8_t scan_duplicate_mode;         /*!< scan duplicate mode */
  uint8_t scan_duplicate_type;         /*!< scan duplicate type */
  uint16_t normal_adv_size;            /*!< Normal adv size for scan duplicate */
  uint16_t mesh_adv_size;              /*!< Mesh adv size for scan duplicate */
  uint16_t send_adv_reserved_size;     /*!< Controller minimum memory value */
  uint32_t controller_debug_flag;      /*!< Controller debug log flag */
  uint8_t mode;                        /*!< Controller mode: BR/EDR, BLE or Dual Mode */
  uint8_t ble_max_conn;                /*!< BLE maximum connection numbers */
  uint8_t bt_max_acl_conn;             /*!< BR/EDR maximum ACL connection numbers */
  uint8_t bt_sco_datapath;             /*!< SCO data path, i.e. HCI or PCM module */
  bool auto_latency;                   /*!< BLE auto latency, used to enhance classic BT performance */
  bool bt_legacy_auth_vs_evt;          /*!< BR/EDR Legacy auth complete event required to  protect from BIAS attack */
  /*
   * Following parameters can not be configured runtime when call esp_bt_controller_init()
   * It will be overwrite with a constant value which in menuconfig or from a macro.
   * So, do not modify the value when esp_bt_controller_init()
   */
  uint8_t bt_max_sync_conn; /*!< BR/EDR maximum ACL connection numbers. Effective in menuconfig */
  uint8_t ble_sca;          /*!< BLE low power crystal accuracy index */
  uint8_t pcm_role;         /*!< PCM role (master & slave)*/
  uint8_t pcm_polar;        /*!< PCM polar trig (falling clk edge & rising clk edge) */
  uint32_t magic;           /*!< Magic number */
} esp_bt_controller_config_t;

esp_err_t esp_bluedroid_enable(void) { return ESP_OK; }
esp_err_t esp_bluedroid_init(void) { return ESP_OK; }

esp_err_t esp_bt_controller_mem_release(esp_bt_mode_t mode) { return ESP_OK; }

#define BT_CONTROLLER_INIT_CONFIG_DEFAULT() {};

esp_err_t esp_bt_controller_init(esp_bt_controller_config_t *cfg) { return ESP_OK; }
esp_err_t esp_bt_controller_enable(esp_bt_mode_t mode) { return ESP_OK; }
typedef enum {
  ESP_BLUEDROID_STATUS_UNINITIALIZED = 0, /*!< Bluetooth not initialized */
  ESP_BLUEDROID_STATUS_INITIALIZED,       /*!< Bluetooth initialized but not enabled */
  ESP_BLUEDROID_STATUS_ENABLED            /*!< Bluetooth initialized and enabled */
} esp_bluedroid_status_t;
esp_bluedroid_status_t esp_bluedroid_get_status(void) { return ESP_BLUEDROID_STATUS_ENABLED; }
