#include <matrix.hpp>

#include "common/matchers.hpp"
#include "common/mocks_provider.hpp"
#include "common/test.hpp"
#include "fake_gpio.hpp"
#include "gpios.hpp"

namespace di = boost::di;
using namespace fakeit;

int main() {
  "matrix_scan_change"_test = [] {
    auto injector = di::make_injector<mocks_provider>(di::bind<>.to(std::make_shared<matrix::conf>(
        std::vector<pin::id>{
            pin::id::GPIO0,
        },
        std::vector<pin::id>{pin::id::GPIO1})));

    auto&& gpios_stub = mock<gpios>();

    auto high_ptr = keep(pin::status::HIGH);
    When(Method(gpios_stub, select)).AlwaysDo([&high_ptr](auto&& id) { return high_ptr; });

    auto&& mat = injector.create<matrix>();
    auto points = mat.scan();

    expect_that<int>(points.size(), matchers::eq(1));
  };

  "matrix_scan_change_for_multiple_gpios"_test = [] {
    auto injector = di::make_injector<mocks_provider>(di::bind<>.to(std::make_shared<matrix::conf>(
        std::vector<pin::id>{
            pin::id::GPIO0,
            pin::id::GPIO1,
        },
        std::vector<pin::id>{
            pin::id::GPIO3,
            pin::id::GPIO4,
        })));

    auto&& gpios_stub = mock<gpios>();
    auto high_ptr = keep(pin::status::HIGH);
    auto low_ptr = keep(pin::status::LOW);

    When(Method(gpios_stub, select)).AlwaysDo([&high_ptr, &low_ptr](auto&& id) {
      if (id == pin::id::GPIO3) {
        return low_ptr;
      } else {
        return high_ptr;
      }
    });

    auto&& mat = injector.create<matrix>();
    auto points = mat.scan();

    expect_that<int>(points.size(), matchers::eq(2));
    expect_that<pin::id>(points.at(0).first, matchers::eq(pin::id::GPIO0));
    expect_that<pin::id>(points.at(0).second, matchers::eq(pin::id::GPIO4));
  };
}
