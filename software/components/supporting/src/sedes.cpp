#include "supporting/sedes.hpp"

constexpr kopinions::key_t::id_t specials[8] = {
    kopinions::key_t::id_t::LCTRL, kopinions::key_t::id_t::LSHIFT, kopinions::key_t::id_t::LALT,
    kopinions::key_t::id_t::LGUI,  kopinions::key_t::id_t::RCTRL,  kopinions::key_t::id_t::RSHIFT,
    kopinions::key_t::id_t::RALT,  kopinions::key_t::id_t::RGUI,
};

std::unique_ptr<char[]> sedes::serialize(const std::vector<kopinions::key_t> & keys) {
  auto chars = std::unique_ptr<char[]>(new char[8]);

  for (auto k : keys) {
    uint8_t mask{0};
    for (auto i = 0u; i < 8; i++) {
      if (specials[i] == k.id && k.sts == kopinions::key_t::status_t::PRESSED) {
        mask |= (1 << i);
      }
    }
  }
  return chars;
}
