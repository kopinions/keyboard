#pragma once
#include <esp_gatt_defs.h>
#include <esp_gatts_api.h>
namespace bt {
class gatt_if_t {
 public:
  virtual esp_err_t connected_with(uint16_t conn_id, esp_bd_addr_t bda, esp_gatt_conn_params_t params) = 0;

  virtual esp_err_t create_attr_tab(const esp_gatts_attr_db_t* gatts_attr_db, uint8_t max_nb_attr,
                                    uint8_t srvc_inst_id) = 0;

  virtual esp_err_t response(uint32_t trans_id, esp_gatt_status_t status, esp_gatt_rsp_t* rsp) = 0;

  virtual esp_err_t send_indicate(uint16_t attr_handle, uint16_t value_len, uint8_t* value, bool need_confirm) = 0;
};

class esp_gatt : public gatt_if_t {
 public:
  explicit esp_gatt(esp_gatt_if_t gatt_if);

  esp_err_t create_attr_tab(const esp_gatts_attr_db_t* gatts_attr_db, uint8_t max_nb_attr,
                            uint8_t srvc_inst_id) override;
  esp_err_t response(uint32_t trans_id, esp_gatt_status_t status, esp_gatt_rsp_t* rsp) override;

  esp_err_t send_indicate(uint16_t attr_handle, uint16_t value_len, uint8_t* value, bool need_confirm) override;

  esp_err_t connected_with(uint16_t conn_id, uint8_t* bda, esp_gatt_conn_params_t params) override;

 private:
  esp_gatt_if_t m_gatt_if;
  uint16_t  m_connection_id;
  esp_bd_addr_t m_connection_remote_bda;
  esp_gatt_conn_params_t m_connection_params;
};
}  // namespace bt