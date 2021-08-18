#pragma once

#include <stdint.h>

#define portTICK_PERIOD_MS 1000

typedef void* TaskHandle_t;

typedef long BaseType_t;
typedef void (*TaskFunction_t)(void*);
typedef unsigned int UBaseType_t;

static inline BaseType_t xTaskCreate(TaskFunction_t pvTaskCode, const char* const pcName, const uint32_t usStackDepth,
                                     void* const pvParameters, UBaseType_t uxPriority,
                                     TaskHandle_t* const pvCreatedTask);

void vTaskDelay(const uint32_t xTicksToDelay);

void vTaskDelete(TaskHandle_t xTaskToDelete);