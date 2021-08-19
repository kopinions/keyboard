#include "esp_gap_ble_api.h"

esp_err_t esp_ble_gap_register_callback(esp_gap_ble_cb_t callback) { return ESP_OK; }
esp_err_t esp_ble_gap_set_device_name(const char *name) { return ESP_OK; }
esp_err_t esp_ble_gap_config_adv_data(esp_ble_adv_data_t *adv_data) { return ESP_OK; }
esp_err_t esp_ble_gap_start_advertising(esp_ble_adv_params_t *adv_params) { return ESP_OK; }
esp_err_t esp_ble_gap_set_security_param(esp_ble_sm_param_t param_type, void *value, uint8_t len) { return ESP_OK; }
esp_err_t esp_ble_gap_security_rsp(esp_bd_addr_t bd_addr, bool accept) { return ESP_OK; }