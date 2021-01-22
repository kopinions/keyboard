#include "ible/specification.hpp"

#include <esp_gap_ble_api.h>

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
    .include_txpower = true,
    .min_interval = 0x0006,  // slave connection min interval, Time = min_interval * 1.25 msec
    .max_interval = 0x0010,  // slave connection max interval, Time = max_interval * 1.25 msec
    .appearance = bt::appearance_t::KEYBOARD,
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
    .appearance = bt::appearance_t::KEYBOARD,
    .manufacturer_len = 0,        // TEST_MANUFACTURER_DATA_LEN,
    .p_manufacturer_data = NULL,  //&test_manufacturer[0],
    .service_data_len = 0,
    .p_service_data = NULL,
    .service_uuid_len = sizeof(adv_service_uuid128),
    .p_service_uuid = adv_service_uuid128,
    .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

void bt::application_t::notified(event_t e) {
  switch (e.event) {
    case ESP_GATTS_REG_EVT: {
      esp_err_t set_dev_name_ret = esp_ble_gap_set_device_name("test_esp32");
      if (set_dev_name_ret) {
        m_logger->error("set name failed", "set name failed");
        break;
      }
      // config adv data
      esp_err_t ret = esp_ble_gap_config_adv_data(&adv_data);
      if (ret) {
        m_logger->error("set name failed", "set name failed");
      }
      // config scan response data
      ret = esp_ble_gap_config_adv_data(&scan_rsp_data);
      if (ret) {
        m_logger->error("set name failed", "set name failed");
      }

//      m_profiles->foreach ([e, this](profile_t* p) { m_attributes->visit(p); });
      break;
    }
    default:
      break;
  }
}

bt::application_t::application_t(id_t id) : m_id(id) { m_profiles = std::make_shared<repository_t<bt::profile_t>>(); }

bt::application_t::application_t(const bt::application_t& o) { m_profiles = o.m_profiles; }
bt::application_t::application_t(bt::application_t&& o) { m_profiles = o.m_profiles; }

bt::application_t::~application_t() {}

void bt::profile_t::notified(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
  m_handler(*this, event, gatts_if, param);

  switch (event) {
    case ESP_GATTS_REG_EVT: {
      for (auto [id, srv] : m_services) {
        auto* vis = new attribute_visitor{std::make_shared<esp_gatt>(gatts_if)};
        srv->accept(dynamic_cast<visitor_t<std::remove_pointer_t<decltype(srv)>>*>(vis));
        delete vis;
      }
      break;
    }
    case ESP_GATTS_CREAT_ATTR_TAB_EVT: {
      for (auto& [id, srv] : m_services) {
        srv->notified(event, gatts_if, param);
      }
      break;
    }
    default:
      break;
  }
}

bt::profile_t::~profile_t() {}
