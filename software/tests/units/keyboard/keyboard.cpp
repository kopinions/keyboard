#include "keyboard/keyboard.hpp"

#include "matchers.hpp"
#include "mocks_provider.hpp"
#include "supporting/mapping.hpp"
#include "test.hpp"

namespace di = boost::di;
using namespace kopinions;

int main() {
  "dummy"_test = [] {
    auto injector = di::make_injector<mocks_provider>(mapping());
    auto&& gpio_stub = mock<gpio>();
    auto&& gpios_stub = mock<gpios>();

    auto kbd = injector.create<keyboard>();

    using namespace fakeit;
    auto&& mock_layout = mock<layout>();
    When(Method(mock_layout, mapping)).Return(std::vector<kopinions::key_t>{});

    expect_that<int>(kbd.scan().size(), matchers::eq(0));
  };
}