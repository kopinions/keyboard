#pragma once

namespace hid {
/// HIDD Features structure
struct feature {
  /// Service Features
  uint8_t svc_features;
  /// Number of Report Char. instances to add in the database
  uint8_t report_nb;
  /// Report Char. Configuration
  uint8_t report_char_cfg[HIDD_LE_NB_REPORT_INST_MAX];
};

struct connection {
  uint16_t id;
  bool in_use;
  bool congest;
  bool connected;
  esp_bd_addr_t remote_bda;
  uint32_t trans_id;
  uint8_t service_id;
};

enum report_mode {
  BOOT,
  REPORT,
};

struct report {
  uint16_t handle;  // Handle of report characteristic
  // Client Characteristic Configuration Descriptor
  uint16_t cccdHandle;  // Handle of CCCD for report characteristic
  uint8_t id;           // Report ID
  uint8_t type;         // Report type
  report_mode mode;     // Protocol mode (report or boot)
} report;

struct application {
  uint8_t id;
  /// Notified handle
  uint16_t ntf_handle;
  /// Attribute handle Table
  uint16_t att_tbl[HIDD_LE_IDX_NB];
  /// Supported Features
  hid::feature features[HIDD_LE_NB_HIDS_INST_MAX];
  /// Current Protocol Mode
  uint8_t proto_mode[HIDD_LE_NB_HIDS_INST_MAX];
  /// Number of HIDS added in the database
  uint8_t hids_nb;
  uint8_t pending_evt;
  uint16_t pending_hal;
};

using binary_coded_decimal = uint16_t;

struct information {
  /// bcdHID
  binary_coded_decimal hid;
  uint8_t country_code;
  uint8_t flags;
};

typedef enum {
  ESP_HIDD_EVENT_REG_FINISH = 0,
  ESP_BAT_EVENT_REG,
  ESP_HIDD_EVENT_DEINIT_FINISH,
  ESP_HIDD_EVENT_BLE_CONNECT,
  ESP_HIDD_EVENT_BLE_DISCONNECT,
  ESP_HIDD_EVENT_BLE_VENDOR_REPORT_WRITE_EVT,
} esp_hidd_cb_event_t;

class processor {
 public:
  std::vector<connection> connections;
  esp_gatt_if_t gatt_if;
  bool enabled;
  bool is_take;
  bool is_primary;
  hid::application app;
  uint8_t inst_id;
};

}  // namespace hid
