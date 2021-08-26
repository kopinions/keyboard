#pragma once

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "config.hpp"
#include "vif/chrono.hpp"
#include "vif/gpio.hpp"
#include "vif/gpios.hpp"
#include "vif/logger.hpp"
#include "vif/pin.hpp"

namespace kopinions {
class matrix {
 public:
  explicit matrix(gpios &, kopinions::clock &, kopinions::matrix_config, kopinions::logging::logger &logger) noexcept;

  std::map<std::pair<pin::id_t, pin::id_t>, pin::status> scan();

  virtual ~matrix() = default;

 private:
  gpios *m_gpios;
  matrix_config m_conf;
  kopinions::clock *m_clk;
  kopinions::logging::logger *m_logger;
  std::map<std::pair<pin::id_t, pin::id_t>, uint64_t> m_debounce;
  std::map<std::pair<pin::id_t, pin::id_t>, pin::status> m_prev;
  std::map<std::pair<pin::id_t, pin::id_t>, pin::status> m_current;
};

}  // namespace kopinions
