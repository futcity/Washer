/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "washer.h"
#include "boards.h"
#include "ports.h"
#include "common.h"

bool Status = false;
uint8_t Threshold = 25;

/*
 * Private functions
 */

static int8_t ReadTemp()
{
    TempSensors[WATER_SENSOR]->requestTemperatures();
    return TempSensors[WATER_SENSOR]->getTempCByIndex(DEFAULT_SENSOR);
}

static uint8_t ReadWaterLevel()
{
    uint8_t level = 0;

    for (uint8_t i = 0; i < LevelsCount; i++) {
        if (digitalRead(Levels[i]) == LOW) {
            level += 35;
        }
    }

    if (level > 100)
        level = 100;

    return level;
}

/*
 * Public functions
 */

uint8_t WasherGetThreshold()
{
    return Threshold;
}

void WasherSetThreshold(uint8_t val)
{
    Threshold = val;
}

bool WasherGetStatus()
{
    return Status;
}

void WasherSetStatus(bool val)
{
    Status = val;
}

void WasherSwitchStatus()
{
    Status = !Status;
}

void WasherUpdate()
{
    int8_t curTemp;
    uint8_t level;
        
    for (uint8_t i = 0; i < TEMP_RETRIES; i++) {
        curTemp = ReadTemp();
        if (curTemp != TEMP_ERR_VAL)
            break;
        delay(1000);
    }
    level = ReadWaterLevel();

    Blynk.virtualWrite(VP_CUR_TEMP, curTemp);
    Blynk.virtualWrite(VP_CUR_LEVEL, level);

    if (curTemp == TEMP_ERR_VAL) {
        digitalWrite(Relays[HEATER_RELAY], LOW);
        LedWidgets[HEATER_LED_WIDGET]->off();
        return;
    }

    if (WasherGetStatus()) {
        /*
         * Control water temperature
         */
        if (curTemp < Threshold) {
            digitalWrite(Relays[HEATER_RELAY], HIGH);
            LedWidgets[HEATER_LED_WIDGET]->on();
        } else {
            digitalWrite(Relays[HEATER_RELAY], LOW);
            LedWidgets[HEATER_LED_WIDGET]->off();
        }

        /*
         * Control water level
         */
        if (level < 100) {
            digitalWrite(Relays[PUMP_RELAY], HIGH);
            LedWidgets[PUMP_LED_WIDGET]->on();
        } else {
            digitalWrite(Relays[PUMP_RELAY], LOW);
            LedWidgets[PUMP_LED_WIDGET]->off();
        }

        digitalWrite(Leds[STATUS_LED], LOW);
        LedWidgets[STATUS_LED_WIDGET]->on();
    } else {
        for (uint8_t i = 0; i < RelaysCount; i++) {
            digitalWrite(Relays[i], LOW);
        }
        for (uint8_t i = 0; i < LedsCount; i++) {
            digitalWrite(Leds[i], LOW);
        }
        for (uint8_t i = 0; i < LedWidgetsCount; i++) {
            LedWidgets[i]->off();
        }
    }
}
