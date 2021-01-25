#include "esp_if/esp_log_sink.hpp"

void kopinions::logging::esp_log_sink::consume(const kopinions::logging::record& rd) {
  ESP_LOGI("KEY", "%s", (rd.message().c_str()));
}
kopinions::logging::esp_log_sink::~esp_log_sink() = default;