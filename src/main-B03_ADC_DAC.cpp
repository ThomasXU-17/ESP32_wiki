#include <Arduino.h>
#include <esp32-hal-dac.h> // 需要引入DAC库

#ifndef ADC_DAC_SAMPLE_ESP32
#define ADC_PIN 34
#define DAC_PIN 25 // ESP32 DAC1-25, DAC2-26
#endif

uint8_t dac_value = 0;  

void setup() {
  Serial.begin(115200);
}

void loop() {
  float vout = (dac_value / 255.0) * 3.3;
  Serial.printf("Vout = %0.2f V\n", vout);
  dac_value++;
  // analogWrite(DAC_PIN, dac_value); // 不可以用analogWrite，它是PWM信号
  dacWrite(DAC_PIN, dac_value);

  // int adc_value = analogRead(ADC_PIN);  // ref of adc: https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/adc.html
  // float vin = (adc_value / 4095.0) * 3.3; // ESP32的ADC范围能达到3.3V
  float vin = analogReadMilliVolts(ADC_PIN) / 1000.0; // 量程不会达到3.3V，最高一般2500mv
  Serial.printf("Vin = %0.2f V\n", vin);
  delay(50);
}

