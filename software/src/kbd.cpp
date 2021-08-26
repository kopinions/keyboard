#include <nvs_flash.h>

#include "esp_if/esp_if.hpp"
#include "ible.hpp"
#include "keyboard/keyboard.hpp"
#include "link/link_control.hpp"
#include "profiles.hpp"
#include "supporting/implementation.hpp"
#include "supporting/mapping.hpp"
#include "supporting/matrix_conf.hpp"

using namespace kopinions;
using namespace kopinions::logging;

extern "C" void app_main() {
  auto ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  static auto injector = di ::make_injector<>(mapping(), conf(), implementation(), definitions());
  auto sche = injector.create<std::shared_ptr<kopinions::scheduler<>>>();

  sche->schedule("test", []() -> void {
    auto kbd = injector.create<std::shared_ptr<kopinions::keyboard>>();
    auto lg = injector.create<std::shared_ptr<kopinions::logging::logger>>();
    auto sedes = injector.create<std::shared_ptr<kopinions::sedes_t>>();
    auto keyboard_definition = injector.create<bt::application_builder_t &>();
    auto links = new link_control_t();

    auto b = new bt::ble("Chaos", bt::appearance_t::KEYBOARD, *lg);
    auto hid = keyboard_definition.build();
    std::cout << hid;
    b->enroll(hid);
    auto a = hid->select(bt::selector_t<bt::characteristic_t *>::$(
        bt::ble_selector_t::profile(0x1)->service(bt::service_t::HID)->characteristic(hid_report_uuid)->nth(0)));
    while (true) {
      auto &&pressed_keys = kbd->scan();
      auto link = links->select();
      auto report = sedes->serialize(pressed_keys);
      auto pressed = report->payload();
      lg->info("pressed[0] = %x, pressed[1] = %x pressed[2] = %x ", pressed[0], pressed[1], pressed[2]);
      if (hid->m_gatt != nullptr) {
        lg->log(level::INFO, "send indicate to the device");

        hid->m_gatt->send_indicate(a->attributes()[1]->m_handle, HID_KEYBOARD_IN_RPT_LEN,
                                   const_cast<uint8_t *>(pressed), false);
      }
      link->send(std::move(report));
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
  });
}
