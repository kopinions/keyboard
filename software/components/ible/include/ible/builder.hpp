#pragma once

template <typename T>
class ibuilder : public std::enable_shared_from_this<ibuilder<T>> {
 public:
  virtual T build() = 0;
  virtual ~ibuilder() = default;

 protected:
  template <typename DERIVED>
  std::shared_ptr<DERIVED> shared_from(DERIVED* derived) {
    assert(this == derived);

    return std::static_pointer_cast<DERIVED>(this->shared_from_this());
  }
};