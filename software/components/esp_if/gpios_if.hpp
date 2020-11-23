#pragma once
#include <map>

#include "vif.hpp"
namespace kopinions {
class gpios_if : public gpios {
 public:
  std::shared_ptr<gpio> select(const pin::id& p) override;
  ~gpios_if() override;

 private:
  std::map<pin::id, std::shared_ptr<gpio_if>> m_gpios;
};

std::shared_ptr<gpio> gpios_if::select(const pin::id& p) {
  if (auto it = m_gpios.find(p); it != m_gpios.end()) {
    return it->second;
  }
  auto io = std::make_shared<gpio_if>(p);
  m_gpios[p] = io;
  return m_gpios[p];
}
gpios_if::~gpios_if() = default;
}  // namespace kopinions
