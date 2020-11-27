#pragma once
#include <cstdint>

namespace kopinions {
class pin {
 public:
  enum id : uint8_t {
    IO0,
    IO1,
    IO2,
    IO3,
    IO4,
    IO5,
    IO6,
    IO7,
    IO8,
    IO9,
    IO10,
    IO11,
    IO12,
    IO13,
    IO14,
    IO15,
    IO16,
    IO17,
    IO18,
    IO19,
    IO20,
    IO21,
    IO22,
    IO23,
    IO24,
    IO25,
    IO26,
    IO27,
    IO28,
    IO29,
    IO30,
    IO31,
    IO32,
    IO33,
    IO34,
    IO35,
    IO36,
    IO37,
    IO38,
    IO39,
    IO40
  };

  enum class mode_t {
    DISABLED,
    INPUT,
    OUTPUT,
    BIDIRECTIONAL,
  };

  enum class capability_t {
    WEAK,
    STRONGER,
    MEDIUM,
    STRONGEST,
  };
  struct opt {
    mode_t mode;
    capability_t cap;
  };
  enum class status { HIGH, LOW };

 private:
  id m_id;
};
}  // namespace kopinions
