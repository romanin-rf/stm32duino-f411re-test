#include <SR74HC595.h>


SR74HC595::SR74HC595() {};

SR74HC595::SR74HC595(uint32_t pinDATA, uint32_t pinUPDT, uint32_t pinCLK)
{
    begin(pinDATA, pinUPDT, pinCLK);
};

void SR74HC595::begin(uint32_t pinDATA, uint32_t pinUPDT, uint32_t pinCLK)
{
    this->__PIN_DATA = pinDATA;
    this->__PIN_UPDT = pinUPDT;
    this->__PIN_CLK = pinCLK;
};

void SR74HC595::init()
{
    pinMode(this->__PIN_DATA, OUTPUT);
    pinMode(this->__PIN_UPDT, OUTPUT);
    pinMode(this->__PIN_CLK, OUTPUT);
};

void SR74HC595::set(byte value)
{
    digitalWrite(this->__PIN_UPDT, LOW);
    shiftOut(this->__PIN_DATA, this->__PIN_CLK, LSBFIRST, value);
    digitalWrite(this->__PIN_UPDT, HIGH);
};