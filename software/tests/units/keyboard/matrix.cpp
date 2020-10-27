
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
  When(Method(gpio_stub, current)).Return(status);

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
    auto&& gpios_stub = mock<gpios>();
    const std::shared_ptr<gpio>& ptr = std::shared_ptr<gpio>(&always_high);
    When(Method(gpios_stub, select)).AlwaysDo([&ptr](auto&& id) { return ptr; });

    auto&& mat = injector.create<matrix>();
    auto points = mat.scan();

    expect_that<int>(points.size(), matchers::eq(1));
  };
}
