#include <Arduino.h>

#include "config.h"
#include "buzzer/buzzer.h"

void setup()
{
#if DEBUG
	Serial.begin(115200);
#endif

	LOG("SETUP START");
	pinMode(LED_BUILTIN, OUTPUT);

	buzzerInit();

	LOG("SETUP FINISHED");
}

void loop()
{
	digitalWrite(LED_BUILTIN, HIGH);
	delay(50);
	digitalWrite(LED_BUILTIN, LOW);
	delay(50);
}