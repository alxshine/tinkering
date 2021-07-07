#include <Arduino.h>
#include "pins.h"

const int CLOCK = D7;
const int CPU_SHIFT = D1;
const int MEM_SHIFT = D2;
const int CLEAR = D6;
const int DELAY_TIME = 0;
const int UPDATE_DELAY = 100;

void clear()
{
  digitalWrite(CLEAR, LOW);
  digitalWrite(CLEAR, HIGH);
}

void shiftBits(bool cpu_value, bool mem_value)
{
  digitalWrite(CPU_SHIFT, cpu_value);
  digitalWrite(MEM_SHIFT, mem_value);
  digitalWrite(CLOCK, HIGH);
  delay(DELAY_TIME);
  digitalWrite(CLOCK, LOW);
}

void showBarValues(unsigned char cpu_value, unsigned char mem_value)
{
  clear();
  for (char i = 8; i > 0; --i)
  {
    shiftBits(cpu_value >= i, mem_value >= i);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(CLOCK, OUTPUT);

  pinMode(CLEAR, OUTPUT);

  pinMode(CPU_SHIFT, OUTPUT);
  pinMode(MEM_SHIFT, OUTPUT);

  digitalWrite(CLEAR, HIGH);

  clear();
}

void loop()
{
  while (!Serial.available())
    delay(100);
  auto read = Serial.readString();
  int cpu, mem;
  sscanf(read.c_str(), "%d,%d", &cpu, &mem);

  showBarValues(cpu, mem);
  Serial.print(cpu);
  Serial.print(",");
  Serial.println(mem);
}