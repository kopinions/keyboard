#pragma once
#include <memory>
#include <string>

namespace matchers {
template <typename T>
class matcher {
 public:
  virtual bool match(const T&) const = 0;
  virtual std::string message(const T&) const = 0;
  virtual ~matcher() = default;
};

template <typename T>
class equal : public matcher<T> {
 public:
  explicit equal(const T& expected, const char* file, int location) noexcept
      : m_expected{expected}, m_file{file}, m_location{location} {}

  bool match(const T& actual) const override { return m_expected == actual; }
  std::string message(const T& actual) const override {
    return std::string{m_file} + ":" + std::to_string(m_location) +
           "\n"
           "Expected: " +
           std::to_string(m_expected) +
           "\n"
           "Actual: " +
           std::to_string(actual);
  }
  virtual ~equal()= default;;

 private:
  T m_expected;
  const char* m_file;
  int m_location;
};

template <typename T>
inline auto eq(const T& t, const char* file = __FILE__, int location = __LINE__) {
  return std::move(std::make_unique<equal<T>>(t, file, location));
}

}  // namespace matchers