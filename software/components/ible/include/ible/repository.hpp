#pragma once

template<typename T>
class repository {
  using id_t = T::identifiable;
  std::shared_ptr<T> find(id_t);
};