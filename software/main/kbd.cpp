#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <vector>

extern "C" {
void app_main();
}

void app_main() {
    int i = 0;
    std::vector<int> a;
    while (1) {

        printf("[%d] Hello world!\n", i);
        i++;
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}