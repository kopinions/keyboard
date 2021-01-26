#pragma once
#include <esp_gatt_defs.h>
#include <esp_gatts_api.h>

#include <memory>

#include "ible/builder.hpp"
#include "ible/repository.hpp"
#include "ible/specification.hpp"
#include "ible/visitor.hpp"
#include "vif.hpp"
namespace bt {

class gatt_if_t {
 public:
  virtual esp_err_t create_attr_tab(const esp_gatts_attr_db_t* gatts_attr_db, uint8_t max_nb_attr,
                                    uint8_t srvc_inst_id) = 0;
};

class esp_gatt : public gatt_if_t {
 public:
  explicit esp_gatt(esp_gatt_if_t gatt_if) : m_gatt_if(gatt_if) {}

  esp_err_t create_attr_tab(const esp_gatts_attr_db_t* gatts_attr_db, uint8_t max_nb_attr,
                            uint8_t srvc_inst_id) override {
    return esp_ble_gatts_create_attr_tab(gatts_attr_db, m_gatt_if, max_nb_attr, srvc_inst_id);
  }

 private:
  esp_gatt_if_t m_gatt_if;
};

using uuid_t = std::uint16_t;

class attribute_visitor;

class attribute_t {
 public:
  enum class type : uint16_t {
    INCLUDE_DECLARATION = 0x2802,
    CHARACTER_DECLARATION = 0x2803,
  };
};

class attribute_visitor;

class characteristic_t : public visitable_t<visitor_t<characteristic_t>> {
  friend class attribute_visitor;
  uint8_t auto_rsp;
  uint16_t uuid_length;
  uint8_t* uuid_p;
  uint16_t perm;
  uint16_t max_length;
  uint16_t length;
  uint8_t* value;

 public:
  void accept(visitor_t<characteristic_t>* t) override { t->visit(this); }
};

class service_t : public visitable_t<visitor_t<service_t>> {
 public:
  using id_t = std::uint16_t;
  void registered(esp_gatt_if_t i) { gatt_if = i; }

  std::vector<characteristic_t> characteristics() { return {}; };

  [[nodiscard]] uuid_t id() const { return m_id; }

  bool matched(esp_gatt_if_t i) { return i == ESP_GATT_IF_NONE || i == gatt_if; }

  void notified(esp_gatts_cb_event_t param, esp_gatt_if_t i, esp_ble_gatts_cb_param_t* ptr) {}

  void accept(visitor_t<service_t>* t) override { t->visit(this); };

 private:
  esp_gatt_if_t gatt_if;
  uuid_t m_id;
};

typedef union {
  struct {
    uint16_t notify_enable : 1;
    uint16_t indicate_enable : 1;
    uint16_t reserved : 14;
  };
  uint16_t value;
} ccc_value_t;

class event_t {
 public:
  esp_gatts_cb_event_t event;
  esp_ble_gatts_cb_param_t* param;
};

class profile_t;

class application_t {
 public:
  using id_t = uint16_t;

  virtual id_t id() const { return m_id; }
  virtual id_t id() { return m_id; }
  explicit application_t(id_t id);

  application_t(const application_t&);
  application_t(application_t&&) noexcept;
  virtual ~application_t();

  virtual std::vector<profile_t> profiles() { return {}; }

  virtual void enroll(const profile_t& profile);

  void notified(std::shared_ptr<bt::gatt_if_t>, event_t e);

 private:
  id_t m_id;
  std::shared_ptr<attribute_visitor> m_attributes;
  std::shared_ptr<repository_t<profile_t>> m_profiles;
  std::shared_ptr<kopinions::logging::logger> m_logger;
};

class profile_builder_t;

class application_builder_t : public ibuilder<application_t> {
 public:
  explicit application_builder_t(std::string app_name);

  static std::shared_ptr<application_builder_t> name(const std::string& name);

  std::shared_ptr<application_builder_t> id(bt::application_t::id_t id);

  std::shared_ptr<application_builder_t> profile(std::function<void(profile_builder_t*)> consumer);

  application_t build() override;

 private:
  std::string m_app_name;
  std::vector<profile_t> m_profiles;
  bt::application_t::id_t m_id;
};

class profile_t : public visitable_t<visitor_t<profile_t>> {
 public:
  using id_t = std::uint16_t;

  explicit profile_t(
      const id_t& id,
      std::function<void(profile_t& p, esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t*)>
          p)
      : m_id{id}, m_handler{p} {};

  void notified(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param);

  std::vector<service_t> services() const { return {}; }

  virtual void enroll(service_t* const srv) { m_services[srv->id()] = srv; }

  void accept(visitor_t<profile_t>* t) override { t->visit(this); };

  profile_t(const profile_t& o) {
    gatts_if = o.gatts_if;
    m_id = o.m_id;
    conn_id = o.conn_id;
    m_handler = o.m_handler;
  };

  profile_t& operator=(const profile_t&) { return *this; };

  virtual ~profile_t();

  esp_gatt_srvc_id_t service_id;
  uint16_t gatts_if;
  uint16_t conn_id;
  uint16_t service_handle;
  esp_bt_uuid_t char_uuid;
  uint16_t char_handle;
  uint16_t descr_handle;
  esp_bt_uuid_t descr_uuid;

  [[nodiscard]] const id_t& id() const { return m_id; }

 private:
  id_t m_id;
  std::map<id_t, service_t*> m_services;

 public:
  std::function<void(profile_t& p, esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t*)>
      m_handler;
};

class profile_builder_t;

class service_builder_t : public ibuilder<service_t> {
 public:
  friend profile_builder_t;

 private:
  service_t build() override;

 private:
};

class profile_builder_t : public ibuilder<profile_t> {
 public:
  friend application_builder_t;
  std::shared_ptr<profile_builder_t> service(std::function<void(service_builder_t*)> consumer);

 private:
  profile_t build() override;
  std::vector<service_t> m_services;
};

enum appearance_t : uint16_t { KEYBOARD = 0x3C1 };

class topic {
 public:
  virtual void subscribed() = 0;
};

class subscriber {
 public:
  virtual void subscribe(std::shared_ptr<topic>) = 0;
};

static const uint16_t s_primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t s_include_service_uuid = ESP_GATT_UUID_INCLUDE_SERVICE;
static const uint16_t s_character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
static const uint16_t s_character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;

class attribute_visitor : public visitor_t<profile_t, service_t, characteristic_t> {
 public:
  attribute_visitor(std::shared_ptr<gatt_if_t> gatt_if) { m_gatt_if = gatt_if; }
  void visit(profile_t* t) override {
    for (auto srv : t->services()) {
      auto* service_visitor = new attribute_visitor(m_gatt_if);
      srv.accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(srv)>>*>(service_visitor));
      delete service_visitor;
    }
  }

  void visit(service_t* t) override {
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

  void visit(characteristic_t* t) override {
    m_attributes.push_back(esp_gatts_attr_db_t{.attr_control = {.auto_rsp = ESP_GATT_AUTO_RSP},
                                               .att_desc = {.uuid_length = 2,
                                                            .uuid_p = (uint8_t*)&s_character_declaration_uuid,
                                                            .perm = ESP_UUID_LEN_16,
                                                            .max_length = 1,
                                                            .length = 1,
                                                            .value = nullptr}});
  }

  ~attribute_visitor() override = default;

 public:
 private:
  std::vector<esp_gatts_attr_db_t> m_attributes;
  std::shared_ptr<gatt_if_t> m_gatt_if;
};

}  // namespace bt