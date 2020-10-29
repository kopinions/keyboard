#include <boost/di.hpp>
#include <vector>

#include "esp_if.hpp"
#include "keyboard.hpp"
#include "matrix.hpp"

namespace di = boost::di;
using namespace kopinions;

extern "C" {
void app_main();
}

void app_main() {
  auto rows = std::vector<pin::id>{
      pin::id::IO26, pin::id::IO27, pin::id::IO32, pin::id::IO33, pin::id::IO34, pin::id::IO35,
  };
  auto cols = std::vector<pin::id>{
      pin::id::IO2,  pin::id::IO4,  pin::id::IO5,  pin::id::IO12, pin::id::IO13,
      pin::id::IO14, pin::id::IO15, pin::id::IO16, pin::id::IO17, pin::id::IO18,
      pin::id::IO19, pin::id::IO21, pin::id::IO22, pin::id::IO23, pin::id::IO25,
  };

  auto injector =
      di ::make_injector<>(di::bind<gpios>.to<gpios_if>(), di::bind<kopinions::clock>.to<kopinions::clock_if>(),
                           di::bind<>.to(std::make_shared<matrix::conf>(rows, cols, 4)));
  auto&& kbd = injector.create<keyboard>();

  auto&& tasks_creator = injector.create<std::shared_ptr<tasks>>();
  auto&& sche = injector.create<std::shared_ptr<scheduler>>();
  auto&& tsk = tasks_creator->create<int>("scan", std::function<void(int)>{[&kbd](int a) {
                                 auto&& res = kbd.scan();
                                 for (auto b : res) {
                                   auto status = b.current();
                                 }
                               }});
  sche->taken<int>(tsk, 1);
}