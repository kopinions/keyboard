#include "keyboard/keyboard.hpp"
std::vector<kopinions::key> kopinions::keyboard::scan() { return m_layout->mapping(m_matrix->scan()); }

kopinions::keyboard::keyboard(kopinions::layout& layout, kopinions::matrix& mat, kopinions::config& conf)
    : m_matrix{&mat}, m_layout{&layout}, m_config{&conf} {}