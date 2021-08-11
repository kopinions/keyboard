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

enum key_t : uint8_t {
  NONE,
  // modifier
  FN,
  LCTRL = 0xE0,
  LSHIFT = 0xE1,
  LALT = 0xE2,
  LGUI = 0xE3,
  RCTRL = 0xE4,
  RSHIFT = 0xE5,
  RALT = 0xE6,
  RGUI = 0xE7,
  // key
  A = 0x4,
  B = 0x5,
  C = 0x6,
  D = 0x7,
  E = 0x8,
  F = 0x9,
  G = 0x0A,
  H = 0x0B,
  I = 0x0C,
  J = 0x0D,
  K = 0x0E,
  L = 0x0F,
  M = 0x10,
  N = 0x11,
  O = 0x12,
  P = 0x13,
  Q = 0x14,
  R = 0x15,
  S = 0x16,
  T = 0x17,
  U = 0x18,
  V = 0x19,
  W = 0x1A,
  X = 0x1B,
  Y = 0x1C,
  Z = 0x1D,
  K1 = 0x1E,
  K2 = 0x1F,
  K3 = 0x20,
  K4 = 0x21,
  K5 = 0x22,
  K6 = 0x23,
  K7 = 0x24,
  K8 = 0x25,
  K9 = 0x26,
  K0 = 0x27,
  ENTER = 0x28,
  ESC = 0x29,
  BACKSPACE = 0x2A,
  TAB = 0x2B,
  SPACE = 0x2C,
  MINUS = 0x2D,
  EQUAL = 0x2E,
  LBRACE = 0x2F,
  RBRACE = 0x30,
  BACKSLASH = 0x31,
  NON_US_NUM = 0x32,
  SEMICOLON = 0x33,
  QUOTE = 0x34,
  TILDE = 0x35,
  COMMA = 0x36,
  PERIOD = 0x37,
  SLASH = 0x38,
  CAPS_LOCK = 0x39,
  // functional key
  F1 = 0x3A,
  F2 = 0x3B,
  F3 = 0x3C,
  F4 = 0x3D,
  F5 = 0x3E,
  F6 = 0x3F,
  F7 = 0x40,
  F8 = 0x41,
  F9 = 0x42,
  F10 = 0x43,
  F11 = 0x44,
  F12 = 0x45,
  F13 = 0x68,
  F14 = 0x69,
  F15 = 0x6A,
  F16 = 0x6B,
  F17 = 0x6C,
  F18 = 0x6D,
  F19 = 0x6E,
  F20 = 0x6F,
  F21 = 0x70,
  F22 = 0x71,
  F23 = 0x72,
  F24 = 0x73,
  PRINTSCREEN = 0x46,
  SCROLL_LOCK = 0x47,
  PAUSE_BREAK = 0x48,
  INSERT = 0x49,
  HOME = 0x4A,
  PAGE_UP = 0x4B,
  DELETE = 0x4C,
  END = 0x4D,
  PAGE_DOWN = 0x4E,
  RIGHT = 0x4F,
  LEFT = 0x50,
  DOWN = 0x51,
  UP = 0x52,
  NUM_LOCK = 0x53,
  MENU = 0x65,
  // num pads
  PAD_SLASH = 0x54,
  PAD_ASTERIX = 0x55,
  PAD_MINUS = 0x56,
  PAD_PLUS = 0x57,
  PAD_ENTER = 0x58,
  PAD_1 = 0x59,
  PAD_2 = 0x5A,
  PAD_3 = 0x5B,
  PAD_4 = 0x5C,
  PAD_5 = 0x5D,
  PAD_6 = 0x5E,
  PAD_7 = 0x5F,
  PAD_8 = 0x60,
  PAD_9 = 0x61,
  PAD_0 = 0x62,
  PAD_PERIOD = 0x63,
  PAD_NON_US_NUM = 0x64,
  PAD_EQUAL = 0x67,
  // media key
  PLAY,
  PAUSE,
  RECORD,
  FAST_FORWARD,
  REWIND,
  NEXT_TRACK,
  PREV_TRACK,
  STOP,
  EJECT,
  RANDOM_PLAY,
  PLAY_PAUSE,
  PLAY_SKIP,
  MUTE = 0x7F,
  VOLUME_INC = 0x80,
  VOLUME_DEC = 0x81,
  // system key
  POWER_DOWN = 0x66,
  SLEEP,
  WAKE_UP,
};

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

// typedef struct {
//   uint8_t map_index;              /*!< HID report map index */
//   uint8_t report_id;              /*!< HID report id */
//   uint8_t report_type;            /*!< HID report type */
//   uint8_t protocol_mode;          /*!< HID protocol mode */
//   esp_hid_usage_t usage;          /*!< HID usage type */
//   uint16_t value_len;             /*!< HID report length in bytes */
// } esp_hid_report_item_t;

using report_t = struct report_t {
  enum class id_t : uint8_t {
    MOUSE_IN = 1,    // Mouse input report ID
    KEY_IN = 2,      // Keyboard input report ID
    CC_IN = 3,       // Consumer Control input report ID
    VENDOR_OUT = 4,  // Vendor output report ID
    LED_OUT = 0,     // LED output report ID
    FEATURE = 0,
  };
  enum class type_t : uint8_t {
    INPUT = 1,
    OUTPUT = 2,
    FEATURE = 3,
  };

  uint16_t handle;  // Handle of report characteristic
  // Client Characteristic Configuration Descriptor
  uint16_t cccdHandle;  // Handle of CCCD for report characteristic
  id_t id;              // Report ID
  type_t type;          // Report type
  usage_t usage;        // usage
  report_mode mode;     // Protocol mode (report or boot)
};

using report_map_t = struct {
  usage_t usage;       /*!< Dominant HID usage. (keyboard > mouse > joystick > gamepad > generic) */
  uint16_t appearance; /*!< Calculated HID Appearance based on the dominant usage */
  uint8_t reports_len; /*!< Number of reports discovered in the report map */
  report_t *reports;   /*!< Reports discovered in the report map */
};

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
