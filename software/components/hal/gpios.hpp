#ifndef GPIOS_HPP
#define GPIOS_HPP
#include <memory>

#include "gpio.hpp"
#include "pin.hpp"
class gpios {
 public:
  virtual std::shared_ptr<gpio> open(const pin& p, const pin::opt& opt) = 0;
};
#endif  // GPIOS_HPP
