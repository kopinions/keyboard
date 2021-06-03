#pragma once
#include <memory>
#include <vector>

#include "config.hpp"
#include "key.hpp"
#include "layout.hpp"
#include "matrix.hpp"
namespace kopinions {
class keyboard {
 public:
  keyboard(layout&, matrix&, config&);
  std::vector<key> scan();

 private:
  matrix* m_matrix;
  layout* m_layout;
  config* m_config;
};

std::vector<key> keyboard::scan() { return m_layout->mapping(m_matrix->scan()); }

keyboard::keyboard(layout& layout, matrix& mat, config& conf) : m_matrix{&mat}, m_layout{&layout}, m_config{&conf} {}
}  // namespace kopinions
