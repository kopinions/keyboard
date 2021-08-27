#include "keyboard/matrix.hpp"
using namespace kopinions;

std::map<std::pair<pin::id_t, pin::id_t>, pin::status> matrix::scan() {
  std::map<std::pair<pin::id_t, pin::id_t>, pin::status> changes;
  for (auto col_id : m_conf.cols()) {
    auto col_io = m_gpios->select(col_id);
    col_io->set(pin::status::HIGH);
    for (auto row_id : m_conf.rows()) {
      auto row_io = m_gpios->select(row_id);
      auto status = row_io->current();
      auto &&id = std::pair<pin::id_t, pin::id_t>{row_id, col_id};
      if (m_prev[id] != status) {
        m_logger->info("debounce on %d %d", row_id, col_id);
        m_debounce[id] = m_clk->now().millis();
      }
      m_prev[id] = status;
      if ((m_clk->now().millis() - m_debounce[id]) >= m_conf.tolerance()) {
        if (m_current[id] != status) {
          m_logger->info("%d %d changed to %d", row_id, col_id, status);
          m_current[id] = status;
          changes[id] = status;
        }
      }
    }
    col_io->set(pin::status::LOW);
  }
  return changes;
}

matrix::matrix(gpios &gpios, kopinions::clock &clk, kopinions::matrix_config conf,
               kopinions::logging::logger &logger) noexcept
    : m_gpios{&gpios}, m_clk{&clk}, m_logger{&logger}, m_conf{std::move(conf)} {
  for (auto row_id : m_conf.rows()) {
    auto io = m_gpios->select(row_id);
    io->option(pin::option_t{
        .dir = pin::direction_t::INPUT,
        .cap = pin::capability_t::STRONGER,
        .pull = pin::pull_mode_t::DOWN,
    });
    io->set(pin::status::LOW);
  }

  for (auto col_id : m_conf.cols()) {
    auto io = m_gpios->select(col_id);
    io->option(pin::option_t{
        .dir = pin::direction_t::BIDIRECTIONAL,
        .cap = pin::capability_t::STRONGER,
        .pull = pin::pull_mode_t::DOWN,
    });
    io->set(pin::status::LOW);
  }
  for (auto row_id : m_conf.rows()) {
    for (auto col_id : m_conf.cols()) {
      auto &&id = std::pair<pin::id_t, pin::id_t>{row_id, col_id};
      m_debounce[id] = m_clk->now().millis();
      m_prev[id] = pin::status::LOW;
      m_current[id] = pin::status::LOW;
    }
  }
}