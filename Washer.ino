/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include <ESP8266WiFi.h>

#include "ports.h"
#include "boards.h"
#include "common.h"
#include "washer.h"

#define MAIN_TMR_DELAY  4000

SimpleTimer MainTimer;

static void ReadButton()
{
    if (digitalRead(Buttons[MAIN_BUTTON]) == LOW) {
        WasherSwitchStatus();
        WasherUpdate();
        Blynk.virtualWrite(VP_STATUS_SWITCH, (int)WasherGetStatus());
        delay(600);
    }
}

static void MainTimerCallback()
{
    WasherUpdate();
}

void setup()
{
    PortsInit();
    Blynk.begin(DEVICE_KEY, WIFI_SSID, WIFI_PASSWD, BLYNK_SERVER, BLYNK_SERVER_PORT);

    for (uint8_t i = 0; i < ButtonsCount; i++) {
        pinMode(Buttons[i], INPUT_PULLUP);
    }

    for (uint8_t i = 0; i < RelaysCount; i++) {
        pinMode(Relays[i], OUTPUT);
    }

    for (uint8_t i = 0; i < LedsCount; i++) {
        pinMode(Leds[i], OUTPUT);
    }

    for (uint8_t i = 0; i < LevelsCount; i++) {
        pinMode(Levels[i], INPUT_PULLUP);
    }

    MainTimer.setInterval(MAIN_TMR_DELAY, MainTimerCallback);
}

void loop()
{
    Blynk.run();
    ReadButton();
    MainTimer.run();
}
