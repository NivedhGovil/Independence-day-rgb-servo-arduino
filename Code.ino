#include <Servo.h>

// Pin Definitions
const int SERVO_PIN  = 9;
const int BUTTON_PIN = 2;

// RGB LED Pins (Must be PWM ~ pins for color mixing)
const int RED_PIN   = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN  = 6;

Servo myServo;

// Servo & Button variables
bool isRunning = false;
bool lastButtonState = HIGH;

int currentAngle = 20;
int sweepDirection = 1;
unsigned long lastMoveTime = 0;
const int stepDelay = 20; // Servo speed (ms per degree)

// RGB LED State Tracking
unsigned long lastColorChangeTime = 0;
int colorState = 0; // 0 = Saffron, 1 = White, 2 = Green

// Function to set RGB LED color (0 - 255)
void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

void setup() {
  myServo.attach(SERVO_PIN);
  myServo.write(currentAngle);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  // Set initial color (Saffron)
  setColor(255, 10, 0); 
}

void loop() {
  unsigned long currentMillis = millis();

  // ==========================================
  // 1. RGB LED LOGIC (Runs Continuously)
  // ==========================================
  // Switch color every 1000ms (1 second)
  if (currentMillis - lastColorChangeTime >= 1000) {
    lastColorChangeTime = currentMillis;
    colorState = (colorState + 1) % 3; // Cycle through 0 -> 1 -> 2 -> 0

    switch (colorState) {
      case 0:
        // Saffron (Orange/Red tint)
        setColor(255, 10, 0);
        break;
      case 1:
        // White
        setColor(255, 255, 255);
        break;
      case 2:
        // Green
        setColor(0, 255, 0);
        break;
    }
  }

  // ==========================================
  // 2. BUTTON & SERVO LOGIC (Controlled by Switch)
  // ==========================================
  bool currentButtonState = digitalRead(BUTTON_PIN);
  
  // Toggle motor state on button press
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    isRunning = !isRunning;
    delay(50); // Simple debounce
  }
  lastButtonState = currentButtonState;

  // If toggled ON, sweep the servo motor
  if (isRunning) {
    if (currentMillis - lastMoveTime >= stepDelay) {
      lastMoveTime = currentMillis;

      currentAngle += sweepDirection;
      myServo.write(currentAngle);

      // Bounce back at limits
      if (currentAngle >= 140) {
        sweepDirection = -1;
      } else if (currentAngle <= 20) {
        sweepDirection = 1;
      }
    }
  }
}
