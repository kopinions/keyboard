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

#include "ible/specification.hpp"
#include "logger.hpp"
#include "repository.hpp"
namespace bt {
class ble {
 public:
  ble(std::string name, bt::appearance_t appearance, std::shared_ptr<kopinions::logging::logger> lg);
  void enable();
  void disable();
  void reset();

 public:
  ble(const ble&) = delete;
  ble(ble&&) = delete;
  ble& operator=(const ble&) = delete;
  ble& operator=(ble&&) = delete;

  void enroll(const bt::application_t& app);

 private:
  static void gap_event_handler(esp_gap_ble_cb_event_t, esp_ble_gap_cb_param_t*);
  static void gatts_event_handler(esp_gatts_cb_event_t, esp_gatt_if_t, esp_ble_gatts_cb_param_t*);
  static std::shared_ptr<repository_t<application_t>> apps();

 private:
  static std::shared_ptr<kopinions::logging::logger> m_logger;
  static std::string name;
  static bool secure;
  static appearance_t appearance;
};
}  // namespace bt

#endif /* IBLE_HPP */
