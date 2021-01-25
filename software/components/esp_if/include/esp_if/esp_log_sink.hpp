#pragma once

#include "esp_log.h"
#include "logger.hpp"
namespace kopinions::logging {
class esp_log_sink : public sink {
 public:
  void consume(const record& rd) override;
  ~esp_log_sink() override;
};

}  // namespace kopinions::logging
