#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <memory>
#include <vector>

#include "config.hpp"
#include "gpios.hpp"
#include "layout.hpp"
#include "matrix.hpp"

class keyboard {
 public:
  class key {
   public:
    enum class id { A, B, C, D };

    enum class status { RELEASED, PRESSED };
  };

  keyboard(std::shared_ptr<gpios> gpios, std::shared_ptr<config>, std::shared_ptr<matrix>, std::shared_ptr<layout>);
  std::vector<key> scan();
};

std::vector<keyboard::key> keyboard::scan() {}
keyboard::keyboard(std::shared_ptr<gpios> gpios, std::shared_ptr<config>, std::shared_ptr<matrix>,
                   std::shared_ptr<layout>) {}
#endif  // KEYBOARD_HPP
