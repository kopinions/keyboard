#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <memory>

#include "matchers.hpp"

void expect_fail__(const char* file, int line, const std::string& message = "") {
  std::printf("%s:%d---%s\n", file, line, message.c_str());
  std::exit(-1);
}

void expect_fail__(const std::string& message = "") {
  std::cout << message << std::endl;
  std::exit(-1);
}

template <typename T>
constexpr void expect(T val, const char* file = __FILE__, int loc = __LINE__) {
  (void)(val || (expect_fail__(file, loc), 0));
}

template <typename T>
constexpr void expect_that(const T& val, const std::unique_ptr<matchers::matcher<T>>& m) {
  (void)(m->match(val) || (expect_fail__(m->message(val)), 0));
}

template <char...>
class test {
 public:
  template <typename T>
  bool operator=(const T& test) {
    test();
    return true;
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
