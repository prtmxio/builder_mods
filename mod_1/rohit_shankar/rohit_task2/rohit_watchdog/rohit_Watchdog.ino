/*
 * ESP32 Motor Control with Packet Parser & Watchdog
 * Hardware: ESP32 + L298N Motor Driver
 */

// --- Motor Pins ---
const int ENA = 25; const int IN1 = 12; const int IN2 = 13;
const int ENB = 26; const int IN3 = 14; const int IN4 = 27;

// --- Watchdog ---
unsigned long lastValidTime = 0;
const unsigned long TIMEOUT = 500;
bool motorsActive = false;

// --- Buffer ---
String input = "";

void setup() {
  Serial.begin(115200);

  input.reserve(50);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  // Force safe startup state
  stopMotors();

  Serial.println("✓ Packet Parser Ready");
  Serial.println("Format: LEFT:<int> RIGHT:<int>");
}

void loop() {

  // --- PACKET PARSING ---
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      int L, R;

      // Flexible parsing (handles optional spacing)
      if (sscanf(input.c_str(), "LEFT:%d RIGHT:%d", &L, &R) == 2 ||
          sscanf(input.c_str(), "LEFT:%dRIGHT:%d", &L, &R) == 2) {

        L = constrain(L, -255, 255);
        R = constrain(R, -255, 255);

        moveMotors(L, R);

        lastValidTime = millis(); // start watchdog after first valid packet

        Serial.print("Parsed: L=");
        Serial.print(L);
        Serial.print(" R=");
        Serial.println(R);
      } else {
        Serial.print("✗ Invalid Packet: ");
        Serial.println(input);
      }

      input = "";
    }
    else if (input.length() < 50) {
      input += c;
    }
    else {
      Serial.println("⚠ Buffer overflow, clearing");
      input = "";
    }
  }

  // --- WATCHDOG ---
  if (motorsActive && lastValidTime > 0 &&
      (millis() - lastValidTime > TIMEOUT)) {
    stopMotors();
  }
}

// --- MOTOR CONTROL ---

void moveMotors(int L, int R) {

  // LEFT motor
  if (L == 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, L > 0 ? HIGH : LOW);
    digitalWrite(IN2, L < 0 ? HIGH : LOW);
  }

  // RIGHT motor
  if (R == 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, R > 0 ? HIGH : LOW);
    digitalWrite(IN4, R < 0 ? HIGH : LOW);
  }

  // Speed control
  analogWrite(ENA, abs(L));
  analogWrite(ENB, abs(R));

  // Correct motor state tracking
  motorsActive = (L != 0 || R != 0);
}

void stopMotors() {

  // Always force safe state (important fix)
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  if (motorsActive) {
    Serial.println("⚠ WATCHDOG TRIGGERED: Motors Stopped");
  }

  motorsActive = false;
}
