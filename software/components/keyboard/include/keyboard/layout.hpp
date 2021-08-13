#pragma once
#include <map>
#include <vector>

#include "vif/pin.hpp"
#include "key.hpp"
namespace kopinions {

class layout {
 public:
  explicit layout(const std::map<std::pair<pin::id, pin::id>, key::identification> &) noexcept;
  std::vector<key> mapping(const std::map<std::pair<pin::id, pin::id>, pin::status> &);
  ~layout() = default;

 private:
  std::map<std::pair<pin::id, pin::id>, key::identification> m_mapping;
};

}  // namespace kopinions
