/*
Filename: Project_Code_BOW
Authors: Fatema Janahi, Selena Nguyen, David Muir, Ciaran Farley
Brief: Code for Bow & Screen 
* Receives data from first Arduino Mega and displays score on LCD screen.
*/


// include the libraries:
#include <LiquidCrystal.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";


//LCD Screen pin setup
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//integer for the score
int score = 0;
//char to receive data
unsigned char data;

//buzzer and led pins
const int buzzer = 22;
int led1 = 27;
int led2 = 29;
int led3 = 31;
int led4 = 33;
int led5 = 35;


int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;

//function decleration 
void screen();

void setup() {

  //setup buzzer and leds as outputs
  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  //set up screen
  lcd.begin(16, 2);
  lcd.clear();

  //open serial port, set data rate to 9600 bps
  Serial.begin(9600);

  //begin radio transmission
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
    while (radio.available()) {
      // Go and read the data and put it into that variable
      radio.read( &data, sizeof(char)); 
      Serial.print(data);
      delay(1000);
      //output score to the screen and lights
      screen();
    }
  }

//function outputs score and turns on corresponding number of lights
//based on data being received. Sounds buzzer once targets are hit.
void screen()
{
  if (data == 48)//Score is 0
  {
    //all lights off
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);

    lcd.clear();
    lcd.print ("Score: 0");
    lcd.setCursor(0, 1);
    lcd.print ("Game has started!");
  }

  if (data == 49) //Score 100
  { 
    //One light on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    lcd.clear();
    lcd.print ("Score: 100");
    lcd.setCursor(0, 1);
    lcd.print ("Nice work!");

    //sound the buzzer
    while (b == 0) //ensure this is done only once
    {
      tone(buzzer, 500, 1500);
      delay(100);
      b = 1;
    }
  }

  if (data == 50)
  { digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);

    lcd.clear();
    lcd.print ("Score: 200");
    lcd.setCursor(0, 1);
    lcd.print ("Keep going!");

    while (c == 0)
    {
      tone(buzzer, 500, 1500);
      delay(100);
      c = 1;
    }
  }

  if (data == 51)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);

    lcd.clear();
    lcd.print ("Score: 300");
    lcd.setCursor(0, 1);
    lcd.print ("Wow!");

    while (d == 0)
    {
      tone(buzzer, 500, 1500);
      delay(100);
      d = 1;
    }
  }

  if (data == 52)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    lcd.clear();
    lcd.print ("Score: 400");
    lcd.setCursor(0, 1);
    lcd.print ("On fire!");

    while (e == 0)
    {
      tone(buzzer, 500, 1500);
      delay(100);
      e = 1;
    }
  }

  if (data == 53)
  { digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);

    lcd.clear();
    lcd.print ("Score: 500");
    lcd.setCursor(0, 1);
    lcd.print ("YOU GET A STAMP!");

    while (f == 0)
    {
      tone(buzzer, 500, 1500);
      delay(100);
      f = 1;
    }
  }
}




