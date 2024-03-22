#include <main.h>

// ! Временные переменные

static String D8S4_TEXT = "HELLO LOH";
static int D8S4_TEXT_LEVEL = D8S4_TEXT.length();

// ! Инициализация объектов

D8S74X4 d8s4(IC1A, IC1B, IC1C, IC1EN, IC2DATA, IC2UPDT, IC2CLK);
#if DEBUG_MODE
    LiquidCrystal_I2C lcd0(LCD0_ADDRESS, LCD0_COLUMNS, LCD0_ROWS);
    LCDMenu menu(&lcd0, 16, 2);
#endif

// ! Главные функции

// ! Задачи FreeRTOS

void taskD8SUpdate(void *pvParameters)
{
    while (1) {
        d8s4.updateDisplay(0);
        vTaskDelay(3 / portTICK_PERIOD_MS);
        d8s4.updateDisplay(1);
        vTaskDelay(3 / portTICK_PERIOD_MS);
        d8s4.updateDisplay(2);
        vTaskDelay(3 / portTICK_PERIOD_MS);
        d8s4.updateDisplay(3);
        vTaskDelay(3 / portTICK_PERIOD_MS);
    };
};

void taskD8SAnimation(void *pvParameters)
{
    while (1) {
        d8s4.writeTextShift(D8S4_TEXT, D8S4_TEXT_LEVEL);
        D8S4_TEXT_LEVEL = D8S4_TEXT_LEVEL != -D8S4_TEXT.length() ? D8S4_TEXT_LEVEL - 1 : D8S4_TEXT.length();
        vTaskDelay(500 / portTICK_PERIOD_MS);
    };
};

/// @brief Setup-функция для настройки пинов.
void setup_pins() {
    
};

/// @brief Setup-функция для найстройки задач FreeRTOS.
void setup_tasks() {
    xTaskCreate(taskD8SUpdate, "D8SUpdate", 128, NULL, 1, NULL);
    xTaskCreate(taskD8SAnimation, "D8SAnimation", 128, NULL, 1, NULL);
};

/// @brief Главная функция `setup()`.
void setup() {
    Serial.begin(115200);
    while (!Serial);
    d8s4.init();
    setup_pins();
    setup_tasks();
    vTaskStartScheduler();
};

/// @brief Функция бесконечного цикла.
/// @note Следует оставить пустой, при использовании `FreeRTOS`, в противном случае, это вызовет "зависания".
void loop() {};
