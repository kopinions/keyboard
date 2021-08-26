#pragma once
#include <vector>

#include "key.hpp"
#include "vif/pin.hpp"
namespace kopinions {

class matrix_config {
 public:
  matrix_config(const std::vector<pin::id> &row, const std::vector<pin::id> &col, unsigned int bounce);

 public:
  [[nodiscard]] const std::vector<pin::id> &rows() const noexcept;

  [[nodiscard]] const std::vector<pin::id> &cols() const noexcept;

  [[nodiscard]] unsigned int tolerance() const noexcept;

 private:
  std::vector<pin::id> m_row;
  std::vector<pin::id> m_col;
  unsigned int m_bounce;
};

}  // namespace kopinions