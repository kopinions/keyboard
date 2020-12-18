#include "ible/ble.hpp"

#include <cstring>
#include <string_view>
constexpr std::string_view LOGGER_TAG = "ble";
constexpr uint16_t HIDD_APP_ID = 0x1812;
constexpr uint16_t BATTRAY_APP_ID = 0x180f;

/** @brief Advertising parameters */
static esp_ble_adv_params_t hidd_adv_params = {
    .adv_int_min = 0x20,
    .adv_int_max = 0x30,
    .adv_type = ADV_TYPE_IND,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    //.peer_addr            =
    //.peer_addr_type       =
    .channel_map = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

ble::ble(std::shared_ptr<kopinions::logging::logger> lg) {
  m_logger = lg;
  esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
  esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
  auto ret = esp_bt_controller_init(&bt_cfg);
  if (ret) {
    m_logger->error("%s: %s initialize controller failed\n", LOGGER_TAG, __func__);
    //    return ESP_FAIL;
  }

  ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
  if (ret) {
    m_logger->error("%s: %s enable controller failed\n", LOGGER_TAG, __func__);
    //    return ESP_FAIL;
  }

  ret = esp_bluedroid_init();
  if (ret) {
    m_logger->error("%s: %s init bluedroid failed\n", LOGGER_TAG, __func__);
    //    return ESP_FAIL;
  }

  ret = esp_bluedroid_enable();
  if (ret) {
    m_logger->error("%s: %s init bluedroid failed\n", LOGGER_TAG, __func__);
    //    return ESP_FAIL;
  }

  esp_ble_gap_register_callback(ble::gap_event_handler);

  esp_ble_gatts_register_callback(ble::gatts_event_handler);
  //  if (!hidd_le_env.enabled) {
  //    memset(&hidd_le_env, 0, sizeof(hidd_le_env_t));
  //    hidd_le_env.enabled = true;
  //  }
  //
  //  hidd_le_env.hidd_cb = hidd_event_callback;
  //  if (hidd_register_cb() != ESP_OK) {
  //    ESP_LOGE(LOG_TAG, "register CB failed");
  //    return ESP_FAIL;
  //  }

  if (esp_ble_gatts_app_register(BATTRAY_APP_ID) != ESP_OK) {
    m_logger->error("%s: %s Register App failed", LOGGER_TAG, __func__);
    //    return ESP_FAIL;
  }
  if (esp_ble_gatts_app_register(HIDD_APP_ID) != ESP_OK) {
    m_logger->error("%s: %s Register App failed", LOGGER_TAG, __func__);
    //    return ESP_FAIL;
  }

  /* set the security iocap & auth_req & key size & init key response key parameters to the stack*/
  esp_ble_auth_req_t auth_req = ESP_LE_AUTH_BOND;  // bonding with peer device after authentication
  esp_ble_io_cap_t iocap = ESP_IO_CAP_NONE;        // set the IO capability to No output No input
  uint8_t key_size = 16;                           // the key size should be 7~16 bytes
  uint8_t init_key = ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK;
  uint8_t rsp_key = ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK;
  esp_ble_gap_set_security_param(ESP_BLE_SM_AUTHEN_REQ_MODE, &auth_req, sizeof(uint8_t));
  esp_ble_gap_set_security_param(ESP_BLE_SM_IOCAP_MODE, &iocap, sizeof(uint8_t));
  esp_ble_gap_set_security_param(ESP_BLE_SM_MAX_KEY_SIZE, &key_size, sizeof(uint8_t));
  /* If your BLE device act as a Slave, the init_key means you hope which types of key of the master should distribut to
   you, and the response key means which key you can distribut to the Master; If your BLE device act as a master, the
   response key means you hope which types of key of the slave should distribut to you,
   and the init key means which key you can distribut to the slave. */
  esp_ble_gap_set_security_param(ESP_BLE_SM_SET_INIT_KEY, &init_key, sizeof(uint8_t));
  esp_ble_gap_set_security_param(ESP_BLE_SM_SET_RSP_KEY, &rsp_key, sizeof(uint8_t));

  //  return ESP_OK;
}
void ble::enable() {}

void ble::gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t* param) {
  switch (event) {
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
      esp_ble_gap_start_advertising(&hidd_adv_params);
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
    default:
      break;
  }
}

#define PROFILE_NUM 1
#define PROFILE_APP_IDX 0

struct gatts_profile_inst {
  esp_gatts_cb_t gatts_cb;
  uint16_t gatts_if;
  uint16_t app_id;
  uint16_t conn_id;
};

static struct gatts_profile_inst heart_rate_profile_tab[PROFILE_NUM] = {
    [PROFILE_APP_IDX] =
        {
            .gatts_cb = esp_hidd_prf_cb_hdl,
            .gatts_if = ESP_GATT_IF_NONE, /* Not get the gatt_if, so initial is ESP_GATT_IF_NONE */
        },

};


void esp_hidd_prf_cb_hdl(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if,
                         esp_ble_gatts_cb_param_t *param) {

  switch (event) {

    case ESP_GATTS_REG_EVT: {
      esp_ble_gap_config_local_icon(ESP_BLE_APPEARANCE_GENERIC_HID);
      esp_hidd_cb_param_t hidd_param;
      hidd_param.init_finish.state = param->reg.status;
      if (param->reg.app_id == HIDD_APP_ID) {
        hidd_le_env.gatt_if = gatts_if;
        if (hidd_le_env.hidd_cb != NULL) {
          (hidd_le_env.hidd_cb)(ESP_HIDD_EVENT_REG_FINISH, &hidd_param);
          hidd_le_create_service(hidd_le_env.gatt_if);
        }
      }
      if (param->reg.app_id == BATTRAY_APP_ID) {
        hidd_param.init_finish.gatts_if = gatts_if;
        if (hidd_le_env.hidd_cb != NULL) {
          (hidd_le_env.hidd_cb)(ESP_BAT_EVENT_REG, &hidd_param);
        }

      }

      break;
    }
    case ESP_GATTS_CONF_EVT:
      break;

    case ESP_GATTS_CREATE_EVT:
      break;

    case ESP_GATTS_CONNECT_EVT: {
      esp_hidd_cb_param_t cb_param = { 0 };
      ESP_LOGI(HID_LE_PRF_TAG, "HID connection establish, conn_id = %x",
               param->connect.conn_id);

      memcpy(cb_param.connect.remote_bda, param->connect.remote_bda,
             sizeof(esp_bd_addr_t));
      cb_param.connect.conn_id = param->connect.conn_id;
      hidd_clcb_alloc(param->connect.conn_id, param->connect.remote_bda);
      esp_ble_set_encryption(param->connect.remote_bda,
                             ESP_BLE_SEC_ENCRYPT_NO_MITM);
      if (hidd_le_env.hidd_cb != NULL) {
        (hidd_le_env.hidd_cb)(ESP_HIDD_EVENT_BLE_CONNECT, &cb_param);

      }



      break;
    }

    case ESP_GATTS_DISCONNECT_EVT: {
      if (hidd_le_env.hidd_cb != NULL) {
        (hidd_le_env.hidd_cb)(ESP_HIDD_EVENT_BLE_DISCONNECT, NULL);
      }
      hidd_clcb_dealloc(param->disconnect.conn_id);
      break;
    }
    case ESP_GATTS_CLOSE_EVT:
      break;
    case ESP_GATTS_WRITE_EVT: {

      break;
    }
    case ESP_GATTS_CREAT_ATTR_TAB_EVT: {
      if (param->add_attr_tab.num_handle == BAS_IDX_NB
          && param->add_attr_tab.svc_uuid.uuid.uuid16
             == ESP_GATT_UUID_BATTERY_SERVICE_SVC
          && param->add_attr_tab.status == ESP_GATT_OK) {
        incl_svc.start_hdl = param->add_attr_tab.handles[BAS_IDX_SVC];
        incl_svc.end_hdl = incl_svc.start_hdl + BAS_IDX_NB - 1;
        ESP_LOGI(HID_LE_PRF_TAG,
                 "%s(), start added the hid service to the stack database. incl_handle = %d",
                 __func__, incl_svc.start_hdl);
        esp_ble_gatts_create_attr_tab(hidd_le_gatt_db, gatts_if,
                                      HIDD_LE_IDX_NB, 0);
      }
      if (param->add_attr_tab.num_handle == HIDD_LE_IDX_NB
          && param->add_attr_tab.status == ESP_GATT_OK) {
        memcpy(hidd_le_env.hidd_inst.att_tbl, param->add_attr_tab.handles,
               HIDD_LE_IDX_NB * sizeof(uint16_t));
        ESP_LOGI(HID_LE_PRF_TAG, "hid svc handle = %x",
                 hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_SVC]);
        hid_add_id_tbl();
        esp_ble_gatts_start_service(
            hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_SVC]);
      } else {
        esp_ble_gatts_start_service(param->add_attr_tab.handles[0]);
      }
      break;
    }

    default:
      break;
  }
}

void ble::gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
  /* If event is register event, store the gatts_if for each profile */
  if (event == ESP_GATTS_REG_EVT) {
    if (param->reg.status == ESP_GATT_OK) {
      heart_rate_profile_tab[PROFILE_APP_IDX].gatts_if = gatts_if;

    } else {
      ESP_LOGI(HID_LE_PRF_TAG, "Reg app failed, app_id %04x, status %d\n", param->reg.app_id, param->reg.status);
      return;
    }
  }

  do {
    int idx;
    for (idx = 0; idx < PROFILE_NUM; idx++) {
      if (gatts_if == ESP_GATT_IF_NONE || /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile
                                             cb function */
          gatts_if == heart_rate_profile_tab[idx].gatts_if) {
        if (heart_rate_profile_tab[idx].gatts_cb) {
          heart_rate_profile_tab[idx].gatts_cb(event, gatts_if, param);
        }
      }
    }
  } while (0);
}
void ble::disable() {}
void ble::reset() {}
