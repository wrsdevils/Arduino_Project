#include <Servo.h>

int val = 2;
Servo servo_5  ;
Servo servo_7  ;
int mesure_distance_cm(byte trig_pin,byte dist_pin)
{
  digitalWrite(trig_pin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig_pin,LOW);
  int value=(pulseIn(dist_pin,HIGH)/2)/29.1+2;
  if(value>255) {value=255; }
  delay(20);
  return value;
}
void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
  pinMode(6,INPUT);
  pinMode(3,OUTPUT);

  pinMode (val, INPUT);
  pinMode (3, OUTPUT);
  Serial.begin(9600);

  servo_5.attach (8) ;
  servo_7.attach (7) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mesure_distance_cm(4,6)<=30){
    int sensor1 = digitalRead(val);
    delay(500) ;
    if (sensor1 == 0) {
      Serial.println("ตรวจพบโลหะ");
      Serial.println();
      delay(500) ;      
      servo_7.write(0);      
      servo_5.write(180);
      tone(3, 10000);
    }
    else {
      Serial.println("พบวัตถุ ไม่พบโลหะ");
      Serial.println();
      delay(500) ;                        
      servo_7.write(180) ;
      servo_5.write(0) ;
      tone(3, 1000);
      }
    
  }
  else{
    Serial.println("ไม่พบวัตถุ");
    Serial.println();
    servo_7.write(90) ;
    servo_5.write(90);
    noTone(3) ;
  }
  delay(3500);
}