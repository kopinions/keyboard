#pragma once
#include <cstdint>

namespace kopinions {
class time {
 public:
  explicit time(uint64_t macroseconds) noexcept : m_millis{macroseconds / 1000} {};

  [[nodiscard]] uint64_t millis() const { return m_millis; }

 private:
  uint64_t m_millis;
};

class clock {
 public:
  virtual kopinions::time now() = 0;
  virtual ~clock() = default;
};
}  // namespace kopinions
