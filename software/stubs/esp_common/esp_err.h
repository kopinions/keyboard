#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t esp_err_t;

/* Definitions for error constants. */
#define ESP_OK 0    /*!< esp_err_t value indicating success (no error) */
#define ESP_FAIL -1 /*!< Generic esp_err_t code indicating failure */

#ifdef __cplusplus
}
#endif
