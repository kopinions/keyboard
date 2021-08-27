#pragma once
#include "pin.hpp"

namespace kopinions {
class gpio {
 public:
  virtual pin::status current() = 0;
  virtual void option(const pin::option_t&) = 0;
  virtual void set(pin::status target) = 0;
  virtual ~gpio() = default;
};
};  // namespace kopinions
