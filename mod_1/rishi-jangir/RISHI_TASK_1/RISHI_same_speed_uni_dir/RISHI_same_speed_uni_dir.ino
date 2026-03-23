// ============================================
// RISHI_same_speed_uni_dir
// Motor runs at constant speed in one direction
// ============================================

#define ENA 6
#define IN1 5
#define IN2 7

int speedValue = 150;

void move_forward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
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

  stop_motor();                 // Safety init
  move_forward(speedValue);     // Start motor
}

void loop() {
  // Continuous forward
}