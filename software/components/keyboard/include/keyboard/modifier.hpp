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
    ~guardian_t() = default;
  };
  modifier_t(std::unique_ptr<modifier_t::guardian_t>,
             const std::map<kopinions::key_t::id_t, kopinions::key_t::id_t> &) noexcept;
  modifier_t(const modifier_t &) = delete;
  modifier_t(modifier_t &&) = delete;
  virtual ~modifier_t();

  virtual std::vector<kopinions::key_t> modify(const std::vector<kopinions::key_t> &);

 private:
  std::unique_ptr<modifier_t::guardian_t> m_guard;
  std::map<kopinions::key_t::id_t, kopinions::key_t::id_t> m_modifier_map;
};

class key_based_guardian_t : public modifier_t::guardian_t {
 public:
  key_based_guardian_t(kopinions::key_t::id_t );
  bool guard(const std::vector<kopinions::key_t> &) override;
  ~key_based_guardian_t() = default;

 private:
  kopinions::key_t::id_t m_kid;
};
