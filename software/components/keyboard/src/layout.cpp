#include "keyboard/layout.hpp"

using namespace kopinions;

layout::layout(const std::map<std::pair<pin::id_t, pin::id_t>, key_t::id_t> &mapping) noexcept : m_mapping{mapping} {}

std::vector<kopinions::key_t> layout::mapping(const std::map<std::pair<pin::id_t, pin::id_t>, pin::status> &sequence) {
  std::vector<kopinions::key_t> pressed;
  for (auto [coord, status] : sequence) {
    pressed.emplace_back(kopinions::key_t{
        m_mapping[coord], status == pin::status::HIGH ? key_t::status_t::PRESSED : key_t::status_t::RELEASED});
  }
  return pressed;
}

layout::~layout() = default;