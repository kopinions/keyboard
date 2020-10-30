#pragma once
#include "gpio.hpp"
#include "gpio_if.hpp"
#include "gpios.hpp"
#include "pin.hpp"
namespace kopinions {
class gpios_if : public gpios {
 public:
  std::shared_ptr<gpio> select(const pin::id& p) override;
  ~gpios_if() override;
};

std::shared_ptr<gpio> gpios_if::select(const pin::id& p) { return std::make_shared<gpio_if>(p); }
gpios_if::~gpios_if() = default;
}  // namespace kopinions
