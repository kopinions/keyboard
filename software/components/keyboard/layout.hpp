#pragma once
#include <map>

#include "pin.hpp"
class layout {
 public:
  virtual std::vector<key> mapping(std::map<std::pair<pin::id, pin::id>, pin::status> &&);
  virtual ~layout() = default;
};

std::vector<key> layout::mapping(std::map<std::pair<pin::id, pin::id>, pin::status> &&) {
  return std::vector<key>();
}
