#include "supporting/sedes.hpp"

#include "matchers.hpp"
#include "test.hpp"

int main() {
  "should_serialize_to_0b01000000_when_ralt_pressed"_test = [] {
    std::vector<kopinions::key_t> keys{{kopinions::key_t::id_t::RALT, kopinions::key_t::status_t::PRESSED}};
    auto *s = new sedes{};
    const std::unique_ptr<uint8_t[]> &ptr = s->serialize(keys);
    uint8_t *buf = ptr.get();

    expect_that<uint8_t>(*buf, matchers::eq((uint8_t)0b01000000));
  };

  "should_serialize_to_0b01000010_when_ralt_lshift_pressed"_test = [] {
    std::vector<kopinions::key_t> keys{
        {kopinions::key_t::id_t::RALT, kopinions::key_t::status_t::PRESSED},
        {kopinions::key_t::id_t::LSHIFT, kopinions::key_t::status_t::PRESSED},
    };
    auto *s = new sedes{};
    const std::unique_ptr<uint8_t[]> &ptr = s->serialize(keys);
    uint8_t *buf = ptr.get();

    expect_that<uint8_t>(*buf, matchers::eq((uint8_t)0b01000010));
  };
}
