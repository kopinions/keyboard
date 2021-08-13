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

}  // namespace kopinions
