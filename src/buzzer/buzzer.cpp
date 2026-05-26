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

// 201
void beepTagAdded()
{
	beep(50, 50);
	beep(50, 50);
	beep(50, 50);
	beep(50, 50);
	beep(50, 50);
	beep(50, 50);
	beep(50, 50);
	beep(50, 50);
	beep(50, 50);
	beep(50, 50);
}

// 202
void beepAdmin()
{
	beep(50, 50);
	beep(50, 50);
	beep(300, 50);
}

// 204
void beepAccepted()
{
	beep(50, 50);
	beep(50, 50);
}

// 403
void beepUnassigned()
{
	beep(300, 100);
	beep(300, 100);
	beep(300, 100);
}

// 404
void beepUnregistered()
{
	beep(1000, 100);
}

// 409
void beepConflict()
{
	beep(500, 50);
	beep(50, 50);
	beep(500, 50);
	beep(50, 50);
}

// error
void beepError()
{
	beep(1000, 100);
	beep(1000, 100);
}