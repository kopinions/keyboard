#pragma once
#include <esp_gatt_defs.h>
#include <stdint.h>
namespace bt {

namespace wellknown {

constexpr bt::uuid_t DEVICE_INFO_SVC_ID = ESP_GATT_UUID_DEVICE_INFO_SVC;
constexpr bt::uuid_t BATTERY_SERVICE_SVC_ID = ESP_GATT_UUID_BATTERY_SERVICE_SVC;
constexpr bt::uuid_t HID_SVC_ID = ESP_GATT_UUID_HID_SVC;

}  // namespace wellknown
}  // namespace bt