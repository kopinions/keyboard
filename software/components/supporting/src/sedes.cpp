#include "supporting/sedes.hpp"

std::unique_ptr<uint8_t[]> sedes_t::serialize(const std::vector<kopinions::key_t>& keys) {
  auto chars = std::unique_ptr<uint8_t[]>(new uint8_t[8]{0});
  int cursor = 2;
  for (auto k : keys) {
    if (auto it = m_modifiers.find(k.id); it != m_modifiers.end()) {
      auto [_, mask] = *it;
      if (k.sts == kopinions::key_t::status_t::PRESSED) {
        chars[0] |= mask;
      }
    } else {
      chars[cursor++] = static_cast<uint8_t>(k.id);
    }
  }
  return std::move(chars);
}
