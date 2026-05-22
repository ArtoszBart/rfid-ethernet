#include <Arduino.h>
#include "config.h"

void buzzerInit()
{
	pinMode(BUZZER_PIN, OUTPUT);
}

void beep(int onTime, int offTime)
{
	digitalWrite(BUZZER_PIN, HIGH);
	delay(onTime);
	digitalWrite(BUZZER_PIN, LOW);
	delay(offTime);
}

void beepWaiting()
{
	beep(100, 50);
}

void beepAccepted()
{
	beep(50, 50);
	beep(50, 50);
}

void beepDenied()
{
	beep(1000, 100);
}