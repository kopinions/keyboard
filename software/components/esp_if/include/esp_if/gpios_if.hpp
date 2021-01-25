#pragma once
#include <map>

#include "esp_if/gpio_if.hpp"
#include "vif.hpp"
namespace kopinions {
class gpios_if : public gpios {
 public:
  std::shared_ptr<gpio> select(pin::id p) override;
  ~gpios_if() override;

 private:
  std::map<pin::id, std::shared_ptr<kopinions::gpio_if>> m_gpios;
};
}  // namespace kopinions
