#include <Arduino.h>
#include "pins.h"

const int CLOCK = D0;
const int SHIFT = D1;
const int CLEAR = D2;
const int DELAY_TIME = 0;
const int UPDATE_DELAY = 100;

int value = 0;

void clear()
{
  digitalWrite(CLEAR, LOW);
  digitalWrite(CLEAR, HIGH);
}

void shiftBit(bool value)
{
  digitalWrite(SHIFT, value);
  digitalWrite(CLOCK, HIGH);
  delay(DELAY_TIME);
  digitalWrite(CLOCK, LOW);
}

void showBarValue(unsigned char value)
{
  clear();
  for (char i = 8; i > 0; --i)
  {
    shiftBit(value >= i);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(CLOCK, OUTPUT);
  pinMode(SHIFT, OUTPUT);
  pinMode(CLEAR, OUTPUT);

  digitalWrite(CLEAR, HIGH);

  clear();
}

void loop()
{
  while (!Serial.available())
    ;
  auto read = Serial.readString();
  int value = read.toInt();

  showBarValue(value);
  Serial.println(value);
  // Serial.printf("Value was %d\r\n", value);
}