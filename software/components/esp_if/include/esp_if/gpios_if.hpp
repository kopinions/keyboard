#pragma once
#include <map>

#include "esp_if/gpio_if.hpp"
#include "vif/gpios.hpp"
namespace kopinions {
class gpios_if : public gpios {
 public:
  gpio* select(pin::id_t p) override;
  ~gpios_if() override;

 private:
  std::map<pin::id_t, kopinions::gpio_if*> m_gpios;
};
}  // namespace kopinions
