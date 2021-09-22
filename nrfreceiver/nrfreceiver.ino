//#include <printf.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ServoTimer2.h>

RF24 radio(7,8);             /* Creating instance 'radio'  ( CE , CSN )   CE -> D7 | CSN -> D8 */                               
const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL;

ServoTimer2 esc;
ServoTimer2 servo1;
ServoTimer2 servo2;

int escValue=1000;
int currSpeed = 1000;
int servo1Value = 1500;
int servo2Value = 1500;
int rx_data[3] = {1000,1000,1000} ;  
void setup() {
// put your setup code here, to run once:
  Serial.begin(9600);            /*Setting baudrate of Serial Port to 9600*/
  radio.begin();                   /* Activate the modem*/
//  radio.setDataRate(RF24_250KBPS);
//  radio.setPALevel(RF24_PA_MAX);
//  printf_begin();
//  radio.printDetails();
  radio.openReadingPipe(1, my_radio_pipe); /* Sets the address of receiver from which program will receive the data*/
  radio.startListening();
  esc.attach(5);
  esc.write(2000);
  delay(2000);
  esc.write(1000);
  servo1.attach(3);
  servo2.attach(4);
}

//void changeSpeedto(int value){
//  delay(5);
//  while(currSpeed < value){
//    currSpeed++;    
//    esc.write(value);
//  }
//}

void loop() {
  if (radio.available())
      {
      while (radio.available())              /* Loop until receiving valid data*/
      {
      radio.read(&rx_data, sizeof(rx_data));/* Read the received data and store in ' rx_data ' */
      escValue = rx_data[0];
      servo1Value = rx_data[1];
      servo2Value = rx_data[2];
      }
    }


    Serial.print("Received Data : ");
    Serial.print(escValue);           /* Print received value on Serial Monitor */
    Serial.print(" ");
    Serial.print(servo1Value);
    Serial.print(" ");
    Serial.println(servo2Value);
    
    esc.write(escValue);
    servo1.write(servo1Value);
    servo2.write(servo2Value);
}
