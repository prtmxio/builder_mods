// ============================================
// Rohit_same_speed_bidir (Improved Version)
// ============================================

#define ENA 6   // PWM Speed Control
#define IN1 5   // Direction Pin 1
#define IN2 7   // Direction Pin 2

int speedValue = 150;   // Constant speed (0–255)
int delayTime = 3000;   // Time for each direction (3 sec)

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  //  SAFETY: Ensure motor is OFF at startup
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

// Forward Function
void move_forward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);
}

// Backward Function
void move_backward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);
}

//  Stop Function
void stop_motor() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop() {

  //  Forward
  move_forward(speedValue);
  delay(delayTime);

  //  Stop before reverse
  stop_motor();
  delay(500);

  //  Reverse
  move_backward(speedValue);
  delay(delayTime);

  //  Stop again
  stop_motor();
  delay(500);
}