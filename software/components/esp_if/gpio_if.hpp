#pragma once
#include "gpio.hpp"

class gpio_if : public gpio {
 public:
  pin::status current() override;
  void option(const pin::opt& opt) override;
  void set(pin::status target) override;
  ~gpio_if() override;
};