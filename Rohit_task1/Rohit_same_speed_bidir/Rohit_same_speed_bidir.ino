// ============================================
// Rohit_same_speed_bidir
// Constant speed in both directions
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
}

void loop() {

  // 🔄 Forward Direction
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedValue);
  delay(delayTime);

  // ⛔ Stop before reversing (optional but safe)
  analogWrite(ENA, 0);
  delay(500);

  // 🔁 Reverse Direction
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speedValue);
  delay(delayTime);

  // ⛔ Stop again
  analogWrite(ENA, 0);
  delay(500);
}