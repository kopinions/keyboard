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

void bt::application_t::enroll(const bt::profile_t& profile) { m_profiles->create(profile); }

void bt::profile_t::notified(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
  m_handler(*this, event, gatts_if, param);

  switch (event) {
    case ESP_GATTS_REG_EVT: {
      for (auto [id, srv] : m_services) {
        auto* vis = new attribute_visitor{std::make_shared<esp_gatt>(gatts_if)};
        srv.accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(srv)>>*>(vis));
        delete vis;
      }
      break;
    }
    case ESP_GATTS_CREAT_ATTR_TAB_EVT: {
      for (auto& [id, srv] : m_services) {
        srv.notified(event, gatts_if, param);
      }
      break;
    }
    default:
      break;
  }
}

bt::profile_t::~profile_t() {}

void bt::profile_t::enroll(bt::service_t srv) {
  m_services.insert(std::make_pair(srv.id(), srv));
  std::cout << m_services.size() << "insert size" << std::endl;
}

std::vector<bt::service_t> bt::profile_t::services() const {
  std::vector<service_t> s;
  std::cout << m_services.size() << "get size" << std::endl;
  for (auto [k, v] : m_services) {
    s.push_back(v);
  }
  return s;
}

bt::profile_t::profile_t(
    const bt::profile_t::id_t& id,
    std::function<void(profile_t&, esp_gatts_cb_event_t, esp_gatt_if_t, esp_ble_gatts_cb_param_t*)> p)
    : m_id{id}, m_handler{p} {}

bt::profile_t::profile_t(const bt::profile_t& o) {
  gatts_if = o.gatts_if;
  m_id = o.m_id;
  conn_id = o.conn_id;
  m_handler = o.m_handler;
  m_services = o.m_services;
  std::cout << m_services.size() << "copy size" << std::endl;
}

bt::profile_t& bt::profile_t::operator=(const bt::profile_t& o) {
  gatts_if = o.gatts_if;
  m_id = o.m_id;
  conn_id = o.conn_id;
  m_handler = o.m_handler;
  m_services = o.m_services;
  std::cout << m_services.size() << "operator size" << std::endl;
  return *this;
}

void bt::profile_t::accept(visitor_t<profile_t>* t) { t->visit(this); }

const bt::profile_t::id_t& bt::profile_t::id() const { return m_id; }

bt::application_builder_t* bt::application_builder_t::name(const std::string& name) {
  return new bt::application_builder_t(name);
}
bt::application_builder_t* bt::application_builder_t::profile(std::function<void(profile_builder_t*)> consumer) {
  auto b = new profile_builder_t();
  consumer(b);
  m_profiles.push_back(b->build());
  delete b;
  return this;
}
bt::application_t bt::application_builder_t::build() {
  application_t application = application_t{m_id};
  for (auto p : m_profiles) {
    application.enroll(p);
  }
  return application;
}

bt::application_builder_t* bt::application_builder_t::id(bt::application_t::id_t id) {
  m_id = id;
  return this;
}

bt::application_builder_t::application_builder_t(std::string app_name) : m_app_name(std::move(app_name)) {}

bt::profile_t bt::profile_builder_t::build() {
  profile_t profile =
      profile_t(1, [](profile_t& p, esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t*) {});
  std::cout << m_services.size() << "build size" << std::endl;
  for (const auto& srv : m_services) {
    profile.enroll(srv);
  }

  return profile;
}

bt::profile_builder_t* bt::profile_builder_t::service(std::function<void(bt::service_builder_t*)> consumer) {
  auto b = new service_builder_t();
  consumer(b);
  m_services.push_back(b->build());
  delete b;
  return this;
}

bt::service_t bt::service_builder_t::build() { return service_t(m_id); }

bt::service_builder_t* bt::service_builder_t::id(bt::service_t::id_t id) {
  m_id = id;
  return this;
}

bt::service_t::service_t(bt::service_t::id_t id) : m_id(id) {}

void bt::service_t::accept(visitor_t<service_t>* t) { t->visit(this); }

void bt::attribute_visitor::visit(bt::profile_t* t) {
  std::cout << "visitor from profile" << std::endl;
  for (auto srv : t->services()) {
    std::cout << t->services().size() << "prepare visitor size" << std::endl;
    auto* service_visitor = new attribute_visitor(m_gatt_if);
    std::cout << t->services().size() << " visitor size" << std::endl;
    auto* v = dynamic_cast<visitor_t<service_t>*>(service_visitor);
    std::cout << t->services().size() << "after cast size" << std::endl;
    srv.accept(v);
    delete service_visitor;
  }
}

void bt::attribute_visitor::visit(bt::service_t* t) {
  std::cout << "visitor from service" << std::endl;
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
  std::cout << "create attribute table" << std::endl;
  esp_err_t err = m_gatt_if->create_attr_tab(m_attributes.data(), 2, 0);
  if (err) {
    std::cout << "error while attribute sevice visitor" << std::endl;
  }
}

void bt::attribute_visitor::visit(bt::characteristic_t* t) {
  m_attributes.push_back(esp_gatts_attr_db_t{.attr_control = {.auto_rsp = ESP_GATT_AUTO_RSP},
                                             .att_desc = {.uuid_length = 2,
                                                          .uuid_p = (uint8_t*)&s_character_declaration_uuid,
                                                          .perm = ESP_UUID_LEN_16,
                                                          .max_length = 1,
                                                          .length = 1,
                                                          .value = nullptr}});
}
