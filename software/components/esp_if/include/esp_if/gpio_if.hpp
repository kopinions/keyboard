#pragma once
#include "vif/gpio.hpp"

namespace kopinions {

class gpio_if : public gpio {
 public:
  explicit gpio_if(const pin::id_t& id) noexcept;
  pin::status current() override;
  void option(const pin::option_t& opt) override;
  void set(pin::status target) override;
  ~gpio_if() override;

 private:
  pin::id_t m_id;
};
}  // namespace kopinions
