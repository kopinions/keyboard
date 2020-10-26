
#include "esp_gpio.hpp"

esp_gpio::~esp_gpio() {}
pin::status esp_gpio::current() { return pin::status::HIGH; }
void esp_gpio::option(const pin::opt& opt) {}
void esp_gpio::set(pin::status target) {}
