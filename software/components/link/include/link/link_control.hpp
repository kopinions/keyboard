#pragma once
#include <optional>
#include "link.hpp"
namespace kopinions {

class link_control_t {
 public:
  virtual std::optional<link_t> select();
};

}  // namespace kopinions
