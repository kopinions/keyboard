#pragma once
#include <map>
#include <vector>

#include "key.hpp"
#include "vif/pin.hpp"
namespace kopinions {

class layout {
 public:
  explicit layout(const std::map<std::pair<pin::id, pin::id>, key_t::id_t> &) noexcept;
  std::vector<key_t> mapping(const std::map<std::pair<pin::id, pin::id>, pin::status> &);
  ~layout() = default;

 private:
  std::map<std::pair<pin::id, pin::id>, key_t::id_t> m_mapping;
};

}  // namespace kopinions
