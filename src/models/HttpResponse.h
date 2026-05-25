#pragma once

#include <Arduino.h>

struct HttpResponse
{
	bool success;
	int statusCode;
	String body;
};