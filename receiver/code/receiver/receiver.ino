#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
const byte address[6] = "add21";


//Values to be received
struct DATA_PACKAGE
{
  int analogVal[6] = {};
  bool digitalVal[6] = {};
};
DATA_PACKAGE data;


void setup()
{  
  //Initializing the DATA_PACKAGE
  for(int i = 0; i < 6; i++)
  {
    data.analogVal[i] = 127;
    data.digitalVal[i] = true;
  }


  
  //Initalizing the radio communication 
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}

void loop()
{
  if(radio.available())
  {
    radio.read(&data, sizeof(DATA_PACKAGE));
  }
}
