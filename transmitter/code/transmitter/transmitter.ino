#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
const byte address[6] = "add21";

//Intialization of all the used pins
const int joy1PotL = A0;
const int joy1PotR = A1;
const int joy2PotL = A2;
const int joy2PotR = A3;
const int pot1 = A4;
const int pot2 = A5;
const int joy1Button = 2;
const int joy2Button = 3;
const int button1 = 4;
const int button2 = 5;
const int button3 = 6;
const int button4 = 10;

//Values of all the input pins
struct DATA_PACKAGE
{
  int joy1PotLVal = 125;
  int joy1PotRVal = 125;
  int joy2PotLVal = 125;
  int joy2PotRVal = 125;
  int pot1Val = 125;
  int pot2Val = 125;
  bool joy1ButtonVal = true;
  bool joy2ButtonVal = true;
  bool button1Val = true;
  bool button2Val = true;
  bool button3Val = true;
  bool button4Val = true;
};
DATA_PACKAGE data;





void setup()
{
  //Initializing all the digital pins as INPUT_PULL
  for(int i = 2; i <= 10; i++)
  {
    if(i != 7 && i != 8 && i != 9)
    {
      pinMode(i, INPUT_PULLUP);
    }
  }

  //Initializing all the analog pins as INPUT
  int analogPins[] = {A0, A1, A2, A3, A4, A5};
  for(int i = 0; i < sizeof(analogPins)/4; i++)
  {
    pinMode(analogPins[i], INPUT);
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
  data.joy1PotLVal = analogRead(joy1PotL);
  data.joy1PotRVal = analogRead(joy1PotR);
  data.joy2PotLVal = analogRead(joy2PotL);
  data.joy2PotRVal = analogRead(joy2PotR);
  data.pot1Val = analogRead(pot1);
  data.pot2Val = analogRead(pot2);
  data.joy1ButtonVal = digitalRead(joy1Button);
  data.joy2ButtonVal = digitalRead(joy2Button);
  data.button1Val = digitalRead(button1);
  data.button2Val = digitalRead(button2);
  data.button3Val = digitalRead(button3);
  data.button4Val = digitalRead(button4);
  
  
  //Write the data to the receiver
  radio.write(&data, sizeof(DATA_PACKAGE));
  delay(500);
}
