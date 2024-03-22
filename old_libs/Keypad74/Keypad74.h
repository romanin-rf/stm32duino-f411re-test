#pragma once
#include <Arduino.h>
#include <SR74HC138.h>

#define KEY74_NO_KEY '\0'
#define KEY74_MAX_KEYS 16U
#define KEY74_DEBOUNCE_TIME 10UL

typedef enum {
    KEY74_ERROR = -2,
    KEY74_IDLE = -1,
    KEY74_REST = 0,
    KEY74_CLAMPED = 1,
    KEY74_PRESSED_CLAMPED = 2,
    KEY74_PRESSED = 3
} Key74State;

typedef struct {
    const uint32_t PIN;
    const uint32_t PIN_MODE;
    const uint8_t ROW;
    const uint8_t NUM;
    const char CODE;
    uint32_t clampedStartTime;
    Key74State state;
} Key74;


class Keypad74 {
    private:
        uint8_t __keysCount = 0;
        Key74 *__keys[KEY74_MAX_KEYS] = {};
        SR74HC138 *__srm;
    public:
        Keypad74(
            uint32_t pinA,
            uint32_t pinB,
            uint32_t pinC,
            uint32_t pinEN
        );
        void init();
        bool addKey(Key74 *key);
        void updateKeysStates();
        const char getKey(bool update = true);
        void _selectRow(byte row);
        int _readKeyState(Key74 *key);
        void _updateKeyState(Key74 *key);
};