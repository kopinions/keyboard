#pragma once
#include <boost/di.hpp>
#include "esp_if/esp_if.hpp"
#include "keyboard/layout.hpp"
#include "supporting/sedes.hpp"
#include "vif.hpp"

namespace di = boost::di;
using namespace kopinions;
using namespace kopinions::logging;

constexpr auto implementation = [] {
  return di::make_injector(di::bind<kopinions::logging::sink>.to<kopinions::logging::esp_log_sink>(),
                           di::bind<kopinions::gpios>.to<kopinions::gpios_if>(),
                           di::bind<kopinions::clock>.to<kopinions::clock_if>(),
                           di::bind<scheduler<>>.to<scheduler_if<>>(), di::bind<level>.to(level::DEBUG)
                           ,di::bind<kopinions::sedes_t>
                           );
};