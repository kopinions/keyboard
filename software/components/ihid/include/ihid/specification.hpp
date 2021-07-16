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

using hid_key_t = uint8_t;
// HID Keyboard/Keypad Usage IDs (subset of the codes available in the USB HID Usage Tables spec)
constexpr hid_key_t HID_KEY_RESERVED = 0u;       // No event inidicated
constexpr hid_key_t HID_KEY_A = 4u;              // Keyboard a and A
constexpr hid_key_t HID_KEY_B = 5u;              // Keyboard b and B
constexpr hid_key_t HID_KEY_C = 6u;              // Keyboard c and C
constexpr hid_key_t HID_KEY_D = 7u;              // Keyboard d and D
constexpr hid_key_t HID_KEY_E = 8u;              // Keyboard e and E
constexpr hid_key_t HID_KEY_F = 9u;              // Keyboard f and F
constexpr hid_key_t HID_KEY_G = 10u;             // Keyboard g and G
constexpr hid_key_t HID_KEY_H = 11u;             // Keyboard h and H
constexpr hid_key_t HID_KEY_I = 12u;             // Keyboard i and I
constexpr hid_key_t HID_KEY_J = 13u;             // Keyboard j and J
constexpr hid_key_t HID_KEY_K = 14u;             // Keyboard k and K
constexpr hid_key_t HID_KEY_L = 15u;             // Keyboard l and L
constexpr hid_key_t HID_KEY_M = 16u;             // Keyboard m and M
constexpr hid_key_t HID_KEY_N = 17u;             // Keyboard n and N
constexpr hid_key_t HID_KEY_O = 18u;             // Keyboard o and O
constexpr hid_key_t HID_KEY_P = 19u;             // Keyboard p and p
constexpr hid_key_t HID_KEY_Q = 20u;             // Keyboard q and Q
constexpr hid_key_t HID_KEY_R = 21u;             // Keyboard r and R
constexpr hid_key_t HID_KEY_S = 22u;             // Keyboard s and S
constexpr hid_key_t HID_KEY_T = 23u;             // Keyboard t and T
constexpr hid_key_t HID_KEY_U = 24u;             // Keyboard u and U
constexpr hid_key_t HID_KEY_V = 25u;             // Keyboard v and V
constexpr hid_key_t HID_KEY_W = 26u;             // Keyboard w and W
constexpr hid_key_t HID_KEY_X = 27u;             // Keyboard x and X
constexpr hid_key_t HID_KEY_Y = 28u;             // Keyboard y and Y
constexpr hid_key_t HID_KEY_Z = 29u;             // Keyboard z and Z
constexpr hid_key_t HID_KEY_1 = 30u;             // Keyboard 1 and !
constexpr hid_key_t HID_KEY_2 = 31u;             // Keyboard 2 and @
constexpr hid_key_t HID_KEY_3 = 32u;             // Keyboard 3 and #
constexpr hid_key_t HID_KEY_4 = 33u;             // Keyboard 4 and %
constexpr hid_key_t HID_KEY_5 = 34u;             // Keyboard 5 and %
constexpr hid_key_t HID_KEY_6 = 35u;             // Keyboard 6 and ^
constexpr hid_key_t HID_KEY_7 = 36u;             // Keyboard 7 and &
constexpr hid_key_t HID_KEY_8 = 37u;             // Keyboard 8 and *
constexpr hid_key_t HID_KEY_9 = 38u;             // Keyboard 9 and (
constexpr hid_key_t HID_KEY_0 = 39u;             // Keyboard 0 and )
constexpr hid_key_t HID_KEY_RETURN = 40u;        // Keyboard Return (ENTER)
constexpr hid_key_t HID_KEY_ESCAPE = 41u;        // Keyboard ESCAPE
constexpr hid_key_t HID_KEY_DELETE = 42u;        // Keyboard DELETE (Backspace)
constexpr hid_key_t HID_KEY_TAB = 43u;           // Keyboard Tab
constexpr hid_key_t HID_KEY_SPACEBAR = 44u;      // Keyboard Spacebar
constexpr hid_key_t HID_KEY_MINUS = 45u;         // Keyboard - and (underscore)
constexpr hid_key_t HID_KEY_EQUAL = 46u;         // Keyboard = and +
constexpr hid_key_t HID_KEY_LEFT_BRKT = 47u;     // Keyboard [ and {
constexpr hid_key_t HID_KEY_RIGHT_BRKT = 48u;    // Keyboard ] and }
constexpr hid_key_t HID_KEY_BACK_SLASH = 49u;    // Keyboard \ and |
constexpr hid_key_t HID_KEY_SEMI_COLON = 51u;    // Keyboard ; and :
constexpr hid_key_t HID_KEY_SGL_QUOTE = 52u;     // Keyboard ' and "
constexpr hid_key_t HID_KEY_GRV_ACCENT = 53u;    // Keyboard Grave Accent and Tilde
constexpr hid_key_t HID_KEY_COMMA = 54u;         // Keyboard , and <
constexpr hid_key_t HID_KEY_DOT = 55u;           // Keyboard . and >
constexpr hid_key_t HID_KEY_FWD_SLASH = 56u;     // Keyboard / and ?
constexpr hid_key_t HID_KEY_CAPS_LOCK = 57u;     // Keyboard Caps Lock
constexpr hid_key_t HID_KEY_F1 = 58u;            // Keyboard F1
constexpr hid_key_t HID_KEY_F2 = 59u;            // Keyboard F2
constexpr hid_key_t HID_KEY_F3 = 60u;            // Keyboard F3
constexpr hid_key_t HID_KEY_F4 = 61u;            // Keyboard F4
constexpr hid_key_t HID_KEY_F5 = 62u;            // Keyboard F5
constexpr hid_key_t HID_KEY_F6 = 63u;            // Keyboard F6
constexpr hid_key_t HID_KEY_F7 = 64u;            // Keyboard F7
constexpr hid_key_t HID_KEY_F8 = 65u;            // Keyboard F8
constexpr hid_key_t HID_KEY_F9 = 66u;            // Keyboard F9
constexpr hid_key_t HID_KEY_F10 = 67u;           // Keyboard F10
constexpr hid_key_t HID_KEY_F11 = 68u;           // Keyboard F11
constexpr hid_key_t HID_KEY_F12 = 69u;           // Keyboard F12
constexpr hid_key_t HID_KEY_PRNT_SCREEN = 70u;   // Keyboard Print Screen
constexpr hid_key_t HID_KEY_SCROLL_LOCK = 71u;   // Keyboard Scroll Lock
constexpr hid_key_t HID_KEY_PAUSE = 72u;         // Keyboard Pause
constexpr hid_key_t HID_KEY_INSERT = 73u;        // Keyboard Insert
constexpr hid_key_t HID_KEY_HOME = 74u;          // Keyboard Home
constexpr hid_key_t HID_KEY_PAGE_UP = 75u;       // Keyboard PageUp
constexpr hid_key_t HID_KEY_DELETE_FWD = 76u;    // Keyboard Delete Forward
constexpr hid_key_t HID_KEY_END = 77u;           // Keyboard End
constexpr hid_key_t HID_KEY_PAGE_DOWN = 78u;     // Keyboard PageDown
constexpr hid_key_t HID_KEY_RIGHT_ARROW = 79u;   // Keyboard RightArrow
constexpr hid_key_t HID_KEY_LEFT_ARROW = 80u;    // Keyboard LeftArrow
constexpr hid_key_t HID_KEY_DOWN_ARROW = 81u;    // Keyboard DownArrow
constexpr hid_key_t HID_KEY_UP_ARROW = 82u;      // Keyboard UpArrow
constexpr hid_key_t HID_KEY_NUM_LOCK = 83u;      // Keypad Num Lock and Clear
constexpr hid_key_t HID_KEY_DIVIDE = 84u;        // Keypad /
constexpr hid_key_t HID_KEY_MULTIPLY = 85u;      // Keypad *
constexpr hid_key_t HID_KEY_SUBTRACT = 86u;      // Keypad -
constexpr hid_key_t HID_KEY_ADD = 87u;           // Keypad +
constexpr hid_key_t HID_KEY_ENTER = 88u;         // Keypad ENTER
constexpr hid_key_t HID_KEYPAD_1 = 89u;          // Keypad 1 and End
constexpr hid_key_t HID_KEYPAD_2 = 90u;          // Keypad 2 and Down Arrow
constexpr hid_key_t HID_KEYPAD_3 = 91u;          // Keypad 3 and PageDn
constexpr hid_key_t HID_KEYPAD_4 = 92u;          // Keypad 4 and Lfet Arrow
constexpr hid_key_t HID_KEYPAD_5 = 93u;          // Keypad 5
constexpr hid_key_t HID_KEYPAD_6 = 94u;          // Keypad 6 and Right Arrow
constexpr hid_key_t HID_KEYPAD_7 = 95u;          // Keypad 7 and Home
constexpr hid_key_t HID_KEYPAD_8 = 96u;          // Keypad 8 and Up Arrow
constexpr hid_key_t HID_KEYPAD_9 = 97u;          // Keypad 9 and PageUp
constexpr hid_key_t HID_KEYPAD_0 = 98u;          // Keypad 0 and Insert
constexpr hid_key_t HID_KEYPAD_DOT = 99u;        // Keypad . and Delete
constexpr hid_key_t HID_KEY_MUTE = 127u;         // Keyboard Mute
constexpr hid_key_t HID_KEY_VOLUME_UP = 128u;    // Keyboard Volume up
constexpr hid_key_t HID_KEY_VOLUME_DOWN = 129u;  // Keyboard Volume down
constexpr hid_key_t HID_KEY_LEFT_CTRL = 224u;    // Keyboard LeftContorl
constexpr hid_key_t HID_KEY_LEFT_SHIFT = 225u;   // Keyboard LeftShift
constexpr hid_key_t HID_KEY_LEFT_ALT = 226u;     // Keyboard LeftAlt
constexpr hid_key_t HID_KEY_LEFT_GUI = 227u;     // Keyboard LeftGUI
constexpr hid_key_t HID_KEY_RIGHT_CTRL = 228u;   // Keyboard LeftContorl
constexpr hid_key_t HID_KEY_RIGHT_SHIFT = 229u;  // Keyboard LeftShift
constexpr hid_key_t HID_KEY_RIGHT_ALT = 230u;    // Keyboard LeftAlt
constexpr hid_key_t HID_KEY_RIGHT_GUI = 231u;    // Keyboard RightGUI

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
