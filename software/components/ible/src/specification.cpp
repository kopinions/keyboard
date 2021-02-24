#include "ible/specification.hpp"

#include <esp_gap_ble_api.h>

#include <utility>

#include "esp_if/esp_log_sink.hpp"
#include "ible/visitors.hpp"

void bt::application_t::notified(std::shared_ptr<gatt_if_t> gatt, event_t e) {
  switch (e.event) {
    case ESP_GATTS_REG_EVT: {

      break;
    }
    case ESP_GATTS_CREAT_ATTR_TAB_EVT: {
      m_attributes = std::make_shared<attribute_visitor>(gatt);
      m_profiles->foreach ([e, this](profile_t* p) { m_attributes->visit(p); });
      m_logger->info("%s", "gatt create attr in the application");
      //      dev->bat_svc.handle = e.param->add_attr_tab.handles[BAS_IDX_SVC];
      //      dev->bat_level_handle = param->add_attr_tab.handles[BAS_IDX_BATT_LVL_VAL];  // so we notify of the change
      //      dev->bat_ccc_handle = param->add_attr_tab.handles[BAS_IDX_BATT_LVL_CCC];    // so we know if we can send
      //      notify ESP_LOGV(TAG, "Battery CREAT_ATTR_TAB service handle = %d", dev->bat_svc.handle);
      //
      //      dev->hid_incl_svc.start_hdl = dev->bat_svc.handle;
      //      dev->hid_incl_svc.end_hdl = dev->bat_svc.handle + BAS_IDX_NB - 1;
      //
      //      esp_ble_gatts_start_service(dev->bat_svc.handle);
      //
      //      // Add the info service next, because it's shared between all device maps
      //      create_info_db(dev);
      break;
    }
    case ESP_GATTS_READ_EVT: {
      m_logger->info("%s", "gatt read in the application");
      //      if (param->read.handle == dev->bat_level_handle) {
      //        ESP_LOGD(TAG, "Battery READ %d", dev->bat_level);
      //      }
      break;
    }
    case ESP_GATTS_WRITE_EVT: {
      m_logger->info("%s", "gatt write in the application");
      //      if (param->write.handle == dev->bat_ccc_handle) {
      //        dev->bat_ccc.value = param->write.value[0];
      //        ESP_LOGV(TAG, "Battery CCC: Notify: %s, Indicate: %s", dev->bat_ccc.notify_enable ? "On" : "Off",
      //        dev->bat_ccc.indicate_enable ? "On" : "Off");
      //      }
      break;
    }
    case ESP_GATTS_SET_ATTR_VAL_EVT: {
      m_logger->info("%s", "gatt set attr val in the application");
      //      if (param->set_attr_val.attr_handle == dev->bat_level_handle) {
      //        ESP_LOGD(TAG, "Battery SET %d, status: 0x%02x", dev->bat_level, param->set_attr_val.status);
      //      }
      break;
    }
    default:
      m_logger->info("%s", "default for the event");
      break;
  }
}

bt::application_t::application_t(id_t id) : m_id(id) {
  m_profiles = std::make_shared<repository_t<bt::profile_t>>();
  m_logger = std::make_shared<kopinions::logging::logger>(kopinions::logging::level::INFO,
                                                          std::make_shared<kopinions::logging::esp_log_sink>());
}

bt::application_t::application_t(const bt::application_t& o) {
  m_id = o.m_id;
  m_profiles = o.m_profiles;
  m_attributes = o.m_attributes;
  m_logger = o.m_logger;
}
bt::application_t::application_t(bt::application_t&& o) noexcept {
  m_id = o.m_id;
  m_profiles = o.m_profiles;
  m_attributes = o.m_attributes;
  m_logger = o.m_logger;
}

bt::application_t::~application_t() {}

void bt::application_t::enroll(const bt::profile_t& profile) { m_profiles->create(profile); }

bt::profile_t::~profile_t() {}

void bt::profile_t::enroll(bt::service_t srv) {
  m_services.insert(std::make_pair(srv.id(), srv));
}

std::vector<bt::service_t> bt::profile_t::services() const {
  std::vector<service_t> s;
  for (auto [k, v] : m_services) {
    s.push_back(v);
  }
  return s;
}

bt::profile_t::profile_t(const bt::profile_t::id_t& id) : m_id{id} {}

bt::profile_t::profile_t(const bt::profile_t& o) {
  m_id = o.m_id;
  m_services = o.m_services;
}

bt::profile_t& bt::profile_t::operator=(const bt::profile_t& o) {
  m_id = o.m_id;
  m_services = o.m_services;
  return *this;
}

void bt::profile_t::accept(visitor_t<profile_t>* t) { t->visit(this); }

const bt::profile_t::id_t& bt::profile_t::id() const { return m_id; }

bt::service_t::service_t(id_t id, std::vector<characteristic_t> characteristics)
    : m_id(id), m_characteristics{std::move(characteristics)} {}

void bt::service_t::accept(visitor_t<service_t>* t) { t->visit(this); }

bt::characteristic_t::characteristic_t(characteristic_t::id_t id, bool automated, characteristic_t::property_t property,
                                       characteristic_t::permission_t permission, uint8_t* value, size_t length,
                                       size_t max_length)
    : m_id(id),
      m_automated(automated),
      m_property(property),
      m_permission(permission),
      m_value(value),
      m_length(length),
      m_max_length(max_length) {}

bool bt::characteristic_t::automated() { return m_automated; }
