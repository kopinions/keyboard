
#include <matrix.hpp>

#include "../../../../../../../../../../Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/bitset"
#include "../../../../../../../../../../Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/iterator"
#include "common/matchers.hpp"
#include "common/mocks_provider.hpp"
#include "common/test.hpp"
#include "gpios.hpp"
#include "keyboard.hpp"

namespace di = boost::di;
using namespace fakeit;

Mock<T> mock_gpio(pin::status status) {
  auto&& gpio_stub = mock<gpio>();
  When(Method(gpio_stub, option)).AlwaysDo([](auto opt) {});
  When(Method(gpio_stub, set)).AlwaysDo([](auto status) {});
  When(Method(gpio_stub, current)).AlwaysDo([]() { return status; });
  return gpio_stub;
}

int main() {
  "matrix_scan_change"_test = [] {
    auto injector = di::make_injector<mocks_provider>(di::bind<>.to(std::make_shared<matrix::conf>(
        std::vector<pin::id>{
            pin::id::GPIO0,
        },
        std::vector<pin::id>{pin::id::GPIO1})));
    auto always_high = mock_gpio(pin::status::HIGH);
    auto always_low = mock_gpio(pin::status::LOW);
    auto&& gpios_stub = mock<gpios>();

    When(Method(gpios_stub, select)).AlwaysDo([&gpio_stub](auto pin) {
      if (pin == pin::id::GPIO0) {
        return always_high;
      } else {
        return always_low;
      }
    });

    auto&& mat = injector.create<matrix>();
    auto points = mat.scan();

    expect_that<int>(points.size(), matchers::eq(0));
  };
}
