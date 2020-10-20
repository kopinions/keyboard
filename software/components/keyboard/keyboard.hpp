#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <memory>
#include <vector>

#include "gpios.hpp"

class keyboard {
 public:
  class key {
   public:
    enum class id { A, B, C, D };

    enum class status { RELEASED, PRESSED };
  };
  keyboard(std::shared_ptr<gpios> gpios);
  std::vector<key> scan();
};

std::vector<keyboard::key> keyboard::scan() {}
keyboard::keyboard(std::shared_ptr<gpios> gpios) {}
#endif  // KEYBOARD_HPP
