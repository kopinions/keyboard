#pragma once

#include <map>
#include <string>
#include <vector>

#include "keyboard/key.hpp"
class modifier_t {
 public:
  modifier_t(const std::function<bool(const std::vector<kopinions::key_t> &)> &,
             std::map<kopinions::key_t::id_t, kopinions::key_t::id_t> &) noexcept;
  modifier_t(std::function<bool(const std::vector<kopinions::key_t> &)> &&,
             std::map<kopinions::key_t::id_t, kopinions::key_t::id_t> &&) noexcept;
  modifier_t() noexcept;
  modifier_t(const modifier_t &);
  modifier_t(modifier_t &&);
  virtual ~modifier_t();

  virtual std::vector<kopinions::key_t> modify(const std::vector<kopinions::key_t> &);

 private:
  std::function<bool(const std::vector<kopinions::key_t> &)> m_guard;
  std::map<kopinions::key_t::id_t, kopinions::key_t::id_t> m_modifier_map;
};
