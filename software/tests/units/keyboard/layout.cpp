#include "layout.hpp"

#include <boost/di.hpp>
#include <supporting/mapping.hpp>
#include <vif.hpp>

#include "common/mocks_provider.hpp"

namespace di = boost::di;
using namespace kopinions;

int main() {
  "should_parse_keyboard_Layout"_test = [] {
    auto injector = di::make_injector<mocks_provider>(layout_mapping());
    auto lay = injector.create<layout>();

    auto mapped = lay.mapping(std::map<std::pair<pin::id, pin::id>, pin::status>{});

    expect_that<int>(mapped.size(), matchers::eq(0));
  };
}