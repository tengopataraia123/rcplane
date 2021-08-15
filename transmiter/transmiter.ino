#include <VirtualWire.h>

byte txBuffer[4] = {0,125,125,125};

float ema_a = 0.1;

int velocity = 0;
int leftRight = 0;
int upDown = 0;
int offset = 0;

int value = 0;

void setup(){
  vw_set_tx_pin(8);
  vw_setup(2000);
  offset = analogRead(0);
  Serial.begin(9600);
}

void loop(){

  velocity = analogRead(0) - offset;
  leftRight = analogRead(2);
  upDown = analogRead(4);
  
//velocity fillter
  velocity = (ema_a*velocity) + (1-ema_a)*velocity;
  velocity = map(velocity,0,640-offset,0,255);
  value = (abs(velocity-value) >= 5) ? velocity : value;
  value = value < 0 ? 0: value;
  value = value > 255 ? 255: value;
  txBuffer[0] = value;

//left right fillter
  if(leftRight > 1000)
    leftRight = 1;
  else if(leftRight < 20)
    leftRight = 2;
  else
    leftRight = 0;

    
//up down fillter
  if(upDown > 1000)
    upDown = 1;
  else if(upDown < 20)
    upDown = 2;
  else
    upDown = 0;


  switch(leftRight){
    case 1:
      txBuffer[1] = 255;
      txBuffer[2] = 255;
      break;
    case 2:
      txBuffer[1] = 0;
      txBuffer[2] = 0;
      break;
    case 0:
      txBuffer[1] = 125;
      txBuffer[2] = 125;
      break;
  }

  switch(upDown){
    case 1:
      txBuffer[3] = 220;
      break;
    case 2:
      txBuffer[3] = 20;
      break;
    case 0:
      txBuffer[3] = 125;
      break;
  }

  Serial.println(txBuffer[0]);
  vw_send(txBuffer,4);
  vw_wait_tx();
}
