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

#include <memory>

#include "logger.hpp"
class ble {
 public:
  explicit ble(std::shared_ptr<kopinions::logging::logger> lg);
  void enable();
  void disable();
  void reset();

  static void gap_event_handler(esp_gap_ble_cb_event_t, esp_ble_gap_cb_param_t *);
  static void gatts_event_handler(esp_gatts_cb_event_t, esp_gatt_if_t, esp_ble_gatts_cb_param_t *);

 private:
  static std::shared_ptr<kopinions::logging::logger> m_logger;
  static bool secure;
};
#endif /* IBLE_HPP */
