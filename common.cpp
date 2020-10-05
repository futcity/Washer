/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "common.h"

WiFiClient Client;
BlynkArduinoClient Transport(Client);
BlynkWifi Blynk(Transport);