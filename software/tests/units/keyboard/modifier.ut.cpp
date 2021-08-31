#include "keyboard/modifier.hpp"

#include "fakes.hpp"
#include "matchers.hpp"
#include "test.hpp"

namespace di = boost::di;
using namespace kopinions;
using namespace fakeit;

int main() {
  "modify_the_pressed_keys"_test = [] {
    auto injector = di::make_injector<mocks_provider>(
        di::bind<modifier_t[]>().to({modifier_t{[](const auto &) -> bool { return true; }}}));

    auto modifier = injector.create<std::vector<modifier_t>>();
    std::vector<kopinions::key_t> pressed{
        {kopinions::key_t::id_t::FN, kopinions::key_t::status_t::PRESSED},
        {kopinions::key_t::id_t::F1, kopinions::key_t::status_t::PRESSED},
    };
//    auto modified = modifier.at(0).modify(pressed);

//    expect_that<int>(modified.size(), matchers::eq(2));
  };
}
