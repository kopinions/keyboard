#pragma once
#include "gpios.hpp"

class esp_gpios : public gpios {
 public:
  std::shared_ptr<gpio> select(const pin::id& p) override;
  ~esp_gpios() override;
};
