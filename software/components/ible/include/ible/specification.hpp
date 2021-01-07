#pragma once
#include "ible/repository.hpp"
#include "ible/specification.hpp"
#include "ible/visitor.hpp"
#include "vif.hpp"
namespace bt {
using uuid_t = std::uint16_t;

class composite_visitor;

class attribute_t : public visitable_t<visitor_t<attribute_t>> {
 public:
  void accept(visitor_t<attribute_t>* t) override { t->visit(this); };
};

class characteristic_t {
  uint8_t auto_rsp;
  uint16_t uuid_length; /*!< UUID length */
  uint8_t* uuid_p;      /*!< UUID value */
  uint16_t perm;        /*!< Attribute permission */
  uint16_t max_length;  /*!< Maximum length of the element*/
  uint16_t length;      /*!< Current length of the element*/
  uint8_t* value;
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

class composite_visitor : public visitor_t<service_t, attribute_t, characteristic_t> {
 public:
  void visit(attribute_t* t) override {}

  void visit(service_t* t) override {}

  void visit(characteristic_t* t) override {}
};

class profile_t {
 public:
  using id_t = std::uint16_t;
  explicit profile_t(
      const id_t& id,
      std::function<void(profile_t& p, esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t*)>
          p)
      : m_id{id}, m_handler{p} {};

  void notified(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
    m_handler(*this, event, gatts_if, param);
    composite_visitor* vis = new composite_visitor;
    switch (event) {
      case ESP_GATTS_REG_EVT: {
        for (auto [id, srv] : m_services) {
          srv->accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(srv)>>*>(vis));
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
  };

  std::vector<service_t> services() const { return {}; }

  virtual void enroll(service_t* const srv) { m_services[srv->id()] = srv; }

  profile_t(const profile_t& o) {
    gatts_if = o.gatts_if;
    m_id = o.m_id;
    conn_id = o.conn_id;
    m_handler = o.m_handler;
  };

  profile_t& operator=(const profile_t&) { return *this; };

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

class application_t {
 public:
  using id_t = uint16_t;
  virtual id_t id() const { return m_id; }
  virtual id_t id() { return m_id; }

  virtual std::vector<profile_t> profiles() { return {}; }

  virtual void enroll(const profile_t& profile) { m_profiles.create(profile.id(), profile.m_handler); }

  void notified(esp_gatts_cb_event_t event, esp_ble_gatts_cb_param_t* param) {
    m_profiles.foreach ([event, param](profile_t* p) { p->notified(event, 0, param); });
  }

 private:
  id_t m_id;
  repository_t<profile_t> m_profiles;
  std::shared_ptr<kopinions::logging::logger> m_logger;
};
}  // namespace bt