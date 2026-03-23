// ============================================
//RISHI_same_speed_bidir
// Constant speed in both directions
// ============================================

#define ENA 6
#define IN1 5
#define IN2 7

int speedValue = 150;
int delayTime = 3000;

void move_forward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);
}

void move_backward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
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

  stop_motor(); // Safety
}

void loop() {
  move_forward(speedValue);
  delay(delayTime);

  stop_motor();
  delay(500);

  move_backward(speedValue);
  delay(delayTime);

  stop_motor();
  delay(500);
}