#include <Arduino.h>
#include <SPI.h>

#include "config.h"
#include "buzzer/buzzer.h"
#include "rfid/rfid.h"
#include "models/ScanData.h"
#include "ethernet/ethernet.h"
#include "led/led.h"

unsigned long uptime;

void setup()
{
#if DEBUG
	Serial.begin(115200);
#endif

	LOG("SETUP START");
	ledsInit();
	ledsOn();

	SPI.begin();

	buzzerInit();
	ethernetInit();
	rfidInit();

	ledsOff();
	LOG("SETUP FINISHED");

	uptime = millis();
}

void loop()
{
	ledBlinkStandby();
	ethernetMaintain(uptime);

	ScanData scanData;
	if (scanRfid(scanData.uid))
	{
		sendRequest(scanData);
	}

	delay(1000);
	ledsOff();
}