#pragma once

namespace hid {
/// Maximal number of Report Char. that can be added in the DB for one HIDS - Up to 11
#define HIDD_LE_NB_REPORT_INST_MAX (5)

/// Maximal length of Report Char. Value
#define HIDD_LE_REPORT_MAX_LEN (255)
/// Maximal length of Report Map Char. Value
constexpr uint16_t HIDD_LE_REPORT_MAP_MAX_LEN = 512u;

/// Length of Boot Report Char. Value Maximal Length
constexpr uint16_t HIDD_LE_BOOT_REPORT_MAX_LEN = 8u;
/// HIDD Features structure
struct feature_t {
  /// Service Features
  uint8_t svc_features;
  /// Number of Report Char. instances to add in the database
  uint8_t report_nb;
  /// Report Char. Configuration
  uint8_t report_char_cfg[HIDD_LE_NB_REPORT_INST_MAX];
};

enum usage_t {
  GENERIC = 0,
  KEYBOARD = 1,
  MOUSE = 2,
  JOYSTICK = 4,
  GAMEPAD = 8,
  TABLET = 16,
  CCONTROL = 32,
  VENDOR = 64
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

typedef struct {
  usage_t usage;       /*!< Dominant HID usage. (keyboard > mouse > joystick > gamepad > generic) */
  uint16_t appearance; /*!< Calculated HID Appearance based on the dominant usage */
  uint8_t reports_len; /*!< Number of reports discovered in the report map */
  //  report_item_t *reports; /*!< Reports discovered in the report map */
} report_map_t;

struct report_t {
  uint16_t handle;  // Handle of report characteristic
  // Client Characteristic Configuration Descriptor
  uint16_t cccdHandle;  // Handle of CCCD for report characteristic
  uint8_t id;           // Report ID
  uint8_t type;         // Report type
  usage_t usage;        // usage
  report_mode mode;     // Protocol mode (report or boot)
} report;

typedef struct {
  //  esp_hid_raw_report_map_t reports_map;
  uint8_t reports_len;
  //  hidd_le_report_item_t *reports;
  //  hidd_le_service_t hid_svc;
  uint16_t hid_control_handle;
  uint16_t hid_protocol_handle;
} hidd_dev_map_t;

struct application {
  uint8_t id;
  /// Notified handle
  uint16_t ntf_handle;
  /// Attribute handle Table
  //  uint16_t att_tbl[HIDD_LE_IDX_NB];
  /// Supported Features
  //  hid::feature_t features[HIDD_LE_NB_HIDS_INST_MAX];
  /// Current Protocol Mode
  //  uint8_t proto_mode[HIDD_LE_NB_HIDS_INST_MAX];
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
}  // namespace hid
