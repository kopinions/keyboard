#ifndef IGPIO_HPP
#define IGPIO_HPP
class gpio_manager {
 public:
  virtual gpio open(const pin& p, const pin::opt& opt) = 0;
};
#endif  // IGPIO_HPP
