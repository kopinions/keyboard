
#include <matrix.hpp>

#include "common/matchers.hpp"
#include "common/mocks_provider.hpp"
#include "common/test.hpp"
#include "gpios.hpp"
#include "keyboard.hpp"

namespace di = boost::di;
using namespace fakeit;

gpio& mock_gpio(pin::status status) {
  auto&& gpio_stub = mock<gpio>();
  When(Method(gpio_stub, option)).AlwaysDo([](auto opt) {});
  When(Method(gpio_stub, set)).AlwaysDo([](auto status) {});
  When(Method(gpio_stub, current)).AlwaysDo([&status]() { return status; });
  return gpio_stub.get();
}

int main() {
  "matrix_scan_change"_test = [] {
    auto injector = di::make_injector<mocks_provider>(di::bind<>.to(std::make_shared<matrix::conf>(
        std::vector<pin::id>{
            pin::id::GPIO0,
        },
        std::vector<pin::id>{pin::id::GPIO1})));

    auto&& always_high = mock_gpio(pin::status::HIGH);
    auto&& always_low = mock_gpio(pin::status::LOW);
    auto&& gpios_stub = mock<gpios>();

    When(Method(gpios_stub, select)).AlwaysDo([&always_high, &always_low](auto&& id) {
      return id == pin::id::GPIO0 ? std::shared_ptr<gpio>{&always_high} : std::shared_ptr<gpio>(&always_low);
    });

    auto&& mat = injector.create<matrix>();
    auto points = mat.scan();

    expect_that<int>(points.size(), matchers::eq(0));
  };
}
