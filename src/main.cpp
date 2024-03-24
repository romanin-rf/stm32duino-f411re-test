#include <main.h>

// ! Временные переменные

static String D8S4_TEXT = "HELLO";
static int D8S4_TEXT_LEVEL = D8S4_TEXT.length();
static char keyLast = KEYPAD74_NO_KEY;
static char keyLastReal = ' ';

// ! Настройки кнопок

static const unsigned int KEYPAD_KEYS_COUNT = 16;
static Key74 KEYPAD_KEYS[KEYPAD_KEYS_COUNT] = {
    Key74(COLUMN0, 0, 7, '7'), Key74(COLUMN1, 0, 8, '8'), Key74(COLUMN2, 0, 9, '9'), Key74(COLUMN3, 0, 15, '+'),
    Key74(COLUMN0, 1, 4, '4'), Key74(COLUMN1, 1, 5, '5'), Key74(COLUMN2, 1, 6, '6'), Key74(COLUMN3, 1, 14, '-'),
    Key74(COLUMN0, 2, 1, '1'), Key74(COLUMN1, 2, 2, '2'), Key74(COLUMN2, 2, 3, '3'), Key74(COLUMN3, 2, 13, '*'),
    Key74(BUTTON0, 3, 10, '/'), Key74(BUTTON1, 3, 0, '0'), Key74(BUTTON2, 3, 11, 'C'), Key74(BUTTON3, 3, 12, '=')
};

// ! Инициализация объектов

D8S74X4 d8s4(IC1A, IC1B, IC1C, IC1EN, IC2DATA, IC2UPDT, IC2CLK);
Keypad74 keypad(IC3A, IC3B, IC3C, IC3EN);
#if DEBUG_MODE
LiquidCrystal_I2C lcd0(LCD0_ADDRESS, LCD0_COLUMNS, LCD0_ROWS);
LCDMenu menu(&lcd0, LCD0_COLUMNS, LCD0_ROWS);

// ! Функции LCDMenu

String gPassString() { return String(); };
String gRealLastKey() { return "LAST KEY: "+String(keyLastReal); };
String gD8S4TextBuffer() {
    char *buffer = d8s4.get_text_buffer();
    return "D8S4 TEXT ["+String(buffer[0])+String(buffer[1])+String(buffer[2])+String(buffer[3])+"]";
};

// ! Настройка LCDMenu

LCDLine PassLine00(&gPassString, 0, 0);
LCDLine PassLine01(&gPassString, 0, 1);

LCDLine KeyLastRealLine(&gRealLastKey, 0, 0);
LCDLine D8S4TextLine(&gD8S4TextBuffer, 0, 1);

LCDScreen KeypadScreen(&KeyLastRealLine, &D8S4TextLine);
#endif

// ! Задачи FreeRTOS

void taskD8SUpdate(void *pvParameters)
{
    while (1) {
        d8s4.updateDisplay(0);
        vTaskDelay(D8S4_UPDATE_DELAY / portTICK_PERIOD_MS);
        d8s4.updateDisplay(1);
        vTaskDelay(D8S4_UPDATE_DELAY / portTICK_PERIOD_MS);
        d8s4.updateDisplay(2);
        vTaskDelay(D8S4_UPDATE_DELAY / portTICK_PERIOD_MS);
        d8s4.updateDisplay(3);
        vTaskDelay(D8S4_UPDATE_DELAY / portTICK_PERIOD_MS);
    };
};

void taskD8SAnimation(void *pvParameters)
{
    while (1) {
        d8s4.writeTextShift(D8S4_TEXT, D8S4_TEXT_LEVEL);
        D8S4_TEXT_LEVEL = D8S4_TEXT_LEVEL != -D8S4_TEXT.length() ? D8S4_TEXT_LEVEL - 1 : D8S4_TEXT.length();
        vTaskDelay(D8S4_ANIMATION_DELAY / portTICK_PERIOD_MS);
    };
};

void taskKeypadCheck(void *pvParameters)
{
    while (1) {
        keyLast = keypad.get_key();
        if (keyLast != KEYPAD74_NO_KEY) { keyLastReal = keyLast; };
        // TODO: Привязка кнопок к действиям
        // TODO: ...
        #if DEBUG_MODE
        if (keyLast == '/') {
            menu.prev_screen();
        } else if (keyLast == 'C') {
            menu.next_screen();
        };
        #endif
        vTaskDelay(KEYPAD_CHECK_DELAY / portTICK_PERIOD_MS);
    };
};

void taskLCDMenuRender(void *pvParameters)
{
    while (1) {
        menu.render();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    };
};

#if DEBUG_MODE
/// @brief Setup-функция для настройки LCD дисплея.
void setup_lcd() {
    lcd0.init();
    lcd0.backlight();
};

/// @brief Setup-функция для настройки LCDMenu.
void setup_lcdmenu() {
    menu.add_screen(&KeypadScreen);
};

/// @brief Setup-функция для настройки кейпада.
void setup_keypad() {
    for (int i = 0; i < KEYPAD_KEYS_COUNT; i++) {
        keypad.add_key(&KEYPAD_KEYS[i]);
    };
    keypad.init();
};
#endif

/// @brief Setup-функция для настройки пинов.
void setup_pins() {
    
};

/// @brief Setup-функция для найстройки задач FreeRTOS.
void setup_tasks() {
    xTaskCreate(taskD8SUpdate, "D8SUpdate", 128, NULL, 1, NULL);
    xTaskCreate(taskD8SAnimation, "D8SAnimation", 128, NULL, 2, NULL);
    xTaskCreate(taskKeypadCheck, "KeypadCheck", 128, NULL, 1, NULL);
    #if DEBUG_MODE
    xTaskCreate(taskLCDMenuRender, "LCDMenuRender", 128, NULL, 1, NULL);
    #endif
};

/// @brief Главная функция `setup()`.
void setup() {
    Serial.begin(115200);
    while (!Serial);
    d8s4.init();
    setup_pins();
    setup_keypad();
    #if DEBUG_MODE
    setup_lcd();
    setup_lcdmenu();
    #endif
    setup_tasks();
    vTaskStartScheduler();
};

/// @brief Функция бесконечного цикла.
/// @note Следует оставить пустой, при использовании `FreeRTOS`, в противном случае, это вызовет "зависания".
void loop() {};
