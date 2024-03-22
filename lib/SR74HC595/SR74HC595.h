#pragma
#include <Arduino.h>


class SR74HC595 {
    private:
        uint32_t __PIN_DATA;
        uint32_t __PIN_UPDT;
        uint32_t __PIN_CLK;
    public:
        SR74HC595();
        SR74HC595(uint32_t pinDATA, uint32_t pinUPDT, uint32_t pinCLK);
        void begin(uint32_t pinDATA, uint32_t pinUPDT, uint32_t pinCLK);
        void init();
        void set(byte value=0U);
};