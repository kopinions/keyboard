#include "ible/specification.hpp"

#include <esp_gap_ble_api.h>

#include "esp_if/esp_log_sink.hpp"

void bt::application_t::notified(std::shared_ptr<gatt_if_t> gatt, event_t e) {
  switch (e.event) {
    case ESP_GATTS_REG_EVT: {
      m_attributes = std::make_shared<attribute_visitor>(gatt);
      m_profiles->foreach ([e, this](profile_t* p) { m_attributes->visit(p); });
      break;
    }
    case ESP_GATTS_CREAT_ATTR_TAB_EVT: {
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
void bt::application_t::enroll(const bt::profile_t& profile) { m_profiles->create(profile.id(), profile.m_handler); }

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

bt::profile_t::~profile_t() {}
std::shared_ptr<bt::application_builder_t> bt::application_builder_t::name(const std::string& name) {
  return std::make_shared<bt::application_builder_t>(name);
}
std::shared_ptr<bt::application_builder_t> bt::application_builder_t::profile(
    std::function<void(profile_builder_t*)> consumer) {
  auto b = new profile_builder_t();
  consumer(b);
  m_profiles.push_back(b->build());
  delete b;
  return shared_from(this);
}
bt::application_t bt::application_builder_t::build() { return application_t{m_id}; }
std::shared_ptr<bt::application_builder_t> bt::application_builder_t::id(bt::application_t::id_t id) {
  m_id = id;
  return shared_from(this);
}
bt::application_builder_t::application_builder_t(std::string app_name) : m_app_name(std::move(app_name)) {}
bt::profile_t bt::profile_builder_t::build() {
  profile_t profile =
      profile_t(1, [](profile_t& p, esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t*) {});
  for (auto srv : m_services) {
    profile.enroll(new service_t{srv});
  }

  return profile;
}
std::shared_ptr<bt::profile_builder_t> bt::profile_builder_t::service(
    std::function<void(bt::service_builder_t*)> consumer) {
  auto b = new service_builder_t();
  consumer(b);
  m_services.push_back(b->build());
  delete b;
  return shared_from(this);
}
bt::service_t bt::service_builder_t::build() { return service_t(); }
