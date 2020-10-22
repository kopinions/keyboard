#pragma once

class matrix {
 public:
  explicit matrix(std::shared_ptr<gpios> gpios) noexcept;
  virtual std::vector<std::pair<uint16_t, uint16_t>> scan(const std::shared_ptr<config>& conf);
  virtual ~matrix() = default;
};

std::vector<std::pair<uint16_t, uint16_t>> matrix::scan(const std::shared_ptr<config>& conf) {
  return std::vector<std::pair<uint16_t, uint16_t>>{};
}

matrix::matrix(std::shared_ptr<gpios> gpios) noexcept {};