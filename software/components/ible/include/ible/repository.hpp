#pragma once

#include <functional>

template <typename T>
class repository_t {
 public:
  using id_t = typename T::id_t;

  virtual T& create(const T& t) {
    m_entities[t.id()] = t;
    return m_entities[t.id()];
  };

  virtual T& of(const id_t& id) { return m_entities[id]; };

  virtual void foreach (std::function<void(T&)> f) {
    for (auto& [k, v] : m_entities) {
      f(v);
    }
  }

  virtual ~repository_t() = default;

 private:
  std::map<id_t, T> m_entities;
};