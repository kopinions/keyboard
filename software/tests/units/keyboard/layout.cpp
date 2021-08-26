#include "keyboard/layout.hpp"

#include <boost/di.hpp>

#include "matchers.hpp"
#include "mocks_provider.hpp"
#include "supporting/mapping.hpp"
#include "test.hpp"

namespace di = boost::di;
using namespace kopinions;

int main() {
  "should_parse_keyboard_Layout"_test = [] {
    auto injector = di::make_injector<mocks_provider>(mapping());
    auto lay = injector.create<layout>();

    auto esc_pressed =
        std::map<std::pair<pin::id_t, pin::id_t>, pin::status>{{{pin::id_t::IO26, pin::id_t::IO2}, pin::status::HIGH}};
    auto mapped = lay.mapping(std::move(esc_pressed));

    expect_that<int>(mapped.size(), matchers::eq(1));
    expect_that<kopinions::key_t::status_t>(mapped[0].sts, matchers::eq(kopinions::key_t::status_t::PRESSED));
    expect_that<kopinions::key_t::id_t>(mapped[0].id, matchers::eq(kopinions::key_t::id_t::ESC));
  };

  "should_parse_keyboard_layout_for_multiple_keys"_test = [] {
    auto injector = di::make_injector<mocks_provider>(mapping());
    auto lay = injector.create<layout>();

    auto ctrl_alt_gui_shift_a = std::map<std::pair<pin::id_t, pin::id_t>, pin::status>{
        {{pin::id_t::IO35, pin::id_t::IO4}, pin::status::HIGH}, {{pin::id_t::IO35, pin::id_t::IO12}, pin::status::HIGH},
        {{pin::id_t::IO35, pin::id_t::IO5}, pin::status::HIGH}, {{pin::id_t::IO34, pin::id_t::IO2}, pin::status::HIGH},
        {{pin::id_t::IO33, pin::id_t::IO4}, pin::status::HIGH},
    };
    auto mapped = lay.mapping(std::move(ctrl_alt_gui_shift_a));

    expect_that<int>(mapped.size(), matchers::eq(5));
    expect_that<kopinions::key_t::status_t>(mapped[0].sts, matchers::eq(kopinions::key_t::status_t::PRESSED));

    auto ctrl =
        std::find_if(mapped.begin(), mapped.end(), [](auto&& $) { return $.id == kopinions::key_t::id_t::LCTRL; });
    expect_that<kopinions::key_t::status_t>(ctrl->sts, matchers::eq(kopinions::key_t::status_t::PRESSED));
  };
}