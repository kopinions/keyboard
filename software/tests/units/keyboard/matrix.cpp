
#include <matrix.hpp>

#include "common/matchers.hpp"
#include "common/mocks_provider.hpp"
#include "common/test.hpp"
#include "gpios.hpp"
#include "keyboard.hpp"

namespace di = boost::di;
using namespace fakeit;
int main() {
  "matrix_scan_change"_test = [] {
    auto injector = di::make_injector<mocks_provider>(di::bind<>.to(std::make_shared<matrix::conf>(
        std::vector<pin::id>{
            pin::id::GPIO0,
        },
        std::vector<pin::id>{pin::id::GPIO1})));
    auto&& gpio_stub = mock<gpio>();
    When(Method(gpio_stub, option)).AlwaysDo([](auto opt) {

    });
    When(Method(gpio_stub, set)).AlwaysDo([](auto status) {

    });
    When(Method(gpio_stub, current)).AlwaysDo([]() { return pin::status::HIGH; });
    auto&& gpios_stub = mock<gpios>();
    When(Method(gpios_stub, select)).AlwaysDo([&gpio_stub](auto pin) {
      return std::shared_ptr<gpio>{&(gpio_stub.get())};
    });

    auto&& mat = injector.create<matrix>();
    auto points = mat.scan();

    expect_that<int>(points.size(), matchers::eq(0));
  };
}
