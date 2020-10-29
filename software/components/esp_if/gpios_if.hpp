#pragma once
#include "gpio.hpp"
#include "gpio_if.hpp"
#include "gpios.hpp"
#include "pin.hpp"

class gpios_if : public gpios {
 public:
  std::shared_ptr<gpio> select(const pin::id& p) override;
  ~gpios_if() override;
};

std::shared_ptr<gpio> gpios_if::select(const pin::id& p) { return std::shared_ptr<gpio_if>(); }
gpios_if::~gpios_if() {}