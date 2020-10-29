#pragma once
namespace kopinions {

class config {
 public:
  config() { m_debounce = 4; }
  unsigned int debounce() const noexcept { return m_debounce; }

 private:
  unsigned int m_debounce;
};

}  // namespace kopinions