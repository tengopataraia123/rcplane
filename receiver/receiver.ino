#include <ServoTimer2.h>
#include <VirtualWire.h>

ServoTimer2 esc;
ServoTimer2 servo1;
ServoTimer2 servo2;
ServoTimer2 servo3;


int escValue=1000;
int currSpeed = 1000;
int servo1Value = 1500;
int servo2Value = 1500;
int servo3Value = 1500;

byte message[4]; // a buffer to store the incoming messages
byte messageLength = 4; // the size of the message

void setup() {
  Serial.begin(9600);
  esc.attach(2);

  esc.write(2000);
  delay(2000);
  esc.write(1000);
  
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  vw_set_rx_pin(13);
  vw_setup(2000);
  vw_rx_start();
  delay(1000);
}

void changeSpeedto(int value){
  delay(20);
  esc.write(value);
}

void loop() {
  changeSpeedto(1000);
  vw_wait_rx();
  if (vw_get_message(message, &messageLength)) {
    escValue = map(message[0],0,255,1000,2000);
    servo1Value = map(message[1],0,255,1000,2000);
    servo2Value = map(message[2],0,255,1000,2000);
    servo3Value = map(message[3],0,255,1000,2000);
  }
  changeSpeedto(escValue);
  servo1.write(servo1Value);
  servo2.write(servo2Value);
  servo3.write(servo3Value);
}
