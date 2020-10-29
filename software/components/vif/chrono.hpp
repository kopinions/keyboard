#pragma once
#include <cstdint>

namespace kopinions {
class time {
 public:
  [[nodiscard]] uint64_t millis() const { return m_millis; }
  explicit time(uint64_t millis) noexcept : m_millis{millis} {};

 private:
  uint64_t m_millis;
};

class clock {
 public:
  virtual kopinions::time now() = 0;
  virtual ~clock() = default;
};
}  // namespace kopinions
