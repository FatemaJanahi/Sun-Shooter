/*
Filename: Project_Code_TARGET
Authors: Fatema Janahi, Selena Nguyen, David Muir, Ciaran Farley
Brief: Code for Targets 
* Checks whether targets are knocked down and communicates with second Arduino Mega,  
* which displays score. 
*/


// include the libraries:
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

//pins for IR sensors
const int IR1 = A1;
const int IR2 = A2;
const int IR3 = A3;
const int IR4 = A4;
const int IR5 = A5;

//initial score
int score = 0;

//booleans of reading to send to receiver
int IR1state = 0;
int IR2state = 0;
int IR3state = 0;
int IR4state = 0;
int IR5state = 0;

//set these integers to 0 initially 
//(to be used to stop reading sensors once targets are down).
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;

//char to store the data (score) to be sent to other Arduino Mega
unsigned char data;

//Setup:
void setup() {
  //set up the transmission
  radio.begin(); 
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  //set up IR sensors as inputs
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  
  delay(2000);

  data = '0'; //sets initial data to be sent as 0 (score=0);
  
  //if a is 0, check the first sensor
  if (a == 0)
  {
    //read the state of sensor 1 (target 1)
    IR1state = analogRead(IR1);
  
    //if the target is down (value found through testing)
    if (IR1state < 400){
      score++; //increment score
      a++; //increment a to stop reading this sensor
    }
  }

  //sensor two
  if (b == 0)
  {
    IR2state = analogRead(IR2);
    if (IR2state < 200) {
      score++;
      b++;
    }
  }

  //sensor three
  if (c == 0)
  { 
    IR3state = analogRead(IR3);
    if (IR3state < 700) {
      score++;
      c++;
    }
  }

  //sensor four
  if (d == 0)
  { IR4state = analogRead(IR4);
    if (IR4state > 600) {
      score++;
      d++;
    }
  }

  //sensor five
  if (e == 0)
  {
    IR5state = analogRead(IR5);
    if (IR5state < 400) {
      score++;
      e++;
    }
  }

//set data based on score;
  if (score == 0)
  { data = '0';
  }
  if (score == 1)
  { data = '1';
  }
  if (score == 2)
  { data = '2';
  }
  if (score == 3)
  { data = '3';
  }
  if (score == 4)
  { data = '4';
  }
  if (score == 5)
  { data = '5';
  }

  delay(1000);

  //send data to the other Arduino
  radio.write( &data, sizeof(unsigned char));
}

