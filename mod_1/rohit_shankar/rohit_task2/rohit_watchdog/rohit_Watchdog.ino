/*
 * ESP32 Motor Control with Packet Parser & Watchdog
 * Hardware: ESP32 + L298N Motor Driver
 */

// --- Motor Pins (L298N / TB6612 style) ---
const int ENA = 25; const int IN1 = 12; const int IN2 = 13;
const int ENB = 26; const int IN3 = 14; const int IN4 = 27;

// --- Watchdog & State ---
unsigned long lastValidTime = 0;
const unsigned long TIMEOUT = 500; // 0.5 second safety window
bool motorsActive = false;

// --- Buffer ---
String input = ""; 

void setup() {
  Serial.begin(115200);
  
  // Pre-allocate memory to prevent fragmentation
  input.reserve(50); 

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  // Ensure robot starts in a safe, stopped state
  stopMotors(); 
  lastValidTime = millis(); 
  
  Serial.println("✓ Packet Parser Ready");
  Serial.println("Format: LEFT:<int> RIGHT:<int>");
}

void loop() {
  // --- 1. PACKET PARSING ---
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      int L, R;
      
      // Robust sscanf check: requires exactly two integers in the correct format
      if (sscanf(input.c_str(), "LEFT:%d RIGHT:%d", &L, &R) == 2) {
        // Constrain to standard 8-bit PWM range (0-255)
        L = constrain(L, -255, 255);
        R = constrain(R, -255, 255);
        
        moveMotors(L, R);
        lastValidTime = millis(); // Reset the watchdog
        
        Serial.print("Parsed: L=");
        Serial.print(L);
        Serial.print(" R=");
        Serial.println(R);
      } else {
        // Log rejected data for debugging
        Serial.print("✗ Invalid Packet: ");
        Serial.println(input);
      }
      
      input = ""; // Clear buffer for next packet
    } 
    else if (input.length() < 50) {
      input += c;
    } else {
      // Emergency buffer clear if garbage data is too long
      Serial.println("⚠ Buffer overflow, clearing");
      input = "";
    }
  }

  // --- 2. WATCHDOG: Safety Check ---
  // If more than 500ms has passed since the last VALID command
  if (motorsActive && (millis() - lastValidTime > TIMEOUT)) {
    stopMotors();
  }
}

// --- MOTOR CONTROL FUNCTIONS ---

void moveMotors(int L, int R) {
  // LEFT motor direction logic
  digitalWrite(IN1, L >= 0 ? HIGH : LOW);
  digitalWrite(IN2, L < 0 ? HIGH : LOW);
  
  // RIGHT motor direction logic
  digitalWrite(IN3, R >= 0 ? HIGH : LOW);
  digitalWrite(IN4, R < 0 ? HIGH : LOW);

  // Apply speed (using absolute value for PWM)
  analogWrite(ENA, abs(L));
  analogWrite(ENB, abs(R));
  
  motorsActive = true;
}

void stopMotors() {
  // Only execute stop if motors are currently running
  if (!motorsActive) return;
  
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  motorsActive = false;
  Serial.println(" WATCHDOG TRIGGERED: Motors Stopped");
}