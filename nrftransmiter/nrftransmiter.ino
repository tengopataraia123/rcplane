#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <printf.h>

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL; //Remember that this code should be the same for the receiver

RF24 radio(9,10);

int txBuffer[3] = {1000,2000,2000};

int velocity,value=0,leftRight,upDown,offset;
float ema_a = 0.6;

void setup()
{
//  Serial.begin(9600);
  radio.begin();
//  printf_begin();
//  radio.printDetails();
  radio.openWritingPipe(my_radio_pipe);
  radio.stopListening();
  offset = analogRead(0);
}

/**************************************************/


void loop()
{
  velocity = analogRead(0)-offset;
  leftRight = analogRead(4);
  upDown = analogRead(2);
  
  //velocity fillter
  velocity = velocity<0?0:velocity;
  velocity = velocity>(640-offset)?(640-offset):velocity;
  velocity = (ema_a*velocity) + (1-ema_a)*velocity;
  velocity = map(velocity,0,640-offset,1000,2000);
  value = (abs(velocity-value) >= 5) ? velocity : value;

  leftRight = map(leftRight,0,1023,2000,1000);
  upDown = map(upDown,0,1023,1000,1800);

//  Serial.print(velocity);           /* Print received value on Serial Monitor */
//  Serial.print(" ");
//  Serial.print(txBuffer[1]);
//  Serial.print(" ");
//  Serial.println(txBuffer[2]);
  
  txBuffer[0] = value;

  txBuffer[1] = leftRight;
  txBuffer[2] = upDown;

  
  radio.write(&txBuffer, sizeof(txBuffer));
}
