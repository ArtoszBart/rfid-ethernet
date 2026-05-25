#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

struct ScanData
{
	String uid;

	void toJson(JsonDocument &doc) const
	{
		doc["uid"] = uid;
	}
};