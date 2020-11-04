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
  auto injector = di ::make_injector<>(mapping(), conf(), implementation());

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
}