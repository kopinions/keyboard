#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <memory>
#include <vector>

#include "config.hpp"
#include "key.hpp"
#include "layout.hpp"
#include "matrix.hpp"

class keyboard {
 public:
  keyboard(std::shared_ptr<layout>, std::shared_ptr<matrix>, std::shared_ptr<config>);
  std::vector<key> scan();

 private:
  std::shared_ptr<matrix> m_matrix;
  std::shared_ptr<layout> m_layout;
  std::shared_ptr<config> m_config;
};

std::vector<key> keyboard::scan() {
  auto&& result = m_matrix->scan();
  return m_layout->mapping(result);
}

keyboard::keyboard(std::shared_ptr<layout> layout, std::shared_ptr<matrix> mat, std::shared_ptr<config> conf)
    : m_matrix{std::move(mat)}, m_layout{std::move(layout)}, m_config{std::move(conf)} {}
#endif  // KEYBOARD_HPP
