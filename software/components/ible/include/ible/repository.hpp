#pragma once

template <typename T>
class repository {
 public:
  using id_t = typename T::identifiable;
  virtual void create(const id_t&, const T&) = 0;
  virtual std::shared_ptr<T> find(const id_t&) const = 0;
  virtual ~repository() = default;
};