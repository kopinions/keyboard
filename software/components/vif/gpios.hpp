#pragma once
#include <memory>

#include "gpio.hpp"
#include "pin.hpp"
class gpios {
 public:
  virtual std::shared_ptr<gpio> select(const pin::id& p) = 0;
  virtual ~gpios() = default;
};