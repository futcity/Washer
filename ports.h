/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#ifndef __PORTS_H__
#define __PORTS_H__

#include <WidgetLED.h>

#define VP_STATUS_SWITCH    V0

#define VP_LED_STATUS   V10
#define VP_LED_HEATER   V11
#define VP_LED_PUMP     V12

#define VP_THRESHOLD    V20

#define VP_CUR_TEMP     V30
#define VP_CUR_LEVEL    V31

typedef enum {
    STATUS_LED_WIDGET,
    HEATER_LED_WIDGET,
    PUMP_LED_WIDGET
} LedWidgetType;

extern uint8_t LedWidgetsCount;
extern WidgetLED *LedWidgets[];

void PortsInit();

#endif
