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
  keyboard(layout&, matrix&);
  virtual std::vector<key_t> scan();

 private:
  matrix* m_matrix;
  layout* m_layout;
};

}  // namespace kopinions
