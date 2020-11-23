#pragma once

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "vif.hpp"

namespace kopinions {
class matrix {
 public:
  class conf {
   public:
    conf(std::vector<pin::id> row, std::vector<pin::id> col, unsigned int bounce);

   public:
    [[nodiscard]] const std::vector<pin::id> &row() const noexcept;

    [[nodiscard]] const std::vector<pin::id> &col() const noexcept;

    [[nodiscard]] unsigned int tolerance() const noexcept;

   private:
    std::vector<pin::id> m_row;
    std::vector<pin::id> m_col;
    unsigned int m_bounce;
  };

  explicit matrix(conf, std::shared_ptr<gpios>, std::shared_ptr<kopinions::clock>) noexcept;

  std::map<std::pair<pin::id, pin::id>, pin::status> scan();

  virtual ~matrix() = default;

 private:
  std::shared_ptr<gpios> m_gpios;
  conf m_conf;
  std::shared_ptr<kopinions::clock> m_clk;
  std::map<std::pair<pin::id, pin::id>, uint64_t> m_debounce;
  std::map<std::pair<pin::id, pin::id>, pin::status> m_prev;
  std::map<std::pair<pin::id, pin::id>, pin::status> m_current;
};

matrix::conf::conf(std::vector<pin::id> row, std::vector<pin::id> col, unsigned int bounce)
    : m_row{std::move(row)}, m_col{std::move(col)}, m_bounce{bounce} {}

const std::vector<pin::id> &matrix::conf::row() const noexcept { return m_row; }

const std::vector<pin::id> &matrix::conf::col() const noexcept { return m_col; }
unsigned int matrix::conf::tolerance() const noexcept { return m_bounce; }

std::map<std::pair<pin::id, pin::id>, pin::status> matrix::scan() {
  std::map<std::pair<pin::id, pin::id>, pin::status> changes;
  for (auto col_id : m_conf.col()) {
    std::cout << (void *)m_gpios.get() << std::endl;
    std::cout << col_id << std::endl;
    auto col_io = m_gpios->select(pin::id::IO27);
    std::cout << (void *)col_io.get() << std::endl;
    col_io->set(pin::status::HIGH);
    for (auto row_id : m_conf.row()) {
      auto row_io = m_gpios->select(row_id);
      auto status = row_io->current();
      auto &&id = std::pair<pin::id, pin::id>{row_id, col_id};
      if (m_prev[id] != status) {
        m_debounce[id] = m_clk->now().millis();
      }
      m_prev[id] = status;
      if ((m_clk->now().millis() - m_debounce[id]) >= m_conf.tolerance()) {
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

matrix::matrix(conf conf, std::shared_ptr<gpios> gpios, std::shared_ptr<kopinions::clock> clk) noexcept
    : m_gpios{gpios}, m_conf{conf}, m_clk{clk} {
  for (auto row_id : m_conf.row()) {
    auto io = m_gpios->select(row_id);
    io->option(pin::opt{.mode = pin::mode_t::BIDIRECTIONAL, .cap = pin::capability_t::WEAK});
    io->set(pin::status::LOW);
  }

  for (auto col_id : m_conf.col()) {
    auto io = m_gpios->select(col_id);
    io->option(pin::opt{.mode = pin::mode_t::BIDIRECTIONAL, .cap = pin::capability_t::MEDIUM});
    io->set(pin::status::LOW);
  }
  for (auto row_id : m_conf.row()) {
    for (auto col_id : m_conf.col()) {
      auto &&id = std::pair<pin::id, pin::id>{row_id, col_id};
      m_debounce[id] = m_clk->now().millis();
      m_prev[id] = pin::status::LOW;
      m_current[id] = pin::status::LOW;
    }
  }
}
}  // namespace kopinions
