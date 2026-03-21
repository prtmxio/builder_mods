// ============================================
// Rohit_var_speed (Final Review Version)
// Motor speed increases and decreases
// ============================================

#define ENA 6   // PWM Speed Control
#define IN1 5   // Direction Pin 1
#define IN2 7   // Direction Pin 2

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // 🔒 SAFETY FIRST: Ensure motor is OFF at startup
  stop_motor();

  // Set direction
  move_forward();
}

// 🚀 Move Forward
void move_forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

// 🔁 Move Backward (for future use)
void move_backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

// 🎛️ Set Speed
void set_speed(int speed) {
  analogWrite(ENA, speed);
}

//  Stop Motor
void stop_motor() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop() {

  //  Slow ramp (0 → 100)
  for(int speed = 0; speed <= 100; speed++) {
    set_speed(speed);
    delay(20);
  }

  //  Fast ramp (101 → 255)
  for(int speed = 101; speed <= 255; speed++) {
    set_speed(speed);
    delay(5);
  }

  //  Decrease (255 → 0)
  for(int speed = 255; speed >= 0; speed--) {
    set_speed(speed);
    delay(10);
  }
}