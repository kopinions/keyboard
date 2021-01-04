#include "ible/ble.hpp"

#include <nvs_flash.h>

#include <cstring>
#include <functional>
#include <map>
#include <memory>
#include <string_view>
constexpr std::string_view LOGGER_TAG = "ble";
bool bt::ble::secure = false;
std::shared_ptr<kopinions::logging::logger> bt::ble::m_logger = std::shared_ptr<kopinions::logging::logger>{};

std::shared_ptr<bt::profile_repository> bt::ble::m_profiles = std::make_shared<profile_repository>();

bt::ble::ble(std::shared_ptr<kopinions::logging::logger> lg) {
  m_logger = lg;
  // Initialize NVS.

  auto ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
  esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
  ret = esp_bt_controller_init(&bt_cfg);

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
    ESP_LOGE("GATTS_TAG", "gatts register error, error code = %x", ret);
    return;
  }

  ret = esp_ble_gap_register_callback(ble::gap_event_handler);
  if (ret) {
    ESP_LOGE("GATTS_TAG", "gap register error, error code = %x", ret);
    return;
  }

  //  esp_ble_gap_register_callback(ble::gap_event_handler);
  //
  //  esp_ble_gatts_register_callback(ble::gatts_event_handler);
}
void bt::ble::enable() {}

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
      ESP_LOGI(
          "GATTS_TAG",
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
  /* If event is register event, store the gatts_if for each profile */
  if (event == ESP_GATTS_REG_EVT) {
    if (param->reg.status == ESP_GATT_OK) {
      for (const auto& p : profiles()->all()) {
        for (auto svc : p->services()) {
          if (svc.id() == param->reg.app_id) {
            svc.registered(gatts_if);
          }
        }
      }
    } else {
      m_logger->error("Reg app failed, app_id %04x, status %d\n", param->reg.app_id, param->reg.status);
      return;
    }
  }

  for (const auto& p : profiles()->all()) {
    if (gatts_if == ESP_GATT_IF_NONE || gatts_if == p->gatts_if) {
      p->notified(event, gatts_if, param);
    }
  }
}
void bt::ble::disable() {}
void bt::ble::reset() {}
std::shared_ptr<bt::profile_repository> bt::ble::profiles() { return m_profiles; }

void bt::ble::register_profile(profile_t::id_t id, const profile_t& p) {
  m_profiles->create(id, p);

  for (auto svc : p.services()) {
    if (esp_ble_gatts_app_register(svc.id()) != ESP_OK) {
      m_logger->error("%s: %s Register App failed", LOGGER_TAG, __func__);

      if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
        m_logger->error("%s: %s blue droid status error", LOGGER_TAG, __func__);
      }
      return;
    }
  }
}

void bt::profile_repository::create(const unsigned short& id, const profile_t& p) {
  m_profiles[id] = std::make_shared<profile_t>(p);
}
std::shared_ptr<bt::profile_t> bt::profile_repository::find(const uint16_t& id) const {
  if (m_profiles.find(id) != m_profiles.end()) {
    return m_profiles.at(id);
  }

  return std::shared_ptr<profile_t>{};
}
std::vector<std::shared_ptr<bt::profile_t>> bt::profile_repository::all() const {
  std::vector<std::shared_ptr<profile_t>> values;
  for (auto p : m_profiles) {
    values.emplace_back(p.second);
  }
  return values;
}
