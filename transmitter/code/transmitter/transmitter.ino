#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
const byte address[6] = "add21";


//This are the digital pins that are use for the buttons
//Digital pins 2 and 3 corspond to the the buttons of the joystick 
//The other pins corspond to the individual buttons number from 1-4
const int DIGITALPINS[6] = {2, 3, 4, 5, 6, 10};


//This are the analog pins used for the potetiometer
//Pins A0, A1, A2 and A3 are connected to the potentiometers on the joysticks
//A4 and A5 are connect to two separete potentiometers
const int ANALOGPINS[6] = {A0, A1, A2, A3, A4, A5};


//Values of all the input pins
struct DATA_PACKAGE
{
  int analogVal[6] = {};
  bool digitalVal[6] = {};
};
DATA_PACKAGE data;







void setup()
{
  //Intializing the values to the default of 127 for analog and 1/true for digital
  for(int i = 0; i < 6; i++)
  {
    data.analogVal[i] = 127;
    data.digitalVal[i] = true;
  }

  
  //Initializing all the digital pins as INPUT_PULL and the analogs to INPUT
  for(int i = 0; i < 6; i++)
  {
    pinMode(DIGITALPINS[i], INPUT_PULLUP);
    pinMode(ANALOGPINS[i], INPUT);
  }


  //Initalizing the radio communication protocol
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}


void loop()
{
  //Reading the data from the sensors and mapping it to the apropriat value
  for(int i = 0; i < 6; i++)
  {
    data.analogVal[i] = map(analogRead(ANALOGPINS[i]), 0, 1023, 0, 255);
    data.digitalVal[i] = digitalRead(DIGITALPINS[i]);
  }
  
  
  //Write the data to the receiver
  radio.write(&data, sizeof(DATA_PACKAGE));
}
