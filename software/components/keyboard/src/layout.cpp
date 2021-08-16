#include "keyboard/layout.hpp"

using namespace kopinions;

layout::layout(const std::map<std::pair<pin::id, pin::id>, key_t::id_t> &mapping) noexcept
    : m_mapping{mapping} {}

std::vector<kopinions::key_t> layout::mapping(const std::map<std::pair<pin::id, pin::id>, pin::status> &sequence) {
  std::vector<kopinions::key_t> pressed;
  for (auto [coord, status] : sequence) {
    pressed.emplace_back(key_t{.id = m_mapping[coord], .sts = status == pin::status::HIGH ? key_t::status::PRESSED : key_t::status::RELEASED});
  }
  return pressed;
}