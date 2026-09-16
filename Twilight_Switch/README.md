# Twilight_Switch

A mini-project: the device measures ambient light level with a photoresistor and,
when it gets dark, automatically turns on a load (relay -> DC motor). Implements
**3.3 V to 5 V** level shifting via a transistor and **hysteresis** in firmware
for stable operation without relay chatter at the switching threshold.

---

## How It Works

Signal chain:

```
Light sensor -> ESP32 (decision) -> 3.3->5 V switch -> Relay module -> Load
   R1 * R2          GPIO ADC        R3 * VT1 * R4       U1        motor + diode
```

1. **Sensor.** Photoresistor `R1` and resistor `R2` form a voltage divider.
   Light level is converted to a voltage read by the ESP32 ADC.
2. **Decision.** The microcontroller compares the ADC value against two thresholds
   (hysteresis) and decides whether to turn the load on or off.
3. **Switch.** Transistor `VT1` (BC547B) matches the 3.3 V logic to the 5 V relay
   input and isolates the 5 V circuit from the ESP32 pins.
4. **Relay.** The module amplifies the signal and mechanically closes the power contacts.
5. **Load.** A DC motor with a protective diode is connected to the relay's dry contacts;
   the motor has its own power supply.

---

## Bill of Materials (BOM)

| # | Component | Value / Model | Purpose |
|---|-----------|---------------|---------|
| DD1 | Microcontroller | ESP32-S3-DevKitC-1 | "Brain": ADC reading, relay control |
| R1 | Photoresistor (LDR) | ~5-10 kOhm | Light sensor |
| R2 | Resistor | 10 kOhm | Lower leg of voltage divider |
| R3 | Resistor | 10 kOhm | Base current limiting for VT1 |
| R4 | Resistor | 10 kOhm | Collector pull-up to +5 V |
| VT1 | Transistor | BC547B (NPN) | Switch / 3.3 V to 5 V level shifter |
| U1 | Relay module | 5 V, 1 channel | Load switching + isolation |
| VD | Diode | 1N400x (e.g. 1N4007) | Flyback protection on motor |
| M1 | DC motor | TT gearmotor, 3-6 V | Load |
| - | Power board | 5 V output (Type-C) | 5 V circuit power supply |
| - | Breadboard, wires | - | Assembly |
| - | Motor power source | 3-6 V batteries | Separate load power supply |

---

## Wiring

### Power supply: two sources, one common ground

- **+3.3 V** — from the ESP32 `3V3` pin (USB powered).
- **+5 V** — from the power board.
- **GND** — common for all: ESP32 `GND`, power board `GND`,
  `R2`, emitter of `VT1`, and relay `GND` all connect here.
  Two separate positive rails, one shared ground.

### Output circuit (motor)

The relay `COM`/`NO` contacts act as a **switch in the positive wire** of the motor:

```
[+ motor source] -> COM -> (relay) -> NO -> [terminal A] -> M1 -> [terminal B] -> [- motor source]
```

The motor is powered by a **separate source**; its ground is **NOT connected** to the logic —
the relay provides galvanic isolation and protects the ESP32 from motor noise.

---

### Environment

- Arduino IDE + **esp32 by Espressif** board package (Boards Manager).
- Board: **ESP32-S3 Dev Module**.
- Serial Monitor: **115200** baud.

---

Schema: https://drive.google.com/file/d/1vhbBhGQc5kWiISbwbE8Wb_8SUfqqywke/view?usp=sharing

Demo: https://drive.google.com/file/d/1gE_kb4EkMD-_r9QQUCjy8BPvogE0WujJ/view?usp=sharing
