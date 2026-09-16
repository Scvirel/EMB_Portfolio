# EMB_Portfolio

Embedded Systems Projects Portfolio built with **ESP32-S3-DevKitC-1** using **PlatformIO** and the **Arduino** framework.

---

## Projects

### [Hello World](Hello%20World/)
First steps with ESP32-S3. Basic breadboard setup with an LED connected to the development board, verifying the toolchain and hardware connectivity.

### [Blink](Blink/)
LED blink program demonstrating two approaches:
- `MultiplePinBlink` — sequential blinking of blue and red LEDs on separate GPIO pins.
- `SinglePinBlink` — single-pin blink with random jitter, toggling the pin between OUTPUT and INPUT modes.

### [Blink Switcher](Blink%20Switcher/)
Two-button LED controller with hardware interrupts:
- External button triggers fast blink mode (200 ms).
- On-board BOOT button triggers slow alternating blink mode (1000 ms).
- Implements software debouncing via timestamp comparison.

### [AnalogRead](AnalogRead/)
Light level measurement using an LDR and the ESP32-S3 ADC:
- Reads raw ADC values and calculates voltage manually.
- Compares manual calculation against the built-in `analogReadMilliVolts()` function.
- Outputs raw data, calculated voltage, SDK voltage, and percentage difference over serial.

### [Twilight_Switch](Twilight_Switch/)
Automatic light-activated relay on ESP32-S3:
- LDR sensor with voltage divider for ambient light measurement.
- Hysteresis-based thresholds to prevent relay chatter.
- 3.3 V to 5 V level shifting via a BC547B NPN transistor.
- Relay module driving a DC motor with flyback diode protection.

---

## Hardware

| Component | Description |
|-----------|-------------|
| ESP32-S3-DevKitC-1 | Main development board (all projects) |
| LEDs | Various colors for blink projects |
| LDR (photoresistor) | Light sensor (AnalogRead, Twilight_Switch) |
| BC547B NPN transistor | Level shifter 3.3 V to 5 V (Twilight_Switch) |
| 5 V relay module | Load switching (Twilight_Switch) |
| DC motor + flyback diode | Load (Twilight_Switch) |

## Build Environment

- **PlatformIO** with Arduino framework
- **Platform:** espressif32
- **Board:** esp32-s3-devkitc-1
- **Serial monitor:** 115200 baud
