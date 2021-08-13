#pragma once
#include "key.hpp"
#include "vif.hpp"
namespace kopinions {

class config {
 public:
  config() { m_debounce = 4; }
  unsigned int debounce() const noexcept;

 private:
  unsigned int m_debounce;
};

class matrix_config {
 public:
  matrix_config(const std::vector<pin::id> &row, const std::vector<pin::id> &col, unsigned int bounce);

 public:
  [[nodiscard]] const std::vector<pin::id> &row() const noexcept;

  [[nodiscard]] const std::vector<pin::id> &col() const noexcept;

  [[nodiscard]] unsigned int tolerance() const noexcept;

 private:
  std::vector<pin::id> m_row;
  std::vector<pin::id> m_col;
  unsigned int m_bounce;
};

}  // namespace kopinions