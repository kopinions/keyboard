#include "ible/visitors.hpp"

static const uint16_t s_primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t s_include_service_uuid = ESP_GATT_UUID_INCLUDE_SERVICE;

void bt::attribute_visitor::visit(bt::profile_t *t) {
  for (auto *srv : t->services()) {
    srv->accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(srv)>> *>(this));
    esp_err_t err = m_gatt_if->create_attr_tab(m_attributes.data(), static_cast<uint8_t>(m_attributes.size()), 0);
    m_attributes.clear();
    if (err) {
      std::cout << "error while attribute service visitor" << std::endl;
    }
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
  m_attributes.push_back(esp_gatts_attr_db_t{
      .attr_control = {.auto_rsp = static_cast<uint8_t>(t->m_automated ? ESP_GATT_AUTO_RSP : ESP_GATT_RSP_BY_APP)},
      .att_desc = {.uuid_length = ESP_UUID_LEN_16,
                   .uuid_p = (uint8_t *)(&t->m_uuid),
                   .perm = static_cast<uint16_t>(t->m_permission),
                   .max_length = t->m_max_length,
                   .length = t->m_length,
                   .value = t->m_value}});
}
bt::attribute_visitor::attribute_visitor(std::shared_ptr<gatt_if_t> gatt_if) { m_gatt_if = std::move(gatt_if); }

void bt::update_handles_visitor::visit(bt::profile_t *t) {
  for (auto *srv : t->services()) {
    srv->accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(srv)>> *>(this));
  }
}
void bt::update_handles_visitor::visit(bt::service_t *t) {
  if (t->id() == std::get<uint16_t>(m_uuid)) {
    t->handled_by(m_handles[m_handle_index]);
    m_handle_index++;
    for (auto c : t->characteristics()) {
      c->accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(c)>> *>(this));
    }
    auto ret = esp_ble_gatts_start_service(m_handles[0]);
    if (ret) {
      m_logger->error("%s: %s start service failed", __func__);
      return;
    }
  }
}
void bt::update_handles_visitor::visit(bt::characteristic_t *t) {
  for (auto attr : t->attributes()) {
    attr->accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(attr)>> *>(this));
  }
}
void bt::update_handles_visitor::visit(bt::attribute_t *t) {
  m_logger->info("%d", m_handles[m_handle_index]);
  t->handled_by(m_handles[m_handle_index]);
  m_handle_index++;
}
bt::update_handles_visitor::update_handles_visitor(kopinions::logging::logger *logger,
                                                   std::shared_ptr<gatt_if_t> gatt_if, uint16_t uuid,
                                                   uint16_t num_handles, uint16_t *handles)
    : m_logger{logger}, m_gatt_if{gatt_if}, m_uuid{uuid}, m_num_handles{num_handles}, m_handles{handles} {
  m_handle_index = 0;
}
