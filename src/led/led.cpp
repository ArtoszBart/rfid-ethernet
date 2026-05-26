#include <Arduino.h>
#include "config.h"

void ledsInit()
{
	pinMode(LED_GREEN_PIN, OUTPUT);
	pinMode(LED_YELLOW_PIN, OUTPUT);
	pinMode(LED_RED_PIN, OUTPUT);
}

void ledsOn()
{
	digitalWrite(LED_GREEN_PIN, HIGH);
	digitalWrite(LED_YELLOW_PIN, HIGH);
	digitalWrite(LED_RED_PIN, HIGH);
}

void ledsOff()
{
	digitalWrite(LED_GREEN_PIN, LOW);
	digitalWrite(LED_YELLOW_PIN, LOW);
	digitalWrite(LED_RED_PIN, LOW);
}

void ledBlinkStandby()
{
	digitalWrite(LED_YELLOW_PIN, HIGH);
	delay(50);
	digitalWrite(LED_YELLOW_PIN, LOW);
	delay(50);
}