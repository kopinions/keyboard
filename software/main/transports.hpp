#pragma once
namespace kopinions {
class transport {

};
class transports {
 public:
  std::optional<transport> select() { return std::nullopt; };
};
}  // namespace kopinions
