#include "Led.h"

Led::Led()
{
    this->_ledpin = 47;
    pinMode(this->_ledpin, OUTPUT);
    this->_color = "UNKOWN";
    this->_delayTime = 1000;

    Serial.print("Default 构造函数 - ");
    Serial.println(this->_color);
}

// Led::Led(byte pin){
//     setPin(pin);
//     this->_color = "UNKOWN";

//     Serial.print("Overloaded 构造函数 para - ");
//     Serial.println(this->_color);
// }

Led::Led(byte pin, uint32_t delayTime, String color) : _delayTime(delayTime), _color(color)
{
    setPin(pin);

    Serial.print("Overloaded 构造函数 2 para - ");
    Serial.println(this->_color);
}

Led::~Led()
{
    Serial.print("析构函数 - ");
    Serial.println(this->_color);
}

byte Led::getPin() const
{
    return this->_ledpin;
}

void Led::setPin(byte pin)
{
    if (pin <= 48)
    {
        this->_ledpin = pin;
    }
    else
    {
        Serial.println("Invalid pin number, use default pin 48");
        this->_ledpin = 48;
    }
    pinMode(this->_ledpin, OUTPUT);
}

uint32_t Led::getDelayTime() const
{
    return this->_delayTime;
}

String Led::getColor() const
{
    return this->_color;
}

void Led::on() const
{
    digitalWrite(this->_ledpin, HIGH);
}

void Led::off() const
{
    digitalWrite(this->_ledpin, LOW);
    Serial.print("Off - ");
    Serial.println(digitalRead(this->_ledpin));
}

void Led::toggle() const
{
    digitalWrite(this->_ledpin, !digitalRead(this->_ledpin));
}

void Led::Blink()
{
    while (1)
    {
        vTaskDelay(this->getDelayTime());
        this->toggle();
        Serial.print("Blink - ");
        Serial.println(digitalRead(this->_ledpin));
    }
}

void Led::startBlinkImpl(void *_this)
{
    static_cast<Led *>(_this)->Blink();
}

void Led::startBlink()
{
    xTaskCreate(Led::startBlinkImpl, "Blink", 1024 * 2, this, 5, &_blinkHandle);
}

void Led::endBlink()
{
    vTaskDelete(_blinkHandle);
    //vTaskDelay(500);
    this->off(); // off() 要放在后面，否则led有可能还会被翻转一次
}