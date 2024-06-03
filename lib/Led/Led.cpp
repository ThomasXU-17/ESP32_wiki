#include "Led.h"

Led::Led(){
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

Led::Led(byte pin, uint32_t delayTime, String color): _delayTime(delayTime), _color(color){
    setPin(pin);

    Serial.print("Overloaded 构造函数 2 para - ");
    Serial.println(this->_color);
}

Led::~Led(){
    Serial.print("析构函数 - ");
    Serial.println(this->_color);
}

byte Led::getPin() const{
    return this->_ledpin;
}

void Led::setPin(byte pin){
    if (pin<=48){
        this->_ledpin = pin;
        
    }else{
        Serial.println("Invalid pin number, use default pin 48");
        this->_ledpin = 48;
    }
    pinMode(this->_ledpin, OUTPUT);
}

uint32_t Led::getDelayTime() const{
    return this->_delayTime;
}

void Led::on() const{
    digitalWrite(this->_ledpin, HIGH);
}

void Led::off() const{
    digitalWrite(this->_ledpin, LOW);
}

void Led::toggle() const{
    digitalWrite(this->_ledpin, !digitalRead(this->_ledpin));
}