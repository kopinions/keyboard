#pragma once
#include <iostream>
class pin {
 public:
  enum class id {
    GPIO0,
    GPIO1,
    GPIO2,
    GPIO3,
    GPIO4,
    GPIO5,
    GPIO6,
    GPIO7,
  };

  enum class mode_t {
    INPUT,
    OUTPUT,
    INOUT,
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
