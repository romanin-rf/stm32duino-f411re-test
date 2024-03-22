#pragma once
#include <Arduino.h>

static unsigned char D7S_CHARAPTERS[60][2] = {
    {' ', 0b11111111},
    {'0', 0b00000011},
    {'1', 0b10011111},
    {'2', 0b00100101},
    {'3', 0b00001101},
    {'4', 0b10011001},
    {'5', 0b01001001},
    {'6', 0b01000001},
    {'7', 0b00011111},
    {'8', 0b00000001},
    {'9', 0b00001001},
    {'A', 0b00010001},
    {'B', 0b00000001},
    {'C', 0b01100011},
    {'D', 0b00000011},
    {'E', 0b01100001},
    {'F', 0b01110001},
    {'G', 0b01000011},
    {'H', 0b10010001},
    {'I', 0b11111111},
    {'J', 0b10001111},
    {'K', 0b11111111},
    {'L', 0b11100011},
    {'M', 0b11111111},
    {'N', 0b11111111},
    {'O', 0b00000011},
    {'P', 0b00110001},
    {'Q', 0b11111111},
    {'R', 0b11111111},
    {'S', 0b01001001},
    {'T', 0b11111111},
    {'U', 0b10000011},
    {'V', 0b11111111},
    {'W', 0b11111111},
    {'X', 0b11111111},
    {'Y', 0b11111111},
    {'Z', 0b11111111},
    {'a', 0b00000101},
    {'b', 0b11000001},
    {'c', 0b11000101},
    {'e', 0b00100001},
    {'f', 0b01110001},
    {'g', 0b01000011},
    {'h', 0b11010001},
    {'i', 0b11111111},
    {'l', 0b10011111},
    {'m', 0b11111111},
    {'n', 0b11010101},
    {'o', 0b11000101},
    {'p', 0b00110001},
    {'q', 0b00011001},
    {'r', 0b11110101},
    {'s', 0b01001001},
    {'t', 0b11111111},
    {'u', 0b11000111},
    {'v', 0b11111111},
    {'w', 0b11111111},
    {'x', 0b11111111},
    {'y', 0b11111111},
    {'z', 0b11111111}
};

/// @brief A class for controlling four 8-segment indicators connected via 74HC138 (to switch between indicators) and 74HC595 (to set a value).
class IC27SD74HC {
    private:
        byte __values[4] = {0b11111111, 0b11111111, 0b11111111, 0b11111111};
        uint8_t __IC2DATA;
        uint8_t __IC2UPDT;
        uint8_t __IC2CLK;
        uint8_t __IC1A;
        uint8_t __IC1B;
        uint8_t __IC1C;
        uint8_t __IC1EN;
    public:
        /// @brief Constructor of the indicators control class.
        /// @param __IC2DATA The DATA pin number (74HC595).
        /// @param __IC2UPDT The UPDT pin number (74HC595).
        /// @param __IC2CLK The CLK pin number (74HC595).
        /// @param __IC1A Pin number for indicator selection (74HC138).
        /// @param __IC1B Pin number for indicator selection (74HC138).
        /// @param __IC1C Pin number for indicator selection (74HC138).
        /// @param __IC1EN The pin number for turning on the chip (74HC138).
        IC27SD74HC(
            const uint8_t __IC2DATA,
            const uint8_t __IC2UPDT,
            const uint8_t __IC2CLK,
            const uint8_t __IC1A,
            const uint8_t __IC1B,
            const uint8_t __IC1C,
            const uint8_t __IC1EN
        );
        /// @brief Sets up pins.
        void init();
        /// @brief Sends a signal to IC1EN.
        void enable();
        /// @brief Sends a signal to IC1EN.
        void disable();
        /// @brief Selecting an indicator.
        /// @param numberDisplay A number from 0-3.
        void select(const uint8_t numberDisplay);
        /// @brief Recording the value for the indicator.
        /// @param value The value is from 0-256. RECOMMENDED: Use the following format: `0b00000001`.
        void write(byte value);
        /// @brief Selecting an indicator and recording data.ы
        /// @param numberDisplay A number from 0-3.
        /// @param value The value is from 0-256. RECOMMENDED: Use the following format: `0b00000001`.
        void selectWrite(const uint8_t numberDisplay, byte value);
        /// @brief Writing data to the buffer. To display data simultaneously on all indicators, use:
        /// @brief  ```cpp
        /// @brief  IC27SD74HC::updateAll();
        /// @brief  ```
        /// @brief  `or`
        /// @brief  ```cpp
        /// @brief  void loop() {
        /// @brief      IC27SD74HC::selectUpdate(0);
        /// @brief      delay(3);
        /// @brief      IC27SD74HC::selectUpdate(1);
        /// @brief      delay(3);
        /// @brief      IC27SD74HC::selectUpdate(2);
        /// @brief      delay(3);
        /// @brief      IC27SD74HC::selectUpdate(3);
        /// @brief      delay(3);
        /// @brief  };
        /// @brief  ```
        /// @brief `delay(3);` - Higher values will cause flickering. And only one indicator will work without delay.
        /// @param valueDisplay0 Data values for the first indicator.
        /// @param valueDisplay1 Data values for the second indicator.
        /// @param valueDisplay2 Data values for the third indicator.
        /// @param valueDisplay3 Data values for the fourth indicator.
        void writeAll(
            byte valueDisplay3=0b11111111,
            byte valueDisplay2=0b11111111,
            byte valueDisplay1=0b11111111,
            byte valueDisplay0=0b11111111
        );
        /// @brief Switching and updating.
        /// @param numberDisplay A number from 0-3.
        void selectUpdate(const uint8_t numberDisplay);
        /// @brief Reads the values from the buffer and touch them for all indicators.
        void updateAll();
        /// @brief !!! IN DEVELOPMENT !!!
        /// @deprecated
        void writeAllText(String text);
};