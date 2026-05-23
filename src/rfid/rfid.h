#pragma once

#include <Arduino.h>

void rfidInit();
bool scanRfid(String &uid);