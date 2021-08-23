#pragma once
#include <memory>
#include <vector>
namespace kopinions {
class message_t {
 public:
  message_t(std::unique_ptr<const uint8_t[]> data, uint32_t size);

  [[nodiscard]] const uint8_t* payload() const;
  [[nodiscard]] uint32_t size() const;

 private:
  std::unique_ptr<const uint8_t[]> m_data;
  unsigned int m_size;
};
}  // namespace kopinions