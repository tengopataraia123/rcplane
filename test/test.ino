#include <Servo.h>

Servo esc;

void setup(){
  Serial.begin(9600);
  esc.attach(2);
  delay(1000);
}

int motorSpeed = 0;

void loop(){

  if(Serial.available() > 0){
    motorSpeed = Serial.parseInt();
  }
  esc.writeMicroseconds(motorSpeed);
  Serial.println(motorSpeed);
}
