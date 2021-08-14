#include <VirtualWire.h>

byte txBuffer[4] = {0,125,125,125};

int value = 0;
float ema_a = 0.6;

void setup(){
  vw_set_tx_pin(12);
  vw_setup(2000);
  Serial.begin(9600);
}

void loop(){

  if(Serial.available() > 0){
    value = Serial.parseInt();
  }
  Serial.println(value);
  txBuffer[0] = value;
  vw_send(txBuffer,4);
  vw_wait_tx();
}
