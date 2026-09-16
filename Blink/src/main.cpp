#include <Arduino.h>

#include <cstdint>

constexpr uint8_t kLedBluePin = 15;
constexpr uint8_t kLedRedPin = 39;
constexpr uint8_t kLedTwoControlPin = 17;

constexpr uint16_t kBlueDelayMs = 200;
constexpr uint16_t kRedDelayMs = 100;
constexpr uint16_t kTwoControlDelayMs = 1000;

constexpr uint8_t kJitterLow = 0;
constexpr uint8_t kJitterHigh = 951;

static void MultiplePinBlink() {
  digitalWrite(kLedBluePin, HIGH);
  delay(kBlueDelayMs);
  digitalWrite(kLedBluePin, LOW);

  digitalWrite(kLedRedPin, HIGH);
  delay(kRedDelayMs);
  digitalWrite(kLedRedPin, LOW);
}

static void SinglePinBlink() {
  const uint16_t jitter = random(kJitterLow, kJitterHigh);
  const uint16_t delay_ms = kTwoControlDelayMs - jitter;

  pinMode(kLedTwoControlPin, OUTPUT);

  digitalWrite(kLedTwoControlPin, HIGH);
  delay(delay_ms);
  digitalWrite(kLedTwoControlPin, LOW);
  delay(delay_ms);

  pinMode(kLedTwoControlPin, INPUT);
  delay(delay_ms);
}

void setup() {
  pinMode(kLedBluePin, OUTPUT);
  pinMode(kLedRedPin, OUTPUT);
}

void loop() {
  // MultiplePinBlink();
  SinglePinBlink();
}
