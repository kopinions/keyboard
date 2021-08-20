#include "supporting/sedes.hpp"

#include <map>

static const std::map<kopinions::key_t::id_t, std::uint8_t> modifiers = {
    {kopinions::key_t::id_t::LCTRL, 0x01}, {kopinions::key_t::id_t::LSHIFT, 0x02},
    {kopinions::key_t::id_t::LALT, 0x04},  {kopinions::key_t::id_t::LGUI, 0x08},
    {kopinions::key_t::id_t::RCTRL, 0x10}, {kopinions::key_t::id_t::RSHIFT, 0x20},
    {kopinions::key_t::id_t::RALT, 0x40},  {kopinions::key_t::id_t::RGUI, 0x80},
};

std::unique_ptr<uint8_t[]> sedes::serialize(const std::vector<kopinions::key_t>& keys) {
  auto chars = std::unique_ptr<uint8_t[]>(new uint8_t[8]);
  int cursor = 2;
  for (auto k : keys) {
    if (auto it = modifiers.find(k.id); it != modifiers.end()) {
      auto [_, mask] = *it;
      if (k.sts == kopinions::key_t::status_t::PRESSED) {
        chars[0] |= mask;
      }
    } else {
      chars[cursor++] = static_cast<uint8_t>(k.id);
    }
  }
  return std::move(chars);
}
