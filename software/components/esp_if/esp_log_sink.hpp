#pragma once

#include "esp_log.h"
#include "logger.hpp"
namespace kopinions {
class esp_log_sink : public sink {
 public:
  void consume(record&& rd) override {
    const char* msg = rd.message().c_str();
    ESP_LOGI("KEY", "%s", msg);
  }
};
}  // namespace kopinions
