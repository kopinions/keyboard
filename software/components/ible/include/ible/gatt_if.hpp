#pragma once
#include <esp_gatt_defs.h>
#include <esp_gatts_api.h>
namespace bt {
class gatt_if_t {
 public:
  virtual esp_err_t create_attr_tab(const esp_gatts_attr_db_t* gatts_attr_db, uint8_t max_nb_attr,
                                    uint8_t srvc_inst_id) = 0;
};

class esp_gatt : public gatt_if_t {
 public:
  explicit esp_gatt(esp_gatt_if_t gatt_if);

  esp_err_t create_attr_tab(const esp_gatts_attr_db_t* gatts_attr_db, uint8_t max_nb_attr,
                            uint8_t srvc_inst_id) override;

 private:
  esp_gatt_if_t m_gatt_if;
};
}  // namespace bt