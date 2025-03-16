#include <Arduino.h>

//Defining the pins from LED's, button, and buzzer to their proper pins on the TTGO
#define RED 25
#define YELLOW 32
#define GREEN 33
#define pushButton 26
#define buzzer 27
int count = 0;

void pressButton();
void buzzOn(int delay1);
void buzzOff(int delay2);
void idleGreen();
void initialLights();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Assigns LED, button, and buzzer pins to output
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP); 
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH); //Turns buzzer on
}

void loop() 
{
  if(count == 0) //Runs initial light sequence for the LEDs at start of program
  {
    delay(1000);
    initialLights();
    
    count = count + 1; //Increment count to not re-run initial lights code
  }

  int read = digitalRead(pushButton); //Catch the button press

  //If the button is not pressed, turn Green LED to idle green state. Else, run pressButton() function
  if (read == HIGH)
  {
    idleGreen();
  }
  else
  {
    Serial.println("Button was Pressed");
    pressButton();
  }
}

void pressButton()
{
  digitalWrite(GREEN, HIGH);

  int j = 0;
  while(j < 5) //Green buzzing cycle of 500ms ON and 1500ms OFF for a total of 10 seconds. (Instructions mentioned for at least 5sec, so we did 10)
  {
  buzzOn(500);
  buzzOff(1500);
  j = j + 1;
  }

  digitalWrite(GREEN, LOW);

  digitalWrite(YELLOW, HIGH); //Yellow buzzing cycle of 500ms ON and 500ms OFF for a total of 2 seconds.
  int a = 0;
  while(a < 2){
  buzzOn(500);
  buzzOff(500);
  a = a + 1;
  }
  digitalWrite(YELLOW, LOW);

  digitalWrite(RED, HIGH); //Red buzzing cycle of 500ms ON and 1500ms OFF for a total of 10 seconds.
  int i = 0;
  while(i < 20){
  buzzOn(250);
  buzzOff(250);
  i = i + 1;
  }

  digitalWrite(RED, LOW);

  digitalWrite(RED, HIGH); //Red-Yellow buzzing cycle of 200ms ON and 200ms OFF for a total of 2 seconds.
  digitalWrite(YELLOW, HIGH);
  int b = 0;
  while(b < 5){
  buzzOn(200);
  buzzOff(200);
  b = b + 1;
  }

  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
}

void buzzOn(int delay1) //Turns on the buzz for delay1 ms.
{
  tone(buzzer, 1000);
  delay(delay1);
}

void buzzOff(int delay2) //Turns off the buzz for delay2 ms.
{
  noTone(buzzer);
  delay(delay2); 
}

void initialLights() //Initial red and red-yellow buzzing cycle in the beginning of the program
{
  digitalWrite(RED, HIGH); //Turns on Red LED at beginning of program
  int i = 0;
  while(i < 5) //Red buzzing cycle of 250ms ON and 250 OFF for a total of 2.5 seconds.
  {
      buzzOn(250);
      buzzOff(250);
      i = i + 1;
  }

  digitalWrite(RED, LOW);

  digitalWrite(RED, HIGH); //Turns on Red LED 
  digitalWrite(YELLOW, HIGH); //Turns on Yellow LED 
  int b = 0;
  while(b < 3) //Red-Yellow buzzing cycle of 200ms ON and 200ms OFF for a total of 1.2 seconds.
  {
    buzzOn(200);
    buzzOff(200);
    b = b + 1;
  }

  digitalWrite(RED, LOW); //Turns off Red LED
  digitalWrite(YELLOW, LOW); //Turns off Yellow LED
}

void idleGreen() //Runs Green buzzing cycle for when Green LED is in idle state (aka no button press)
{
    digitalWrite(GREEN, HIGH);
    buzzOn(500);
    buzzOff(1500);
}