#include "keyboard.hpp"

#include <memory>

#include "gpios.hpp"
#include "common/mocks_provider.hpp"
#include "common/matchers.hpp"
#include "common/test.hpp"


int main() {
  "dummy"_test = [] {
//    auto injector = di::make_injector<mocks_provider>();
    auto&& gpio_stub = mock<gpio>();
    auto&& gpios_stub = mock<gpios>();

//    auto kbd = injector.create<keyboard>();

    expect_that<bool>(true, matchers::eq(true));
  };
}