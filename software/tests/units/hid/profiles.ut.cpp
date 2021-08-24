#include "profiles.hpp"

#include "test.hpp"

namespace di = boost::di;
using namespace kopinions;

int main() {
  "dummy"_test = [] {
    auto injector = di::make_injector<>(definitions());

    auto kbd = injector.create<bt::application_builder_t*>();
    auto kbd1 = injector.create<bt::application_builder_t*>();
    assert(kbd == kbd1);
  };
}