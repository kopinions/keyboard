#pragma once
#include <map>
#include <vector>

#include "key.hpp"
#include "pin.hpp"
namespace kopinions {

class layout {
 public:
  explicit layout(const std::map<std::pair<pin::id, pin::id>, key::identification> &) noexcept;
  virtual std::vector<key> mapping(std::map<std::pair<pin::id, pin::id>, pin::status> &&);
  virtual ~layout() = default;

 private:
  std::map<std::pair<pin::id, pin::id>, key::identification> m_mapping;
};
layout::layout(const std::map<std::pair<pin::id, pin::id>, key::identification> &mapping) noexcept
    : m_mapping{mapping} {}

std::vector<kopinions::key> layout::mapping(std::map<std::pair<pin::id, pin::id>, pin::status> &&sequence) {
  std::vector<kopinions::key> pressed;
  for (auto [coord, status] : sequence) {
    pressed.emplace_back(
        key{.id = m_mapping[coord], .sts = status == pin::status::HIGH ? key::status::PRESSED : key::status::RELEASED});
  }
  return pressed;
}

}  // namespace kopinions
