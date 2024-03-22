#include <LCDMenu.h>

// *********************
// ! LCDLine Functions !
// *********************
LCDLine::LCDLine(GetLineStringType function, const int8_t column, const int8_t row) {
    this->__function = function;
    this->__column = column;
    this->__row = row;
};

void LCDLine::render(LCDMenuDisplayClass *lcd, const int8_t columns, const int8_t rows) {
    String text = this->__function();
    const int needed = columns - text.length();
    if (needed > 0) {
        for (int i = needed; i > 0; i--) {
            text += ' ';
        };
    } else if (needed < 0) {
        text = text.substring(0, columns);
    };
    lcd->setCursor(this->__column, this->__row);
    lcd->print(text);
};

// ***********************
// ! LCDScreen Functions !
// ***********************
LCDScreen::LCDScreen() {};
LCDScreen::LCDScreen(LCDLine *first) {
    this->add_line(first);
};
LCDScreen::LCDScreen(LCDLine *first, LCDLine *second) {
    this->add_line(first);
    this->add_line(second);
};
LCDScreen::LCDScreen(LCDLine *first, LCDLine *second, LCDLine *third) {
    this->add_line(first);
    this->add_line(second);
    this->add_line(third);
};
LCDScreen::LCDScreen(LCDLine *first, LCDLine *second, LCDLine *third, LCDLine *fourth) {
    this->add_line(first);
    this->add_line(second);
    this->add_line(third);
    this->add_line(fourth);
};

bool LCDScreen::add_line(LCDLine *line) {
    if (LCD_MENU_MAX_LINES > this->__countLines) {
        this->__lines[this->__countLines] = line;
        this->__countLines++;
        return true;
    };
    return false;
};

void LCDScreen::render(LCDMenuDisplayClass *lcd, const int8_t columns, const int8_t rows) {
    if (this->__countLines > 0) {
        if (this->__index >= 0) {
            for (int i = 0; i < this->__countLines; i++) {
                this->__lines[i]->render(lcd, columns, rows);
            };
        };
    } else {
        lcd->clear();
    };
};

// *********************
// ! LCDMenu Functions !
// *********************
LCDMenu::LCDMenu(LCDMenuDisplayClass *lcd, const int8_t columns, const int8_t rows) {
    this->__lcd = lcd;
    this->__columns = columns;
    this->__rows = rows;
};

bool LCDMenu::add_screen(LCDScreen *screen) {
    if (LCD_MENU_MAX_SCREENS > this->__countScreens) {
        screen->__index = this->__countScreens;
        this->__screens[this->__countScreens] = screen;
        this->__countScreens++;
        return true;
    };
    return false;
};

void LCDMenu::next_screen() {
    if (this->__countScreens > (this->__currentScreen + 1)) {
        this->__currentScreen++;
    };
};

void LCDMenu::prev_screen() {
    if ((this->__currentScreen - 1) >= 0) {
        this->__currentScreen--;
    };
};

void LCDMenu::render() {
    const uint32_t startThisRenderTime = millis();
    if (this->__countScreens > 0) {
        this->__screens[this->__currentScreen]->render(this->__lcd, this->__columns, this->__rows);
    } else {
        this->__lcd->clear();
    };
    const uint32_t endThisRenderTime = millis();
    this->__currentFPS = 1000.0f / float(endThisRenderTime - this->__renderLastTime);
    this->__renderLastTime = endThisRenderTime;
    this->__renderLastLossTime = endThisRenderTime - startThisRenderTime;
};

float LCDMenu::get_fps() { return this->__currentFPS; };

uint32_t LCDMenu::get_frame_loss() { return this->__renderLastLossTime; };
