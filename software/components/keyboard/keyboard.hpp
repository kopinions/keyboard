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
  keyboard(const std::shared_ptr<layout>&, const std::shared_ptr<matrix>&, const std::shared_ptr<config>&);
  std::vector<key> scan();

 private:
  std::shared_ptr<matrix> m_matrix;
  std::shared_ptr<layout> m_layout;
  std::shared_ptr<config> m_config;
};

std::vector<key> keyboard::scan() { return m_layout->mapping(m_matrix->scan()); }

keyboard::keyboard(const std::shared_ptr<layout>& layout, const std::shared_ptr<matrix>& mat,
                   const std::shared_ptr<config>& conf)
    : m_matrix{mat}, m_layout{layout}, m_config{conf} {}
}  // namespace kopinions
