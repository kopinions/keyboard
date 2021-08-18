#pragma once

#include <stdint.h>

#define portTICK_PERIOD_MS  1000

typedef void * TaskHandle_t;

void vTaskDelete( TaskHandle_t xTaskToDelete ) {

};

void vTaskDelay( const uint32_t xTicksToDelay );