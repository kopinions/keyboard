#ifndef KBD_ESP_LOG_H
#define KBD_ESP_LOG_H

#include <cstdarg>
#include <cstdio>
typedef enum {
  ESP_LOG_NONE,   /*!< No log output */
  ESP_LOG_ERROR,  /*!< Critical errors, software module can not recover on its own */
  ESP_LOG_WARN,   /*!< Error conditions from which recovery measures have been taken */
  ESP_LOG_INFO,   /*!< Information messages which describe normal flow of events */
  ESP_LOG_DEBUG,  /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
  ESP_LOG_VERBOSE /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the
                     output. */
} esp_log_level_t;

#define LOG_LOCAL_LEVEL ESP_LOG_INFO

void esp_log_write(esp_log_level_t level, const char *tag, const char *format, ...) {
  va_list list;
  va_start(list, format);
  printf(format, list);
  va_end(list);
}

#define ESP_LOG_LEVEL(level, tag, format, ...)                    \
  do {                                                            \
    if (level == ESP_LOG_ERROR) {                                 \
      esp_log_write(ESP_LOG_ERROR, tag, format, ##__VA_ARGS__);   \
    } else if (level == ESP_LOG_WARN) {                           \
      esp_log_write(ESP_LOG_WARN, tag, format, ##__VA_ARGS__);    \
    } else if (level == ESP_LOG_DEBUG) {                          \
      esp_log_write(ESP_LOG_DEBUG, tag, format, ##__VA_ARGS__);   \
    } else if (level == ESP_LOG_VERBOSE) {                        \
      esp_log_write(ESP_LOG_VERBOSE, tag, format, ##__VA_ARGS__); \
    } else {                                                      \
      esp_log_write(ESP_LOG_INFO, tag, format, ##__VA_ARGS__);    \
    }                                                             \
  } while (0)

#define ESP_LOG_LEVEL_LOCAL(level, tag, format, ...)                                \
  do {                                                                              \
    if (LOG_LOCAL_LEVEL >= level) ESP_LOG_LEVEL(level, tag, format, ##__VA_ARGS__); \
  } while (0)

#define ESP_LOGE(tag, format, ...) ESP_LOG_LEVEL_LOCAL(ESP_LOG_ERROR, tag, format, ##__VA_ARGS__)
#define ESP_LOGW(tag, format, ...) ESP_LOG_LEVEL_LOCAL(ESP_LOG_WARN, tag, format, ##__VA_ARGS__)
#define ESP_LOGI(tag, format, ...) ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO, tag, format, ##__VA_ARGS__)
#define ESP_LOGD(tag, format, ...) ESP_LOG_LEVEL_LOCAL(ESP_LOG_DEBUG, tag, format, ##__VA_ARGS__)
#define ESP_LOGV(tag, format, ...) ESP_LOG_LEVEL_LOCAL(ESP_LOG_VERBOSE, tag, format, ##__VA_ARGS__)
#endif  // KBD_ESP_LOG_H
