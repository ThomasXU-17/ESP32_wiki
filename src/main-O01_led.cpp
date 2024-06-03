#include <Arduino.h>
#include "Led.h"

#ifndef LED_SAMPLE_ESP32S3
#define PIN_LED_RED 46
#define PIN_LED_YELLOW 47
#define PIN_LED_GREEN 48
#endif

void task_led(void *pt) {
  Led led = *(Led *)pt;
  while (1) {
    led.toggle();
    vTaskDelay(led.getDelayTime());
  }
}

Led ledGreen(PIN_LED_GREEN, 500, "GREEN");
Led ledYellow(PIN_LED_YELLOW, 2000, "YELLOW");
Led ledRed(PIN_LED_RED, 3000, "RED");

void setup(){
    Serial.begin(115200);

    if (xTaskCreate(task_led,
                  "Blink Green",
                  1024,
                  &ledGreen,
                  1,
                  NULL) == pdPASS)
    Serial.println("Task: Green LED Created.");

    if (xTaskCreate(task_led,
                  "Blink Yellow",
                  1024,
                  &ledYellow,
                  1,
                  NULL) == pdPASS)
    Serial.println("Task: Yellow LED Created.");

    if (xTaskCreate(task_led,
                  "Blink Red",
                  1024,
                  &ledRed,
                  1,
                  NULL) == pdPASS)
    Serial.println("Task: Red LED Created.");
}

void loop(){
    delay(500);
}