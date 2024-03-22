#pragma once
#include <Arduino.h>

class SR74HC138 {
    private:
        uint32_t __PIN_A;
        uint32_t __PIN_B;
        uint32_t __PIN_C;
        uint32_t __PIN_EN;
        bool __enabled = false;
    public:
        SR74HC138();
        SR74HC138(
            uint32_t pinA,
            uint32_t pinB,
            uint32_t pinC,
            uint32_t pinEN
        );
        void begin(
            uint32_t pinA,
            uint32_t pinB,
            uint32_t pinC,
            uint32_t pinEN
        );
        void init();
        void enable();
        void disable();
        bool isEnabled();
        void set(byte value=0b000);
};