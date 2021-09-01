#include "keyboard/modifier.hpp"

#include "fakes.hpp"
#include "matchers.hpp"
#include "test.hpp"

namespace di = boost::di;
using namespace kopinions;
using namespace fakeit;

int main() {
  "modify_the_pressed_keys"_test = [] {
    auto injector = di::make_injector<mocks_provider>(di::bind<modifier_t[]>.to<modifier_t>({
        modifier_t{[](const auto &) -> bool { return true; }},
        modifier_t{[](const auto &) -> bool { return true; }},
    }));

    auto modifiers = injector.create<std::vector<modifier_t>>();
    std::vector<kopinions::key_t> pressed{
        {kopinions::key_t::id_t::FN, kopinions::key_t::status_t::PRESSED},
        {kopinions::key_t::id_t::F1, kopinions::key_t::status_t::PRESSED},
    };
    expect_that<int>(modifiers.size(), matchers::eq(2));
    auto modified = modifiers.at(0).modify(pressed);
  };
}
