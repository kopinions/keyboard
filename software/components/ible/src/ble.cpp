#include "ible/ble.hpp"

#include <esp_bt_main.h>
#include <esp_bt.h>

#include <cstring>
#define LOGGER_TAG "ble"
bool bt::ble::secure = false;
kopinions::logging::logger* bt::ble::m_logger = nullptr;

bt::ble::ble(const std::string& device_name, bt::appearance_t device_appearance, kopinions::logging::logger& lg) {
  m_name = device_name;
  m_appearance = device_appearance;
  m_logger = &lg;
  esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
  esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
  auto ret = esp_bt_controller_init(&bt_cfg);

  if (ret) {
    m_logger->error("%s: %s initialize controller failed\n", LOGGER_TAG, __func__);
    return;
  }
  ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
  if (ret) {
    m_logger->error("%s: %s enable controller failed\n", LOGGER_TAG, __func__);
    return;
  }

  ret = esp_bluedroid_init();
  if (ret) {
    m_logger->error("%s: %s init bluedroid failed\n", LOGGER_TAG, __func__);
    return;
  }
  ret = esp_bluedroid_enable();
  if (ret) {
    m_logger->error("%s: %s init bluedroid failed\n", LOGGER_TAG, __func__);
    return;
  }

  ret = esp_ble_gatts_register_callback(ble::gatts_event_handler);
  if (ret) {
    m_logger->error("%s: %s gatts register error, error code = %x", LOGGER_TAG, __func__, ret);
    return;
  }

  if (auto ret = esp_ble_gap_register_callback(ble::gap_event_handler); ret != ESP_OK) {
    m_logger->error("gap register error, error code = %x", ret);
    return;
  }

  esp_err_t set_dev_name_ret = esp_ble_gap_set_device_name(m_name.data());
  if (set_dev_name_ret) {
    m_logger->error("set name failed", "set name failed");
  }

  uint8_t hidd_service_uuid128[] = {
      /* LSB <--------------------------------------------------------------------------------> MSB */
      // first uuid, 16bit, [12],[13] is the value
      0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0x12, 0x18, 0x00, 0x00,
  };

  esp_ble_adv_data_t adv_data = {
      .set_scan_rsp = false,
      .include_name = true,
      .include_txpower = true,
      .min_interval = 0x0006,  // slave connection min interval, Time = min_interval * 1.25 msec
      .max_interval = 0x0010,  // slave connection max interval, Time = max_interval * 1.25 msec
      .appearance = m_appearance,
      .manufacturer_len = 0,
      .p_manufacturer_data = nullptr,
      .service_data_len = 0,
      .p_service_data = nullptr,
      .service_uuid_len = sizeof(hidd_service_uuid128),
      .p_service_uuid = hidd_service_uuid128,
      .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),

  };

  // config adv data
  m_logger->info("config the adv data", "");
  if (auto ret = esp_ble_gap_config_adv_data(&adv_data); ret != ESP_OK) {
    m_logger->error("set name failed", "set name failed");
  }

  esp_ble_auth_req_t auth_req = ESP_LE_AUTH_BOND;  // bonding with peer device after authentication
  esp_ble_io_cap_t iocap = ESP_IO_CAP_NONE;        // set the IO capability to No output No input
  uint8_t key_size = 16;                           // the key size should be 7~16 bytes
  uint8_t init_key = ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK;
  uint8_t rsp_key = ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK;
  esp_ble_gap_set_security_param(ESP_BLE_SM_AUTHEN_REQ_MODE, &auth_req, sizeof(uint8_t));
  esp_ble_gap_set_security_param(ESP_BLE_SM_IOCAP_MODE, &iocap, sizeof(uint8_t));
  esp_ble_gap_set_security_param(ESP_BLE_SM_MAX_KEY_SIZE, &key_size, sizeof(uint8_t));
  /* If your BLE device act as a Slave, the init_key means you hope which types of key of the master should distribute
  to you, and the response key means which key you can distribute to the Master; If your BLE device act as a master, the
  response key means you hope which types of key of the slave should distribute to you,
  and the init key means which key you can distribute to the slave. */
  esp_ble_gap_set_security_param(ESP_BLE_SM_SET_INIT_KEY, &init_key, sizeof(uint8_t));
  esp_ble_gap_set_security_param(ESP_BLE_SM_SET_RSP_KEY, &rsp_key, sizeof(uint8_t));
}
void bt::ble::enable() {}

static esp_ble_adv_params_t adv_params = {
    .adv_int_min = 0x20,
    .adv_int_max = 0x40,
    .adv_type = ADV_TYPE_IND,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    //.peer_addr            =
    //.peer_addr_type       =
    .channel_map = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

void bt::ble::gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t* param) {
  m_logger->info("%s", "gap event handler");
  static uint8_t adv_config_done = 0;
  constexpr uint8_t adv_config_flag = (1 << 0);
  constexpr uint8_t scan_rsp_config_flag = (1 << 1);

  switch (event) {
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
      m_logger->info("%s", "start advertising");
      adv_config_done &= (~adv_config_flag);
      if (adv_config_done == 0) {
        esp_ble_gap_start_advertising(&adv_params);
      }
      break;
    case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
      m_logger->info("%s", "start advertising rsp");
      adv_config_done &= (~scan_rsp_config_flag);
      if (adv_config_done == 0) {
        esp_ble_gap_start_advertising(&adv_params);
      }
      break;
    case ESP_GAP_BLE_SEC_REQ_EVT:
      for (int i = 0; i < ESP_BD_ADDR_LEN; i++) {
        ble::m_logger->debug("%s: %x:", LOGGER_TAG, param->ble_security.ble_req.bd_addr[i]);
      }
      esp_ble_gap_security_rsp(param->ble_security.ble_req.bd_addr, true);
      break;
    case ESP_GAP_BLE_AUTH_CMPL_EVT:
      ble::secure = true;
      esp_bd_addr_t bd_addr;
      std::memcpy(bd_addr, param->ble_security.auth_cmpl.bd_addr, sizeof(esp_bd_addr_t));
      ble::m_logger->info("%s: remote BD_ADDR: %08x%04x", LOGGER_TAG,
                          (bd_addr[0] << 24) + (bd_addr[1] << 16) + (bd_addr[2] << 8) + bd_addr[3],
                          (bd_addr[4] << 8) + bd_addr[5]);
      ble::m_logger->info("%s: address type = %d", LOGGER_TAG, param->ble_security.auth_cmpl.addr_type);
      ble::m_logger->info("%s: pair status = %s", LOGGER_TAG,
                          param->ble_security.auth_cmpl.success ? "success" : "fail");
      if (!param->ble_security.auth_cmpl.success) {
        ble::m_logger->error("%s: fail reason = 0x%x", LOGGER_TAG, param->ble_security.auth_cmpl.fail_reason);
      }
      break;

    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
      // advertising start complete event to indicate advertising start successfully or failed
      if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
        m_logger->info("%s", "Advertising start failed\n");
      }
      m_logger->info("%s", "Advertising start done\n");
      break;
    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
      if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
        m_logger->info("%s", "Advertising stop failed\n");
      } else {
        m_logger->info("%s", "Stop adv successfully\n");
      }
      break;
    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
      m_logger->info(
          "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
          param->update_conn_params.status, param->update_conn_params.min_int, param->update_conn_params.max_int,
          param->update_conn_params.conn_int, param->update_conn_params.latency, param->update_conn_params.timeout);
      break;
    default:
      break;
  }
}

void bt::ble::gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
  m_logger->info("%s", "gatt event handler");
  static std::map<esp_gatt_if_t, application_t::id_t> gatt_ifs;
  static std::map<esp_gatt_if_t, std::shared_ptr<gatt_if_t>> gatt_ifs_;
  if (event == ESP_GATTS_REG_EVT) {
    if (param->reg.status == ESP_GATT_OK) {
      apps()->foreach ([&param, &gatts_if](auto* app) {
        if (app->id() == param->reg.app_id) {
          gatt_ifs[gatts_if] = app->id();
          gatt_ifs_[gatts_if] = std::make_shared<esp_gatt>(gatts_if);
        }
      });

    } else {
      m_logger->error("Reg app failed, app_id %04x, status %d\n", param->reg.app_id, param->reg.status);
      return;
    }
  }

  apps()
      ->of(gatt_ifs[gatts_if])
      ->notified(gatt_ifs_[gatts_if], event_t{
                                          .event = event,
                                          .param = param,
                                      });
}
void bt::ble::disable() {}
void bt::ble::reset() {}

void bt::ble::enroll(bt::application_t* app) {
  apps()->create(app);
  if (esp_ble_gatts_app_register(app->id()) != ESP_OK) {
    m_logger->error("%s: %s Register App failed", LOGGER_TAG, __func__);

    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
      m_logger->error("%s: %s blue droid status error", LOGGER_TAG, __func__);
    }
    return;
  }
}

std::shared_ptr<repository_t<bt::application_t>> bt::ble::apps() {
  static std::shared_ptr<repository_t<application_t>> m_apps;
  if (m_apps == nullptr) {
    m_apps = std::make_shared<repository_t<application_t>>();
  }
  return m_apps;
}
