// ============================================
// Rohit_var_speed
// Motor speed increases and decreases
// ============================================

#define ENA 6   // PWM Speed Control
#define IN1 5   // Direction Pin 1
#define IN2 7   // Direction Pin 2

int delayTime = 10;   // Speed change delay

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Set one direction
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void loop() {

  // 🔼 Slow ramp (0 → 100)
  for(int speed = 0; speed <= 100; speed++) {
    analogWrite(ENA, speed);
    delay(20);   // slower change
  }

  // 🔼 Fast ramp (101 → 255)
  for(int speed = 101; speed <= 255; speed++) {
    analogWrite(ENA, speed);
    delay(5);    // faster change
  }

  // 🔽 Decrease (255 → 0)
  for(int speed = 255; speed >= 0; speed--) {
    analogWrite(ENA, speed);
    delay(10);
  }
}