#include "keyboard/keyboard.hpp"
std::vector<kopinions::key_t> kopinions::keyboard::scan() { return m_layout->mapping(m_matrix->scan()); }

kopinions::keyboard::keyboard(kopinions::layout& layout, kopinions::matrix& mat) : m_matrix{&mat}, m_layout{&layout} {}