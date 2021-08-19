#include "esp_bt_main.h"

esp_err_t esp_bluedroid_enable(void) { return ESP_OK; }
esp_err_t esp_bluedroid_init(void) { return ESP_OK; }
esp_err_t esp_bt_controller_mem_release(esp_bt_mode_t mode) { return ESP_OK; }
esp_err_t esp_bt_controller_init(esp_bt_controller_config_t *cfg) { return ESP_OK; }
esp_err_t esp_bt_controller_enable(esp_bt_mode_t mode) { return ESP_OK; }
esp_bluedroid_status_t esp_bluedroid_get_status(void) { return ESP_BLUEDROID_STATUS_ENABLED; }
