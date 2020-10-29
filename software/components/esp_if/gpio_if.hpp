#pragma once
#include "gpio.hpp"
namespace kopinions {

class gpio_if : public gpio {
 public:
  pin::status current() override;
  void option(const pin::opt& opt) override;
  void set(pin::status target) override;
  ~gpio_if() override;
};

gpio_if::~gpio_if() {}
pin::status gpio_if::current() { return pin::status::HIGH; }
void gpio_if::option(const pin::opt& opt) {}
void gpio_if::set(pin::status target) {}
}  // namespace kopinions
