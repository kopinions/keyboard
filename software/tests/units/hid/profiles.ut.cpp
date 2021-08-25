#include "profiles.hpp"

#include "test.hpp"

namespace di = boost::di;
using namespace kopinions;

int main() {
  "DISABLED_should_inject_the_same_application_builder_when_injected_multiple_times"_test = [] {
    auto injector = di::make_injector<>(definitions());

    auto builder = injector.create<bt::application_builder_t&>();
    auto other_builder = injector.create<bt::application_builder_t&>();
    builder.m_app_name = "xxx";

    if (other_builder.m_app_name != "xxx") {
      throw std::exception();
    };
  };
}