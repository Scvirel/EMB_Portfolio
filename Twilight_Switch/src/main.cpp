#include <Arduino.h>

constexpr uint8_t kLdrPin   = 6;
constexpr uint8_t kRelayPin = 17;

constexpr uint16_t kThresholdDark  = 1200;
constexpr uint16_t kThresholdLight = 2000;

constexpr uint8_t kRelayOnLevel = HIGH;

constexpr uint8_t kLoopDelayMs = 100;

bool g_relay_on = false;

bool ComputeRelayState(int adc_value, bool previous_state) {
    if (adc_value < kThresholdDark) {
        return true;
    }

    if (adc_value > kThresholdLight) {
        return false;
    }

    return previous_state;
}

void ApplyRelayState(bool relay_on) {
    digitalWrite(kRelayPin, relay_on ? kRelayOnLevel : !kRelayOnLevel);
}

void setup() {
    Serial.begin(115200);

    pinMode(kRelayPin, OUTPUT);

    ApplyRelayState(g_relay_on);
}

void loop() {
    const int adc_value = analogRead(kLdrPin);

    g_relay_on = ComputeRelayState(adc_value, g_relay_on);

    ApplyRelayState(!g_relay_on);

    Serial.printf("ADC = %4d | relay = %s\n", adc_value, g_relay_on ? "ON" : "OFF");
    delay(kLoopDelayMs);
}
