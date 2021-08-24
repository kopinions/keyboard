#include "esp_if/esp_log_sink.hpp"

void kopinions::logging::esp_log_sink::consume(const kopinions::logging::record& rd) {
  const char* msg = rd.message().c_str();
  switch (rd.lvl()) {
    case level::DEBUG:
      ESP_LOGD("kbd", "%s", msg);
      break;
    case level::INFO:
      ESP_LOGI("kbd", "%s", msg);
      break;
    case level::WARN:
      ESP_LOGW("kbd", "%s", msg);
      break;
    case level::ERROR:
    case level::FATAL:
      ESP_LOGE("kbd", "%s", msg);
      break;
  }
}
kopinions::logging::esp_log_sink::~esp_log_sink() = default;