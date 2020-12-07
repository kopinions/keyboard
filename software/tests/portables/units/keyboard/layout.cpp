#include "layout.hpp"

#include <boost/di.hpp>
#include <vector>

#include "common/mocks_provider.hpp"
#include "supporting/mapping.hpp"

namespace di = boost::di;
using namespace kopinions;

int main() {
  "should_parse_keyboard_Layout"_test = [] {
    auto injector = di::make_injector<mocks_provider>(mapping());
    auto lay = injector.create<layout>();

    auto esc_pressed =
        std::map<std::pair<pin::id, pin::id>, pin::status>{{{pin::id::IO26, pin::id::IO2}, pin::status::HIGH}};
    auto mapped = lay.mapping(std::move(esc_pressed));

    expect_that<int>(mapped.size(), matchers::eq(1));
    expect_that<key::status>(mapped[0].sts, matchers::eq(key::status::PRESSED));
    expect_that<key::identification>(mapped[0].id, matchers::eq(key::identification::ESC));
  };

  "should_parse_keyboard_layout_for_multiple_keys"_test = [] {
    auto injector = di::make_injector<mocks_provider>(mapping());
    auto lay = injector.create<layout>();

    auto ctrl_alt_gui_shift_a = std::map<std::pair<pin::id, pin::id>, pin::status>{
        {{pin::id::IO35, pin::id::IO4}, pin::status::HIGH}, {{pin::id::IO35, pin::id::IO12}, pin::status::HIGH},
        {{pin::id::IO35, pin::id::IO5}, pin::status::HIGH}, {{pin::id::IO34, pin::id::IO2}, pin::status::HIGH},
        {{pin::id::IO33, pin::id::IO4}, pin::status::HIGH},
    };
    auto mapped = lay.mapping(std::move(ctrl_alt_gui_shift_a));

    expect_that<int>(mapped.size(), matchers::eq(5));
    expect_that<key::status>(mapped[0].sts, matchers::eq(key::status::PRESSED));

    auto ctrl = std::find_if(mapped.begin(), mapped.end(), [](auto&& $) { return $.id == key::identification::CTRL; });
    expect_that<key::status>(ctrl->sts, matchers::eq(key::status::PRESSED));
  };
}