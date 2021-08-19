#include "driver/gpio.h"

esp_err_t gpio_set_drive_capability(gpio_num_t gpio_num, gpio_drive_cap_t strength) { return ESP_OK; }

int gpio_get_level(gpio_num_t gpio_num) { return 0; }

esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level) { return ESP_OK; }

esp_err_t gpio_set_direction(gpio_num_t gpio_num, gpio_mode_t mode) { return ESP_OK; }