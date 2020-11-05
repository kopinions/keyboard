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
    auto&& tasks_creator = injector.create<std::shared_ptr<tasks>>();
    auto&& lg = injector.create<std::shared_ptr<logger>>();
    auto&& tsk = tasks_creator->create<int>("scan", std::function<void(int)>{[&kbd, &lg](int a) {
                                              auto&& res = kbd.scan();
                                              for (auto b : res) {
                                                auto status = b.current();
                                                lg->log(logger::level::DEBUG, "%s", status);
                                              }
                                            }});
    auto&& disp = injector.create<std::shared_ptr<dispatcher>>();
    disp->dispatch<int>(tsk, 1);
  };
}