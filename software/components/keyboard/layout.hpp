#pragma once
#include <map>
#include <vector>

#include "key.hpp"
#include "pin.hpp"
namespace kopinions {

class layout {
 public:
  explicit layout(const std::map<std::pair<pin::id, pin::id>, key::id> &) noexcept;
  virtual std::vector<key> mapping(std::map<std::pair<pin::id, pin::id>, pin::status> &&);
  virtual ~layout() = default;

 private:
  std::map<std::pair<pin::id, pin::id>, key::id> m_mapping;
};
layout::layout(const std::map<std::pair<pin::id, pin::id>, key::id> &mapping) noexcept : m_mapping{mapping} {}

std::vector<kopinions::key> layout::mapping(std::map<std::pair<pin::id, pin::id>, pin::status> &&) {
  return std::vector<key>();
}

}  // namespace kopinions
