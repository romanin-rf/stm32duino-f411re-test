#include <SR74HC138.h>

SR74HC138::SR74HC138() {};

SR74HC138::SR74HC138(uint32_t pinA, uint32_t pinB, uint32_t pinC, uint32_t pinEN)
{
    begin(pinA, pinB, pinC, pinEN);
};

void SR74HC138::begin(uint32_t pinA, uint32_t pinB, uint32_t pinC, uint32_t pinEN)
{
    this->__PIN_A = pinA;
    this->__PIN_B = pinB;
    this->__PIN_C = pinC;
    this->__PIN_EN = pinEN;
};

void SR74HC138::init()
{
    pinMode(this->__PIN_A, OUTPUT);
    pinMode(this->__PIN_B, OUTPUT);
    pinMode(this->__PIN_C, OUTPUT);
    pinMode(this->__PIN_EN, OUTPUT);
};

void SR74HC138::enable()
{
    digitalWrite(this->__PIN_EN, HIGH);
    this->__enabled = true;
};

void SR74HC138::disable()
{
    digitalWrite(this->__PIN_EN, LOW);
    this->__enabled = false;
};

bool SR74HC138::isEnabled()
{
    return this->__enabled;
};

void SR74HC138::set(byte value)
{
    /// condition ? expression-true : expression-false;
    digitalWrite(this->__PIN_A, (value & 0b001) ? HIGH : LOW);
    digitalWrite(this->__PIN_B, (value & 0b010) ? HIGH : LOW);
    digitalWrite(this->__PIN_C, (value & 0b100) ? HIGH : LOW);
};