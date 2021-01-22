#pragma once

#include <functional>
#include <map>
#include <type_traits>

template <typename T>
class repository_t {
 public:
  using id_t = typename std::conditional_t<std::is_pointer_v<T>, std::remove_pointer_t<T>, T>::id_t;
  template <typename... Args>
  T* create(id_t id, Args... args) {
    m_entities[id] = new T{id, std::forward<Args>(args)...};
    return m_entities[id];
  };

  virtual T* of(const id_t& id) { return m_entities[id]; };

  virtual void foreach (std::function<void(T*)> f) {
    for (auto& [k, v] : m_entities) {
      f(v);
    }
  }

  virtual ~repository_t() = default;

 private:
  std::map<id_t, T*> m_entities;
};