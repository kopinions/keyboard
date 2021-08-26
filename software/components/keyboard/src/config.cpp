#include "keyboard/config.hpp"

using namespace kopinions;

matrix_config::matrix_config(const std::vector<pin::id_t>& row, const std::vector<pin::id_t>& col, unsigned int bounce)
    : m_row{row}, m_col{col}, m_bounce{bounce} {}

const std::vector<pin::id_t>& matrix_config::rows() const noexcept { return m_row; }

const std::vector<pin::id_t>& matrix_config::cols() const noexcept { return m_col; }

unsigned int matrix_config::tolerance() const noexcept { return m_bounce; }

matrix_config::matrix_config(matrix_config&& o) noexcept : m_col{o.m_col}, m_row{o.m_row}, m_bounce{o.m_bounce} {}

matrix_config::matrix_config(const matrix_config& o) noexcept : m_col{o.m_col}, m_row{o.m_row}, m_bounce{o.m_bounce} {}
