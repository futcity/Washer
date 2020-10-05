/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkEsp8266.h>

#define DEVICE_KEY  ""

#define WIFI_SSID   ""
#define WIFI_PASSWD ""

#define BLYNK_SERVER        ""
#define BLYNK_SERVER_PORT   8080

#define TRUE    1
#define FALSE   0
#define LED_ON  255
#define LED_OFF 0

extern BlynkWifi Blynk;

#endif
