# Blink Switcher

## Description

Two-button LED controller for ESP32-S3 using hardware interrupts. Each button selects a different blink pattern for two LEDs.

### Modes

| Mode | Trigger | LED behavior | Delay |
|------|---------|-------------|-------|
| Fast | External button (GPIO 21) | Both LEDs blink in sync | 200 ms |
| Slow | On-board BOOT button (GPIO 0) | LEDs alternate (LED1 on -> off, LED2 on -> off) | 1000 ms |
| None | Default at startup | LEDs off | — |

### Features

- **Hardware interrupts** — button presses are handled via `attachInterruptArg()` on `CHANGE`, so the main loop is not blocked by polling.
- **Software debounce** — each button press is ignored if less than 50 ms has passed since the last press, preventing false triggers from contact bounce.
- **IRAM_ATTR ISR** — the interrupt handler is placed in IRAM for fast execution.

### Known Issues

- The current LED pattern runs to completion before a new mode takes effect. The pattern is not interrupted mid-cycle.

## Hardware

| Component | Pin | Description |
|-----------|-----|-------------|
| LED 1 | GPIO 15 | First LED |
| LED 2 | GPIO 16 | Second LED |
| External button | GPIO 21 | Fast mode (INPUT_PULLUP) |
| BOOT button | GPIO 0 | Slow mode (built-in on board) |

## Links

Schema: https://drive.google.com/file/d/1dN2s8rYZ_k2mxkT0VHxvLLb-azNNMfyN/view?usp=sharing

Demo: https://drive.google.com/file/d/1Sl1IBnObOxNTVYSIgCUZrlHDPpr7gl-f/view?usp=sharing

## Build

- **Platform:** espressif32
- **Board:** esp32-s3-devkitc-1
- **Framework:** Arduino
