#include "keyboard/matrix.hpp"

#include "fakes.hpp"
#include "matchers.hpp"
#include "test.hpp"

namespace di = boost::di;
using namespace kopinions;
using namespace fakeit;

int main() {
  "matrix_scan_change"_test = [] {
    auto injector = di::make_injector<mocks_provider>(di::bind<kopinions::matrix_config>.to(
        matrix_config{std::vector<pin::id_t>{pin::id_t::IO0}, std::vector<pin::id_t>{pin::id_t::IO1}, 0}));
    auto&& gpios_stub = mock<gpios>(true);
    auto&& clk = mock<kopinions::clock>(true);
    auto&& msink = mock<kopinions::logging::sink>(true);
    When(Method(msink, consume)).AlwaysDo([](const auto&) {});

    When(Method(clk, now)).AlwaysDo([]() { return kopinions::time{0}; });

    auto high_ptr = keep(pin::status::HIGH);
    When(Method(gpios_stub, select)).AlwaysDo([&high_ptr](auto&& id) { return high_ptr; });

    auto mat = injector.create<matrix>();
    auto points = mat.scan();

    expect_that<int>(points.size(), matchers::eq(1));
  };

  "matrix_scan_change_for_multiple_gpios"_test = [] {
    auto injector = di::make_injector<mocks_provider>(di::bind<kopinions::matrix_config>.to(matrix_config(
        std::vector<pin::id_t>{
            pin::id_t::IO0,
            pin::id_t::IO1,
        },
        std::vector<pin::id_t>{
            pin::id_t::IO3,
            pin::id_t::IO4,
        },
        0)));

    auto&& msink = mock<kopinions::logging::sink>(true);
    When(Method(msink, consume)).AlwaysDo([](const auto&) {});

    auto&& gpios_stub = mock<gpios>(true);
    auto&& clk = mock<kopinions::clock>(true);
    auto high_ptr = keep(pin::status::HIGH);
    auto low_ptr = keep(pin::status::LOW);
    When(Method(clk, now)).AlwaysDo([]() { return kopinions::time{0}; });

    When(Method(gpios_stub, select)).AlwaysDo([&high_ptr, &low_ptr](auto&& id) {
      if (id == pin::id_t::IO0) {
        return low_ptr;
      } else {
        return high_ptr;
      }
    });

    auto&& mat = injector.create<matrix>();
    auto points = mat.scan();

    expect_that<int>(points.size(), matchers::eq(2));
    auto id = std::pair<pin::id_t, pin::id_t>{pin::id_t::IO1, pin::id_t::IO4};
    expect_that<pin::status>(points[id], matchers::eq(pin::status::HIGH));
  };

  "matrix_scan_ignore_debounce_in_tolerable_range"_test = [] {
    auto injector = di::make_injector<mocks_provider>(di::bind<kopinions::matrix_config>.to(matrix_config(
        std::vector<pin::id_t>{
            pin::id_t::IO0,
            pin::id_t::IO1,
        },
        std::vector<pin::id_t>{
            pin::id_t::IO3,
            pin::id_t::IO4,
        },
        4)));

    auto&& msink = mock<kopinions::logging::sink>(true);
    When(Method(msink, consume)).AlwaysDo([](const auto&) {});

    auto&& gpios_stub = mock<gpios>(true);
    auto&& clk = mock<kopinions::clock>(true);

    auto high_ptr = keep(pin::status::HIGH);
    auto low_ptr = keep(pin::status::LOW);

    auto idx = 0;
    When(Method(clk, now)).AlwaysDo([&idx]() {
      std::vector<kopinions::time> times{kopinions::time{0}, kopinions::time{5000}};
      return times[idx];
    });
    When(Method(gpios_stub, select)).AlwaysDo([&high_ptr, &low_ptr, &idx](auto&& id) {
      if (id == pin::id_t::IO0) {
        return low_ptr;
      } else {
        return high_ptr;
      }
    });

    auto&& mat = injector.create<matrix>();
    auto&& first_scan_points = mat.scan();
    expect_that<int>(first_scan_points.size(), matchers::eq(0));
    idx++;
    auto&& second_scan_points = mat.scan();
    expect_that<int>(second_scan_points.size(), matchers::eq(2));
  };
}
