#pragma once

#include "../models/ScanData.h"

void ethernetInit();
void ethernetMaintain(unsigned long runtime);
void sendRequest(const ScanData &requestData);