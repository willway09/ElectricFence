#include "data.h"

void setup() {
  #if defined(__AVR_ATmega328P__) //If Arduino Uno, Nano, etc. (ATmega328p-based)
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
  #elif defined(ESP8266) //If ESP8266
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
  #else
    #error "Unsupported Board Type"
  #endif
}

void loop() {
  unsigned long start = micros();
  int index = 0;
  
  while(micros() - start <= 1000000) { //One second
  
    if(index >= changes) break;
    if(micros() - start >= times[index]) {
      #if defined(__AVR_ATmega328P__) //If Arduino Uno, Nano, etc. (ATmega328p-based)
        PORTB = state[index];
      #elif defined(ESP8266) //If ESP8266
        //Bit shift 12, because first output pin is 12
        GPIO_REG_WRITE(GPIO_OUT_ADDRESS, state[index] << 12);
      #else
        #error "Unsupported Board Type"
      #endif
      index++;
    }
  }
}
