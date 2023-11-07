#include <Arduino.h>
#include "saa.h"

//data writing through 74HC595

//AO is high to indicate address buffer input
void mode_latch(){
    digitalWrite(pinAO, HIGH);
    digitalWrite(pinWR, LOW);
    delayMicroseconds(5);
    digitalWrite(pinWR, HIGH);
}

//AO is high to indicate control register input
void mode_write(){
    digitalWrite(pinAO, LOW);
    digitalWrite(pinWR, LOW);
    delayMicroseconds(5);
    digitalWrite(pinWR, HIGH);
}

void mode_inactive(){
    digitalWrite(pinWR, HIGH);
}

void write_data(unsigned char address, unsigned char data){
    mode_inactive();

    //write address
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, address);
    //take the latch pin high
    digitalWrite(latchPin, HIGH);

    mode_latch(); //now inputting to address buffer
    mode_inactive(); //now off

    //write data to control register
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, data);

    //take the latch pin high
    digitalWrite(latchPin, HIGH);

    mode_write();
    mode_inactive();
}