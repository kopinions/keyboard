#pragma once

#include <map>
#include <memory>
#include <vector>

#include "keyboard/key.hpp"

class sedes_t {
 public:
  std::unique_ptr<uint8_t[]> serialize(const std::vector<kopinions::key_t> &);

 private:
  const std::map<kopinions::key_t::id_t, std::uint8_t> m_modifiers = {
      {kopinions::key_t::id_t::LCTRL, 0x01}, {kopinions::key_t::id_t::LSHIFT, 0x02},
      {kopinions::key_t::id_t::LALT, 0x04},  {kopinions::key_t::id_t::LGUI, 0x08},
      {kopinions::key_t::id_t::RCTRL, 0x10}, {kopinions::key_t::id_t::RSHIFT, 0x20},
      {kopinions::key_t::id_t::RALT, 0x40},  {kopinions::key_t::id_t::RGUI, 0x80},
  };
};
