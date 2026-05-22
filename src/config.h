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