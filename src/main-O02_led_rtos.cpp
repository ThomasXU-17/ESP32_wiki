/*
  参考:
   https://www.freertos.org/FreeRTOS_Support_Forum_Archive/July_2010/freertos_Is_it_possible_create_freertos_task_in_c_3778071.html
   https://stackoverflow.com/questions/45831114/c-freertos-task-invalid-use-of-non-static-member-function
   https://electronics.stackexchange.com/questions/373793/using-c-objects-within-freertos-tasks
*/

#include <Arduino.h>
#include "Led.h"

#ifndef LED_SAMPLE_ESP32S3
#define PIN_LED_RED 46
#define PIN_LED_YELLOW 47
#define PIN_LED_GREEN 48
#endif

Led ledGreen(PIN_LED_GREEN, 500, "GREEN"); // 一定要定义全局变量
Led ledYellow(PIN_LED_YELLOW, 2000, "YELLOW");
Led ledRed(PIN_LED_RED, 3000, "RED");

void setup()
{
  Serial.begin(115200);

  ledGreen.startBlink();
  vTaskDelay(10250);
  ledGreen.endBlink();
}

void loop()
{
  delay(500);
}