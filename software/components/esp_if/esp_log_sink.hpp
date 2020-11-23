#pragma once

#include "esp_log.h"
#include "logger.hpp"
namespace kopinions::logging {
class esp_log_sink : public sink {
 public:
  void consume(const record& rd) override;
  ~esp_log_sink() override;
};

void esp_log_sink::consume(const record& rd) {
  ESP_LOGI("KEY", "%s", (rd.message().c_str()));
}
esp_log_sink::~esp_log_sink() = default;

}  // namespace kopinions::logging
