#pragma once
#include "esp_if.hpp"
#include "layout.hpp"
#include "vif.hpp"
namespace di = boost::di;
using namespace kopinions;
using namespace kopinions::logging;

constexpr auto implementation = [] {
  return di::make_injector(di::bind<gpios>.to<gpios_if>(),
                           di::bind<sink>.to<esp_log_sink>(),
                           di::bind<kopinions::clock>.to<kopinions::clock_if>().in(di::singleton),
                           di::bind<scheduler<>>.to<scheduler_if<>>().in(di::singleton),
                            di::bind<level>.to(level::DEBUG));
};