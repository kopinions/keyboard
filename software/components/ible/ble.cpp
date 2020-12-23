#include "ible/ble.hpp"

#include <nvs_flash.h>

#include <cstring>
#include <functional>
#include <map>
#include <memory>
#include <string_view>
constexpr std::string_view LOGGER_TAG = "ble";
bool ble::secure = false;
std::shared_ptr<kopinions::logging::logger> ble::m_logger = std::shared_ptr<kopinions::logging::logger>{};

std::shared_ptr<profile_repository> ble::m_profiles = std::make_shared<profile_repository>();

ble::ble(std::shared_ptr<kopinions::logging::logger> lg) {
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

  esp_ble_gap_register_callback(ble::gap_event_handler);

  esp_ble_gatts_register_callback(ble::gatts_event_handler);

  constexpr uint16_t HIDD_APP_ID = 0x1812;
  constexpr uint16_t BATTRAY_APP_ID = 0x180f;

  if (esp_ble_gatts_app_register(BATTRAY_APP_ID) != ESP_OK) {
    m_logger->error("%s: %s Register App failed", LOGGER_TAG, __func__);
    return;
  }
  //  if (esp_ble_gatts_app_register(HIDD_APP_ID) != ESP_OK) {
  //    m_logger->error("%s: %s Register App failed", LOGGER_TAG, __func__);
  //    return;
  //  }
  std::cout << "test" << std::endl;
  m_logger->info("%s: %s Register App failed", LOGGER_TAG, __func__);

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

void ble::gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
  /* If event is register event, store the gatts_if for each profile */
  if (event == ESP_GATTS_REG_EVT) {
    if (param->reg.status == ESP_GATT_OK) {
      auto ptr = profiles()->find(param->reg.app_id);
      if (ptr != nullptr) {
        ptr->gatts_if = gatts_if;
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
void ble::disable() {}
void ble::reset() {}
std::shared_ptr<profile_repository> ble::profiles() { return m_profiles; }

void ble::register_profile(profile::identifiable id, const profile& p) { m_profiles->create(id, p); }

void profile_repository::create(const unsigned short& id, const profile& p) {
  m_profiles[id] = std::make_shared<profile>(p);
}
std::shared_ptr<profile> profile_repository::find(const uint16_t& id) const {
  if (m_profiles.find(id) != m_profiles.end()) {
    return m_profiles.at(id);
  }

  return std::shared_ptr<profile>{};
}
std::vector<std::shared_ptr<profile>> profile_repository::all() const {
  std::vector<std::shared_ptr<profile>> values;
  for (auto p : m_profiles) {
    values.emplace_back(p.second);
  }
  return values;
}
