#include "ible/visitors.hpp"

static const uint16_t s_primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t s_include_service_uuid = ESP_GATT_UUID_INCLUDE_SERVICE;
static const uint16_t s_character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
static const uint16_t s_character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;

static const uint16_t s_bat_level_uuid = ESP_GATT_UUID_BATTERY_LEVEL;
static const uint16_t s_bat_char_pres_format_uuid = ESP_GATT_UUID_CHAR_PRESENT_FORMAT;
static const uint8_t s_char_prop_read_notify = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY;

void bt::attribute_visitor::visit(bt::profile_t *t) {
  std::cout << "visit profile" << std::endl;
  for (auto srv : t->services()) {
    auto *service_visitor = new attribute_visitor(m_gatt_if);
    std::cout << service_visitor->m_attributes.size() << "  :attributes" << std::endl;

    srv.accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(srv)>> *>(service_visitor));
    std::cout << service_visitor->m_attributes.size() << "  :attributes" << std::endl;
    delete service_visitor;
  }
}
static const uint16_t s_bat_svc = ESP_GATT_UUID_BATTERY_SERVICE_SVC;
static uint8_t bat_level = 1;

void bt::attribute_visitor::visit(bt::service_t *t) {
  std::cout << "visit service" << std::endl;
  std::cout << m_attributes.size() << "  :attributes before service visit" << std::endl;
  m_attributes.push_back(esp_gatts_attr_db_t{.attr_control = {.auto_rsp = ESP_GATT_AUTO_RSP},
                                             .att_desc = {.uuid_length = ESP_UUID_LEN_16,
                                                          .uuid_p = (uint8_t *)&s_primary_service_uuid,
                                                          .perm = ESP_GATT_PERM_READ,
                                                          .max_length = 2,
                                                          .length = 2,
                                                          .value = (uint8_t *)&s_bat_svc}});

  for (auto c : t->characteristics()) {
    c.accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(c)>> *>(this));
  }
  std::cout << m_attributes.size() << "  :attributes after service visit" << std::endl;

  esp_err_t err = m_gatt_if->create_attr_tab(m_attributes.data(), 2, 0);
  if (err) {
    std::cout << "error while attribute sevice visitor" << std::endl;
  }
}

void bt::attribute_visitor::visit(bt::characteristic_t *t) {
  std::cout << "visit characteristic" << std::endl;
  m_attributes.push_back(esp_gatts_attr_db_t{.attr_control = {.auto_rsp = ESP_GATT_AUTO_RSP},
                                             .att_desc = {.uuid_length = ESP_UUID_LEN_16,
                                                          .uuid_p = (uint8_t *)&s_character_declaration_uuid,
                                                          .perm = ESP_GATT_PERM_READ,
                                                          .max_length = 1,
                                                          .length = 1,
                                                          .value = (uint8_t *)&s_char_prop_read_notify}});

  m_attributes.push_back(esp_gatts_attr_db_t{.attr_control = {.auto_rsp = ESP_GATT_AUTO_RSP},
                                             .att_desc = {.uuid_length = ESP_UUID_LEN_16,
                                                          .uuid_p = (uint8_t *)&s_bat_level_uuid,
                                                          .perm = ESP_GATT_PERM_READ,
                                                          .max_length = 1,
                                                          .length = 1,
                                                          .value = (uint8_t *)&bat_level}});

  m_attributes.push_back(esp_gatts_attr_db_t{.attr_control = {.auto_rsp = ESP_GATT_AUTO_RSP},
                                             .att_desc = {.uuid_length = ESP_UUID_LEN_16,
                                                          .uuid_p = (uint8_t *)&s_character_client_config_uuid,
                                                          .perm = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
                                                          .max_length = 2,
                                                          .length = 0,
                                                          .value = nullptr}});

  m_attributes.push_back(esp_gatts_attr_db_t{.attr_control = {.auto_rsp = ESP_GATT_AUTO_RSP},
                                             .att_desc = {.uuid_length = ESP_UUID_LEN_16,
                                                          .uuid_p = (uint8_t *)&s_bat_char_pres_format_uuid,
                                                          .perm = ESP_GATT_PERM_READ,
                                                          .max_length = 7,
                                                          .length = 0,
                                                          .value = nullptr}});
}