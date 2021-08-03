#include <nvs_flash.h>

#include <cstring>

#include "esp_if/esp_if.hpp"
#include "ible.hpp"
#include "ihid.hpp"
#include "keyboard.hpp"
#include "matrix.hpp"
#include "object.hpp"
#include "supporting/mapping.hpp"
#include "transports.hpp"

using namespace kopinions;
using namespace kopinions::logging;

static const uint16_t s_primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t s_include_service_uuid = ESP_GATT_UUID_INCLUDE_SERVICE;
static const uint16_t s_character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
static const uint16_t s_character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;

static const uint16_t s_bat_level_uuid = ESP_GATT_UUID_BATTERY_LEVEL;
static const uint16_t s_bat_char_pres_format_uuid = ESP_GATT_UUID_CHAR_PRESENT_FORMAT;
static const uint8_t s_char_prop_read_notify = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
static const uint8_t bat_lev_ccc[2] = {0x00, 0x00};
static uint8_t bat_level = 1;

static const uint16_t primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
static const uint16_t character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
static const uint16_t hid_info_char_uuid = ESP_GATT_UUID_HID_INFORMATION;
static const uint16_t hid_report_map_uuid = ESP_GATT_UUID_HID_REPORT_MAP;
static const uint16_t hid_control_point_uuid = ESP_GATT_UUID_HID_CONTROL_POINT;
static const uint16_t hid_report_uuid = ESP_GATT_UUID_HID_REPORT;
static const uint16_t hid_proto_mode_uuid = ESP_GATT_UUID_HID_PROTO_MODE;
static const uint16_t hid_kb_input_uuid = ESP_GATT_UUID_HID_BT_KB_INPUT;
static const uint16_t hid_kb_output_uuid = ESP_GATT_UUID_HID_BT_KB_OUTPUT;
static const uint16_t hid_mouse_input_uuid = ESP_GATT_UUID_HID_BT_MOUSE_INPUT;
static const uint16_t hid_repot_map_ext_desc_uuid = ESP_GATT_UUID_EXT_RPT_REF_DESCR;
static const uint16_t hid_report_ref_descr_uuid = ESP_GATT_UUID_RPT_REF_DESCR;

#define ATT_SVC_HID 0x1812
#define ESP_HID_FLAGS_REMOTE_WAKE 0x01           // RemoteWake
#define ESP_HID_FLAGS_NORMALLY_CONNECTABLE 0x02  // NormallyConnectable
static uint16_t hid_le_svc = ATT_SVC_HID;
static uint8_t hidInfo[4] = {
    0x11, 0x11,                                                     // bcdHID (USB HID version)
    0x00,                                                           // bCountryCode
    ESP_HID_FLAGS_REMOTE_WAKE | ESP_HID_FLAGS_NORMALLY_CONNECTABLE  // Flags
};
/// HID Information structure
typedef struct {
  /// bcdHID
  uint16_t bcdHID;
  /// bCountryCode
  uint8_t bCountryCode;
  /// Flags
  uint8_t flags;
} hids_hid_info_t;

static unsigned char hidReportMap[] = {
    0x05, 0x01,  // Usage Page (Generic Desktop Ctrls)
    0x09, 0x02,  // Usage (Mouse)
    0xA1, 0x01,  // Collection (Application)
    0x85, 0x01,  //   Report ID (1)
    0x09, 0x01,  //   Usage (Pointer)
    0xA1, 0x00,  //   Collection (Physical)
    0x05, 0x09,  //     Usage Page (Button)
    0x19, 0x01,  //     Usage Minimum (0x01)
    0x29, 0x03,  //     Usage Maximum (0x03)
    0x15, 0x00,  //     Logical Minimum (0)
    0x25, 0x01,  //     Logical Maximum (1)
    0x75, 0x01,  //     Report Size (1)
    0x95, 0x03,  //     Report Count (3)
    0x81, 0x02,  //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x05,  //     Report Size (5)
    0x95, 0x01,  //     Report Count (1)
    0x81, 0x01,  //     Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,  //     Usage Page (Generic Desktop Ctrls)
    0x09, 0x30,  //     Usage (X)
    0x09, 0x31,  //     Usage (Y)
    0x09, 0x38,  //     Usage (Wheel)
    0x15, 0x81,  //     Logical Minimum (-127)
    0x25, 0x7F,  //     Logical Maximum (127)
    0x75, 0x08,  //     Report Size (8)
    0x95, 0x03,  //     Report Count (3)
    0x81, 0x06,  //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,        //   End Collection
    0xC0,        // End Collection

    0x05, 0x01,  // Usage Page (Generic Desktop Ctrls)
    0x09, 0x06,  // Usage (Keyboard)
    0xA1, 0x01,  // Collection (Application)
    0x85, 0x02,  //   Report ID (2)
    0x05, 0x07,  //   Usage Page (Kbrd/Keypad)
    0x19, 0xE0,  //   Usage Minimum (0xE0)
    0x29, 0xE7,  //   Usage Maximum (0xE7)
    0x15, 0x00,  //   Logical Minimum (0)
    0x25, 0x01,  //   Logical Maximum (1)
    0x75, 0x01,  //   Report Size (1)
    0x95, 0x08,  //   Report Count (8)
    0x81, 0x02,  //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x01,  //   Report Count (1)
    0x75, 0x08,  //   Report Size (8)
    0x81, 0x01,  //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x05,  //   Report Count (5)
    0x75, 0x01,  //   Report Size (1)
    0x05, 0x08,  //   Usage Page (LEDs)
    0x19, 0x01,  //   Usage Minimum (Num Lock)
    0x29, 0x05,  //   Usage Maximum (Kana)
    0x91, 0x02,  //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x95, 0x01,  //   Report Count (1)
    0x75, 0x03,  //   Report Size (3)
    0x91, 0x01,  //   Output (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x95, 0x06,  //   Report Count (6)
    0x75, 0x08,  //   Report Size (8)
    0x15, 0x00,  //   Logical Minimum (0)
    0x25, 0x65,  //   Logical Maximum (101)
    0x05, 0x07,  //   Usage Page (Kbrd/Keypad)
    0x19, 0x00,  //   Usage Minimum (0x00)
    0x29, 0x65,  //   Usage Maximum (0x65)
    0x81, 0x00,  //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,        // End Collection

    0x05, 0x0C,  // Usage Page (Consumer)
    0x09, 0x01,  // Usage (Consumer Control)
    0xA1, 0x01,  // Collection (Application)
    0x85, 0x03,  //   Report ID (3)
    0x09, 0x02,  //   Usage (Numeric Key Pad)
    0xA1, 0x02,  //   Collection (Logical)
    0x05, 0x09,  //     Usage Page (Button)
    0x19, 0x01,  //     Usage Minimum (0x01)
    0x29, 0x0A,  //     Usage Maximum (0x0A)
    0x15, 0x01,  //     Logical Minimum (1)
    0x25, 0x0A,  //     Logical Maximum (10)
    0x75, 0x04,  //     Report Size (4)
    0x95, 0x01,  //     Report Count (1)
    0x81, 0x00,  //     Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,        //   End Collection
    0x05, 0x0C,  //   Usage Page (Consumer)
    0x09, 0x86,  //   Usage (Channel)
    0x15, 0xFF,  //   Logical Minimum (-1)
    0x25, 0x01,  //   Logical Maximum (1)
    0x75, 0x02,  //   Report Size (2)
    0x95, 0x01,  //   Report Count (1)
    0x81, 0x46,  //   Input (Data,Var,Rel,No Wrap,Linear,Preferred State,Null State)
    0x09, 0xE9,  //   Usage (Volume Increment)
    0x09, 0xEA,  //   Usage (Volume Decrement)
    0x15, 0x00,  //   Logical Minimum (0)
    0x75, 0x01,  //   Report Size (1)
    0x95, 0x02,  //   Report Count (2)
    0x81, 0x02,  //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0xE2,  //   Usage (Mute)
    0x09, 0x30,  //   Usage (Power)
    0x09, 0x83,  //   Usage (Recall Last)
    0x09, 0x81,  //   Usage (Assign Selection)
    0x09, 0xB0,  //   Usage (Play)
    0x09, 0xB1,  //   Usage (Pause)
    0x09, 0xB2,  //   Usage (Record)
    0x09, 0xB3,  //   Usage (Fast Forward)
    0x09, 0xB4,  //   Usage (Rewind)
    0x09, 0xB5,  //   Usage (Scan Next Track)
    0x09, 0xB6,  //   Usage (Scan Previous Track)
    0x09, 0xB7,  //   Usage (Stop)
    0x15, 0x01,  //   Logical Minimum (1)
    0x25, 0x0C,  //   Logical Maximum (12)
    0x75, 0x04,  //   Report Size (4)
    0x95, 0x01,  //   Report Count (1)
    0x81, 0x00,  //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x80,  //   Usage (Selection)
    0xA1, 0x02,  //   Collection (Logical)
    0x05, 0x09,  //     Usage Page (Button)
    0x19, 0x01,  //     Usage Minimum (0x01)
    0x29, 0x03,  //     Usage Maximum (0x03)
    0x15, 0x01,  //     Logical Minimum (1)
    0x25, 0x03,  //     Logical Maximum (3)
    0x75, 0x02,  //     Report Size (2)
    0x81, 0x00,  //     Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,        //   End Collection
    0x81, 0x03,  //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,        // End Collection

    0x06, 0xFF, 0xFF,  // Usage Page (Vendor Defined 0xFFFF)
    0x09, 0xA5,        // Usage (0xA5)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x04,        //   Report ID (4)
    0x09, 0xA6,        //   Usage (0xA6)
    0x09, 0xA9,        //   Usage (0xA9)
    0x75, 0x08,        //   Report Size (8)
    0x95, 0x7F,        //   Report Count (127)
    0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,              // End Collection

    // 250 bytes
};
static uint16_t hidExtReportRefDesc = ESP_GATT_UUID_BATTERY_LEVEL;

#define HID_PROTOCOL_MODE_REPORT 0x01  // Report Protocol Mode
static uint8_t hidProtocolMode = HID_PROTOCOL_MODE_REPORT;
// HID Report Reference characteristic descriptor, key input
/* Attribute value lengths */
#define HID_PROTOCOL_MODE_LEN 1   // HID Protocol Mode
#define HID_INFORMATION_LEN 4     // HID Information
#define HID_REPORT_REF_LEN 2      // HID Report Reference Descriptor
#define HID_EXT_REPORT_REF_LEN 2  // External Report Reference Descriptor
#include <type_traits>

template <typename E>
constexpr auto underlying(E e) noexcept {
  return static_cast<std::underlying_type_t<E>>(e);
}
static uint8_t hidReportRefKeyIn[HID_REPORT_REF_LEN] = {underlying(hid::report_t::id_t::KEY_IN),
                                                        underlying(hid::report_t::type_t::INPUT)};
static uint8_t hidReportRefLedOut[HID_REPORT_REF_LEN] = {underlying(hid::report_t::id_t::LED_OUT),
                                                         underlying(hid::report_t::type_t::OUTPUT)};
static uint8_t hidReportRefCCIn[HID_REPORT_REF_LEN] = {underlying(hid::report_t::id_t::CC_IN),
                                                       underlying(hid::report_t::type_t::INPUT)};
static uint8_t hidReportRefFeature[HID_REPORT_REF_LEN] = {underlying(hid::report_t::id_t::FEATURE),
                                                          underlying(hid::report_t::type_t::FEATURE)};

typedef uint8_t key_mask_t;
// HID keyboard input report length
#define HID_KEYBOARD_IN_RPT_LEN 8

// HID LED output report length
#define HID_LED_OUT_RPT_LEN 1

// HID mouse input report length
#define HID_MOUSE_IN_RPT_LEN 5

// HID consumer control input report length
#define HID_CC_IN_RPT_LEN 2

#define HID_NUM_REPORTS 9
static hid::report_map_t hid_rpt_map[HID_NUM_REPORTS];
static hid::report_map_t *hid_dev_rpt_tbl;
static uint8_t hid_dev_rpt_tbl_Len;

static hid::report_map_t *hid_dev_rpt_by_id(hid::report_t::id_t id, hid::report_t::type_t type) {
  hid::report_map_t *rpt = hid_dev_rpt_tbl;

  // TODO: find the report
  //  for (uint8_t i = hid_dev_rpt_tbl_Len; i > 0; i--, rpt++) {
  //    if (rpt->id == id && rpt->type == type && rpt->mode == hidProtocolMode) {
  //      return rpt;
  //    }
  //  }

  return NULL;
}

void esp_hidd_send_keyboard_value(uint16_t conn_id, esp_gatt_if_t ga, uint16_t handle, key_mask_t special_key_mask, uint8_t *keyboard_cmd,
                                  uint8_t num_key) {
  if (num_key > HID_KEYBOARD_IN_RPT_LEN - 2) {
    ESP_LOGE("HID_LE_PRF_TAG", "%s(), the number key should not be more than %d", __func__, HID_KEYBOARD_IN_RPT_LEN);
    return;
  }

  uint8_t buffer[HID_KEYBOARD_IN_RPT_LEN] = {0};

  buffer[0] = special_key_mask;

  for (int i = 0; i < num_key; i++) {
    buffer[i + 2] = keyboard_cmd[i];
  }

  ESP_LOGD("HID_LE_PRF_TAG", "the key vaule = %d,%d,%d, %d, %d, %d,%d, %d", buffer[0], buffer[1], buffer[2], buffer[3],
           buffer[4], buffer[5], buffer[6], buffer[7]);
  // TODO: replace the gattif with actual gattif
  //  esp_gatt_if_t anIf = hidd_le_env.gatt_if;

  hid::report_map_t *p_rpt;

  // get att handle for report
  if ((p_rpt = hid_dev_rpt_by_id(hid::report_t ::id_t::KEY_IN, hid::report_t::type_t::INPUT)) != NULL) {
    // if notifications are enabled
    // TODO(neo): replace the handle with create table handle
    //    uint16_t handle = p_rpt->handle;
    ESP_LOGD("HID_LE_PRF_TAG", "%s(), send the report, handle = %d", __func__, handle);
    esp_ble_gatts_send_indicate(ga, conn_id, handle, HID_KEYBOARD_IN_RPT_LEN, buffer, false);
  }
  return;
}

void hid_dev_register_reports(uint8_t num_reports, hid::report_map_t *p_report) {
  hid_dev_rpt_tbl = p_report;
  hid_dev_rpt_tbl_Len = num_reports;
  return;
}
static void hid_add_id_tbl(void) {
  // Key input report
  //  hid_rpt_map[1].id = hidReportRefKeyIn[0];
  //  hid_rpt_map[1].type = hidReportRefKeyIn[1];
  //  hid_rpt_map[1].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_KEY_IN_VAL];
  //  hid_rpt_map[1].cccdHandle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_KEY_IN_CCC];
  //  hid_rpt_map[1].mode = HID_PROTOCOL_MODE_REPORT;
  //
  //  // Consumer Control input report
  //  hid_rpt_map[2].id = hidReportRefCCIn[0];
  //  hid_rpt_map[2].type = hidReportRefCCIn[1];
  //  hid_rpt_map[2].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_CC_IN_VAL];
  //  hid_rpt_map[2].cccdHandle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_CC_IN_CCC];
  //  hid_rpt_map[2].mode = HID_PROTOCOL_MODE_REPORT;
  //
  //  // LED output report
  //  hid_rpt_map[3].id = hidReportRefLedOut[0];
  //  hid_rpt_map[3].type = hidReportRefLedOut[1];
  //  hid_rpt_map[3].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_LED_OUT_VAL];
  //  hid_rpt_map[3].cccdHandle = 0;
  //  hid_rpt_map[3].mode = HID_PROTOCOL_MODE_REPORT;
  //
  //  // Boot keyboard input report
  //  // Use same ID and type as key input report
  //  hid_rpt_map[4].id = hidReportRefKeyIn[0];
  //  hid_rpt_map[4].type = hidReportRefKeyIn[1];
  //  hid_rpt_map[4].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_BOOT_KB_IN_REPORT_VAL];
  //  hid_rpt_map[4].cccdHandle = 0;
  //  hid_rpt_map[4].mode = HID_PROTOCOL_MODE_BOOT;
  //
  //  // Boot keyboard output report
  //  // Use same ID and type as LED output report
  //  hid_rpt_map[5].id = hidReportRefLedOut[0];
  //  hid_rpt_map[5].type = hidReportRefLedOut[1];
  //  hid_rpt_map[5].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_BOOT_KB_OUT_REPORT_VAL];
  //  hid_rpt_map[5].cccdHandle = 0;
  //  hid_rpt_map[5].mode = HID_PROTOCOL_MODE_BOOT;
  //
  //  // Feature report
  //  hid_rpt_map[7].id = hidReportRefFeature[0];
  //  hid_rpt_map[7].type = hidReportRefFeature[1];
  //  hid_rpt_map[7].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_VAL];
  //  hid_rpt_map[7].cccdHandle = 0;
  //  hid_rpt_map[7].mode = HID_PROTOCOL_MODE_REPORT;

  // Setup report ID map

  hid_dev_register_reports(HID_NUM_REPORTS, hid_rpt_map);
}

extern "C" void app_main() {
  auto ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  auto sche = new scheduler_if<>;

  sche->schedule("test", []() -> void {
    auto ios = new gpios_if;
    auto clk = new clock_if;
    auto mtx = new matrix(*ios, *clk);
    auto lay = new layout(layout_mapping);
    auto cfg = new config();
    auto kbd = new keyboard(*lay, *mtx, *cfg);
    auto sink = new esp_log_sink();
    auto lg = new logger(level::INFO, sink);
    auto trans = new transports();

    auto b = new bt::ble("Chaos", bt::appearance_t::KEYBOARD, *lg);

    auto hid =
        bt::application_builder_t::name("hid")
            ->id(0x01)
            ->profile([](bt::profile_builder_t *p) {
              p->service([](bt::service_builder_t *s) {
                s->id(bt::service_t::id_t::BATTERY);
                s->characteristic([](bt::characteristic_builder_t *c) {
                  c->id(s_bat_level_uuid);
                  c->declare([](bt::characteristic_declare_builder_t *d) {
                    d->property(bt::characteristic_t::property_t::READ | bt::characteristic_t::property_t::NOTIFY);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                  });
                  c->value([](bt::characteristic_value_builder_t *v) {
                    v->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    v->value(&bat_level, 1, 1);
                  });
                  c->descriptor([](bt::characteristic_descriptor_builder_t *d) {
                    d->id(s_character_client_config_uuid);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED |
                                  bt::characteristic_t::permission_t::WRITE_ENCRYPTED);
                    d->value(nullptr, 0, sizeof(uint16_t));
                  });
                  c->descriptor([](bt::characteristic_descriptor_builder_t *d) {
                    d->id(s_bat_char_pres_format_uuid);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    d->value(nullptr, 0, sizeof(bt::characteristic_t::presentation_format));
                  });
                });
              });

              p->service([](bt::service_builder_t *s) {
                s->id(bt::service_t::id_t::HID);
                s->include([](bt::service_include_builder_t *ic) { ic->id(bt::service_t::id_t::BATTERY); });

                s->characteristic([](bt::characteristic_builder_t *c) {
                  c->id(hid_info_char_uuid);
                  c->declare([](bt::characteristic_declare_builder_t *d) {
                    d->property(bt::characteristic_t::property_t::READ);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                  });
                  c->value([](bt::characteristic_value_builder_t *v) {
                    v->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    v->value(hidInfo, sizeof(hidInfo), sizeof(hids_hid_info_t));
                  });
                });
                s->characteristic([](bt::characteristic_builder_t *c) {
                  c->id(hid_control_point_uuid);
                  c->declare([](bt::characteristic_declare_builder_t *d) {
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    d->property(bt::characteristic_t::property_t::WRITE_NR);
                  });
                  c->value([](bt::characteristic_value_builder_t *v) {
                    v->permission(bt::characteristic_t::permission_t::WRITE_ENCRYPTED);
                    v->value(nullptr, 0, sizeof(uint8_t));
                  });
                });
                s->characteristic([](bt::characteristic_builder_t *c) {
                  c->id(hid_report_map_uuid);
                  c->declare([](bt::characteristic_declare_builder_t *d) {
                    d->property(bt::characteristic_t::property_t::READ);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                  });
                  c->value([](bt::characteristic_value_builder_t *v) {
                    v->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    v->value(hidReportMap, sizeof(hidReportMap), hid::HIDD_LE_REPORT_MAP_MAX_LEN);
                  });
                  c->descriptor([](bt::characteristic_descriptor_builder_t *d) {
                    d->id(hid_repot_map_ext_desc_uuid);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    d->value(reinterpret_cast<uint8_t *>(&hidExtReportRefDesc), sizeof(uint16_t), sizeof(uint16_t));
                  });
                });
                s->characteristic([](bt::characteristic_builder_t *c) {
                  c->id(hid_proto_mode_uuid);
                  c->declare([](bt::characteristic_declare_builder_t *d) {
                    d->property(bt::characteristic_t::property_t::READ | bt::characteristic_t::property_t::WRITE);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                  });
                  c->value([](bt::characteristic_value_builder_t *v) {
                    v->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED |
                                  bt::characteristic_t::permission_t::WRITE_ENCRYPTED);
                    v->value(&hidProtocolMode, sizeof(hidProtocolMode), sizeof(uint8_t));
                  });
                });
                s->characteristic([](bt::characteristic_builder_t *c) {
                  c->id(hid_report_uuid);
                  c->declare([](bt::characteristic_declare_builder_t *d) {
                    d->property(bt::characteristic_t::property_t::READ | bt::characteristic_t::property_t::NOTIFY);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                  });
                  c->value([](bt::characteristic_value_builder_t *v) {
                    v->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    v->value(nullptr, 0, HIDD_LE_REPORT_MAX_LEN);
                  });
                  c->descriptor([](bt::characteristic_descriptor_builder_t *d) {
                    d->id(character_client_config_uuid);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED |
                                  bt::characteristic_t::permission_t::WRITE_ENCRYPTED);
                    d->value(nullptr, 0, sizeof(uint16_t));
                  });
                  c->descriptor([](bt::characteristic_descriptor_builder_t *d) {
                    d->id(hid_report_ref_descr_uuid);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    d->value(hidReportRefKeyIn, sizeof(hidReportRefKeyIn), sizeof(hidReportRefKeyIn));
                  });
                });

                s->characteristic([](bt::characteristic_builder_t *c) {
                  c->id(hid_report_uuid);
                  c->declare([](bt::characteristic_declare_builder_t *d) {
                    d->property(bt::characteristic_t::property_t::READ | bt::characteristic_t::property_t::WRITE);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                  });
                  c->value([](bt::characteristic_value_builder_t *v) {
                    v->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED |
                                  bt::characteristic_t::permission_t::WRITE_ENCRYPTED);
                    v->value(nullptr, 0, HIDD_LE_REPORT_MAX_LEN);
                  });
                  c->descriptor([](bt::characteristic_descriptor_builder_t *d) {
                    d->id(hid_report_ref_descr_uuid);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    d->value(hidReportRefLedOut, sizeof(hidReportRefLedOut), sizeof(hidReportRefLedOut));
                  });
                });

                s->characteristic([](bt::characteristic_builder_t *c) {
                  c->id(hid_report_uuid);
                  c->declare([](bt::characteristic_declare_builder_t *d) {
                    d->property(bt::characteristic_t::property_t::READ | bt::characteristic_t::property_t::NOTIFY);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                  });
                  c->value([](bt::characteristic_value_builder_t *v) {
                    v->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    v->value(nullptr, 0, HIDD_LE_REPORT_MAX_LEN);
                  });
                  c->descriptor([](bt::characteristic_descriptor_builder_t *d) {
                    d->id(character_client_config_uuid);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED |
                                  bt::characteristic_t::permission_t::WRITE_ENCRYPTED);
                    d->value(nullptr, 0, sizeof(uint16_t));
                  });
                  c->descriptor([](bt::characteristic_descriptor_builder_t *d) {
                    d->id(hid_report_ref_descr_uuid);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    d->value(hidReportRefCCIn, sizeof(hidReportRefCCIn), sizeof(hidReportRefCCIn));
                  });
                });

                s->characteristic([](bt::characteristic_builder_t *c) {
                  c->id(hid_kb_input_uuid);
                  c->declare([](bt::characteristic_declare_builder_t *d) {
                    d->property(bt::characteristic_t::property_t::READ | bt::characteristic_t::property_t::NOTIFY);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                  });
                  c->value([](bt::characteristic_value_builder_t *v) {
                    v->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    v->value(nullptr, 0, hid::HIDD_LE_BOOT_REPORT_MAX_LEN);
                  });
                  c->descriptor([](bt::characteristic_descriptor_builder_t *d) {
                    d->id(character_client_config_uuid);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED |
                                  bt::characteristic_t::permission_t::WRITE_ENCRYPTED);
                    d->value(nullptr, 0, sizeof(uint16_t));
                  });
                });
                s->characteristic([](bt::characteristic_builder_t *c) {
                  c->id(hid_kb_output_uuid);
                  c->declare([](bt::characteristic_declare_builder_t *d) {
                    d->property(bt::characteristic_t::property_t::READ | bt::characteristic_t::property_t::WRITE);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                  });
                  c->value([](bt::characteristic_value_builder_t *v) {
                    v->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED |
                                  bt::characteristic_t::permission_t::WRITE_ENCRYPTED);
                    v->value(nullptr, 0, hid::HIDD_LE_BOOT_REPORT_MAX_LEN);
                  });
                });

                s->characteristic([](bt::characteristic_builder_t *c) {
                  c->id(hid_report_uuid);
                  c->declare([](bt::characteristic_declare_builder_t *d) {
                    d->property(bt::characteristic_t::property_t::READ | bt::characteristic_t::property_t::WRITE);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                  });
                  c->value([](bt::characteristic_value_builder_t *v) {
                    v->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    v->value(nullptr, 0, HIDD_LE_REPORT_MAX_LEN);
                  });
                  c->descriptor([](bt::characteristic_descriptor_builder_t *d) {
                    d->id(hid_report_ref_descr_uuid);
                    d->permission(bt::characteristic_t::permission_t::READ_ENCRYPTED);
                    d->value(hidReportRefFeature, sizeof(hidReportRefFeature), sizeof(hidReportRefFeature));
                  });
                });
              });
            })
            ->build();

    std::cout << hid;
    b->enroll(hid);

    while (true) {
      lg->log(level::INFO, "%s %d", "xxx1111", 222);

      auto &&res = kbd->scan();
      auto tx = trans->select();

      uint8_t buffer[HID_CC_IN_RPT_LEN] = {0, 28};
      auto special_key_mask = 0;

      auto a = hid->select(bt::selector_t<bt::characteristic_t*>::$(
          bt::ble_selector_t::profile(0x1)->service(bt::service_t::HID)->characteristic(hid_report_uuid)->nth(0)));

      lg->log(level::INFO, "%d", a->id());
      esp_hidd_send_keyboard_value(hid->m_connection, 0, a->attributes()[1]->m_handle, static_cast<key_mask_t>(special_key_mask), buffer, 2);

      ESP_LOGD("HID_LE_PRF_TAG", "buffer[0] = %x, buffer[1] = %x", buffer[0], buffer[1]);

      for (auto b : res) {
        auto status = b.sts;
        lg->log(level::DEBUG, "%d", status);
      }

      vTaskDelay(60000 / portTICK_PERIOD_MS);
    }
  });
}