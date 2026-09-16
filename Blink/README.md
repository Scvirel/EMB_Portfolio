# Blink

## Description

LED blink program for ESP32-S3 demonstrating two approaches to GPIO control.

### MultiplePinBlink

Sequentially blinks two LEDs on separate pins:
- **Blue LED** on GPIO 15 — 200 ms pulse.
- **Red LED** on GPIO 39 — 100 ms pulse.

Demo: https://drive.google.com/file/d/1NfXfAylSOV6m54ZDUZ9bli6Zf8xuH-AV/view?usp=drive_link

### SinglePinBlink (enhanced)

Single-pin blink on GPIO 17 with two additional techniques:
- **Random jitter** — each cycle subtracts a random value (0–951 ms) from the base 1000 ms delay, creating a non-uniform blink pattern.
- **Pin mode toggling** — the pin alternates between `OUTPUT` (drives LED) and `INPUT` (high-impedance, LED off), demonstrating dynamic GPIO reconfiguration.

Demo: https://drive.google.com/file/d/1EF--oniYstLsza4TdF_dIzHEcYL6jSHV/view?usp=drive_link

## Hardware

| Component | Pin | Description |
|-----------|-----|-------------|
| Blue LED | GPIO 15 | MultiplePinBlink |
| Red LED | GPIO 39 | MultiplePinBlink |
| LED | GPIO 17 | SinglePinBlink (dual-mode control) |

## Build

- **Platform:** espressif32
- **Board:** esp32-s3-devkitc-1
- **Framework:** Arduino
