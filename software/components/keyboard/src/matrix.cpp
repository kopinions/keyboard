#include "keyboard/matrix.hpp"
using namespace kopinions;

std::map<std::pair<pin::id, pin::id>, pin::status> matrix::scan() {
  std::map<std::pair<pin::id, pin::id>, pin::status> changes;
  for (auto col_id : m_conf->col()) {
    auto col_io = m_gpios->select(col_id);
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

matrix::matrix(gpios &gpios, kopinions::clock &clk, matrix_config& conf) noexcept : m_gpios{&gpios}, m_clk{&clk}, m_conf{&conf} {
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