#pragma once
#include "ible/ble.hpp"

namespace hid {
class hid_handler {};
static hid_handler handler = hid_handler{};

/*
 *  if (event == ESP_GATTS_REG_EVT) {
        if (param->reg.status != ESP_GATT_OK) {
            ESP_LOGE(TAG, "Reg app failed, app_id %04x, status %d", param->reg.app_id, param->reg.status);
            return;
        } else {
            if (param->reg.app_id == ESP_GATT_UUID_DEVICE_INFO_SVC) {
                s_dev->info_svc.gatt_if = gatts_if;
            } else if (param->reg.app_id == ESP_GATT_UUID_BATTERY_SERVICE_SVC) {
                s_dev->bat_svc.gatt_if = gatts_if;
            } else if (param->reg.app_id >= ESP_GATT_UUID_HID_SVC && param->reg.app_id < (ESP_GATT_UUID_HID_SVC +
 s_dev->devices_len)) { ESP_LOGV(TAG, "HID SVC[%u] IF: %d", param->reg.app_id - ESP_GATT_UUID_HID_SVC, gatts_if);
                s_dev->devices[param->reg.app_id - ESP_GATT_UUID_HID_SVC].hid_svc.gatt_if = gatts_if;
            } else {
                ESP_LOGE(TAG, "Unknown Application, app_id %04x", param->reg.app_id);
                return;
            }
        }
    } else if (event == ESP_GATTS_CREAT_ATTR_TAB_EVT) {
        free(_last_db);
        _last_db = NULL;
    }

    if (s_dev->bat_svc.gatt_if && gatts_if == s_dev->bat_svc.gatt_if) {
        bat_event_handler(s_dev, event, gatts_if, param);
    } else if (s_dev->info_svc.gatt_if && gatts_if == s_dev->info_svc.gatt_if) {
        info_event_handler(s_dev, event, gatts_if, param);
    } else {
        int devi = get_device_map_index_by_gatts_if (s_dev, gatts_if);
        if (devi >= 0) {
            hid_event_handler(s_dev, devi, event, gatts_if, param);
        } else {
            ESP_LOGE(TAG, "Unknown gatts_if %u", gatts_if);
        }
        return;
    }
 */

static const bt::profile_t gatt_hid = bt::profile_t{
    0x00, [](bt::profile_t& p, esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
      switch (event) {
        case ESP_GATTS_REG_EVT: {
          for (auto svc : p.services()) {
            if (svc.id() == param->reg.app_id) {
              svc.registered(gatts_if);
            }
          }
          break;
        }
        default: {
          for (auto svc : p.services()) {
          }
          break;
        }
      }
    }};
}  // namespace hid

static uint8_t adv_service_uuid128[32] = {
    /* LSB <--------------------------------------------------------------------------------> MSB */
    // first uuid, 16bit, [12],[13] is the value
    0xfb,
    0x34,
    0x9b,
    0x5f,
    0x80,
    0x00,
    0x00,
    0x80,
    0x00,
    0x10,
    0x00,
    0x00,
    0xEE,
    0x00,
    0x00,
    0x00,
    // second uuid, 32bit, [12], [13], [14], [15] is the value
    0xfb,
    0x34,
    0x9b,
    0x5f,
    0x80,
    0x00,
    0x00,
    0x80,
    0x00,
    0x10,
    0x00,
    0x00,
    0xFF,
    0x00,
    0x00,
    0x00,
};
static esp_ble_adv_data_t adv_data = {
    .set_scan_rsp = false,
    .include_name = true,
    .include_txpower = false,
    .min_interval = 0x0006,  // slave connection min interval, Time = min_interval * 1.25 msec
    .max_interval = 0x0010,  // slave connection max interval, Time = max_interval * 1.25 msec
    .appearance = 0x00,
    .manufacturer_len = 0,        // TEST_MANUFACTURER_DATA_LEN,
    .p_manufacturer_data = NULL,  //&test_manufacturer[0],
    .service_data_len = 0,
    .p_service_data = NULL,
    .service_uuid_len = sizeof(adv_service_uuid128),
    .p_service_uuid = adv_service_uuid128,
    .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};
// scan response data
static esp_ble_adv_data_t scan_rsp_data = {
    .set_scan_rsp = true,
    .include_name = true,
    .include_txpower = true,
    //.min_interval = 0x0006,
    //.max_interval = 0x0010,
    .appearance = 0x00,
    .manufacturer_len = 0,        // TEST_MANUFACTURER_DATA_LEN,
    .p_manufacturer_data = NULL,  //&test_manufacturer[0],
    .service_data_len = 0,
    .p_service_data = NULL,
    .service_uuid_len = sizeof(adv_service_uuid128),
    .p_service_uuid = adv_service_uuid128,
    .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};
#define GATTS_DEMO_CHAR_VAL_LEN_MAX 0x40
static uint8_t char1_str[] = {0x11, 0x22, 0x33};
static esp_gatt_char_prop_t a_property = 0;
static esp_gatt_char_prop_t b_property = 0;

static esp_attr_value_t gatts_demo_char1_val = {
    .attr_max_len = GATTS_DEMO_CHAR_VAL_LEN_MAX,
    .attr_len = sizeof(char1_str),
    .attr_value = char1_str,
};

#include "ible.hpp"
constexpr char* GATTS_TAG = "";
static auto pro = bt::profile_t{
    0x180f,
    [](bt::profile_t& p, esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) -> void {
      switch (event) {
        case ESP_GATTS_REG_EVT: {
#define GATTS_SERVICE_UUID_TEST_A 0x00FF
#define GATTS_NUM_HANDLE_TEST_A 4
          ESP_LOGI("GATTS_TAG", "REGISTER_APP_EVT, status %d, app_id %d\n", param->reg.status, param->reg.app_id);

          esp_err_t set_dev_name_ret = esp_ble_gap_set_device_name("test_esp32");
          if (set_dev_name_ret) {
            ESP_LOGE(GATTS_TAG, "set device name failed, error code = %x", set_dev_name_ret);
          }
          // config adv data
          esp_err_t ret = esp_ble_gap_config_adv_data(&adv_data);
          if (ret) {
            ESP_LOGE(GATTS_TAG, "config adv data failed, error code = %x", ret);
          }
          // config scan response data
          ret = esp_ble_gap_config_adv_data(&scan_rsp_data);
          if (ret) {
            ESP_LOGE(GATTS_TAG, "config scan response data failed, error code = %x", ret);
          }
          p.service_id.is_primary = true;
          p.service_id.id.inst_id = 0x00;
          p.service_id.id.uuid.len = ESP_UUID_LEN_16;
          p.service_id.id.uuid.uuid.uuid16 = GATTS_SERVICE_UUID_TEST_A;
          esp_ble_gatts_create_service(gatts_if, &p.service_id, GATTS_NUM_HANDLE_TEST_A);
          break;
        }
        case ESP_GATTS_READ_EVT: {
          ESP_LOGI(GATTS_TAG, "GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id,
                   param->read.trans_id, param->read.handle);
          esp_gatt_rsp_t rsp;
          memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
          rsp.attr_value.handle = param->read.handle;
          rsp.attr_value.len = 4;
          rsp.attr_value.value[0] = 0xde;
          rsp.attr_value.value[1] = 0xed;
          rsp.attr_value.value[2] = 0xbe;
          rsp.attr_value.value[3] = 0xef;
          esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
          break;
        }
        case ESP_GATTS_WRITE_EVT: {
          ESP_LOGI(GATTS_TAG, "GATT_WRITE_EVT, conn_id %d, trans_id %d, handle %d", param->write.conn_id,
                   param->write.trans_id, param->write.handle);
          //              if (!param->write.is_prep) {
          //                ESP_LOGI(GATTS_TAG, "GATT_WRITE_EVT, value len %d, value :", param->write.len);
          //                esp_log_buffer_hex(GATTS_TAG, param->write.value, param->write.len);
          //                if (gl_profile_tab[PROFILE_A_APP_ID].descr_handle == param->write.handle &&
          //                param->write.len == 2) {
          //                  uint16_t descr_value = param->write.value[1] << 8 | param->write.value[0];
          //                  if (descr_value == 0x0001) {
          //                    if (a_property & ESP_GATT_CHAR_PROP_BIT_NOTIFY) {
          //                      ESP_LOGI(GATTS_TAG, "notify enable");
          //                      uint8_t notify_data[15];
          //                      for (int i = 0; i < sizeof(notify_data); ++i) {
          //                        notify_data[i] = i % 0xff;
          //                      }
          //                      // the size of notify_data[] need less than MTU size
          //                      esp_ble_gatts_send_indicate(gatts_if, param->write.conn_id,
          //                                                  gl_profile_tab[PROFILE_A_APP_ID].char_handle,
          //                                                  sizeof(notify_data), notify_data, false);
          //                    }
          //                  } else if (descr_value == 0x0002) {
          //                    if (a_property & ESP_GATT_CHAR_PROP_BIT_INDICATE) {
          //                      ESP_LOGI(GATTS_TAG, "indicate enable");
          //                      uint8_t indicate_data[15];
          //                      for (int i = 0; i < sizeof(indicate_data); ++i) {
          //                        indicate_data[i] = i % 0xff;
          //                      }
          //                      // the size of indicate_data[] need less than MTU size
          //                      esp_ble_gatts_send_indicate(gatts_if, param->write.conn_id,
          //                                                  gl_profile_tab[PROFILE_A_APP_ID].char_handle,
          //                                                  sizeof(indicate_data), indicate_data, true);
          //                    }
          //                  } else if (descr_value == 0x0000) {
          //                    ESP_LOGI(GATTS_TAG, "notify/indicate disable ");
          //                  } else {
          //                    ESP_LOGE(GATTS_TAG, "unknown descr value");
          //                    esp_log_buffer_hex(GATTS_TAG, param->write.value, param->write.len);
          //                  }
          //                }
          //              }
          //              example_write_event_env(gatts_if, &a_prepare_write_env, param);
          break;
        }
        case ESP_GATTS_EXEC_WRITE_EVT:
          ESP_LOGI(GATTS_TAG, "ESP_GATTS_EXEC_WRITE_EVT");
          esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, ESP_GATT_OK, NULL);
          //                  example_exec_write_event_env(&a_prepare_write_env, param);
          break;
        case ESP_GATTS_MTU_EVT:
          ESP_LOGI(GATTS_TAG, "ESP_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
          break;
        case ESP_GATTS_UNREG_EVT:
          break;
        case ESP_GATTS_CREATE_EVT: {
          ESP_LOGI(GATTS_TAG, "CREATE_SERVICE_EVT, status %d,  service_handle %d\n", param->create.status,
                   param->create.service_handle);
          constexpr uint16_t GATTS_CHAR_UUID_TEST_A = 0xFF01;
          p.service_handle = param->create.service_handle;
          p.char_uuid.len = ESP_UUID_LEN_16;
          p.char_uuid.uuid.uuid16 = GATTS_CHAR_UUID_TEST_A;

          esp_ble_gatts_start_service(p.service_handle);
          auto a_property = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
          esp_err_t add_char_ret =
              esp_ble_gatts_add_char(p.service_handle, &p.char_uuid, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
                                     a_property, &gatts_demo_char1_val, NULL);
          if (add_char_ret) {
            ESP_LOGE(GATTS_TAG, "add char failed, error code =%x", add_char_ret);
          }
          break;
        }
        case ESP_GATTS_ADD_INCL_SRVC_EVT:
          break;
        case ESP_GATTS_ADD_CHAR_EVT: {
          uint16_t length = 0;
          const uint8_t* prf_char;

          ESP_LOGI(GATTS_TAG, "ADD_CHAR_EVT, status %d,  attr_handle %d, service_handle %d\n", param->add_char.status,
                   param->add_char.attr_handle, param->add_char.service_handle);
          p.char_handle = param->add_char.attr_handle;
          p.descr_uuid.len = ESP_UUID_LEN_16;
          p.descr_uuid.uuid.uuid16 = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
          esp_err_t get_attr_ret = esp_ble_gatts_get_attr_value(param->add_char.attr_handle, &length, &prf_char);
          if (get_attr_ret == ESP_FAIL) {
            ESP_LOGE(GATTS_TAG, "ILLEGAL HANDLE");
          }

          ESP_LOGI(GATTS_TAG, "the gatts demo char length = %x\n", length);
          for (int i = 0; i < length; i++) {
            ESP_LOGI(GATTS_TAG, "prf_char[%x] =%x\n", i, prf_char[i]);
          }
          esp_err_t add_descr_ret = esp_ble_gatts_add_char_descr(p.service_handle, &p.descr_uuid,
                                                                 ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, NULL, NULL);
          if (add_descr_ret) {
            ESP_LOGE(GATTS_TAG, "add char descr failed, error code =%x", add_descr_ret);
          }
          break;
        }
        case ESP_GATTS_ADD_CHAR_DESCR_EVT:
          p.descr_handle = param->add_char_descr.attr_handle;
          ESP_LOGI(GATTS_TAG, "ADD_DESCR_EVT, status %d, attr_handle %d, service_handle %d\n",
                   param->add_char_descr.status, param->add_char_descr.attr_handle,
                   param->add_char_descr.service_handle);
          break;
        case ESP_GATTS_DELETE_EVT:
          break;
        case ESP_GATTS_START_EVT:
          ESP_LOGI(GATTS_TAG, "SERVICE_START_EVT, status %d, service_handle %d\n", param->start.status,
                   param->start.service_handle);
          break;
        case ESP_GATTS_STOP_EVT:
          break;
        case ESP_GATTS_CONNECT_EVT: {
          esp_ble_conn_update_params_t conn_params = {{0}};
          memcpy(conn_params.bda, param->connect.remote_bda, sizeof(esp_bd_addr_t));
          /* For the IOS system, please reference the apple official documents about the ble connection
           * parameters restrictions. */
          conn_params.latency = 0;
          conn_params.max_int = 0x20;  // max_int = 0x20*1.25ms = 40ms
          conn_params.min_int = 0x10;  // min_int = 0x10*1.25ms = 20ms
          conn_params.timeout = 400;   // timeout = 400*10ms = 4000ms
          ESP_LOGI(GATTS_TAG,
                   "ESP_GATTS_CONNECT_EVT, conn_id %d, remote %02x:%02x:%02x:%02x:%02x:%02x:", param->connect.conn_id,
                   param->connect.remote_bda[0], param->connect.remote_bda[1], param->connect.remote_bda[2],
                   param->connect.remote_bda[3], param->connect.remote_bda[4], param->connect.remote_bda[5]);
          p.conn_id = param->connect.conn_id;
          // start sent the update connection parameters to the peer device.
          esp_ble_gap_update_conn_params(&conn_params);
          break;
        }
        case ESP_GATTS_DISCONNECT_EVT:
          ESP_LOGI(GATTS_TAG, "ESP_GATTS_DISCONNECT_EVT, disconnect reason 0x%x", param->disconnect.reason);
          //                  esp_ble_gap_start_advertising(&adv_params);
          break;
        case ESP_GATTS_CONF_EVT:
          ESP_LOGI(GATTS_TAG, "ESP_GATTS_CONF_EVT, status %d attr_handle %d", param->conf.status, param->conf.handle);
          if (param->conf.status != ESP_GATT_OK) {
            esp_log_buffer_hex(GATTS_TAG, param->conf.value, param->conf.len);
          }
          break;
        case ESP_GATTS_OPEN_EVT:
        case ESP_GATTS_CANCEL_OPEN_EVT:
        case ESP_GATTS_CLOSE_EVT:
        case ESP_GATTS_LISTEN_EVT:
        case ESP_GATTS_CONGEST_EVT:
        default:
          break;
      }
    }};