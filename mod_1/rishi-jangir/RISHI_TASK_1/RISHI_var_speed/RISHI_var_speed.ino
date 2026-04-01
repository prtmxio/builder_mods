// ============================================
// RISHI_var_speed
// Motor speed increases and decreases
// ============================================

#define ENA 6
#define IN1 5
#define IN2 7

void move_forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void set_speed(int speed) {
  analogWrite(ENA, speed);
}

void stop_motor() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  stop_motor();    // Safety init
  move_forward();  // Set direction
}

void loop() {
  // Speed ramp up: 0 → 255
  for (int speed = 0; speed <= 255; speed++) {
    set_speed(speed);
    delay(10);   // Adjust delay for smoothness
  }

  // Speed ramp down: 255 → 0
  for (int speed = 255; speed >= 0; speed--) {
    set_speed(speed);
    delay(10);   // Same delay for symmetry
  }
}
