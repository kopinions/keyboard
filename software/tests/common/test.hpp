#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <memory>

#include "matchers.hpp"

void fail(const std::string& message = "") {
  std::cerr << message << std::endl;
  std::exit(-1);
}

template <typename T>
constexpr void expect_that(const T& val, const std::unique_ptr<matchers::matcher<T>>& m) {
  (void)(m->match(val) || (fail(m->message(val)), 0));
}

template <char...>
class test {
 public:
  template <typename T>
  test& operator=(const T& test) {
    test();
    return *this;
  }
};

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wgnu-string-literal-operator-template"
#endif

template <typename T, T... chars>
constexpr auto operator""_test() {
  return test<chars...>{};
}
#endif  // TEST_HPP
