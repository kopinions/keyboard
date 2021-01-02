#pragma once
#include <type_traits>
#include <variant>

#include "esp_event.h"
#include "specification.hpp"

namespace hid {

enum event_type { ANY, STARTED, CONNECTED, PROTOCOL_MODE, CONTROL, OUTPUT, FEATURE, DISCONNECTED, STOPPED };

struct connected_t {};

struct started_t {};

struct disconnected_t {};

struct protocol_t {};

struct controlled_t {};

struct outputted_t {};

struct featured_t {};

struct stopped_t {};

using event_payload_t =
    std::variant<started_t, connected_t, protocol_t, controlled_t, outputted_t, featured_t, disconnected_t, stopped_t>;

class event_t {
 public:
  using type_t = event_type;
  using payload_t = event_payload_t;
};

struct config_t {
  uint16_t vendor_id;
  uint16_t product_id;
  uint16_t version;
  const char *device_name;
  const char *manufacturer_name;
  const char *serial_number;
};

class device_t {
 public:
  virtual bool connected() = 0;
  virtual esp_err_t subscribe(event_t event, esp_event_handler_t callback) = 0;
  virtual esp_err_t unsubscribe(event_t event, esp_event_handler_t callback) = 0;
  virtual esp_err_t report(hid::report_t r, uint8_t *data, std::size_t length) = 0;
};

class ble_hid_t : public hid::device_t {
 public:
  bool connected() override { return false; }
  esp_err_t subscribe(event_t event, esp_event_handler_t callback) override { return 0; }
  esp_err_t unsubscribe(event_t event, esp_event_handler_t callback) override { return 0; }
  esp_err_t report(hid::report_t r, uint8_t *data, std::size_t length) override { return 0; }

 private:
  ble_hid_t *dev;
  xSemaphoreHandle sem;
  esp_event_loop_handle_t event_loop_handle;
  hid::config_t config;
  uint16_t appearance;

  bool m_connected;
  uint16_t conn_id;
  esp_bd_addr_t remote_bda;

  bt::ccc_value_t bat_ccc;
  uint8_t bat_level;  // 0 - 100 - battery percentage
  uint8_t control;    // 0x00 suspend, 0x01 suspend off
  uint8_t protocol;   // 0x00 boot, 0x01 report

  bt::service_t battery;
  bt::service_t information;
  esp_gatts_incl_svc_desc_t hid_incl_svc;

  uint16_t bat_level_handle;
  uint16_t bat_ccc_handle;

  uint8_t pnp[7];

  uint8_t devices_len;
};

}  // namespace hid
