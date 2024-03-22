#include <Keypad74.h>

void Keypad74::_selectRow(byte row)
{
    this->__srm->set(row);
};

int Keypad74::_readKeyState(Key74 *key)
{
    this->_selectRow(key->ROW);
    pinMode(key->PIN, key->PIN_MODE);
    return digitalRead(key->PIN);
};

void Keypad74::_updateKeyState(Key74 *key)
{
    const int signal = this->_readKeyState(key);
    if (  !( (signal == HIGH) || (signal == LOW) )  ) {
        key->clampedStartTime = 0UL;
        key->state = Key74State::KEY74_ERROR;
        return;
    };
    switch (key->state)
    {
        case Key74State::KEY74_REST:
            if (signal == HIGH) {
                key->clampedStartTime = millis();
                key->state = Key74State::KEY74_CLAMPED;
            };
            break;
        case Key74State::KEY74_CLAMPED:
            if (signal == HIGH) {
                if ((millis() - key->clampedStartTime) > KEY74_DEBOUNCE_TIME) {
                    key->clampedStartTime = 0UL;
                    key->state = Key74State::KEY74_PRESSED_CLAMPED;
                };
            } else if (signal == LOW) {
                key->clampedStartTime = 0UL;
                key->state = Key74State::KEY74_REST;
            };
            break;
        case Key74State::KEY74_PRESSED_CLAMPED:
            if (signal == LOW) {
                key->state = Key74State::KEY74_PRESSED;
            };
            break;
        case Key74State::KEY74_ERROR:
            if (signal == HIGH) {
                key->clampedStartTime = millis();
                key->state = Key74State::KEY74_CLAMPED;
            } else if (signal == LOW) {
                key->state = Key74State::KEY74_REST;
            };
            break;
        case Key74State::KEY74_PRESSED:
            break;
        case Key74State::KEY74_IDLE:
            break;
        default:
            key->clampedStartTime = 0UL;
            key->state = Key74State::KEY74_ERROR;
            break;
    };
};

Keypad74::Keypad74(
    uint32_t pinA,
    uint32_t pinB,
    uint32_t pinC,
    uint32_t pinEN
)
{
    this->__srm = new SR74HC138(pinA, pinB, pinC, pinEN);
};

void Keypad74::init()
{
    this->__srm->init();
    this->__srm->enable();
};

bool Keypad74::addKey(Key74 *key)
{
    if (KEY74_MAX_KEYS > this->__keysCount >= 0) {
        pinMode(key->PIN, key->PIN_MODE);
        key->state = Key74State::KEY74_REST;
        this->__keys[this->__keysCount] = key;
        this->__keysCount++;
        return true;
    };
    return false;
};

void Keypad74::updateKeysStates()
{
    for (uint8_t i = 0; i < this->__keysCount; i++) {
        this->_updateKeyState(this->__keys[i]);
    };
};

const char Keypad74::getKey(bool update)
{
    for (uint8_t i = 0; i < this->__keysCount; i++) {
        if (update) {
            this->_updateKeyState(this->__keys[i]);
        };
        if (this->__keys[i]->state == Key74State::KEY74_PRESSED)
        {
            this->__keys[i]->state = Key74State::KEY74_REST;
            return this->__keys[i]->CODE;
        };
    }
    return KEY74_NO_KEY;
};