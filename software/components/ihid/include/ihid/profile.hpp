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
            svc.notified(event, gatts_if, param);
          }
          break;
        }
      }
    }};
}  // namespace hid