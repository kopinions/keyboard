#ifndef GPIO_HPP
#define GPIO_HPP
#include "pin.hpp"

class gpio {
 public:
  virtual pin::status current() = 0;
  virtual void set(pin::status target) = 0;
  virtual ~gpio() = default;
};
#endif  // GPIO_HPP
