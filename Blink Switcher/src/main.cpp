#include <Arduino.h>
#include <cstdint>

enum Mode : uint8_t {
    kModeNone = 0,
    kModeFast = 1,
    kModeSlow = 2,
};

struct Button {
    const uint8_t kPIN;
    uint32_t      last_button_press_time;
    Mode          mode;
};

constexpr uint8_t kLedPin1 = 15;
constexpr uint8_t kLedPin2 = 16;

constexpr uint8_t kButtonExtPin  = 21;
constexpr uint8_t kButtonBootPin = 0;  // Board BOOT button

constexpr uint8_t  kFastDelay = 200;
constexpr uint16_t kSlowDelay = 1000;

constexpr uint32_t kDebounceDelayMs = 50;

Button externalButton = {kButtonExtPin, 0, kModeFast};
Button bootButton     = {kButtonBootPin, 0, kModeSlow};

volatile Mode current_mode = kModeNone;

void IRAM_ATTR CheckButtonPress(void* obj) {
    uint32_t now = millis();
    Button* button = static_cast<Button*>(obj);

    if (digitalRead(button->kPIN) == LOW &&  // Debounce avoidance
        now - button->last_button_press_time > kDebounceDelayMs) {
        current_mode                   = button->mode;
        button->last_button_press_time = now;
    }
}

void RunFastMode() {
    digitalWrite(kLedPin1, HIGH);
    digitalWrite(kLedPin2, HIGH);
    delay(kFastDelay);
    digitalWrite(kLedPin1, LOW);
    digitalWrite(kLedPin2, LOW);
    delay(kFastDelay);
}

void RunSlowMode() {
    digitalWrite(kLedPin1, HIGH);
    digitalWrite(kLedPin2, LOW);
    delay(kSlowDelay);
    digitalWrite(kLedPin1, LOW);
    digitalWrite(kLedPin2, HIGH);
    delay(kSlowDelay);
    digitalWrite(kLedPin2, LOW);
}

void setup() {
    pinMode(kLedPin1, OUTPUT);
    pinMode(kLedPin2, OUTPUT);

    pinMode(kButtonExtPin, INPUT_PULLUP);
    pinMode(kButtonBootPin, INPUT_PULLUP);

    digitalWrite(kLedPin1, LOW);
    digitalWrite(kLedPin2, LOW);

    attachInterruptArg(digitalPinToInterrupt(kButtonExtPin),
                       CheckButtonPress, &externalButton, CHANGE);
    attachInterruptArg(digitalPinToInterrupt(kButtonBootPin),
                       CheckButtonPress, &bootButton, CHANGE);
}

void loop() {
    switch (current_mode) {
        case kModeFast:
            RunFastMode();
            break;
        case kModeSlow:
            RunSlowMode();
            break;
        default:
            break;
    }
}
