#pragma once
#include "ible/specification.hpp"
#include "vif.hpp"
namespace bt {
using uuid_t = std::uint16_t;
class characteristic_t {};

class service_t {
 public:
  void registered(esp_gatt_if_t i) { gatt_if = i; }

  std::vector<characteristic_t> characteristics() { return {}; };

  [[nodiscard]] uuid_t id() const { return m_id; }

  bool matched(esp_gatt_if_t i) { return i == ESP_GATT_IF_NONE || i == gatt_if; }

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
  };

  std::vector<service_t> services() const { return {}; }

  profile_t(const profile_t& o) {
    gatts_if = o.gatts_if;
    m_id = o.m_id;
    conn_id = o.conn_id;
    m_handler = o.m_handler;
  };

  profile_t& operator=(const profile_t&) = delete;

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
  std::function<void(profile_t& p, esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t*)>
      m_handler;
};

class application_t {
 public:
  using id_t = uint16_t;
  virtual id_t id() const { return m_id; }
  virtual id_t id() { return m_id; }

  virtual std::vector<profile_t> profiles() { return {}; }

  void notified(esp_gatts_cb_event_t event, esp_ble_gatts_cb_param_t*) {}

 private:
  id_t m_id;
  std::shared_ptr<kopinions::logging::logger> m_logger;
};
}  // namespace bt