#include "layout.hpp"

#include <boost/di.hpp>

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
    expect_that<key::status>(mapped[0].current(), matchers::eq(key::status::PRESSED));
    expect_that<key::id>(mapped[0].identity(), matchers::eq(key::id::ESC));
  };
}