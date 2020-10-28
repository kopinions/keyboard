#pragma once
#include "pin.hpp"
class layout {
 public:
  virtual std::vector<key> mapping(const std::vector<std::pair<pin::id, pin::id>> &);
  virtual ~layout() = default;
};

std::vector<key> layout::mapping(const std::vector<std::pair<pin::id, pin::id>> &) { return std::vector<key>(); }
