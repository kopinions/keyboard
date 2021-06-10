#include "ible/visitors.hpp"

static const uint16_t s_primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t s_include_service_uuid = ESP_GATT_UUID_INCLUDE_SERVICE;
static const uint16_t CHARACTERISTIC_DECLARE = ESP_GATT_UUID_CHAR_DECLARE;
static const uint16_t s_character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;

static const uint16_t s_bat_level_uuid = ESP_GATT_UUID_BATTERY_LEVEL;
static const uint16_t s_bat_char_pres_format_uuid = ESP_GATT_UUID_CHAR_PRESENT_FORMAT;
static const uint8_t s_char_prop_read_notify = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY;

static const uint16_t s_bat_svc = ESP_GATT_UUID_BATTERY_SERVICE_SVC;
static uint8_t bat_level = 1;
enum {
  BAS_IDX_SVC,

  BAS_IDX_BATT_LVL_CHAR,
  BAS_IDX_BATT_LVL_VAL,
  BAS_IDX_BATT_LVL_CCC,
  BAS_IDX_BATT_LVL_PRES_FMT,

  BAS_IDX_NB,
};
static const uint16_t s_character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
static void add_db_record(esp_gatts_attr_db_t *db, size_t index, uint8_t *uuid, uint8_t perm, uint16_t max_length, uint16_t length, uint8_t *value)
{
  db[index].attr_control.auto_rsp = ESP_GATT_AUTO_RSP;
  db[index].att_desc.uuid_length = ESP_UUID_LEN_16;
  db[index].att_desc.uuid_p = uuid;
  db[index].att_desc.perm = perm;
  db[index].att_desc.max_length = max_length;
  db[index].att_desc.length = length;
  db[index].att_desc.value = value;
}

void bt::attribute_visitor::visit(bt::profile_t *t) {
  std::cout << "visit profile" << std::endl;
  for (auto srv : t->services()) {
//    auto *service_visitor = new attribute_visitor(m_gatt_if);
//    srv.accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(srv)>> *>(service_visitor));
//
//    for (auto a : service_visitor->m_attributes) {
//      std::cout << "length" << a.att_desc.length << std::endl;
//      std::cout << "uuid length" << a.att_desc.uuid_length << std::endl;
//    }
//    auto *_last_db = new esp_gatts_attr_db_t[service_visitor->m_attributes.size() +1];
//    for (auto i = 0; i < service_visitor->m_attributes.size(); i++) {
//      _last_db[i].att_desc.uuid_length = service_visitor->m_attributes.at(i).att_desc.uuid_length;
//      _last_db[i].att_desc.uuid_p = service_visitor->m_attributes.at(i).att_desc.uuid_p;
//      _last_db[i].att_desc.length = service_visitor->m_attributes.at(i).att_desc.length;
//      _last_db[i].att_desc.max_length = service_visitor->m_attributes.at(i).att_desc.max_length;
//      _last_db[i].att_desc.perm = service_visitor->m_attributes.at(i).att_desc.perm;
//      _last_db[i].att_desc.value = service_visitor->m_attributes.at(i).att_desc.value;
//      _last_db[i].attr_control.auto_rsp = service_visitor->m_attributes.at(i).attr_control.auto_rsp;
//    }

    static esp_gatts_attr_db_t *_last_db = NULL;

    _last_db = (esp_gatts_attr_db_t *)malloc(sizeof(esp_gatts_attr_db_t) * BAS_IDX_NB);
    if (!_last_db) {
      std::cout << "malloc error";
    }
    add_db_record(_last_db, BAS_IDX_SVC, (uint8_t *)&s_primary_service_uuid, ESP_GATT_PERM_READ, 2, 2, (uint8_t *)&s_bat_svc);
    add_db_record(_last_db, BAS_IDX_BATT_LVL_CHAR, (uint8_t *)&s_character_declaration_uuid, ESP_GATT_PERM_READ, 1, 1, (uint8_t *)&s_char_prop_read_notify);
    add_db_record(_last_db, BAS_IDX_BATT_LVL_VAL, (uint8_t *)&s_bat_level_uuid, ESP_GATT_PERM_READ, 1, 1, (uint8_t *)&bat_level);
    add_db_record(_last_db, BAS_IDX_BATT_LVL_CCC, (uint8_t *)&s_character_client_config_uuid, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, 2, 0,  NULL);
    add_db_record(_last_db, BAS_IDX_BATT_LVL_PRES_FMT, (uint8_t *)&s_bat_char_pres_format_uuid, ESP_GATT_PERM_READ, 7, 0,  NULL);

    esp_err_t err = m_gatt_if->create_attr_tab(_last_db, BAS_IDX_NB, 0);
    if (err) {
      std::cout << "error while attribute sevice visitor" << std::endl;
    }
    free(_last_db);
    //    delete service_visitor;
  }
}

void bt::attribute_visitor::visit(bt::service_t *t) {
  std::cout << "visit service" << std::endl;
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
}

void bt::attribute_visitor::visit(bt::characteristic_t *t) {
  std::cout << "visit characteristic" << std::endl;
  m_attributes.push_back(esp_gatts_attr_db_t{.attr_control = {.auto_rsp = ESP_GATT_AUTO_RSP},
                                             .att_desc = {.uuid_length = ESP_UUID_LEN_16,
                                                          .uuid_p = (uint8_t *)&CHARACTERISTIC_DECLARE,
                                                          .perm = ESP_GATT_PERM_READ,
                                                          .max_length = 1,
                                                          .length = 1,
                                                          .value = (uint8_t *)&(t->m_property)}});

  size_t i = sizeof(decltype(t->m_id)) / sizeof(uint8_t);
  std::cout << "size i " << i << std::endl;
  m_attributes.push_back(
      esp_gatts_attr_db_t{.attr_control = {.auto_rsp = static_cast<uint8_t>(t->automated() ? 1u : 0u)},
                          .att_desc = {.uuid_length = ESP_UUID_LEN_16,
                                       .uuid_p = (uint8_t *)(&s_bat_level_uuid),
                                       .perm = static_cast<uint16_t>(t->m_permission),
                                       .max_length = 1,
                                       .length = 1,
                                       .value = t->m_value}});
}