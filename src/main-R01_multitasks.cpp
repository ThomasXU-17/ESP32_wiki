#include <Arduino.h>

#ifndef MULTITASKS
#define LED1_PIN 23
#define LED2_PIN 22
#define LED1_DELAY 500
#define LED2_DELAY 1000
#endif

typedef struct {
    byte pin;
    int delay;
} LED_t;

void task_led(void * pt){
    LED_t * ptLED = (LED_t *) pt;
    byte pin = ptLED->pin;
    int delay = ptLED->delay;

    pinMode(pin, OUTPUT);
    for(;;){
        digitalWrite(pin, !digitalRead(pin));    
        vTaskDelay(pdMS_TO_TICKS(delay));
    }
}

void setup(){
    Serial.begin(115200);

    LED_t led1;
    led1.pin = LED1_PIN;
    led1.delay = LED2_DELAY;

    LED_t led2 = {
        .pin = LED2_PIN,
        .delay = LED2_DELAY
    };

    if (xTaskCreate(
        task_led, 
        "Blink 23", 
        1024, 
        (void *) &led1, 
        1, 
        NULL
    ) == pdPASS){
        Serial.println("Task1: LED1 flash task created");
    }

    if (xTaskCreate(
        task_led, 
        "Blink 22", 
        1024, 
        (void *) &led2, 
        1, 
        NULL
    ) == pdPASS){
        Serial.println("Task2: LED2 flash task created");
    }
}

void loop(){
    
}   