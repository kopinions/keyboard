#include "ible/visitors.hpp"

static const uint16_t s_primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t s_include_service_uuid = ESP_GATT_UUID_INCLUDE_SERVICE;
static const uint16_t s_character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
static const uint16_t s_character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;

void bt::attribute_visitor::visit(bt::profile_t* t) {
  std::cout << "visit profile" << std::endl;
  for (auto srv : t->services()) {
    auto* service_visitor = new attribute_visitor(m_gatt_if);
    srv.accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(srv)>>*>(service_visitor));
    delete service_visitor;
  }
}

void bt::attribute_visitor::visit(bt::service_t* t) {
  std::cout << "visit service" << std::endl;
  m_attributes.push_back(esp_gatts_attr_db_t{.attr_control = {.auto_rsp = ESP_GATT_AUTO_RSP},
                                             .att_desc = {.uuid_length = 2,
                                                          .uuid_p = (uint8_t*)&s_primary_service_uuid,
                                                          .perm = ESP_UUID_LEN_16,
                                                          .max_length = 2,
                                                          .length = 1,
                                                          .value = nullptr}});

  for (auto c : t->characteristics()) {
    c.accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(c)>>*>(this));
  }

  esp_err_t err = m_gatt_if->create_attr_tab(m_attributes.data(), 2, 0);
  if (err) {
    std::cout << "error while attribute sevice visitor" << std::endl;
  }
}

void bt::attribute_visitor::visit(bt::characteristic_t* t) {
  std::cout << "visit characteristic" << std::endl;

  m_attributes.push_back(esp_gatts_attr_db_t{.attr_control = {.auto_rsp = ESP_GATT_AUTO_RSP},
                                             .att_desc = {.uuid_length = 2,
                                                          .uuid_p = (uint8_t*)&s_character_declaration_uuid,
                                                          .perm = ESP_UUID_LEN_16,
                                                          .max_length = 1,
                                                          .length = 1,
                                                          .value = nullptr}});

  m_attributes.push_back(esp_gatts_attr_db_t{.attr_control = {.auto_rsp = ESP_GATT_AUTO_RSP},
                                             .att_desc = {.uuid_length = 2,
                                                          .uuid_p = (uint8_t*)&s_character_client_config_uuid,
                                                          .perm = ESP_UUID_LEN_16,
                                                          .max_length = 1,
                                                          .length = 1,
                                                          .value = nullptr}});
}