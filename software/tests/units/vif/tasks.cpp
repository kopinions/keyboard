#include "fakes.hpp"
#include "matchers.hpp"
#include "supporting/mapping.hpp"
#include "test.hpp"

namespace di = boost::di;
using namespace kopinions;

int main() {
  "should_able_to_dispatch_the_task"_test = [] {
    auto injector = di::make_injector<>(mapping(), fakes());
    auto&& s = injector.create<std::shared_ptr<scheduler<int>>>();
    static int arg = 0;
    task<void(int)> t = [](int actual) -> void {
      std::cout << "called with actual: " << actual << std::endl;
      arg = actual;
      expect_that<int>(actual, matchers::eq(1));
    };

    s->schedule("test task", t, 1);
    expect_that<int>(arg, matchers::eq(1));
  };
}