#include <boost/di.hpp>
#include <supporting/implementation.hpp>
#include <vector>

#include "esp_if.hpp"
#include "keyboard.hpp"
#include "matrix.hpp"
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

  auto&& sche = injector.create<std::shared_ptr<scheduler<int>>>();
  task<void(int)> pFunction = [](int) {};
  sche->schedule("xxx", pFunction, 1);
}