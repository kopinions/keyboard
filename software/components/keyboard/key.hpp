#pragma once
namespace kopinions {

class key {
 public:
  enum class id { A, B, C, D };

  enum class status { RELEASED, PRESSED };

  [[nodiscard]] const status& current() const { return m_status; }

 private:
  status m_status;
};
}  // namespace kopinions
