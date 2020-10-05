/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "boards.h"

#ifdef BOARD_NODEMCU_V1

#define HEATER_PIN      D5
#define PUMP_PIN        D6

#define BUTTON_MAIN_PIN D3
#define LED_STATUS_PIN  D0

#define DS_SENSOR_PIN   D4

#define LEVEL_PIN_0     D1
#define LEVEL_PIN_1     D2
#define LEVEL_PIN_2     D7

OneWire Ow(DS_SENSOR_PIN);
DallasTemperature WaterSensor(&Ow);

uint8_t Buttons[] = {
    BUTTON_MAIN_PIN
};

uint8_t ButtonsCount = ARRAY_ITEMS_COUNT(Buttons);

uint8_t Relays[] = {
    HEATER_PIN,
    PUMP_PIN
};

uint8_t RelaysCount = ARRAY_ITEMS_COUNT(Relays);

uint8_t Leds[] = {
    LED_STATUS_PIN
};

uint8_t LedsCount = ARRAY_ITEMS_COUNT(Leds);

uint8_t Levels[] = {
    LEVEL_PIN_0,
    LEVEL_PIN_1,
    LEVEL_PIN_2
};

uint8_t LevelsCount = ARRAY_ITEMS_COUNT(Levels);

DallasTemperature *TempSensors[] = {
    &WaterSensor
};

uint8_t TempSensorsCount = ARRAY_ITEMS_COUNT(TempSensors);

#endif
