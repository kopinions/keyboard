#include "ible/specification.hpp"

#include <cstring>
#include <strstream>

#include "esp_if/esp_log_sink.hpp"
#include "ible/visitors.hpp"

void bt::application_t::notified(std::shared_ptr<gatt_if_t> gatt, event_t e) {
  switch (e.event) {
    case ESP_GATTS_REG_EVT: {
      m_logger->info("%s", "gatt reg for the application");
      this->m_gatt = gatt;
      auto register_visitor = new attribute_visitor(gatt);
      for (auto* profile : m_profiles) {
        register_visitor->visit(profile);
      }
      delete register_visitor;
      break;
    }
    case ESP_GATTS_CREAT_ATTR_TAB_EVT: {
      m_logger->info("%s", "gatt create attr in the application");
      auto param = e.param->add_attr_tab;
      auto handles_visitor =
          new update_handles_visitor(this, m_logger, gatt, param.svc_uuid.uuid.uuid16, param.num_handle, param.handles);
      for (auto* profile : m_profiles) {
        handles_visitor->visit(profile);
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
      auto& connect_param = e.param->connect;
      this->m_gatt->connected_with(connect_param.conn_id, connect_param.remote_bda, connect_param.conn_params);
      m_logger->info("%s %x", "gatt connect ", connect_param.conn_id);
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
      gatt->response(e.param->read.trans_id, ESP_GATT_OK, &rsp);
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

bt::application_t::~application_t() {}

void bt::application_t::dump(std::ostream& o) const {
  o << "app id:" << m_id << std::endl << "profiles:" << std::endl;

  for (auto* profile : m_profiles) {
    o << profile;
  }
}
std::vector<bt::profile_t*>& bt::application_t::profiles() { return m_profiles; }

bt::application_t::application_t(bt::application_t::id_t id, std::vector<bt::profile_t*> profiles)
    : m_id{id}, m_profiles{std::move(profiles)} {
  auto sink = new kopinions::logging::esp_log_sink();
  m_logger = new kopinions::logging::logger(kopinions::logging::level::INFO, sink);
}
bt::profile_t* bt::application_t::profile(bt::profile_t::id_t id) const {
  for (auto profile : m_profiles) {
    if (profile->id() == id) {
      return profile;
    }
  }
  return nullptr;
}

bt::characteristic_t* bt::application_t::select(selector_t<bt::characteristic_t*>* selector) {
  for (auto profile : m_profiles) {
    selector->visit(profile);
  }
  return selector->selected();
}

bt::profile_t::~profile_t() = default;

std::vector<bt::service_t*> bt::profile_t::services() const { return m_services; }

bt::profile_t::profile_t(const bt::profile_t::id_t& id, std::vector<bt::service_t*> services)
    : dumpable_t("  "), m_id{id}, m_services{std::move(services)} {}

void bt::profile_t::accept(visitor_t<profile_t>* t) { t->visit(this); }

const bt::profile_t::id_t& bt::profile_t::id() const { return m_id; }
void bt::profile_t::dump(std::ostream& o) const {
  o << indent() << "profile id:" << m_id << std::endl << indent() << "services:" << std::endl;
  for (auto srv : m_services) {
    o << srv;
  }
}
bt::service_t* bt::profile_t::service(bt::service_t::id_t id) const {
  for (auto service : m_services) {
    if (service->id() == id) {
      return service;
    }
  }
  return nullptr;
}

bt::service_t::service_t(id_t id, std::vector<characteristic_t*> characteristics, service_t* included)
    : dumpable_t("    "), m_id(id), m_characteristics{std::move(characteristics)}, m_included{included} {}

void bt::service_t::accept(visitor_t<service_t>* t) { t->visit(this); }

void bt::service_t::dump(std::ostream& o) const {
  o << indent() << "id:" << m_id << std::endl;
  o<< indent() <<  "start:" <<  m_handle << std::endl;
  o<< indent() <<  "end:" <<  m_end << std::endl;
  if (m_included != nullptr) {
    o << indent() << "included: " << std::endl;
    o << indent() << m_included << std::endl;
  }
  o << indent() << "characteristics:" << std::endl;
  for (const auto& c : m_characteristics) {
    o << c;
  }
}

std::vector<bt::characteristic_t*> bt::service_t::characteristics() { return m_characteristics; }

bt::service_t::id_t& bt::service_t::id() { return m_id; }

void bt::service_t::handled_by(uint16_t handle, uint16_t end) {
  m_handle = handle;
  m_end = end;
}

void bt::characteristic_t::dump(std::ostream& o) const {
  for (auto attr : m_attributes) {
    o << attr;
  }
}

bt::characteristic_t::characteristic_t(bt::characteristic_t::id_t id, std::vector<bt::attribute_t*> args)
    : dumpable_t("      "), m_id{id}, m_attributes{std::move(args)} {}

void bt::characteristic_t::accept(visitor_t<bt::characteristic_t>* t) { t->visit(this); }
bt::characteristic_t::id_t bt::characteristic_t::id() const { return m_id; }

bt::attribute_t::attribute_t(uint16_t uuid, bt::characteristic_t::permission_t perm,
                             bt::characteristic_t::property_t prop)
    : dumpable_t("        "), m_uuid{uuid}, m_permission{perm}, m_length{1}, m_max_length{1}, m_automated{true} {
  m_value = new uint8_t;
  *m_value = static_cast<uint8_t>(prop);
}

bt::attribute_t::attribute_t(uint16_t uuid, bt::characteristic_t::permission_t perm, uint8_t* value, uint16_t length,
                             uint16_t maxlength, bool automated)
    : dumpable_t("        "),
      m_uuid{uuid},
      m_permission{perm},
      m_value{value},
      m_length{length},
      m_max_length{maxlength},
      m_automated{automated} {}

void bt::attribute_t::dump(std::ostream& o) const {
  o << indent() << "id: " << m_uuid << std::endl
    << indent() << "permission: " << m_permission << std::endl
    << indent() << "length: " << m_length << std::endl
    << indent() << "max_length: " << m_max_length << std::endl
    << indent() << "automated: " << m_automated << std::endl
    << indent() << "value: " << std::hex << (m_value != nullptr ? (*m_value) : 0) << std::endl;
}

void bt::attribute_t::accept(visitor_t<attribute_t>* t) { t->visit(this); }

void bt::attribute_t::handled_by(uint16_t handle) { m_handle = handle; }
uint16_t bt::attribute_t::id() { return m_uuid; }
