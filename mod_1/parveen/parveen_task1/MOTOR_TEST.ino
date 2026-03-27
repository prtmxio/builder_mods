#define ENA 6//PWM speed control
#define IN1 5   //Direction Pin1
#define IN2 7  //Direction Pin2

void setup()
{
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  // Ensure motor is OFF at start
  stop_motor();

}

void loop()
{  
   // 1.(a)Direction(FORWARD) 
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  
  // 1.(b)Direction(BACKWARD) swap...IN1 & IN2 logic


  // 2.Ramp up from(0-100)
  for(int speed = 0; speed<=100;speed++){
    analogWrite(ENA,speed);
    delay(20);
  }
  
  // 3.Ramp up(101-255)
  for(int speed = 101; speed<=255;speed++){
    analogWrite(ENA,speed);
    delay(5);
  }
  delay(2000);  // Running for 2 sec

  // 4.Ramp down(255-0)
  for(int speed = 255;speed>=0;speed--){
    analogWrite(ENA,speed);
    delay(15);
  }
  delay(1000); // Rest for 1 sec
}
void stop_motor(){
  analogWrite(ENA,0);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
}

