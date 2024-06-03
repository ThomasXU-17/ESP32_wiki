#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led
{
private:
    byte _ledpin;
    String _color;
    uint32_t _delayTime;

    TaskHandle_t _blinkHandle;

public:
    Led();
    // Led(byte pin);
    Led(byte pin, uint32_t delayTime = 1000, String color = "UNKOWN");
    ~Led();
    byte getPin() const;
    void setPin(byte pin);
    String getColor() const;
    uint32_t getDelayTime() const;
    void on() const;
    void off() const;
    void toggle() const;

    // for led_rtos
    void Blink();
    static void startBlinkImpl(void *_this);
    void startBlink();
    void endBlink();
};

#endif