/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/*
 * DEVICE HARDWARE
 */
#define DEVICE_NODEMCU_V1
//#define DEVICE_SONOFF_V2
//#define DEVICE_SONOFF_V3

//#define MULTIPLE_RELAY

//#define NAROD_MON_ENABLED

/*
 * APPLICATION DEFINES
 */
#define DEVICE_KEY  ""

#define WIFI_SSID   ""
#define WIFI_PASSWD ""

#define SERVER_ADDR ""
#define SERVER_PORT 8080

#define MAIN_TMR_DELAY      4000
#define SERIAL_SPEED        9600
#define DEFAULT_DS_ADDR     0
#define LEVELS_COUNT        3
#define TRUE                1

/*
 * VIRTUAL PINS DEFINES
 */
#define VP_CONTROL_TEMP     V0
#define VP_CUR_TEMP         V1
#define VP_STATUS_SWITCH    V2
#define VP_WATER_LEVEL      V3
#define VP_STATUS_LED       V4
#define VP_HEATER_LED       V5
#define VP_PUMP_LED         V6

/*
 * GPIO DEFINES
 */
#ifdef DEVICE_NODEMCU_V1
#define LEVEL_PIN_0   D1
#define LEVEL_PIN_1   D2
#define LEVEL_PIN_2   D7

#define HEATER_PIN  D5
#define PUMP_PIN    D6

#define DS_SENSOR_PIN   D4
#endif

/*
 * APPLICATION CLASSES
 */
SimpleTimer MainTimer;
OneWire Ow(DS_SENSOR_PIN);
DallasTemperature DsSensor(&Ow);

WidgetLED StatusLed(VP_STATUS_LED);
WidgetLED HeaterLed(VP_HEATER_LED);
WidgetLED PumpLed(VP_PUMP_LED);

/*
 * APPLICATION VARIABLES
 */
int8_t ControlTemp = 0;
bool Status = false;

 uint8_t Levels[] = {
     LEVEL_PIN_0,
     LEVEL_PIN_1,
     LEVEL_PIN_2
 };

 void MainTimerCallback();

/*
 * BLYNK CALLBACKS
 */
BLYNK_CONNECTED()
{
    Blynk.syncAll();
}

BLYNK_WRITE(VP_STATUS_SWITCH)
{
    if (param.asInt() == TRUE) {
        Status = true;
    } else {
        Status = false;
    }
    MainTimerCallback();
}

BLYNK_WRITE(VP_CONTROL_TEMP)
{
    ControlTemp = param.asInt();
}

/*
 * OTHER FUNCTIONS
 */
uint8_t GetWaterLevel()
{
    uint8_t level = 0;

    for (uint8_t i = 0; i < LEVELS_COUNT; i++) {
        if (digitalRead(Levels[i]) == LOW) {
            level += 35;
        }
    }

    if (level > 100) {
        level = 100;
    }

    return level;
}

int8_t GetWaterTemp()
{
    DsSensor.requestTemperatures();
    return DsSensor.getTempCByIndex(DEFAULT_DS_ADDR);
}

void MainTimerCallback()
{
    uint8_t level;
    int8_t temp;

    level = GetWaterLevel();
    temp = GetWaterTemp();

    Blynk.virtualWrite(VP_CUR_TEMP, temp);
    Blynk.virtualWrite(VP_WATER_LEVEL, level);

    if (Status) {
        StatusLed.on();

        if (temp < ControlTemp) {
#ifdef MULTIPLE_RELAY
            digitalWrite(HEATER_PIN, LOW);
#else
            pinMode(HEATER_PIN, OUTPUT);
#endif
            HeaterLed.on();
        }
        if (temp > ControlTemp) {
#ifdef MULTIPLE_RELAY
            digitalWrite(HEATER_PIN, HIGH);
#else
            pinMode(HEATER_PIN, INPUT);
#endif
            HeaterLed.off();
        }
        if (level <= 70) {
#ifdef MULTIPLE_RELAY
            digitalWrite(PUMP_PIN, LOW);
#else
            pinMode(PUMP_PIN, OUTPUT);
#endif
            PumpLed.on();
        }
        if (level == 100) {
#ifdef MULTIPLE_RELAY
            digitalWrite(PUMP_PIN, HIGH);
#else
            pinMode(PUMP_PIN, INPUT);
#endif
            PumpLed.off();
        }
    } else {
        StatusLed.off();
        HeaterLed.off();
        PumpLed.off();
#ifdef MULTIPLE_RELAY
        digitalWrite(HEATER_PIN, HIGH);
        digitalWrite(PUMP_PIN, HIGH);
#else
        pinMode(HEATER_PIN, INPUT);
        pinMode(PUMP_PIN, INPUT);
#endif
    }
}

/*
 * APPLICATION MAIN FUNCTIONS
 */
void setup()
{
    Serial.begin(SERIAL_SPEED);
    Blynk.begin(DEVICE_KEY, WIFI_SSID, WIFI_PASSWD, SERVER_ADDR, SERVER_PORT);

    MainTimer.setInterval(MAIN_TMR_DELAY, MainTimerCallback);

    for (uint8_t i = 0; i < LEVELS_COUNT; i++) {
        pinMode(Levels[i], INPUT_PULLUP);
    }

#ifdef MULTIPLE_RELAY
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(PUMP_PIN, OUTPUT);
#else
    pinMode(HEATER_PIN, INPUT);
    pinMode(PUMP_PIN, INPUT);
#endif

    digitalWrite(HEATER_PIN, HIGH);
    digitalWrite(PUMP_PIN, HIGH);

    DsSensor.begin();
}

void loop()
{
    Blynk.run();

    MainTimer.run();
}
