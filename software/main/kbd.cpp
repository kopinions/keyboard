#include <boost/di.hpp>
#include <supporting/implementation.hpp>

#include "esp_if.hpp"
#include "keyboard.hpp"
#include "layout.hpp"
#include "matrix.hpp"
#include "reporter.hpp"
#include "supporting/mapping.hpp"
#include "supporting/matrix_conf.hpp"

namespace di = boost::di;
using namespace kopinions;

extern "C" {
void app_main();
}

void app_main() {
  auto injector = di::make_injector<>(mapping(), conf(), implementation());

  auto&& kbd = injector.create<keyboard>();
  auto&& lg = injector.create<std::shared_ptr<logger>>();
  auto&& sche = injector.create<std::shared_ptr<scheduler<>>>();
  sche->schedule("test", [&kbd, &lg]() -> void {
    while (true) {
      std::cout << "test" << std::endl;
      //      auto&& res = kbd.scan();
      //      for (auto b : res) {
      //        auto status = b.sts;
      //        lg->log(logger::level::DEBUG, "%s", status);
      //      }
      vTaskDelay(10);
    }
  });
}