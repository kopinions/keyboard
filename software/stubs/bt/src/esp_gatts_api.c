#include "esp_gatts_api.h"

esp_err_t esp_ble_gatts_register_callback(esp_gatts_cb_t callback) { return ESP_OK; }

esp_err_t esp_ble_gatts_app_register(uint16_t app_id) { return ESP_OK; }

esp_err_t esp_ble_gatts_create_attr_tab(const esp_gatts_attr_db_t *gatts_attr_db, esp_gatt_if_t gatts_if,
                                        uint8_t max_nb_attr, uint8_t srvc_inst_id) {
  return ESP_GATT_OK;
}
esp_err_t esp_ble_gatts_send_response(esp_gatt_if_t gatts_if, uint16_t conn_id, uint32_t trans_id,
                                      esp_gatt_status_t status, esp_gatt_rsp_t *rsp) {
  return ESP_OK;
}

esp_err_t esp_ble_gatts_send_indicate(esp_gatt_if_t gatts_if, uint16_t conn_id, uint16_t attr_handle,
                                      uint16_t value_len, uint8_t *value, bool need_confirm) {
  return ESP_OK;
}

esp_err_t esp_ble_gatts_start_service(uint16_t service_handle) { return ESP_OK; }