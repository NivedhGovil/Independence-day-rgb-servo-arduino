# Design Decisions

## 1. Non-Blocking Timing with `millis()` Instead of `delay()`

### Decision
Use `millis()` for servo sweep and LED color changes rather than `delay()`.

### Why
- **Responsiveness** — The button remains responsive while the servo is moving. With `delay()`, the entire program would freeze, and button presses would be missed.

---

## 2. PWM Pins for RGB LED (Pins 3, 5, 6)

### Decision
Use Arduino pins 3, 5, and 6 (PWM-capable) for RGB LED control.

### Why
- **PWM (Pulse Width Modulation)** allows brightness control (0-255) via `analogWrite()`
- Pins 3, 5, 6 are the only PWM pins available on Arduino Uno besides pin 9 (reserved for servo)

### Alternative Considered
Using non-PWM pins with digital on/off would only allow 8 color combinations (2³), not smooth color gradients.

---

## 3. Servo Angle Range: 20° to 140°

### Decision
Sweep the servo between 20° and 140° instead of the full 0° to 180°.

### Why
- **Mechanical safety** — Prevents servo from hitting the end of its range and the ground, which can damage the motor and look unrealistic. 
- **Smooth motion** — Larger angle range (120°) creates a natural waving motion

---

## 4. Color Cycle Every 1 Second

### Decision
Change RGB LED color every 1000ms (1 second).

### Why
- **Human perception** — 1 second is fast enough to see the flag colors clearly, but slow enough to appreciate each color
- **Power efficiency** — Not too fast (which would drain battery faster)

### Alternative Considered
Faster cycling (every 100ms) felt quick and uncomprehensive. 
Slower (every 5s) makes it too slow and tests patience.

---

## 5. Common Cathode RGB LED

### Decision
Use a common cathode RGB LED (all color legs go HIGH, common leg to GND).

### Why
- **More common** — Easier to source and cheaper than common anode
- **Standard Arduino tutorials** — Most resources use common cathode

---

## 6. Step Delay of 20ms Per Degree

### Decision
Move servo 1° every 20ms (total sweep time: ~2.4 seconds for 120° range).

### Why
- **Smooth motion** — Makes the motion slow enough to cope up with human eyes. 
- **Servo capability** — SG90 servo can reliably move 1° in 20ms. Too fast can damage it.

