#pragma once
namespace kopinions {

class config {
 public:
  config() { m_debounce = 4; }
  unsigned int debounce() const noexcept { return m_debounce; }

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

matrix_config::matrix_config(const std::vector<pin::id> &row, const std::vector<pin::id> &col, unsigned int bounce)
    : m_row{row}, m_col{col}, m_bounce{bounce} {}

const std::vector<pin::id> &matrix_config::row() const noexcept { return m_row; }

const std::vector<pin::id> &matrix_config::col() const noexcept { return m_col; }
unsigned int matrix_config::tolerance() const noexcept { return m_bounce; }

}  // namespace kopinions