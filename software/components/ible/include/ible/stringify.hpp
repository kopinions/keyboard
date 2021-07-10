#ifndef STRINGIFY_HPP
#define STRINGIFY_HPP
class stringify_t {
 public:
  [[nodiscard]] virtual std::string stringify() const = 0;
};
#endif  // STRINGIFY_HPP
