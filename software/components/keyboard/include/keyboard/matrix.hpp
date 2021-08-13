#pragma once

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "config.hpp"
#include "vif.hpp"

namespace kopinions {
class matrix {
 public:
  explicit matrix(gpios &, kopinions::clock &) noexcept;

  std::map<std::pair<pin::id, pin::id>, pin::status> scan();

  virtual ~matrix() = default;

 private:
  gpios *m_gpios;
  matrix_config *m_conf;
  kopinions::clock *m_clk;
  std::map<std::pair<pin::id, pin::id>, uint64_t> m_debounce;
  std::map<std::pair<pin::id, pin::id>, pin::status> m_prev;
  std::map<std::pair<pin::id, pin::id>, pin::status> m_current;
};

}  // namespace kopinions
