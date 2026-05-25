#pragma once

// ===== DEBUG =====
#define DEBUG 1 // logs

#if DEBUG
#define LOG(x) Serial.println(x)
#define LOGF(x, y) \
  Serial.print(x); \
  Serial.println(y)
#else
#define LOG(x)
#define LOGF(x, y)
#endif

// ===== PINS =====
#define BUZZER_PIN 5

#define RC522_CS 10
#define RC522_RST 9

#define W5500_CS 8
#define W5500_RST 7
