#include "keyboard/config.hpp"
#include "matchers.hpp"
#include "supporting/matrix_conf.hpp"
#include "test.hpp"

int main() {
  "should_inject_the_matrix_conf"_test = [] {
    static auto injector = di ::make_injector<>(conf());
    auto matrix_config = injector.create<kopinions::matrix_config>();
    expect_that<std::size_t>(matrix_config.rows().size(), matchers::eq(std::size_t{6}));
  };
}
