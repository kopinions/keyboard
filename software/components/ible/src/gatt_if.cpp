#include "ible/gatt_if.hpp"

#include <cstring>
#include <iostream>

bt::esp_gatt::esp_gatt(esp_gatt_if_t gatt_if) : m_gatt_if(gatt_if) {}

esp_err_t bt::esp_gatt::create_attr_tab(const esp_gatts_attr_db_t *gatts_attr_db, uint8_t max_nb_attr,
                                        uint8_t srvc_inst_id) {
  return esp_ble_gatts_create_attr_tab(gatts_attr_db, m_gatt_if, max_nb_attr, srvc_inst_id);
}
esp_err_t bt::esp_gatt::response(uint32_t trans_id, esp_gatt_status_t status, esp_gatt_rsp_t *rsp) {
  return esp_ble_gatts_send_response(m_gatt_if, m_connection_id, trans_id, ESP_GATT_OK, rsp);
}
esp_err_t bt::esp_gatt::send_indicate(uint16_t attr_handle, uint16_t value_len, const uint8_t *value, bool need_confirm) {
  return esp_ble_gatts_send_indicate(m_gatt_if, m_connection_id, attr_handle, value_len, value, need_confirm);
}

esp_err_t bt::esp_gatt::connected_with(uint16_t conn_id, uint8_t *bda, esp_gatt_conn_params_t params) {
  m_connection_id = conn_id;
  std::memcpy(m_connection_remote_bda, bda, 6);
  m_connection_params = params;
  return ESP_GATT_OK;
}
