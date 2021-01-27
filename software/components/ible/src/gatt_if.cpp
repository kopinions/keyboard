#include "ible/gatt_if.hpp"

#include <iostream>

bt::esp_gatt::esp_gatt(esp_gatt_if_t gatt_if) : m_gatt_if(gatt_if) {}

esp_err_t bt::esp_gatt::create_attr_tab(const esp_gatts_attr_db_t *gatts_attr_db, uint8_t max_nb_attr,
                                        uint8_t srvc_inst_id) {
  std::cout << "create attribute to the bt stack" << std::endl;
  return esp_ble_gatts_create_attr_tab(gatts_attr_db, m_gatt_if, max_nb_attr, srvc_inst_id);
}
