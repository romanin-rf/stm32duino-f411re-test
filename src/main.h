#pragma once

// ! Найстройки компиляции

#define DEBUG_MODE true

// ! Используемые библеотеки

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <D8S74X4.h>
#if DEBUG_MODE
    #include <LiquidCrystal_I2C.h>
    #include <LCDMenu.h>
#endif


// ! Настройки

// ! Переменные LCD дисплея
#if DEBUG_MODE
    #define LCD0_ADDRESS 0x27
    #define LCD0_COLUMNS 16
    #define LCD0_ROWS 2
#endif

// ! Пины ICx

/// @brief Пин 1-ого бита сдвига, микросхемы 74HC138 (IC1).
#define IC1A PC6
/// @brief Пин 2-ого бита сдвига, микросхемы 74HC138 (IC1).
#define IC1B PC5
/// @brief Пин 3-его бита сдвига, микросхемы 74HC138 (IC1).
#define IC1C PA12
/// @brief Пин включения, микросхемы 74HC138 (IC1).
#define IC1EN PA11

/// @brief Пин данных, микросхемы 74HC595 (IC2).
#define IC2DATA PB15
/// @brief Пин обновления, микросхемы 74HC595 (IC2).
#define IC2UPDT PB14
/// @brief Пин завершения ввода, микросхемы 74HC595 (IC2).
#define IC2CLK PB13

/// @brief Пин 1-ого бита сдвига, микросхемы 74HC138 (IC3).
#define IC3A PB12
/// @brief Пин 2-ого бита сдвига, микросхемы 74HC138 (IC3).
#define IC3B PB2
/// @brief Пин 3-его бита сдвига, микросхемы 74HC138 (IC3).
#define IC3C PB1
/// @brief Пин включения, микросхемы 74HC138 (IC3).
#define IC3EN PC4

// ! Пины компанентов

/// @brief Пин зуммера.
#define SPEAKER PA8
/// @brief Пин зуммера.
#define SG1 PA8

/// @brief Пин датчика температура (1).
#define TEMP1 PA4
/// @brief Пин датчика температура (1).
#define T1 PA4

/// @brief Пин датчика температуры (2).
#define TEMP2 PB0
/// @brief Пин датчика температуры (2).
#define T2 PB0

/// @brief Пин регулятора напряжения (1).
#define VADJ1 PA0
/// @brief Пин регулятора напряжения (1).
#define R1 PA0

/// @brief Пин регулятора напряжения (2).
#define VADJ2 PA1
/// @brief Пин регулятора напряжения (2).
#define R2 PA0

// ! Пины кнопочной матрицы

/// @brief Пин для считывания нажатия c кнопок: `S7/S4/S1`.
#define COLUMN0 PA10
/// @brief Пин для считывания нажатия c кнопок: `S8/S5/S2`.
#define COLUMN1 PB3
/// @brief Пин для считывания нажатия c кнопок: `S9/S6/S3`.
#define COLUMN2 PB5
/// @brief Пин для считывания нажатия c кнопок: `S15/S14/S13`.
#define COLUMN3 PB4

/// @brief Пин для считывания нажатия c кнопки `S10`.
#define BUTTON0 PB10
/// @brief Пин для считывания нажатия c кнопки `S0`.
#define BUTTON1 PC1
/// @brief Пин для считывания нажатия c кнопки `S11`.
#define BUTTON2 PC0
/// @brief Пин для считывания нажатия c кнопки `S12`.
#define BUTTON3 PC3

// ! Специальный пины

/// @brief Пин SCL.
#define SCL PB8
/// @brief Пин SCA.
#define SCA PB9
/// @brief Пин SQW.
#define SQW PC9

// ! Пины светодиодов

/// @brief Пин светодиода (1).
#define RED1 PC7
/// @brief Пин светодиода (4).
#define RED2 PA9

/// @brief Пин светодиода (3).
#define GREEN1 PA5
/// @brief Пин светодиода (6).
#define GREEN2 PA6

/// @brief Пин светодиода (2).
#define YELLOW1 PA7
/// @brief Пин светодиода (5).
#define YELLOW2 PB6
/// @brief Пин светодиода (1).

#define LED1 PC7
/// @brief Пин светодиода (2).
#define LED2 PA7
/// @brief Пин светодиода (3).
#define LED3 PA5
/// @brief Пин светодиода (4).
#define LED4 PA9
/// @brief Пин светодиода (5).
#define LED5 PB6
/// @brief Пин светодиода (6).
#define LED6 PA6