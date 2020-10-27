#pragma once
#include "gpio.hpp"
#include "pin.hpp"

class fake_gpio : public gpio {
 public:
  friend std::shared_ptr<gpio> keep(pin::status);
  pin::status current() override { return m_status; }
  void option(const pin::opt& opt) override {}
  void set(pin::status target) override {}
  ~fake_gpio() override = default;

 private:
  fake_gpio(pin::status status) : m_status{status} {}
  pin::status m_status;
};

std::shared_ptr<gpio> keep(pin::status s) { return std::shared_ptr<fake_gpio>(new fake_gpio(s)); };