#include "esp_if/gpio_if.hpp"

#include "driver/gpio.h"

kopinions::gpio_if::~gpio_if() = default;

kopinions::pin::status kopinions::gpio_if::current() {
  return gpio_get_level(static_cast<gpio_num_t>(m_id)) > 0 ? pin::status::HIGH : pin::status::LOW;
}

void kopinions::gpio_if::option(const pin::option_t& opt) {
  auto gpio_no = static_cast<gpio_num_t>(m_id);
  switch (opt.cap) {
    case pin::capability_t::WEAK:
      gpio_set_drive_capability(gpio_no, gpio_drive_cap_t::GPIO_DRIVE_CAP_0);
      break;
    case pin::capability_t::STRONGER:
      gpio_set_drive_capability(gpio_no, gpio_drive_cap_t::GPIO_DRIVE_CAP_1);
      break;
    case pin::capability_t::MEDIUM:
      gpio_set_drive_capability(gpio_no, gpio_drive_cap_t::GPIO_DRIVE_CAP_2);
      break;
    case pin::capability_t::STRONGEST:
      gpio_set_drive_capability(gpio_no, gpio_drive_cap_t::GPIO_DRIVE_CAP_3);
      break;
  }

  switch (opt.dir) {
    case pin::direction_t::INPUT:
      gpio_set_direction(gpio_no, gpio_mode_t::GPIO_MODE_INPUT);
      break;
    case pin::direction_t::OUTPUT:
      gpio_set_direction(gpio_no, gpio_mode_t::GPIO_MODE_OUTPUT);
      break;
    case pin::direction_t::BIDIRECTIONAL:
      gpio_set_direction(gpio_no, gpio_mode_t::GPIO_MODE_INPUT_OUTPUT);
      break;
    default:
      gpio_set_direction(gpio_no, gpio_mode_t::GPIO_MODE_DISABLE);
  }

  switch (opt.pull) {
    case pin::pull_mode_t::UP:
      gpio_set_pull_mode(gpio_no, gpio_pull_mode_t::GPIO_PULLUP_ONLY);
      break;
    case pin::pull_mode_t::DOWN:
      gpio_set_pull_mode(gpio_no, gpio_pull_mode_t::GPIO_PULLDOWN_ONLY);
      break;
    case pin::pull_mode_t::UPDOWN:
      gpio_set_pull_mode(gpio_no, gpio_pull_mode_t::GPIO_PULLUP_PULLDOWN);
      break;
    default:
      gpio_set_pull_mode(gpio_no, gpio_pull_mode_t::GPIO_FLOATING);
      break;
  }
}

void kopinions::gpio_if::set(kopinions::pin::status target) {
  auto gpio_no = static_cast<gpio_num_t>(m_id);
  gpio_set_level(gpio_no, target == kopinions::pin::status::HIGH ? 1 : 0);
}

kopinions::gpio_if::gpio_if(const pin::id_t& id) noexcept : m_id(id) {}
