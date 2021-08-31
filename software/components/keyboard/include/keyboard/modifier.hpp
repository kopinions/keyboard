#pragma once

#include <map>
#include <vector>

#include "keyboard/key.hpp"
class modifier_t {
 public:
  modifier_t(const std::function<bool(const std::vector<kopinions::key_t> &)> &) noexcept;
  modifier_t(std::function<bool(const std::vector<kopinions::key_t> &)> &&) noexcept;
  modifier_t() noexcept;
  virtual ~modifier_t();

  virtual std::vector<kopinions::key_t> modify(const std::vector<kopinions::key_t> &);

 private:
  std::function<bool(const std::vector<kopinions::key_t>)> m_guard;
  //  std::map<kopinions::key_t, kopinions::key_t> m_modifier_map;
};
