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

extern "C" void app_main() {
  auto sche = std::make_shared<scheduler_if<>>();

  sche->schedule("test", []() -> void {
    auto ios = std::make_shared<gpios_if>();
    auto clk = std::make_shared<clock_if>();
    auto mtx = std::make_shared<matrix>(ios, clk);
    auto lay = std::make_shared<layout>(layout_mapping);
    auto cfg = std::make_shared<config>();
    auto kbd = std::make_shared<keyboard>(lay, mtx, cfg);
    auto lg = std::make_shared<logger>(level::INFO, std::make_shared<esp_log_sink>());
    auto trans = std::make_shared<transports>();
    //    const std::shared_ptr<endpoint>& ep = std::make_shared<endpoint>();
    const std::shared_ptr<bt::ble>& b = std::make_shared<bt::ble>("Chaos", bt::appearance_t::KEYBOARD, lg);

    static const uint16_t s_primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
    static const uint16_t s_include_service_uuid = ESP_GATT_UUID_INCLUDE_SERVICE;
    static const uint16_t s_character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
    static const uint16_t s_character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;

    static const uint16_t s_bat_level_uuid = ESP_GATT_UUID_BATTERY_LEVEL;
    static const uint16_t s_bat_char_pres_format_uuid = ESP_GATT_UUID_CHAR_PRESENT_FORMAT;
    static const uint8_t s_char_prop_read_notify = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
    static uint8_t bat_level = 1;

    const bt::application_t& app = bt::application_builder_t::name("kbd")
                                       ->id(0x0001)
                                       ->profile([](bt::profile_builder_t* p) {
                                         p->service([](bt::service_builder_t* s) {
                                           s->id(1);
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
      lg->log(level::DEBUG, "%s", "xxx1111");

      auto&& res = kbd->scan();
      trans->select();

      for (auto b : res) {
        auto status = b.sts;
        lg->log(level::DEBUG, "%s", status);
      }

      vTaskDelay(100);
    }
  });
}