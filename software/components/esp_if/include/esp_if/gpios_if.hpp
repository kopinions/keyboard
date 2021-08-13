#pragma once
#include <map>

#include "esp_if/gpio_if.hpp"
#include "vif/gpios.hpp"
namespace kopinions {
class gpios_if : public gpios {
 public:
  gpio* select(pin::id p) override;
  ~gpios_if() override;

 private:
  std::map<pin::id, kopinions::gpio_if*> m_gpios;
};
}  // namespace kopinions
