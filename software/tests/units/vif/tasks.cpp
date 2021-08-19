#include "common/fakes.hpp"
#include "vif.hpp"
#include "supporting/mapping.hpp"
#include "supporting/matrix_conf.hpp"

namespace di = boost::di;
using namespace kopinions;

int main() {
  "should_able_to_dispatch_the_task"_test = [] {
    auto injector = di::make_injector<>(mapping(), conf(), fakes());
    auto&& s = injector.create<std::shared_ptr<scheduler<int>>>();
    int arg = 0;
    task<void(int)> t = [&arg](int actual) -> void {
      std::cout << "task callback called" << std::endl;
      arg = actual;
    };

    s->schedule("test task", t, 1);

    expect_that<int>(arg, matchers::eq(1));
  };
}