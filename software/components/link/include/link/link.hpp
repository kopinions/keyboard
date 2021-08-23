#pragma once
#include <memory>
#include <vector>

#include "message.hpp"
namespace kopinions {
class link_t {
 public:
  void send(std::unique_ptr<message_t>);
};
}  // namespace kopinions
