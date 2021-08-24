#include <nvs_flash.h>

#include <cstring>

#include "esp_if/esp_if.hpp"
#include "ible.hpp"
#include "ihid.hpp"
#include "profiles.hpp"
#include "keyboard/keyboard.hpp"
#include "keyboard/matrix.hpp"
#include "link/link_control.hpp"
#include "object.hpp"
#include "supporting/implementation.hpp"
#include "supporting/mapping.hpp"
#include "supporting/matrix_conf.hpp"
#include "supporting/sedes.hpp"

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
    auto keyboard_definition = injector.create<bt::application_builder_t*>();
    auto links = new link_control_t();

    auto b = new bt::ble("Chaos", bt::appearance_t::KEYBOARD, *lg);
    auto hid = keyboard_definition->build();
    std::cout << hid;
    b->enroll(hid);
    while (true) {
      lg->log(level::INFO, "%s %d", "xxx1111", 222);

      auto &&res = kbd->scan();
      auto link = links->select();

      auto a = hid->select(bt::selector_t<bt::characteristic_t *>::$(
          bt::ble_selector_t::profile(0x1)->service(bt::service_t::HID)->characteristic(hid_report_uuid)->nth(0)));

      lg->log(level::INFO, "%d", a->id());
      std::vector<kopinions::key_t> keys = {{kopinions::key_t::id_t::LALT, kopinions::key_t::status_t::PRESSED},
                                            {kopinions::key_t::id_t::SPACE, kopinions::key_t::status_t::PRESSED}};

      auto ptr = sedes->serialize(keys);

      auto buff = ptr->payload();
      ESP_LOGI("HID_LE_PRF_TAG", "buffer[0] = %x, buffer[1] = %x buff[2] =%x ", buff[0], buff[1], buff[2]);
      if (hid->m_gatt != nullptr) {
        lg->log(level::INFO, "send indicate to the device");

        hid->m_gatt->send_indicate(a->attributes()[1]->m_handle, HID_KEYBOARD_IN_RPT_LEN, const_cast<uint8_t *>(buff),
                                   false);
      }
      link->send(std::move(ptr));
      vTaskDelay(500 / portTICK_PERIOD_MS);
      std::vector<kopinions::key_t> keys1 = {{kopinions::key_t::id_t::LALT, kopinions::key_t::status_t::RELEASED},
                                             {kopinions::key_t::id_t::SPACE, kopinions::key_t::status_t::RELEASED}};
      auto ptr1 = sedes->serialize(keys1);
      auto buff1 = ptr1->payload();
      ESP_LOGI("HID_LE_PRF_TAG", "buffer[0] = %x, buffer[1] = %x buff[2] =%x ", buff1[0], buff1[1], buff1[2]);
      if (hid->m_gatt != nullptr) {
        lg->log(level::INFO, "send indicate to the device");

        hid->m_gatt->send_indicate(a->attributes()[1]->m_handle, HID_KEYBOARD_IN_RPT_LEN, const_cast<uint8_t *>(buff),
                                   false);
      }
      link->send(std::move(ptr1));

      for (auto b : res) {
        auto status = b.sts;
        lg->log(level::DEBUG, "%d", status);
      }

      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  });
}
