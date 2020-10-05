/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#ifndef __BOARDS_H__
#define __BOARDS_H__

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ARRAY_ITEMS_COUNT(_array) \
        (sizeof (_array) / sizeof (*(_array)))

//#define BOARD_SONOFF_DUAL
#define BOARD_NODEMCU_V1

typedef enum {
    STATUS_LED
} LedType;

typedef enum {
    MAIN_BUTTON
} ButtonType;

typedef enum {
    HEATER_RELAY,
    PUMP_RELAY
} RelayType;

typedef enum {
    WATER_SENSOR
} TempSensorType;

extern uint8_t ButtonsCount;
extern uint8_t RelaysCount;
extern uint8_t LedsCount;
extern uint8_t LevelsCount;
extern uint8_t TempSensorsCount;

extern uint8_t Relays[];
extern uint8_t Leds[];
extern uint8_t Levels[];
extern uint8_t Buttons[];
extern DallasTemperature *TempSensors[];

#endif
