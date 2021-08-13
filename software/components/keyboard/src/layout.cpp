#include "keyboard/layout.hpp"

using namespace kopinions;

layout::layout(const std::map<std::pair<pin::id, pin::id>, key::identification> &mapping) noexcept
    : m_mapping{mapping} {}

std::vector<kopinions::key> layout::mapping(const std::map<std::pair<pin::id, pin::id>, pin::status> &sequence) {
  std::vector<kopinions::key> pressed;
  for (auto [coord, status] : sequence) {
    pressed.emplace_back(
        key{.id = m_mapping[coord], .sts = status == pin::status::HIGH ? key::status::PRESSED : key::status::RELEASED});
  }
  return pressed;
}