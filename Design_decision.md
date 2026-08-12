# Design Decisions

## 1. Non-Blocking Timing with `millis()` Instead of `delay()`

### Decision
Use `millis()` for servo sweep and LED color changes rather than `delay()`.

### Why
- **Responsiveness** — The button remains responsive while the servo is moving. With `delay()`, the entire program would freeze, and button presses would be missed.
- **Concurrent operations** — The LED cycles independently of servo motion. Both can happen simultaneously.
- **Better UX** — Pressing the button instantly toggles the servo without waiting for current operations to finish.

### Trade-off
Slightly more complex code (tracking timestamps), but vastly better user experience.

---

## 2. PWM Pins for RGB LED (Pins 3, 5, 6)

### Decision
Use Arduino pins 3, 5, and 6 (PWM-capable) for RGB LED control.

### Why
- **PWM (Pulse Width Modulation)** allows brightness control (0-255) via `analogWrite()`
- Pins 3, 5, 6 are the only PWM pins available on Arduino Uno besides pin 9 (reserved for servo)
- Enables smooth color mixing (e.g., Saffron = high red + low green)

### Alternative Considered
Using non-PWM pins with digital on/off would only allow 8 color combinations (2³), not smooth color gradients.

---

## 3. Servo Angle Range: 20° to 140°

### Decision
Sweep the servo between 20° and 140° instead of the full 0° to 180°.

### Why
- **Mechanical safety** — Prevents servo from hitting the end of its range abruptly, which can damage the motor
- **Smooth motion** — Larger angle range (120°) creates a natural waving motion
- **Flag physics** — A 120° swing mimics realistic flag waving motion

### Trade-off
Doesn't use the full servo range, but prioritizes longevity and natural motion.

---

## 4. Color Cycle Every 1 Second

### Decision
Change RGB LED color every 1000ms (1 second).

### Why
- **Human perception** — 1 second is fast enough to see the flag colors clearly, but slow enough to appreciate each color
- **Synchronized with servo** — Independent timing means LED cycles continuously (even if servo is off), creating visual interest
- **Power efficiency** — Not too fast (which would drain battery faster)

### Alternative Considered
Faster cycling (every 100ms) felt jarring; slower (every 5s) made the display feel static.

---

## 5. Common Cathode RGB LED

### Decision
Use a common cathode RGB LED (all color legs go HIGH, common leg to GND).

### Why
- **More common** — Easier to source and cheaper than common anode
- **Standard Arduino tutorials** — Most resources use common cathode
- **Simpler logic** — `digitalWrite(HIGH)` = color on, `digitalWrite(LOW)` = color off

### Trade-off
Requires 3 resistors (one per color leg); common anode would also work but requires inverted logic (255 - value).

---

## 6. Internal Pull-Up for Button (No External Resistor)

### Decision
Use Arduino's `INPUT_PULLUP` mode instead of adding an external pull-up resistor.

### Why
- **Simplicity** — Fewer components = fewer wiring mistakes
- **Built-in feature** — Arduino Uno has internal 20kΩ pull-up resistors
- **Cost** — Saves 1 resistor
- **Reliable** — Well-tested in Arduino hardware

### Trade-off
Slightly slower response (due to resistor value), but negligible for a button.

---

## 7. Step Delay of 20ms Per Degree

### Decision
Move servo 1° every 20ms (total sweep time: ~2.4 seconds for 120° range).

### Why
- **Smooth motion** — 50 Hz update rate is imperceptible to human eyes
- **Servo capability** — SG90 servo can reliably move 1° in 20ms
- **Performance** — Doesn't waste CPU cycles with faster updates

### Alternative Considered
- 10ms per degree (faster): Too twitchy, more CPU load
- 50ms per degree (slower): Motion becomes jerky/noticeable

---

## 8. Debounce Delay of 50ms

### Decision
Use `delay(50)` for button debounce.

### Why
- **Eliminates chatter** — Mechanical buttons bounce for 10-50ms; 50ms ensures a clean signal
- **Simple** — One `delay()` for debounce is acceptable (doesn't block other operations in this design)

### Trade-off
Uses blocking `delay()`, but only happens on button press (not in main loop), so responsiveness isn't affected.

---

## Future Improvements

1. **WiFi Control** — Add Arduino MKR WiFi 1010 for remote on/off via mobile app
2. **Light Sensor** — Auto-adjust LED brightness based on ambient light
3. **Acceleration/Deceleration** — Smooth ramp-up/down for more realistic flag motion
4. **SD Card Logging** — Store motion patterns for replay
