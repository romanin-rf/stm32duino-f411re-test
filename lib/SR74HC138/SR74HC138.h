#pragma once
#include <Arduino.h>


class SR74HC138 {
    private:
        uint32_t __PIN_A;
        uint32_t __PIN_B;
        uint32_t __PIN_C;
        uint32_t __PIN_EN;
        byte __value = 0b000U;
        bool __inited = false;
        bool __enabled = false;
    public:
        SR74HC138();
        SR74HC138(uint32_t pinA, uint32_t pinB, uint32_t pinC, uint32_t pinEN);
        void begin(uint32_t pinA, uint32_t pinB, uint32_t pinC, uint32_t pinEN);
        void init();
        /// @brief Устанавливает на пине EN `высокий` сигнал.
        void enable();
        /// @brief Устанавливает на пине EN `низкий` сигнал.
        void disable();
        /// @brief Проверяет сигнал на пине EN.
        /// @return `true`, если на пине установлен высокий сигнал, иначе `false`.
        bool is_enabled();
        /// @brief Устанавливает значение сдвига на входах 74HC138.
        /// @param value Значение от 0 до 7 (от 0b000 до 0b111).
        void set(byte value=0U);
};