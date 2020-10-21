#ifndef PINS_HPP
#define PINS_HPP
class pin {
 public:
  enum class id {
    GPIO0, GPIO1
  };
  class opt {};
  enum class status { HIGH, LOW };
};
#endif  // PINS_HPP
