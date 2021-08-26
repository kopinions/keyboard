#pragma once
#include <map>
#include <vector>

#include "key.hpp"
#include "vif/pin.hpp"
namespace kopinions {

class layout {
 public:
  explicit layout(const std::map<std::pair<pin::id_t, pin::id_t>, key_t::id_t> &) noexcept;
  virtual std::vector<key_t> mapping(const std::map<std::pair<pin::id_t, pin::id_t>, pin::status> &);
  virtual ~layout();

 private:
  std::map<std::pair<pin::id_t, pin::id_t>, key_t::id_t> m_mapping;
};

}  // namespace kopinions
