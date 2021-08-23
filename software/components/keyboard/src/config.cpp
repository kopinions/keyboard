#include "keyboard/config.hpp"

using namespace kopinions;

matrix_config::matrix_config(const std::vector<pin::id> &row, const std::vector<pin::id> &col, unsigned int bounce)
    : m_row{row}, m_col{col}, m_bounce{bounce} {}

const std::vector<pin::id> &matrix_config::row() const noexcept { return m_row; }

const std::vector<pin::id> &matrix_config::col() const noexcept { return m_col; }
unsigned int matrix_config::tolerance() const noexcept { return m_bounce; }