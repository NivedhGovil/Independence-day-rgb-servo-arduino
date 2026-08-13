# Waving Tiranga — Arduino Servo Flag with Tricolour RGB

An Arduino project that mounts the Indian national flag on a servo horn and waves it back and forth. Simultaneously, an RGB LED cycles through the three colours of the flag — saffron, white, and green.

The servo is toggled ON/OFF with a push button. The LED runs continuously, independent of the servo and button state.

---

## Features

- **Waving flag motion** — servo sweeps smoothly between 20° and 140° and bounces back at the limits
- **Tricolour LED cycle** — saffron → white → green, changing every second
- **Push-button toggle** — one press starts the wave, the next press stops it
- **Non-blocking timing** — both the servo sweep and the LED cycle use `millis()` instead of `delay()`, so the LED keeps cycling and the button stays responsive while the servo is moving

---

## Hardware Required

| Qty | Component | Notes |
|-----|-----------|-------|
| 1 | Arduino Uno / Nano | Any ATmega328P board works |
| 1 | Micro servo (SG90 / MG90S) | MG90S recommended if the flag is large or on a long stick |
| 1 | RGB LED (common cathode) | See note below if yours is common anode |
| 3 | 220Ω resistors | One for each LED colour leg |
| 1 | Push button (tactile switch) | No external resistor needed — internal pull-up is used |
| — | Jumper wires, breadboard | |
| 1 | Paper/cloth flag + light stick | Taped or glued to the servo horn |
| 1 | External 5V supply (optional) | Recommended if the servo stutters or resets the board |

---

## Wiring & Schematics

For wiring details and a full schematic, see the wiring and schematic files included in this repository (for example, Schematic.png). These files contain the wiring diagram, pin assignments, and power/ground connections used by the reference sketch.

## Other files

- Schematic.png — wiring diagram / schematic (image)
- Arduino sketch(es) — the code files in this repository implement the servo motion, LED cycling, and button handling. Review the .ino files for the exact pin assignments and behaviour.

---

## License

MIT — free to use, modify, and share.
