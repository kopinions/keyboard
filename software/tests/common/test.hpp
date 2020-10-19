#ifndef TEST_HPP
#define TEST_HPP

//#include <iostream>
//
void expect_fail__(const char* file, int line) {
//  std::printf("%s:%d:%s\n", file, line, file);
//  std::exit(-1);
}
template <typename T>
constexpr void expect(T val, int loc = __LINE__, const char* file = __FILE__) {
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

template <typename T, T... Chars>
constexpr auto operator""_test() {
  return test<Chars...>{};
}
#endif  // TEST_HPP
