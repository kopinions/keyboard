#include <boost/di.hpp>
#include <gpios_if.hpp>
#include <keyboard.hpp>
#include <vector>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "matrix.hpp"
#include "pin.hpp"
namespace di = boost::di;

extern "C" {
void app_main();
}

void app_main() {
  int i = 0;
  std::vector<int> a;
  while (1) {
    i++;
    auto injector = di ::make_injector<>(
        di::bind<gpios>.to<gpios_if>(),
        di::bind<>.to(std::make_shared<matrix::conf>(
        std::vector<pin::id>{
            pin::id::GPIO0,
        },
        std::vector<pin::id>{pin::id::GPIO1})));
    injector.create<keyboard>();
    vTaskDelay(3000 / portTICK_PERIOD_MS);
  }
}