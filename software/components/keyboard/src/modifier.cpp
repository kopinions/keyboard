#include "keyboard/modifier.hpp"

std::vector<kopinions::key_t> modifier_t::modify(const std::vector<kopinions::key_t> &keys) {
  if (m_guard(keys)) {
    std::vector<kopinions::key_t> modified;
    for (auto k : keys) {
      if (kopinions::key_t::status_t::PRESSED == k.sts) {
        if (auto founded = m_modifier_map.find(k.id); founded != m_modifier_map.end()) {
          auto [from, to] = *founded;
          if (to != kopinions::NONE) {
            modified.push_back({to, kopinions::key_t::status_t::PRESSED});
          }
        }
      }
    }
    return modified;
  } else {
    return keys;
  }
}
modifier_t::modifier_t(const std::function<bool(const std::vector<kopinions::key_t> &)> &guard,
                       std::map<kopinions::key_t::id_t, kopinions::key_t::id_t> &v) noexcept
    : m_guard{guard}, m_modifier_map{v} {}

modifier_t::modifier_t(const modifier_t &o) {
  m_guard = o.m_guard;
  m_v = o.m_v;
}
modifier_t::modifier_t(modifier_t &&o) {
  m_guard = std::move(m_guard);
  m_v = std::move(o.m_v);
}
modifier_t::modifier_t(std::function<bool(const std::vector<kopinions::key_t> &)> &&guard,
                       std::map<kopinions::key_t::id_t, kopinions::key_t::id_t> &&v) noexcept
    : m_guard{std::move(guard)}, m_modifier_map{std::move(v)} {}

modifier_t::modifier_t() noexcept = default;
modifier_t::~modifier_t() = default;
