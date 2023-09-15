#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"
#include "driver/gpio.h"
#include "soc/wdev_reg.h"
#include "xtensa/core-macros.h"

#include "define.h"

#include "firebase_module.h"

void FIREBASE_TASK(void *pvParameter)
{
    (void)pvParameter;
    firebase_setup();
    delay(100);
    Serial.println("Firebase Start");

    while(1)
    {
        firebase_loop();
        vTaskDelay(1000 / portTICK_RATE_MS);
        // vTaskDelay(100 / portTICK_RATE_MS);
    }
}

void freeRTOS_setup() {
    
    xTaskCreatePinnedToCore(&FIREBASE_TASK, "firebase_task", 8192, NULL, 6, NULL, ARDUINO_RUNNING_CORE);

}