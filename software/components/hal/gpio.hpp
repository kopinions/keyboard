#ifndef GPIO_HPP
#define GPIO_HPP
class gpio {
 public:
  virtual status current();
  virtual void assert(status target);
};
#endif  // GPIO_HPP
