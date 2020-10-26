#pragma once
#include "gpio.hpp"

class esp_gpio : public gpio {
 public:
  pin::status current() override;
  void option(const pin::opt& opt) override;
  void set(pin::status target) override;
  ~esp_gpio() override;
};