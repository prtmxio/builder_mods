// ============================================
// Rohit_same_speed_uni_dir
// Motor runs at constant speed in one direction
// ============================================

#define ENA 6   // PWM Speed Control
#define IN1 5   // Direction Pin 1
#define IN2 7   // Direction Pin 2

int speedValue = 150;  /// ============================================
// Rohit_same_speed_uni_dir (Improved Version)
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

  //  SAFETY: Ensure motor is OFF at startup
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  // Start motor after safe init
  move_forward(speedValue);
}

// Forward Function
void move_forward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);
}

//  Optional Stop Function (good practice)
void stop_motor() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop() {
  // Motor runs continuously in forward direction
}/ Set speed (0 to 255)

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Set motor direction (Forward)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Set constant speed
  analogWrite(ENA, speedValue);
}

void loop() {
  // Empty loop → motor runs continuously
}