#include <7SD74HC.h>


IC27SD74HC::IC27SD74HC(
    const uint8_t __IC2DATA,
    const uint8_t __IC2UPDT,
    const uint8_t __IC2CLK,
    const uint8_t __IC1A,
    const uint8_t __IC1B,
    const uint8_t __IC1C,
    const uint8_t __IC1EN
)
{
    this->__IC2DATA = __IC2DATA;
    this->__IC2UPDT = __IC2UPDT;
    this->__IC2CLK = __IC2CLK;
    this->__IC1A = __IC1A;
    this->__IC1B = __IC1B;
    this->__IC1C = __IC1C;
    this->__IC1EN = __IC1EN;
};

void IC27SD74HC::init()
{
    pinMode(this->__IC2DATA, OUTPUT);
    pinMode(this->__IC2UPDT, OUTPUT);
    pinMode(this->__IC2CLK, OUTPUT);
    pinMode(this->__IC1A, OUTPUT);
    pinMode(this->__IC1B, OUTPUT);
    pinMode(this->__IC1C, OUTPUT);
    pinMode(this->__IC1EN, OUTPUT);
};

void IC27SD74HC::enable()
{
    digitalWrite(this->__IC1EN, HIGH);
};

void IC27SD74HC::disable()
{
    digitalWrite(this->__IC1EN, LOW);
};

void IC27SD74HC::select(const uint8_t numberDisplay)
{
    switch (numberDisplay)
    {
        case 0:
            digitalWrite(this->__IC1A, LOW);
            digitalWrite(this->__IC1B, LOW);
            digitalWrite(this->__IC1C, LOW);
            break;
        case 1:
            digitalWrite(this->__IC1A, HIGH);
            digitalWrite(this->__IC1B, LOW);
            digitalWrite(this->__IC1C, LOW);
            break;
        case 2:
            digitalWrite(this->__IC1A, LOW);
            digitalWrite(this->__IC1B, HIGH);
            digitalWrite(this->__IC1C, LOW);
            break;
        case 3:
            digitalWrite(this->__IC1A, HIGH);
            digitalWrite(this->__IC1B, HIGH);
            digitalWrite(this->__IC1C, LOW);
            break;
        default:
            digitalWrite(this->__IC1A, LOW);
            digitalWrite(this->__IC1B, LOW);
            digitalWrite(this->__IC1C, LOW);
            break;
    };
};

void IC27SD74HC::write(const byte value)
{
    digitalWrite(this->__IC2UPDT, LOW);
    shiftOut(this->__IC2DATA, this->__IC2CLK, LSBFIRST, value);
    digitalWrite(this->__IC2UPDT, HIGH);
};

void IC27SD74HC::selectWrite(const uint8_t numberDisplay, byte value)
{
    this->select(numberDisplay);
    this->write(value);
};

void IC27SD74HC::writeAll(byte valueDisplay3, byte valueDisplay2, byte valueDisplay1, byte valueDisplay0)
{
    this->__values[0] = valueDisplay0;
    this->__values[1] = valueDisplay1;
    this->__values[2] = valueDisplay2;
    this->__values[3] = valueDisplay3;
};

void IC27SD74HC::selectUpdate(const uint8_t numberDisplay)
{
    this->selectWrite(numberDisplay, this->__values[numberDisplay]);
};

void IC27SD74HC::updateAll()
{
    this->selectWrite(0, this->__values[0]);
    this->selectWrite(1, this->__values[1]);
    this->selectWrite(2, this->__values[2]);
    this->selectWrite(3, this->__values[3]);
};