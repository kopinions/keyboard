#pragma once
#include <string>

class dumpable_t {
 public:
  dumpable_t() = default;
  explicit dumpable_t(std::string indent) : m_indent{std::move(indent)} {}
  virtual void dump(std::ostream& o) const = 0;

 protected:
  [[nodiscard]] virtual std::string indent() const { return m_indent; };

 private:
  std::string m_indent;
};

template <typename T>
std::ostream& operator<<(std::ostream& o, T* src) {
  src->dump(o);
  return o;
}
