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
  explicit matrix(const std::shared_ptr<gpios> &, const std::shared_ptr<kopinions::clock> &) noexcept;

  std::map<std::pair<pin::id, pin::id>, pin::status> scan();

  virtual ~matrix() = default;

 private:
  std::shared_ptr<gpios> m_gpios;
  matrix_config *m_conf;
  std::shared_ptr<kopinions::clock> m_clk;
  std::map<std::pair<pin::id, pin::id>, uint64_t> m_debounce;
  std::map<std::pair<pin::id, pin::id>, pin::status> m_prev;
  std::map<std::pair<pin::id, pin::id>, pin::status> m_current;
};

std::map<std::pair<pin::id, pin::id>, pin::status> matrix::scan() {
  std::map<std::pair<pin::id, pin::id>, pin::status> changes;
  for (auto col_id : m_conf->col()) {
    auto col_io = m_gpios->select(pin::id::IO27);
    col_io->set(pin::status::HIGH);
    for (auto row_id : m_conf->row()) {
      auto row_io = m_gpios->select(row_id);
      auto status = row_io->current();
      auto &&id = std::pair<pin::id, pin::id>{row_id, col_id};
      if (m_prev[id] != status) {
        m_debounce[id] = m_clk->now().millis();
      }
      m_prev[id] = status;
      if ((m_clk->now().millis() - m_debounce[id]) >= m_conf->tolerance()) {
        if (m_current[id] != status) {
          m_current[id] = status;
          changes[id] = status;
        }
      }
    }
    col_io->set(pin::status::LOW);
  }
  return changes;
}

matrix::matrix(const std::shared_ptr<gpios> &gpios, const std::shared_ptr<kopinions::clock> &clk) noexcept
    : m_gpios{gpios}, m_clk{clk} {
  m_conf = new matrix_config(
      std::vector<pin::id>{
          pin::id::IO2,
          pin::id::IO4,
          pin::id::IO5,
          pin::id::IO12,
          pin::id::IO13,
          pin::id::IO14,
          pin::id::IO15,
          pin::id::IO16,
          pin::id::IO17,
          pin::id::IO18,
          pin::id::IO19,
          pin::id::IO21,
          pin::id::IO22,
          pin::id::IO23,
          pin::id::IO25,
      },
      std::vector<pin::id>{pin::id::IO26, pin::id::IO27, pin::id::IO32, pin::id::IO33}, 4);
  for (auto row_id : m_conf->row()) {
    auto io = m_gpios->select(row_id);
    io->option(pin::opt{.mode = pin::mode_t::BIDIRECTIONAL, .cap = pin::capability_t::WEAK});
    io->set(pin::status::LOW);
  }

  for (auto col_id : m_conf->col()) {
    auto io = m_gpios->select(col_id);
    io->option(pin::opt{.mode = pin::mode_t::BIDIRECTIONAL, .cap = pin::capability_t::MEDIUM});
    io->set(pin::status::LOW);
  }
  for (auto row_id : m_conf->row()) {
    for (auto col_id : m_conf->col()) {
      auto &&id = std::pair<pin::id, pin::id>{row_id, col_id};
      m_debounce[id] = m_clk->now().millis();
      m_prev[id] = pin::status::LOW;
      m_current[id] = pin::status::LOW;
    }
  }
}
}  // namespace kopinions
