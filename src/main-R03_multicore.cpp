#include <Arduino.h>

void taskA(void *ptParam) {
  while (1) {
    Serial.println("taskA: " + String(xPortGetCoreID()));
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreatePinnedToCore(taskA, "Task A", 1024 * 4, NULL, 1, NULL, 0);
}

void loop() {
  Serial.println("task Loop:" + String(xPortGetCoreID()));
  vTaskDelay(pdMS_TO_TICKS(2000));
}