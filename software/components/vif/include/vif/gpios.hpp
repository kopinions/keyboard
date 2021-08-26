#pragma once
#include <memory>

#include "gpio.hpp"
#include "pin.hpp"

namespace kopinions {

class gpios {
 public:
  virtual gpio* select(pin::id_t p) = 0;
  virtual ~gpios() = default;
};
}  // namespace kopinions
