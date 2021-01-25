#include "esp_if/gpios_if.hpp"

#include "pin.hpp"

std::shared_ptr<kopinions::gpio> kopinions::gpios_if::select(kopinions::pin::id p) {
  if (auto it = m_gpios.find(p); it != m_gpios.end()) {
    return it->second;
  }
  auto io = std::make_shared<gpio_if>(p);
  m_gpios[p] = io;
  return m_gpios[p];
}

kopinions::gpios_if::~gpios_if() = default;