#include "esp_if/chrono_if.hpp"

kopinions::time kopinions::clock_if::now() {
  int64_t time = esp_timer_get_time();
  return kopinions::time(time);
}