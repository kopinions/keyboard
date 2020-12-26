#ifndef IBLE_HPP
#define IBLE_HPP

#include <esp_bt.h>
#include <esp_bt_defs.h>
#include <esp_bt_device.h>
#include <esp_bt_main.h>
#include <esp_gap_ble_api.h>
#include <esp_gatt_defs.h>
#include <esp_gatts_api.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/queue.h>

#include <functional>
#include <map>
#include <memory>

#include "logger.hpp"
#include "repository.hpp"
namespace bt {

class characteristic_t {};

class service_t {
 public:
  esp_gatt_if_t gatt_if;
  uint16_t handle;

  std::vector<characteristic_t> characteristics(){

  };
};

typedef union {
  struct {
    uint16_t notify_enable : 1;
    uint16_t indicate_enable : 1;
    uint16_t reserved : 14;
  };
  uint16_t value;
} ccc_value_t;

class profile {
 public:
  using identifiable = uint16_t;
  explicit profile(
      const identifiable& id,
      std::function<void(profile& p, esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t*)> p)
      : m_id{id}, m_handler{p} {};
  void notified(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
    m_handler(*this, event, gatts_if, param);
  };

  profile(const profile& o) {
    gatts_if = o.gatts_if;
    m_id = o.m_id;
    conn_id = o.conn_id;
    m_handler = o.m_handler;
  };

  profile& operator=(const profile&) = delete;

  esp_gatt_srvc_id_t service_id;
  uint16_t gatts_if;
  uint16_t conn_id;
  uint16_t service_handle;
  esp_bt_uuid_t char_uuid;
  uint16_t char_handle;
  uint16_t descr_handle;
  esp_bt_uuid_t descr_uuid;

  [[nodiscard]] const identifiable& id() const { return m_id; }

 private:
  identifiable m_id;
  std::function<void(profile& p, esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t*)>
      m_handler;
};

class profile_repository : public repository<profile> {
 public:
  void create(const id_t& id, const profile& p) override;
  [[nodiscard]] std::shared_ptr<profile> find(const id_t& id) const override;

  [[nodiscard]] std::vector<std::shared_ptr<profile>> all() const;
  ~profile_repository() override = default;

 private:
  std::map<id_t, std::shared_ptr<profile>> m_profiles;
};

class ble {
 public:
  explicit ble(std::shared_ptr<kopinions::logging::logger> lg);
  void enable();
  void disable();
  void reset();

  static void gap_event_handler(esp_gap_ble_cb_event_t, esp_ble_gap_cb_param_t*);
  static void gatts_event_handler(esp_gatts_cb_event_t, esp_gatt_if_t, esp_ble_gatts_cb_param_t*);

  void register_profile(profile::identifiable id, const profile& p);
  static std::shared_ptr<profile_repository> profiles();

 private:
  static std::shared_ptr<kopinions::logging::logger> m_logger;
  static bool secure;
  static std::shared_ptr<profile_repository> m_profiles;
};
}  // namespace bt

#endif /* IBLE_HPP */
