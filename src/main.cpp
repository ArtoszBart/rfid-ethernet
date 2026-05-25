#include <Arduino.h>
#include <SPI.h>

#include "config.h"
#include "buzzer/buzzer.h"
#include "rfid/rfid.h"
#include "models/ScanData.h"
#include "ethernet/ethernet.h"

unsigned long uptime;

void setup()
{
#if DEBUG
	Serial.begin(115200);
#endif

	LOG("SETUP START");
	pinMode(LED_BUILTIN, OUTPUT);

	SPI.begin();

	buzzerInit();
	ethernetInit();
	rfidInit();

	LOG("SETUP FINISHED");
	uptime = millis();
}

void loop()
{
	digitalWrite(LED_BUILTIN, HIGH);
	delay(50);
	digitalWrite(LED_BUILTIN, LOW);
	delay(50);

	ethernetMaintain(uptime);

	ScanData scanData;
	if (scanRfid(scanData.uid))
	{
		sendRequest(scanData);
	}

	delay(1000);
}