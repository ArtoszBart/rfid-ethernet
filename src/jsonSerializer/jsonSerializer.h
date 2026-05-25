#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

template <typename T>
String serializeToJson(const T &data)
{
	JsonDocument doc;

	data.toJson(doc);

	String json;
	serializeJson(doc, json);

	return json;
}