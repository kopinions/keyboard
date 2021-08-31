#pragma once
#include <vector>

#include "key.hpp"
#include "vif/pin.hpp"
namespace kopinions {

class matrix_config {
 public:
  matrix_config(const std::vector<pin::id_t>& row, const std::vector<pin::id_t>& col, unsigned int bounce);
  matrix_config(std::vector<pin::id_t>&& row, std::vector<pin::id_t>&& col, unsigned int bounce);
  matrix_config(const matrix_config&) noexcept;
  matrix_config(matrix_config&&) noexcept;
  matrix_config() noexcept;

 public:
  [[nodiscard]] const std::vector<pin::id_t>& rows() const noexcept;

  [[nodiscard]] const std::vector<pin::id_t>& cols() const noexcept;

  [[nodiscard]] unsigned int tolerance() const noexcept;

 private:
  std::vector<pin::id_t> m_row;
  std::vector<pin::id_t> m_col;
  unsigned int m_bounce;
};

}  // namespace kopinions