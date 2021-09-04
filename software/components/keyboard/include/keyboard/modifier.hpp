#pragma once

#include <map>
#include <string>
#include <vector>

#include "keyboard/key.hpp"
class modifier_t {
 public:
  class guardian_t {
   public:
    virtual bool guard(const std::vector<kopinions::key_t> &) = 0;
    virtual ~guardian_t() = default;
  };
  modifier_t(std::unique_ptr<modifier_t::guardian_t>,
             const std::map<kopinions::key_t::id_t, kopinions::key_t::id_t> &) noexcept;
  modifier_t(const modifier_t &) noexcept;
  modifier_t(modifier_t &&) noexcept;
  virtual ~modifier_t();

  virtual std::vector<kopinions::key_t> modify(const std::vector<kopinions::key_t> &);

 private:
  std::unique_ptr<modifier_t::guardian_t> m_guard;
  std::map<kopinions::key_t::id_t, kopinions::key_t::id_t> m_modifier_map;
};

class modifiers_t {
 public:
  modifiers_t(std::initializer_list<modifier_t>);

  virtual std::vector<kopinions::key_t> modifiers(const std::vector<kopinions::key_t> &);

 private:
  std::vector<std::unique_ptr<modifier_t>> m_modifiers;
};

class key_based_guardian_t : public modifier_t::guardian_t {
 public:
  key_based_guardian_t(kopinions::key_t::id_t);
  key_based_guardian_t(key_based_guardian_t &&);
  key_based_guardian_t(const key_based_guardian_t &);
  bool guard(const std::vector<kopinions::key_t> &) override;
  ~key_based_guardian_t() override = default;

 private:
  kopinions::key_t::id_t m_kid;
};
