#pragma once
#include <stdint.h>
#include "WiFi.h"

int parceInt(uint8_t r0, uint8_t r1, uint8_t r2, uint8_t r3);
short getLamp(short x, short y, short width);
void connect(const char ssid[], const char password[], const int serial);