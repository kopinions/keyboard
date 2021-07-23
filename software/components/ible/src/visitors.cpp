#include "ible/visitors.hpp"

static const uint16_t s_primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t s_include_service_uuid = ESP_GATT_UUID_INCLUDE_SERVICE;

void bt::attribute_visitor::visit(bt::profile_t *t) {
  for (auto *srv : t->services()) {
    auto *service_visitor = new attribute_visitor(m_gatt_if);
    srv->accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(srv)>> *>(service_visitor));
    esp_err_t err = m_gatt_if->create_attr_tab(service_visitor->m_attributes.data(),
                                               static_cast<uint8_t>(service_visitor->m_attributes.size()), 0);
    if (err) {
      std::cout << "error while attribute sevice visitor" << std::endl;
    }
    delete service_visitor;
  }
}

void bt::attribute_visitor::visit(bt::service_t *t) {
  m_attributes.push_back(esp_gatts_attr_db_t{.attr_control = {.auto_rsp = ESP_GATT_AUTO_RSP},
                                             .att_desc = {.uuid_length = ESP_UUID_LEN_16,
                                                          .uuid_p = (uint8_t *)&s_primary_service_uuid,
                                                          .perm = ESP_GATT_PERM_READ,
                                                          .max_length = 2,
                                                          .length = 2,
                                                          .value = (uint8_t *)&t->id()}});

  for (auto c : t->characteristics()) {
    c->accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(c)>> *>(this));
  }
}

void bt::attribute_visitor::visit(bt::characteristic_t *t) {
  for (auto attr : t->attributes()) {
    attr->accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(attr)>> *>(this));
  }
}

void bt::attribute_visitor::visit(bt::attribute_t *t) {
  m_attributes.push_back(
      esp_gatts_attr_db_t{.attr_control = {.auto_rsp = static_cast<uint8_t>(t->m_automated ? 1u : 0u)},
                          .att_desc = {.uuid_length = ESP_UUID_LEN_16,
                                       .uuid_p = (uint8_t *)(&t->m_uuid),
                                       .perm = static_cast<uint16_t>(t->m_permission),
                                       .max_length = t->m_max_length,
                                       .length = t->m_length,
                                       .value = t->m_value}});
}
