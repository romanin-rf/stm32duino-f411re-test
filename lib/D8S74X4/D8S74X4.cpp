#include <D8S74X4.h>

unsigned int integerAbsolute(int value) { if (value < 0) { return value * -1; }; return value; };


D8S74X4::D8S74X4() {};
D8S74X4::D8S74X4(
    uint32_t ic1a,
    uint32_t ic1b,
    uint32_t ic1c,
    uint32_t ic1en,
    uint32_t ic2data,
    uint32_t ic2updt,
    uint32_t ic2clk
)
{
    begin(ic1a, ic1b, ic1c, ic1en, ic2data, ic2updt, ic2clk);
};

void D8S74X4::begin(
    uint32_t ic1a,
    uint32_t ic1b,
    uint32_t ic1c,
    uint32_t ic1en,
    uint32_t ic2data,
    uint32_t ic2updt,
    uint32_t ic2clk
)
{
    if (!this->__begined) {
        this->__ic1 = new SR74HC138(ic1a, ic1b, ic1c, ic1en);
        this->__ic2 = new SR74HC595(ic2data, ic2updt, ic2clk);
        this->__begined = true;
    };
};

void D8S74X4::init()
{
    if ((!this->__inited) && (this->__begined)) {
        this->__ic1->init();
        this->__ic2->init();
        this->__ic1->enable();
    };
};

bool D8S74X4::is_ready()
{
    return this->__begined && this->__inited;
};

void D8S74X4::writeDisplay(uint8_t displayNumber, byte value)
{
    if (3 >= displayNumber >= 0) {
        this->__values[displayNumber] = value;
    }
};

void D8S74X4::writeDisplays(byte valueDisplay3, byte valueDisplay2, byte valueDisplay1, byte valueDisplay0)
{
    this->writeDisplay(0, valueDisplay0);
    this->writeDisplay(1, valueDisplay1);
    this->writeDisplay(2, valueDisplay2);
    this->writeDisplay(3, valueDisplay3);
};

void D8S74X4::updateDisplay(uint8_t displayNumber)
{
    if (3 >= displayNumber >= 0) {
        this->__ic1->set(displayNumber);
        this->__ic2->set(this->__values[displayNumber]);
    };
};

void D8S74X4::updateDisplays()
{
    this->updateDisplay(0);
    this->updateDisplay(1);
    this->updateDisplay(2);
    this->updateDisplay(3);
};

void D8S74X4::writeText(String text)
{
    char t = 0;
    char s = 0;
    byte values[4] = {0b11111110, 0b11111110, 0b11111110, 0b11111110};
    if (text.length() < 4) {
        for (int n = 4 - text.length(); n > 0; n--) {
            text += ' ';
        };
    };
    for (uint8_t vi = 0U; vi < 4; vi++) {
        t = text[vi];
        for (uint8_t si = 0U; si < D8S_CHARAPTERS_LENGTH; si++) {
            s = D8S_CHARAPTERS_KEYS[si];
            if (t == s) {
                values[vi] = D8S_CHARAPTERS_VALUES[si];
                break;
            };
        };
    };
    this->writeDisplays(values[0], values[1], values[2], values[3]);
};

void D8S74X4::writeTextShift(
    String text,
    int level
)
{
    const unsigned int alevel = integerAbsolute(level);
    if (alevel >= text.length()) {
        text = String();
    } else if (level == 0) {
        // *pass
    } else if (level > 0) {
        for (int i = level; i > 0; i--) { text = ' ' + text; };
    } else if (level < 0) {
        text = text.substring(alevel);
    };
    return this->writeText(text);
};