#include <Keypad74.h>

// ! Основной класс

Keypad74::Keypad74() {};
Keypad74::Keypad74(uint32_t pinA, uint32_t pinB, uint32_t pinC, uint32_t pinEN)
{
    this->begin(pinA, pinB, pinC, pinEN);
};

void Keypad74::begin(uint32_t pinA, uint32_t pinB, uint32_t pinC, uint32_t pinEN)
{
    if (!this->__begined) {
        this->__srm = new SR74HC138(pinA, pinB, pinC, pinEN);
        this->__begined = true;
    };
};

void Keypad74::init()
{
    if (this->__begined && !this->__inited) {
        this->__srm->init();
        this->__srm->enable();
        this->__inited = true;
    };
};

bool Keypad74::is_ready() { return this->__begined && this->__inited; };

bool Keypad74::add_key(Key74 *key)
{
    if ( this->is_ready() && (KEYPAD74_MAX_KEYS > this->__keysCount >= 0) )
    {
        pinMode(key->PIN, key->PIN_MODE);
        this->__keys[this->__keysCount] = key;
        this->__keysCount++;
        return true;
    };
    return false;
};

void Keypad74::select_key(Key74 *key)
{
    pinMode(key->PIN, key->PIN_MODE);
    this->__srm->set(key->ROW);
};

int Keypad74::read_key(Key74 *key)
{
    this->select_key(key);
    return digitalRead(key->PIN);
};

void Keypad74::update_key_state(Key74 *key)
{
    const int signal = this->read_key(key);
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
                if ((millis() - key->clampedStartTime) > this->__debounceTime) {
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

void Keypad74::update_keys_states()
{
    for (uint8_t i = 0; i < this->__keysCount; i++) {
        this->update_key_state(this->__keys[i]);
    };
};

const char Keypad74::get_key(bool update=true)
{
    for (uint8_t i = 0; i < this->__keysCount; i++) {
        if (update) {
            this->update_key_state(this->__keys[i]);
        };
        if (this->__keys[i]->state == Key74State::KEY74_PRESSED)
        {
            this->__keys[i]->state = Key74State::KEY74_REST;
            return this->__keys[i]->CODE;
        };
    };
    return KEYPAD74_NO_KEY;
};