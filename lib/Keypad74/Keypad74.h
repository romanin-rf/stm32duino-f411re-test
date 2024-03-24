#pragma once
#include <Arduino.h>
#include <SR74HC138.h>

// ! Настройки

#define KEYPAD74_NO_KEY '\0'
#define KEYPAD74_MAX_KEYS 16U
#define KEYPAD74_DEBOUNCE_TIME 10UL

// ! Типы

typedef enum {
    KEY74_ERROR = -2,
    KEY74_IDLE = -1,
    KEY74_REST = 0,
    KEY74_CLAMPED = 1,
    KEY74_PRESSED_CLAMPED = 2,
    KEY74_PRESSED = 3
} Key74State;

/*
typedef struct {
    const uint32_t PIN;
    const uint8_t ROW;
    const uint8_t NUM;
    const char CODE;
    uint32_t clampedStartTime;
    Key74State state;
} Key74;
*/

typedef void (*DelayFunc)(uint32_t);

// ! Тип классы

class Key74 {
    friend class Keypad74;
    public:
        uint32_t clampedStartTime = 0;
        Key74State state = Key74State::KEY74_REST;
        uint32_t PIN;
        uint8_t ROW;
        uint8_t NUM;
        char CODE;

        Key74(uint32_t pin, uint8_t row, uint8_t num, const char code);
};


// ! Основной класс

class Keypad74 {
    private:
        SR74HC138 *__srm;
        uint8_t __keysCount = 0;
        Key74 *__keys[KEYPAD74_MAX_KEYS] = {};
        uint32_t __debounceTime = KEYPAD74_DEBOUNCE_TIME;
        bool __begined = false;
        bool __inited = false;
    public:
        Keypad74();
        Keypad74(uint32_t pinA, uint32_t pinB, uint32_t pinC, uint32_t pinEN);
        void begin(uint32_t pinA, uint32_t pinB, uint32_t pinC, uint32_t pinEN);
        void init();
        bool is_ready();
        bool add_key(Key74 *key);
        void select_key(Key74 *key);
        int read_key(Key74 *key);
        void update_key_state(Key74 *key);
        void update_keys_states();
        const char get_key(bool update=true);
};