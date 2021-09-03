#include "keyboard/modifier.hpp"

#include "fakes.hpp"
#include "matchers.hpp"
#include "test.hpp"

namespace di = boost::di;
using namespace kopinions;
using namespace fakeit;

int main() {
  "modify_the_pressed_keys"_test = [] {
    auto modifier = modifier_t(std::make_unique<key_based_guardian_t>(FN), {
                                             {F1, PLAY},
                                             {FN, NONE},
                                         });
    std::vector<kopinions::key_t> pressed{
        {kopinions::key_t::id_t::FN, kopinions::key_t::status_t::PRESSED},
        {kopinions::key_t::id_t::F1, kopinions::key_t::status_t::PRESSED},
    };
    auto modified = modifier.modify(pressed);
    expect_that<int>(modified.size(), matchers::eq(1));
    expect_that<kopinions::key_t::id_t>(modified.at(0).id, matchers::eq(PLAY));
  };
}
