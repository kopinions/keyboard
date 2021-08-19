#include "esp_log.h"
void esp_log_write(esp_log_level_t level, const char *tag, const char *format, ...) {
  va_list list;
  va_start(list, format);
  printf(format, list);
  va_end(list);
}
