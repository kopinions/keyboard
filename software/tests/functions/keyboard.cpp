#include "keyboard.hpp"

#include "common/fakes.hpp"
#include "supporting/mapping.hpp"
#include "supporting/matrix_conf.hpp"
#include "vif.hpp"

namespace di = boost::di;
using namespace kopinions;

int main() {
  "should_able_to_dispatch_the_task"_test = [] {
    auto injector = di ::make_injector<>(mapping(), conf(), fakes());

    auto&& kbd = injector.create<keyboard>();
    auto&& sched = injector.create<std::shared_ptr<scheduler<>>>();
    auto&& lg = injector.create<std::shared_ptr<logger>>();
    task<void()> t = [&kbd, &lg]() {
      lg->log(logger::level::DEBUG, "%s", "started by scheduler");
      auto&& res = kbd.scan();
      lg->log(logger::level::DEBUG, "%s", res.size());
      for (auto b : res) {
        auto status = b.current();
        lg->log(logger::level::DEBUG, "%s", status);
      }
    };
    auto&& tsk = sched->schedule("scan", t);
  };
}