#include "ible/specification.hpp"

#include <cstring>
#include <strstream>

#include "esp_if/esp_log_sink.hpp"
#include "ible/visitors.hpp"

void bt::application_t::notified(std::shared_ptr<gatt_if_t> gatt, event_t e) {
  switch (e.event) {
    case ESP_GATTS_REG_EVT: {
      m_logger->info("%s", "gatt reg for the application");
      if (m_attributes == nullptr) {
        m_attributes = std::make_shared<attribute_visitor>(gatt);
        m_profiles->foreach ([e, this](profile_t* p) { m_attributes->visit(p); });
      }
      break;
    }
    case ESP_GATTS_CREAT_ATTR_TAB_EVT: {
      m_logger->info("%s", "gatt create attr in the application");
      if (e.param->add_attr_tab.svc_uuid.uuid.uuid16 == bt::service_t::id_t::BATTERY &&
          e.param->add_attr_tab.status == ESP_GATT_OK) {
        auto bat_svc_handle = e.param->add_attr_tab.handles[0];
        //        auto bat_level_handle = e.param->add_attr_tab.handles[BAS_IDX_BATT_LVL_VAL];  // so we notify of the
        //        change auto bat_ccc_handle = e.param->add_attr_tab.handles[BAS_IDX_BATT_LVL_CCC];    // so we know if
        //        we can send notify ESP_LOGV(TAG, "Battery CREAT_ATTR_TAB service handle = %d", dev->bat_svc.handle);
        //        dev->hid_incl_svc.start_hdl = dev->bat_svc.handle;
        //        dev->hid_incl_svc.end_hdl = dev->bat_svc.handle + BAS_IDX_NB - 1;
        m_logger->info("start service %d", bat_svc_handle);
        auto ret = esp_ble_gatts_start_service(bat_svc_handle);
        if (ret) {
          m_logger->error("%s: %s start service failed", __func__);
          return;
        }
      } else if (e.param->add_attr_tab.svc_uuid.uuid.uuid16 == bt::service_t::id_t::HID &&
                 e.param->add_attr_tab.status == ESP_GATT_OK) {
        auto hid_svc_handle = e.param->add_attr_tab.handles[0];
        m_logger->info("start service %d", hid_svc_handle);
        auto ret = esp_ble_gatts_start_service(hid_svc_handle);
        if (ret) {
          m_logger->error("%s: %s start hid service failed", __func__);
          return;
        }
      }

      // Add the info service next, because it's shared between all device maps
      break;
    }
    case ESP_GATTS_START_EVT: {
      m_logger->info("%s", "gatts start event");
      // use event loop

      break;
    }
    case ESP_GATTS_CONNECT_EVT: {
      m_logger->info("%s", "gatt connect");
      break;
    }

    case ESP_GATTS_READ_EVT: {
      m_logger->info("%s", "gatt read in the application");
      //      if (param->read.handle == dev->bat_level_handle) {
      //        ESP_LOGD(TAG, "Battery READ %d", dev->bat_level);
      //      }
      esp_gatt_rsp_t rsp;
      memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
      rsp.attr_value.handle = e.param->read.handle;
      rsp.attr_value.len = 4;
      rsp.attr_value.value[0] = 0xde;
      rsp.attr_value.value[1] = 0xed;
      rsp.attr_value.value[2] = 0xbe;
      rsp.attr_value.value[3] = 0xef;
      gatt->response(e.param->read.conn_id, e.param->read.trans_id, ESP_GATT_OK, &rsp);
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
      m_logger->info("%s %d", "default for the event", e.event);
      break;
  }
}

bt::application_t::application_t(id_t id) : dumpable_t(), m_id(id) {
  m_profiles = std::make_shared<repository_t<bt::profile_t>>();
  auto sink = new kopinions::logging::esp_log_sink();
  m_logger = new kopinions::logging::logger(kopinions::logging::level::INFO, sink);
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

void bt::application_t::enroll(bt::profile_t* const profile) { m_profiles->create(profile); }

void bt::application_t::dump(std::ostream& o) const {
  o << "app id:" << m_id << std::endl << "profiles:" << std::endl;
  m_profiles->foreach ([&](profile_t* p) { o << p; });
}

bt::profile_t::~profile_t() {}

void bt::profile_t::enroll(bt::service_t* srv) { m_services.insert(std::make_pair(srv->id(), srv)); }

std::vector<bt::service_t*> bt::profile_t::services() const {
  std::vector<service_t*> s;
  for (auto [k, v] : m_services) {
    s.push_back(v);
  }
  return s;
}

bt::profile_t::profile_t(const bt::profile_t::id_t& id) : dumpable_t("  "), m_id{id} {}

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
void bt::profile_t::dump(std::ostream& o) const {
  o << indent() << "profile id:" << m_id << std::endl << indent() << "services:" << std::endl;
  for (auto [id, srv] : m_services) {
    o << srv;
  }
}

bt::service_t::service_t(id_t id, std::vector<characteristic_t*> characteristics)
    : dumpable_t("    "), m_id(id), m_characteristics{std::move(characteristics)} {}

void bt::service_t::accept(visitor_t<service_t>* t) { t->visit(this); }
void bt::service_t::dump(std::ostream& o) const {
  o << indent() << "id:" << m_id << std::endl << indent() << "characteristics:" << std::endl;
  for (const auto& c : m_characteristics) {
    o << c;
  }
}

void bt::characteristic_t::dump(std::ostream& o) const {
  for (auto attr : m_attributes) {
    o << attr;
  }
}

bt::characteristic_t::characteristic_t(std::vector<bt::attribute_t*> args)
    : dumpable_t("      "), m_attributes{std::move(args)} {}

void bt::characteristic_t::accept(visitor_t<bt::characteristic_t>* t) { t->visit(this); }

bt::attribute_t::attribute_t(bt::uuid_t, bt::characteristic_t::permission_t, uint8_t*, uint16_t length,
                             uint16_t maxlength, bool automated)
    : dumpable_t("        ") {}
void bt::attribute_t::dump(std::ostream& o) const { o << indent() << "attribute" << std::endl; }

void bt::attribute_t::accept(visitor_t<attribute_t>* t) { t->visit(this); }
