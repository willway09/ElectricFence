#include "data.h"

void setup()
{
  Serial.begin(9600);
  //DDRB = B0000011;
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  unsigned long start = micros();
  int index = 0;
  
  while(micros() - start <= 1000000) { //One second
  
    if(index >= changes) break;
    if(micros() - start >= times[index]) {
      PORTB = state[index];
      index++;
    }
  }
}
