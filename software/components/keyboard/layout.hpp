#pragma once
class layout {
 public:
  virtual std::vector<key> mapping(const std::vector<std::pair<uint16_t, uint16_t>> &);
  virtual ~layout() = default;
};

std::vector<key> layout::mapping(const std::vector<std::pair<uint16_t, uint16_t>> &) { return std::vector<key>(); }
