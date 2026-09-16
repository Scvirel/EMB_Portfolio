#include <Arduino.h>

constexpr uint8_t  kAdcPin = 6;
constexpr float_t  kUref   = 3.1f;
constexpr uint16_t kAdcMax = 4095;
constexpr uint8_t  kDelay  = 100;

float_t percentageDifference(float_t value1, float_t value2) {
    float_t numerator = abs(value1 - value2);
    float_t average   = (value1 + value2) / 2.0f;
    if (average == 0) return 0;

    return (numerator / average) * 100.0f;
}

void setup() {
    pinMode(kAdcPin, INPUT);
    Serial.begin(115200);
}

void loop() {
    uint16_t rawData         = analogRead(kAdcPin);
    float_t  uCalc           = rawData * (kUref / kAdcMax);
    uint32_t analogReadValue = analogReadMilliVolts(kAdcPin);

    Serial.print("RAW data: ");
    Serial.println(rawData);

    Serial.print("Ucalc: ");
    Serial.println(uCalc);

    Serial.print("Value from analogReadMilliVolts: ");
    Serial.println(analogReadValue);

    Serial.print("Percentage Difference: ");
    Serial.print(percentageDifference(uCalc, analogReadValue / 1000.0f));
    Serial.println(" %");

    delay(kDelay);
}
