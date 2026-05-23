#include <MFRC522.h>

#include "../config.h"
#include "buzzer/buzzer.h"

MFRC522 rfid(RC522_CS, RC522_RST);

void rfidInit()
{
	pinMode(RC522_CS, OUTPUT);
	pinMode(RC522_RST, OUTPUT);
	digitalWrite(RC522_CS, LOW);
	rfid.PCD_Init();
}

void rfidStart()
{
	digitalWrite(RC522_CS, LOW);
	rfid.PCD_Init();
	delay(50);
}

void rfidStop()
{
	rfid.PICC_HaltA();
	rfid.PCD_StopCrypto1();
	digitalWrite(RC522_CS, HIGH);
}

bool isCardDetected()
{
	return rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial();
}

String readUID()
{
	String uid = "";

	for (byte i = 0; i < rfid.uid.size; i++)
	{
		if (rfid.uid.uidByte[i] < 0x10)
			uid += "0";

		uid += String(rfid.uid.uidByte[i], HEX);

		if (i < rfid.uid.size - 1)
			uid += ":";
	}

	uid.toUpperCase();

	return uid;
}

bool scanRfid(String &uid)
{
	rfidStart();

	if (!isCardDetected())
		return false;

	uid = readUID();
	beepWaiting();

	rfidStop();

	return true;
}