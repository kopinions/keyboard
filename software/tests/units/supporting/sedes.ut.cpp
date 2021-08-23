#include "supporting/sedes.hpp"

#include "matchers.hpp"
#include "test.hpp"

int main() {
  "should_serialize_to_0b01000000_when_ralt_pressed1"_test = [] {
    std::vector<kopinions::key_t> keys{{kopinions::key_t::id_t::RALT, kopinions::key_t::status_t::PRESSED}};
    auto *s = new sedes_t{};
    auto ptr = s->serialize(keys);
    const uint8_t *buf = ptr->payload();

    expect_that<uint8_t>(*buf, matchers::eq((uint8_t)0b01000000));
    expect_that<uint32_t>(ptr->size(), matchers::eq(8u));
    for (auto i = 1; i < 8; i++) {
      expect_that<uint8_t>(*(buf + i), matchers::eq((uint8_t)0x0));
    }
  };

  "should_serialize_to_0b01000000_when_ralt_pressed"_test = [] {
    std::vector<kopinions::key_t> keys{{kopinions::key_t::id_t::RALT, kopinions::key_t::status_t::PRESSED}};
    auto *s = new sedes_t{};
    auto ptr = s->serialize(keys);
    const uint8_t *buf = ptr->payload();

    expect_that<uint8_t>(*buf, matchers::eq((uint8_t)0b01000000));
    for (auto i = 1; i < 8; i++) {
      expect_that<uint8_t>(*(buf + i), matchers::eq((uint8_t)0x0));
    }
  };

  "should_serialize_to_0b01000010_when_ralt_lshift_pressed"_test = [] {
    std::vector<kopinions::key_t> keys{
        {kopinions::key_t::id_t::RALT, kopinions::key_t::status_t::PRESSED},
        {kopinions::key_t::id_t::LSHIFT, kopinions::key_t::status_t::PRESSED},
    };
    auto *s = new sedes_t{};
    auto ptr = s->serialize(keys);
    const uint8_t *buf = ptr->payload();

    expect_that<uint8_t>(*buf, matchers::eq((uint8_t)0b01000010));
    for (auto i = 1; i < 8; i++) {
      expect_that<uint8_t>(*(buf + i), matchers::eq((uint8_t)0x0));
    }
  };

  "should_serialize_to_0x00_when_ralt_lshift_released"_test = [] {
    std::vector<kopinions::key_t> keys{
        {kopinions::key_t::id_t::RALT, kopinions::key_t::status_t::RELEASED},
        {kopinions::key_t::id_t::LSHIFT, kopinions::key_t::status_t::RELEASED},
    };
    auto *s = new sedes_t{};
    auto ptr = s->serialize(keys);
    const uint8_t *buf = ptr->payload();

    expect_that<uint8_t>(*buf, matchers::eq((uint8_t)0x00));
    for (auto i = 1; i < 8; i++) {
      expect_that<uint8_t>(*(buf + i), matchers::eq((uint8_t)0x0));
    }
  };

  "should_serialize_the_third_byte_to_0x04_when_key_is_a_pressed"_test = [] {
    std::vector<kopinions::key_t> keys{
        {kopinions::key_t::id_t::A, kopinions::key_t::status_t::PRESSED},
    };
    auto *s = new sedes_t{};
    auto ptr = s->serialize(keys);
    const uint8_t *buf = ptr->payload();

    expect_that<uint8_t>(*(buf + 2), matchers::eq((uint8_t)0x04));
    for (auto i = 3; i < 8; i++) {
      expect_that<uint8_t>(*(buf + i), matchers::eq((uint8_t)0x0));
    }
  };
  "should_serialize_the_third_byte_to_0x00_when_key_is_a_released"_test = [] {
    std::vector<kopinions::key_t> keys{
        {kopinions::key_t::id_t::A, kopinions::key_t::status_t::RELEASED},
    };
    auto *s = new sedes_t{};
    auto ptr = s->serialize(keys);
    const uint8_t *buf = ptr->payload();

    for (auto i = 2; i < 8; i++) {
      expect_that<uint8_t>(*(buf + i), matchers::eq((uint8_t)0x0));
    }
  };
}
