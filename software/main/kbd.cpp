#include <boost/di.hpp>
#include <supporting/implementation.hpp>

#include "esp_if.hpp"
#include "keyboard.hpp"
#include "matrix.hpp"
#include "reporter.hpp"
#include "supporting/mapping.hpp"
#include "supporting/matrix_conf.hpp"

namespace di = boost::di;
using namespace kopinions;
using namespace kopinions::logging;

extern "C" {
void app_main();
}

void app_main() {
  auto container = di::make_injector<>(di::bind<matrix_config>.to(matrix_config(rows, cols, 4)), implementation());

  auto sche = container.create<std::shared_ptr<scheduler<>>>();

  sche->schedule("test", [&container]() -> void {
    auto kbd = container.create<matrix>();
    kbd.scan();
    auto lg = container.create<std::shared_ptr<logger>>();
    while (true) {
      //      lg->log(level::DEBUG, "%s", "xxx1111");

      //      auto&& res = kbd.scan();
      //      for (auto b : res) {
      //        auto status = b.sts;
      //        lg->log(level::DEBUG, "%s", status);
      //      }
      vTaskDelay(100);
    }
  });
}