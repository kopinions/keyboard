#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>

void expect_fail__(const char* file, int line) {
  std::printf("%s:%d\n", file, line);
  std::exit(-1);
}
template <typename T>
constexpr void expect(T val, const char* file = __FILE__, int loc = __LINE__) {
  (void)(val || (expect_fail__(file, loc), 0));
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
