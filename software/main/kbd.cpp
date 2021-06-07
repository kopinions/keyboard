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
void heap_caps_alloc_failed_hook(size_t requested_size, uint32_t caps, const char* function_name) {
  printf("%s was called but failed to allocate %d bytes with 0x%X capabilities. \n", function_name, requested_size,
         caps);
}

void hid_demo_task(void* pvParameters) {
  auto ios = new gpios_if;
  auto clk = new clock_if;
  auto mtx = new matrix(*ios, *clk);
  auto lay = new layout(layout_mapping);
  auto cfg = new config();
  auto kbd = new keyboard(*lay, *mtx, *cfg);
  auto sink = new esp_log_sink();
  auto lg = new logger(level::INFO, sink);
  auto trans = new transports();

  static const uint16_t s_primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
  static const uint16_t s_include_service_uuid = ESP_GATT_UUID_INCLUDE_SERVICE;
  static const uint16_t s_character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
  static const uint16_t s_character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;

  static const uint16_t s_bat_level_uuid = ESP_GATT_UUID_BATTERY_LEVEL;
  static const uint16_t s_bat_char_pres_format_uuid = ESP_GATT_UUID_CHAR_PRESENT_FORMAT;
  static const uint8_t s_char_prop_read_notify = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
  static uint8_t bat_level = 1;
  esp_err_t error = heap_caps_register_failed_alloc_callback(heap_caps_alloc_failed_hook);
  auto b = new bt::ble("Chaos", bt::appearance_t::KEYBOARD, *lg);

  const bt::application_t& app = bt::application_builder_t::name("kbd")
                                     ->id(0x0001)
                                     ->profile([](bt::profile_builder_t* p) {
                                       p->service([](bt::service_builder_t* s) {
                                         s->id(ESP_GATT_UUID_BATTERY_SERVICE_SVC);
                                         s->characteristic([](bt::characteristic_builder_t* c) {
                                           c->id(s_bat_level_uuid);
                                           c->property(bt::characteristic_t::property_t::READ);
                                           c->property(bt::characteristic_t::property_t::NOTIFY);
                                           c->permission(bt::characteristic_t::permission_t::READ);
                                           c->value(&bat_level, 1, 1);
                                         });
                                       });
                                     })
                                     ->build();
  b->enroll(app);

  while (true) {
    lg->log(level::INFO, "%s %d", "xxx1111", 222);

    auto&& res = kbd->scan();
    auto tx = trans->select();

    for (auto b : res) {
      auto status = b.sts;
      lg->log(level::DEBUG, "%d", status);
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

extern "C" void app_main() {
  auto ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  xTaskCreate(&hid_demo_task, "hid_task", 3500, NULL, 5, NULL);

  //  auto sche = new scheduler_if<>;
  //
  //  sche->schedule("test", []() -> void {
  //    auto ios = std::make_shared<gpios_if>();
  //    auto clk = std::make_shared<clock_if>();
  //    auto mtx = std::make_shared<matrix>(ios, clk);
  //    auto lay = std::make_shared<layout>(layout_mapping);
  //    auto cfg = std::make_shared<config>();
  //    auto kbd = std::make_shared<keyboard>(lay, mtx, cfg);
  //    auto lg = std::make_shared<logger>(level::INFO, std::make_shared<esp_log_sink>());
  //    auto trans = std::make_shared<transports>();
  //    //    const std::shared_ptr<endpoint>& ep = std::make_shared<endpoint>();
  //    const std::shared_ptr<bt::ble>& b = std::make_shared<bt::ble>("Chaos", bt::appearance_t::KEYBOARD, lg);
  //
  //    static const uint16_t s_primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
  //    static const uint16_t s_include_service_uuid = ESP_GATT_UUID_INCLUDE_SERVICE;
  //    static const uint16_t s_character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
  //    static const uint16_t s_character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
  //
  //    static const uint16_t s_bat_level_uuid = ESP_GATT_UUID_BATTERY_LEVEL;
  //    static const uint16_t s_bat_char_pres_format_uuid = ESP_GATT_UUID_CHAR_PRESENT_FORMAT;
  //    static const uint8_t s_char_prop_read_notify = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
  //    static uint8_t bat_level = 1;
  //
  //    //    const bt::application_t& app = bt::application_builder_t::name("kbd")
  //    //                                       ->id(0x0001)
  //    //                                       ->profile([](bt::profile_builder_t* p) {
  //    //                                         p->service([](bt::service_builder_t* s) {
  //    //                                           s->id(ESP_GATT_UUID_BATTERY_SERVICE_SVC);
  //    //                                           s->characteristic([](bt::characteristic_builder_t* c) {
  //    //                                             c->id(s_bat_level_uuid);
  //    //                                             c->property(bt::characteristic_t::property_t::READ);
  //    //                                             c->property(bt::characteristic_t::property_t::NOTIFY);
  //    //                                             c->permission(bt::characteristic_t::permission_t::READ);
  //    //                                             c->value(&bat_level, 1, 1);
  //    //                                           });
  //    //                                         });
  //    //                                       })
  //    //                                       ->build();
  //    //    b->enroll(app);
  //
  //    while (true) {
  //      lg->log(level::DEBUG, "%s %d", "xxx1111", 222);
  //
  //      auto&& res = kbd->scan();
  //      trans->select();
  //
  //      for (auto b : res) {
  //        auto status = b.sts;
  //        lg->log(level::DEBUG, "%d", status);
  //      }
  //
  //      vTaskDelay(100);
  //    }
  //  });
  //  while (true) {
  //    vTaskDelay(1000 / portTICK_PERIOD_MS);
  //  }
}