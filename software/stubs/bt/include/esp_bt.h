#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  ESP_BT_MODE_IDLE = 0x00,       /*!< Bluetooth is not running */
  ESP_BT_MODE_BLE = 0x01,        /*!< Run BLE mode */
  ESP_BT_MODE_CLASSIC_BT = 0x02, /*!< Run Classic BT mode */
  ESP_BT_MODE_BTDM = 0x03,       /*!< Run dual mode */
} esp_bt_mode_t;

#ifdef __cplusplus
}
#endif