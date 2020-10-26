#include "esp_gpio.hpp"
#include "esp_gpios.hpp"

std::shared_ptr<gpio> esp_gpios::select(const pin::id& p) { return std::shared_ptr<esp_gpio>(); }
esp_gpios::~esp_gpios() {}