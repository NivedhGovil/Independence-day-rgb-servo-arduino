# Waving Tiranga — Arduino Servo Flag with Tricolour RGB

An Arduino project that mounts the Indian national flag on a servo horn and sweeps it back and forth to create a continuous waving motion. Alongside it, an RGB LED cycles through the three colours of the flag — saffron, white, and green — one second each.

The servo is toggled ON/OFF with a push button. The LED runs continuously, independent of the servo state.

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

## Wiring

### Servo
| Servo Wire | Connect To |
|-----------|-----------|
| Signal (orange/yellow) | Pin **9** |
| VCC (red) | 5V |
| GND (brown/black) | GND |

### RGB LED
Each colour leg goes through its own 220Ω resistor. The long leg (common cathode) goes to GND.

| LED Leg | Arduino Pin |
|---------|------------|
| Red | Pin **3** (PWM) |
| Green | Pin **5** (PWM) |
| Blue | Pin **6** (PWM) |
| Common | GND |

### Button
| Button Leg | Connect To |
|-----------|-----------|
| Leg 1 | Pin **2** |
| Leg 2 | GND |

The button uses `INPUT_PULLUP`, so the pin reads HIGH when idle and LOW when pressed. No resistor required.

---

## Important Wiring Notes

**Common anode LED?** If your RGB LED's long leg goes to 5V instead of GND, the colours will appear inverted. Fix it by changing one line inside `setColor()`:

```cpp
analogWrite(RED_PIN,   255 - red);
analogWrite(GREEN_PIN, 255 - green);
analogWrite(BLUE_PIN,  255 - blue);
```

**Why pins 3, 5, 6 for the LED?** The `Servo` library takes over Timer1 on the Uno, which disables PWM on pins 9 and 10. Pins 3, 5, and 6 run off Timer2 and Timer0, so `analogWrite()` still works there. Do not move the LED to pin 10 or 11.

**Servo power.** A bare SG90 will run off the Arduino's 5V rail, but a flag adds load and inertia. If the board browns out, resets, or the LED flickers when the servo moves, power the servo from an external 5V supply and connect **both grounds together**.

---

## Software Setup

1. Install the [Arduino IDE](https://www.arduino.cc/en/software)
2. `Servo.h` ships with the IDE — no extra library install needed
3. Open the sketch, select your board and port under **Tools**
4. Upload

---

## How It Works

The `loop()` runs two independent blocks on every pass.

**1. LED cycle.** A timestamp (`lastColorChangeTime`) is compared against `millis()`. Once 1000 ms have elapsed, `colorState` advances using modulo 3, wrapping 0 → 1 → 2 → 0, and the matching colour is written to the LED.

**2. Button and servo.** The button state is read every loop. A state change from HIGH to LOW (the moment of press) flips the `isRunning` flag — this edge detection is what makes one press equal one toggle, rather than the servo running only while the button is held.

When `isRunning` is true, the servo advances one degree every `stepDelay` milliseconds. `sweepDirection` flips from `+1` to `-1` at 140° and back to `+1` at 20°, producing the continuous back-and-forth wave.

---

## Customisation

| Variable | Default | Effect |
|----------|---------|--------|
| `stepDelay` | `20` | Milliseconds per degree. Lower = faster wave. Below ~5 the servo may not keep up |
| `currentAngle >= 140` | `140` | Upper sweep limit |
| `currentAngle <= 20` | `20` | Lower sweep limit |
| `>= 1000` | `1000` | LED colour hold time in milliseconds |

### Tuning the flag colours

The sketch currently uses `setColor(255, 10, 0)` for saffron, which reads as a deep red-orange. For colours closer to the official flag specification:

| Colour | Hex | RGB values |
|--------|-----|-----------|
| India Saffron | `#FF9933` | `setColor(255, 153, 51)` |
| White | `#FFFFFF` | `setColor(255, 255, 255)` |
| India Green | `#138808` | `setColor(19, 136, 8)` |

Cheap RGB LEDs are rarely colour-accurate — the red channel usually dominates. Adjust the green value up or down by 20–30 until the saffron looks right to your eye.

---

## Known Limitations

- **Debounce is blocking.** The `delay(50)` after a button press briefly freezes the loop. It works fine here, but a timestamp-based debounce would be cleaner if you extend the project.
- **No sweep easing.** The servo moves at a constant rate, so the wave is mechanical rather than fluid. Applying a sine curve to `stepDelay` would soften the motion at the turning points.
- **Servo position is not reset on stop.** Pressing the button mid-sweep leaves the flag wherever it was.

---

## Possible Extensions

- Add a buzzer to play a tune while the flag waves
- Use a second servo for a horizontal axis to get a more realistic ripple
- Fade between LED colours instead of switching instantly
- Add an LDR so the LED only lights up in low ambient light

---

## License

MIT — free to use, modify, and share.
