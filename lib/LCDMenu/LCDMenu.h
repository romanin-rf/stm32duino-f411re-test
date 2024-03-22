#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// ! Настройки

#define LCDMenuDisplayClass LiquidCrystal_I2C
#define LCD_MENU_MAX_SCREENS 8
#define LCD_MENU_MAX_LINES 2

// ! Типы

typedef String (*GetLineStringType)();

// ! Основной код

class LCDLine {
    friend class LCDScreen;
    public:
        LCDLine(GetLineStringType function, const int8_t column, const int8_t row);
        void render(LCDMenuDisplayClass *lcd, const int8_t columns, const int8_t rows);
    private:
        int8_t __column;
        int8_t __row;
        GetLineStringType __function;
};


class LCDScreen {
    friend class LCDMenu;
    public:
        LCDScreen();
        LCDScreen(LCDLine *first);
        LCDScreen(LCDLine *first, LCDLine *second);
        LCDScreen(LCDLine *first, LCDLine *second, LCDLine *third);
        LCDScreen(LCDLine *first, LCDLine *second, LCDLine *third, LCDLine *fourth);
        bool add_line(LCDLine *line);
        void render(LCDMenuDisplayClass *lcd, const int8_t columns, const int8_t rows);
    private:
        int8_t __index = -1;
        int8_t __countLines = 0;
        LCDLine *__lines[LCD_MENU_MAX_LINES];
};


class LCDMenu {
    public:
        LCDMenu(LCDMenuDisplayClass *lcd, const int8_t columns, const int8_t rows);
        bool add_screen(LCDScreen *screen);
        void next_screen();
        void prev_screen();
        void render();
        float get_fps();
        uint32_t get_frame_loss();
    private:
        int8_t __columns;
        int8_t __rows;
        LiquidCrystal_I2C *__lcd;
        float __currentFPS = 0;
        uint32_t __renderLastTime = 0;
        uint32_t __renderLastLossTime = 0;
        int8_t __currentScreen = 0;
        int8_t __countScreens = 0;
        LCDScreen *__screens[LCD_MENU_MAX_SCREENS];
};