


// First we'll set up constants for the pin numbers.
// This will make it easier to follow the code below.
#include <NewPing.h>

#define TRIGGER_PIN       12
#define ECHO_PIN          11
#define MAX_DISTANCE      200

#define CLK               5
#define DT                6

int count = 0;
int clkState;
int clkLastState;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

const int button1Pin = 2;  // pushbutton 1 pin
const int button2Pin = 3;

void setup()
{
  // Set up the pushbutton pins to be an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);  
  
  Serial.begin(115200);
  clkLastState = digitalRead(CLK);
     
}


void loop()
{
  readButtons();
  readUltrasonic();
  
  clkLastState = readRotary();

  Serial.write(255);
  delay(5);
}

void readButtons()
{
  int button1State, button2State;
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  
  if(button1State == 1) {
    Serial.write(0);
  } else {
    Serial.write(1);
  }

  if(button2State == 1) {
    Serial.write(0);
  } else {
    Serial.write(1);
  }
}

void readUltrasonic()
{
  unsigned int uS = sonar.ping();
  int b1 = uS >> 7;
  int b2 = uS & 127;
  Serial.write(b1);
  Serial.write(b2);
}

int readRotary()
{
  clkState = digitalRead(CLK);
  
  
  if (clkState != clkLastState)
  {
    if (digitalRead(DT) != clkState)
    {
      count++;
    } else {
      count--;
    }
    // count can be negative using two's complement
    int sign = count & 64;
    if (sign == 1){
      Serial.write(count * -1);
    } else {
      Serial.write(count);
    }
  }
  return clkState;
}
