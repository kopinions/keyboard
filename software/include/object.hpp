#pragma once
#include <string>
#include <vector>

class object {
 public:
  [[nodiscard]] const object* parent() const { return m_parent; }
  [[nodiscard]] std::vector<object*> children() const { return m_children; };

 private:
  std::vector<object*> m_children;
  std::string m_name;
  object* m_parent;
};