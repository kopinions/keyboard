#pragma once
#include "gpios.hpp"
#include "gpio.hpp"

class gpios_if : public gpios {
 public:
  std::shared_ptr<gpio> select(const pin::id& p) override;
  ~gpios_if() override ;
};
