#include <Arduino.h>

#include "config.h"
#include "buzzer/buzzer.h"
#include "rfid/rfid.h"
#include "models/ScanData.h"

void setup()
{
#if DEBUG
	Serial.begin(115200);
#endif

	LOG("SETUP START");
	pinMode(LED_BUILTIN, OUTPUT);

	buzzerInit();
	rfidInit();

	LOG("SETUP FINISHED");
}

void loop()
{
	digitalWrite(LED_BUILTIN, HIGH);
	delay(50);
	digitalWrite(LED_BUILTIN, LOW);
	delay(50);

	ScanData scanData;
	if (scanRfid(scanData.uid))
	{
		LOGF("UID: ", scanData.uid);
	}

	delay(1000);
}