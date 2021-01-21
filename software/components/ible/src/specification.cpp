#include "ible/specification.hpp"

void bt::application_t::notified(event_t e) {
  switch (e.event) {
    case ESP_GATTS_REG_EVT: {
      m_profiles.foreach ([e, this](profile_t* p) { m_attributes->visit(p); });
      break;
    }
    default:
      break;
  }
}

void bt::profile_t::notified(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
  m_handler(*this, event, gatts_if, param);

  switch (event) {
    case ESP_GATTS_REG_EVT: {
      for (auto [id, srv] : m_services) {
        auto* vis = new attribute_visitor{std::make_shared<esp_gatt>(gatts_if)};
        srv->accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(srv)>>*>(vis));
        delete vis;
      }
      break;
    }
    case ESP_GATTS_CREAT_ATTR_TAB_EVT: {
      for (auto& [id, srv] : m_services) {
        srv->notified(event, gatts_if, param);
      }
      break;
    }
    default:
      break;
  }
}