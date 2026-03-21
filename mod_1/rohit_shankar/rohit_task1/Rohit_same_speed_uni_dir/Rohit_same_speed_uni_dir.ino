// ============================================
// Rohit_same_speed_uni_dir (Final Version)
// Motor runs at constant speed in one direction
// ============================================

#define ENA 6   // PWM Speed Control
#define IN1 5   // Direction Pin 1
#define IN2 7   // Direction Pin 2

int speedValue = 150;  // Set speed (0 to 255)

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // SAFETY: Ensure motor is OFF at startup
  stop_motor();

  // Start motor after safe init
  move_forward(speedValue);
}

//  Forward Function
void move_forward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);
}

//Stop Function
void stop_motor() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop() {
  // Motor runs continuously
}
