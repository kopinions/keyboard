#include "keyboard/modifier.hpp"

std::vector<kopinions::key_t> modifier_t::modify(const std::vector<kopinions::key_t> &keys) {
  if (m_guard(keys)) {
    std::vector<kopinions::key_t> modified;
    for (auto k : keys) {
      //      if (m_modifier_map.find(k) == m_modifier_map.end()) {
      //
      //      }
    }
    return keys;
  } else {
    return keys;
  }
}
modifier_t::modifier_t(std::function<bool(const std::vector<kopinions::key_t> &)> guard
                       ) noexcept
    : m_guard{std::move(guard)}{}

modifier_t::modifier_t() noexcept = default;
modifier_t::~modifier_t() = default;
