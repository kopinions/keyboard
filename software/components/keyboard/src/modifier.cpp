#include "keyboard/modifier.hpp"

std::vector<kopinions::key_t> modifier_t::modify(const std::vector<kopinions::key_t> &keys) {
  if (m_guard->guard(keys)) {
    std::vector<kopinions::key_t> modified;
    for (auto k : keys) {
      if (kopinions::key_t::status_t::PRESSED == k.sts) {
        if (auto founded = m_modifier_map.find(k.id); founded != m_modifier_map.end()) {
          auto [_, to] = *founded;
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
modifier_t::modifier_t(std::unique_ptr<guardian_t> guard,
                       const std::map<kopinions::key_t::id_t, kopinions::key_t::id_t> &v) noexcept
    : m_guard{std::move(guard)}, m_modifier_map{v} {}

modifier_t::~modifier_t() = default;

bool key_based_guardian_t::guard(const std::vector<kopinions::key_t> &keys) {
  auto founded = std::find_if(keys.begin(), keys.end(), [=](auto const &k) {
    if (k.id == m_kid && k.sts == kopinions::key_t::status_t::PRESSED) {
      return true;
    }
  });
  return founded != keys.end();
}

key_based_guardian_t::key_based_guardian_t(kopinions::key_t::id_t id) : m_kid{id} {}
