#include "profiles.hpp"
#include "test.hpp"

namespace di = boost::di;
using namespace kopinions;

int main() {
  "should_inject_the_same_application_builder_when_injected_multiple_times"_test = [] {
    auto injector = di::make_injector<>(definitions());

    auto builder = injector.create<std::shared_ptr<bt::application_builder_t>>();
    auto other_builder = injector.create<std::shared_ptr<bt::application_builder_t>>();
    assert(builder == other_builder);
  };
}