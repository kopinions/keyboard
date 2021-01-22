#include <cstring>

#include "esp_if.hpp"
#include "ible.hpp"
#include "ihid.hpp"
#include "keyboard.hpp"
#include "matrix.hpp"
#include "object.hpp"
#include "supporting/mapping.hpp"
#include "transports.hpp"

using namespace kopinions;
using namespace kopinions::logging;

extern "C" void app_main() {
  auto sche = std::make_shared<scheduler_if<>>();

  sche->schedule("test", []() -> void {
    auto ios = std::make_shared<gpios_if>();
    auto clk = std::make_shared<clock_if>();
    auto mtx = std::make_shared<matrix>(ios, clk);
    auto lay = std::make_shared<layout>(layout_mapping);
    auto cfg = std::make_shared<config>();
    auto kbd = std::make_shared<keyboard>(lay, mtx, cfg);
    auto lg = std::make_shared<logger>(level::INFO, std::make_shared<esp_log_sink>());
    auto trans = std::make_shared<transports>();
    //    const std::shared_ptr<endpoint>& ep = std::make_shared<endpoint>();
    const std::shared_ptr<bt::ble>& b = std::make_shared<bt::ble>(lg);
    const bt::application_t& app = bt::application_t::builder_t::name("kbd")->id(0x0001)->build();

    b->enroll(app);

    while (true) {
      lg->log(level::DEBUG, "%s", "xxx1111");

      auto&& res = kbd->scan();
      trans->select();

      for (auto b : res) {
        auto status = b.sts;
        lg->log(level::DEBUG, "%s", status);
      }

      vTaskDelay(100);
    }
  });
}