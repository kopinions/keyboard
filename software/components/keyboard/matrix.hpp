#pragma once

#include <memory>
#include <vector>

#include "gpios.hpp"
#include "pin.hpp"

class matrix {
 public:
  class conf {
   public:
    conf(std::vector<pin::id> row, std::vector<pin::id> col);

   public:
    [[nodiscard]] const std::vector<pin::id> &row() const noexcept;

    [[nodiscard]] const std::vector<pin::id> &col() const noexcept;

   private:
    std::vector<pin::id> m_row;
    std::vector<pin::id> m_col;
  };

  explicit matrix(std::shared_ptr<conf>, std::shared_ptr<gpios> gpios) noexcept;

  virtual std::vector<std::pair<uint16_t, uint16_t>> scan();

  virtual ~matrix() = default;

 private:
  std::shared_ptr<gpios> m_gpios;
  std::shared_ptr<conf> m_conf;
};

matrix::conf::conf(std::vector<pin::id> row, std::vector<pin::id> col) : m_row(std::move(row)), m_col(std::move(col)) {}

const std::vector<pin::id> &matrix::conf::row() const noexcept { return m_row; }

const std::vector<pin::id> &matrix::conf::col() const noexcept { return m_col; }

std::vector<std::pair<uint16_t, uint16_t>> matrix::scan() {
  std::vector<std::pair<uint16_t, uint16_t>> pressed;
  for (auto row_id : m_conf->row()) {
    auto row_io = m_gpios->select(row_id);
    row_io->set(pin::status::HIGH);
    for (auto col_id : m_conf->col()) {
      auto col_io = m_gpios->select(col_id);
      auto status = col_io->current();
      if (status == pin::status::HIGH) {
        const std::pair<unsigned short, unsigned short> &args = std::make_pair<uint16_t, uint16_t>(0, 0);
        pressed.emplace_back(args);
      }
    }
  }

  return pressed;
}

matrix::matrix(std::shared_ptr<conf> conf, std::shared_ptr<gpios> gpios) noexcept
    : m_gpios{std::move(gpios)}, m_conf{std::move(conf)} {
  for (auto row_id : m_conf->row()) {
    auto io = m_gpios->select(row_id);
    io->option(pin::opt{.mode = pin::mode_t::INOUT});
    io->set(pin::status::LOW);
  }

  for (auto col_id : m_conf->col()) {
    auto io = m_gpios->select(col_id);
    io->option(pin::opt{.mode = pin::mode_t::INOUT, .cap = pin::capability_t::WEAK});
    io->set(pin::status::LOW);
  }
}