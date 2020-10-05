/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "ports.h"
#include "common.h"
#include "washer.h"
#include "boards.h"

WidgetLED LedStatus(Blynk);
WidgetLED LedHeater(Blynk);
WidgetLED LedPump(Blynk);

WidgetLED *LedWidgets[] = {
    &LedStatus,
    &LedHeater,
    &LedPump
};

uint8_t LedWidgetsCount = ARRAY_ITEMS_COUNT(LedWidgets);

void PortsInit()
{
    LedStatus.setVPin(VP_LED_STATUS);
    LedHeater.setVPin(VP_LED_HEATER);
    LedPump.setVPin(VP_LED_PUMP);
}

BLYNK_CONNECTED()
{
    Blynk.syncAll();
}

BLYNK_WRITE(VP_STATUS_SWITCH)
{
    if (param.asInt() == TRUE) {
        WasherSetStatus(true);
    } else {
        WasherSetStatus(false);
    }
    WasherUpdate();
}

BLYNK_WRITE(VP_THRESHOLD)
{
    WasherSetThreshold(param.asInt());
}
