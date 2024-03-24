#pragma once
#include <Arduino.h>
#include <SR74HC138.h>
#include <SR74HC595.h>

// ! Cимволы

static const uint8_t D8S_CHARAPTERS_LENGTH = 39U;
static const char D8S_CHARAPTERS_KEYS[D8S_CHARAPTERS_LENGTH] = {
    ' ', '-', '+',
    // ! Цифры
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    // ! Буквы (верхний регистр)
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'
};
static const byte D8S_CHARAPTERS_VALUES[D8S_CHARAPTERS_LENGTH] = {
    0b11111111, 0b11111101, 0b11111111,
    // ! Цифры
    0b00000011, 0b10011111, 0b00100101, 0b00001101, 0b10011001,
    0b01001001, 0b01000001, 0b00011111, 0b00000001, 0b00001001,
    // ! Буквы (верхний регистр)
    0b00010001, 0b00000001, 0b01100011, 0b00000011, 0b01100001,
    0b01110001, 0b01000011, 0b10010001, 0b11111111, 0b10001111,
    0b11111111, 0b11100011, 0b11111111, 0b11111111, 0b00000011,
    0b00110001, 0b11111111, 0b11111111, 0b01001001, 0b11111111,
    0b10000011, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111
};

/*
    {'a', 0b00000101}, {'b', 0b11000001}, {'c', 0b11000101}, {'e', 0b00100001}, {'f', 0b01110001},
    {'g', 0b01000011}, {'h', 0b11010001}, {'i', 0b11111111}, {'l', 0b10011111}, {'m', 0b11111111},
    {'n', 0b11010101}, {'o', 0b11000101}, {'p', 0b00110001}, {'q', 0b00011001}, {'r', 0b11110101},
    {'s', 0b01001001}, {'t', 0b11111111}, {'u', 0b11000111}, {'v', 0b11111111}, {'w', 0b11111111}, 
    {'x', 0b11111111}, {'y', 0b11111111}, {'z', 0b11111111}
*/

// ! Функции

unsigned int integerAbsolute(int value);

// ! Главный класс

class D8S74X4 {
    private:
        SR74HC138 *__ic1;
        SR74HC595 *__ic2;
        byte __values[4] = {0b11111111, 0b11111111, 0b11111111, 0b11111111};
        char __valuesText[4] = {' ', ' ', ' ', ' '};
        bool __begined = false;
        bool __inited = false;
    public:
        D8S74X4();
        D8S74X4(
            uint32_t ic1a,
            uint32_t ic1b,
            uint32_t ic1c,
            uint32_t ic1en,
            uint32_t ic2data,
            uint32_t ic2updt,
            uint32_t ic2clk
        );
        void begin(
            uint32_t ic1a,
            uint32_t ic1b,
            uint32_t ic1c,
            uint32_t ic1en,
            uint32_t ic2data,
            uint32_t ic2updt,
            uint32_t ic2clk
        );
        void init();
        bool is_ready();
        /// @brief Записывает значения в буффер.
        /// @note На индикаторе ничего не меняеться.
        /// @param displayNumber Номер дисплея начиная с конца (от 0 до 3).
        /// @param value Значение на входах у индикатора, от 0 до 255 (от 0b00000000 до 0b11111111).
        void writeDisplay(uint8_t displayNumber, byte value);
        /// @brief Устанавливает значения в буффер сразу для всех индикаторов.
        /// @note На индикаторе ничего не меняеться.
        /// @param valueDisplay3 Значение на входах у индикатора (3), от 0 до 255 (от 0b00000000 до 0b11111111).
        /// @param valueDisplay2 Значение на входах у индикатора (2), от 0 до 255 (от 0b00000000 до 0b11111111).
        /// @param valueDisplay1 Значение на входах у индикатора (1), от 0 до 255 (от 0b00000000 до 0b11111111).
        /// @param valueDisplay0 Значение на входах у индикатора (0), от 0 до 255 (от 0b00000000 до 0b11111111).
        void writeDisplays(
            byte valueDisplay3=0b11111111,
            byte valueDisplay2=0b11111111,
            byte valueDisplay1=0b11111111,
            byte valueDisplay0=0b11111111
        );
        /// @brief Устанавливает значения в буффер в формате текста.
        /// @param text Текст, который будет установлен как значение буффера.
        /// @note Обрезает текст до четырёх символов, начивая с первого символа.
        void writeText(String text);
        /// @brief Устанавливает значение в буффер при этом сдвигает текст на опредедённое количество символов.
        /// @param text Текст, который будет установлен как значение буффера.
        /// @param shift_length Значение сдвига, если значение отрицательное, то сдвиг происходит влево, иначе в право.
        /// @note Пустоты заполняются пробелами.
        void writeTextShift(String text, int shift_length);
        /// @brief Считывает значения из буффера и устанавливает значение для входов индикатора.
        /// @note Рекомдуется, использовать именно эту функцию в связке с функцией задержки установленной на 3 милисекунды.
        /// @note ```cpp
        /// @note   while (true) {
        /// @note        updateDisplay(0);
        /// @note        delay(3);
        /// @note        updateDisplay(1);
        /// @note        delay(3);
        /// @note        updateDisplay(2);
        /// @note        delay(3);
        /// @note        updateDisplay(3);
        /// @note        delay(3);
        /// @note   };
        /// @note   ```
        /// @param displayNumber Номер дисплея начиная с конца (от 0 до 3).
        void updateDisplay(uint8_t displayNumber);
        /// @brief Считывает значения из буффера сразу для всех индикаторов и устанавливает значения для входов всех индикаторов.
        /// @note Функция не эффективна так сразу после установки значения на один иникатор переключается моментально на следующий.
        /// @note Индикатор, просто не успевает ничего отобразить.
        /// @note Рекомендуется, использовать функцию:
        /// @note ```cpp
        /// @note D8S7X4::updateDisplay(displayNumber);
        /// @note ```
        void updateDisplays();

        char * get_text_buffer();
};