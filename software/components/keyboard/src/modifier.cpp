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

modifier_t::modifier_t(const modifier_t &o) noexcept : m_modifier_map{std::move(o.m_modifier_map)} {
  key_based_guardian_t *pGuardian = dynamic_cast<key_based_guardian_t *>(o.m_guard.get());
  m_guard = std::unique_ptr<modifier_t::guardian_t>(new key_based_guardian_t{*pGuardian});
}

modifier_t::modifier_t(modifier_t &&o) noexcept
    : m_guard(std::move(o.m_guard)), m_modifier_map{std::move(o.m_modifier_map)} {}

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
key_based_guardian_t::key_based_guardian_t(key_based_guardian_t &&o) : m_kid{o.m_kid} {}
key_based_guardian_t::key_based_guardian_t(const key_based_guardian_t &o) : m_kid{o.m_kid} {}

std::vector<kopinions::key_t> modifiers_t::modifiers(const std::vector<kopinions::key_t> &keys) {
  std::vector<kopinions::key_t> result;
  for (auto &modifier : m_modifiers) {
    result = modifier->modify(result.empty() ? keys : result);
  }
  return result;
}

modifiers_t::modifiers_t(std::initializer_list<modifier_t> modifies) {
  for (auto &modifier : modifies) {
    m_modifiers.emplace_back(std::make_unique<modifier_t>(std::move(modifier)));
  }
}
