#pragma once

class config {
 public:
  unsigned int debounce() const noexcept { return m_debounce; }

 private:
  unsigned int m_debounce;
};