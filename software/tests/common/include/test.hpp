#pragma once
#include <iostream>
#include <utility>

#include "matchers.hpp"
#include "vif/serializer.hpp"

void fail(const std::string& message = "") {
  std::cerr << message << std::endl;
  std::exit(-1);
}

template <typename T>
constexpr void expect_that(const T& val, const std::unique_ptr<matchers::matcher<T>>& m) {
  (void)(m->match(val) || (fail(m->message(val)), 0));
}

class test {
 public:
  explicit test(std::string name) : m_name{std::move(name)} {};
  template <typename T>
  test& operator=(const T& test) {
    try {
      if (m_name.rfind("DISABLED", 0) == 0) {
        std::cout << std::string{"test: "} << m_name << std::string{" skipped "} << std::endl;
      } else {
        test();
      }
    } catch (const std::exception& e) {
      std::cout << std::string{"test: "} << m_name << std::string{e.what()} << std::endl;
      exit(1);
    }
    return *this;
  }

 private:
  std::string m_name;
};

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wgnu-string-literal-operator-template"
#endif

// template <typename T, T... chars>
auto operator""_test(const char* str, size_t len) { return test{std::string{str, len}}; }
