#include "freertos/task.h"

#include <unistd.h>
#ifdef __cplusplus
extern "C" {
#endif
BaseType_t xTaskCreate(TaskFunction_t pvTaskCode, const char* const pcName, const uint32_t usStackDepth,
                       void* const pvParameters, UBaseType_t uxPriority, TaskHandle_t* const pvCreatedTask) {}

void vTaskDelay(const uint32_t xTicksToDelay) { sleep(xTicksToDelay); }

void vTaskDelete(TaskHandle_t xTaskToDelete) {}
#ifdef __cplusplus
}
#endif