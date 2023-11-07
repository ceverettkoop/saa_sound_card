//SAA1099P midi controller
//

#include <Arduino.h>
#include "saa.h"
#include "input.h"
#include "note.h"

static unsigned long lastUpdate = 0;

void setup(){

    Serial.begin(57600);

    //magic to get 8mhz clock on pin A5
    //credit to: https://forum.arduino.cc/t/how-to-get-8mhz-on-a-gpio-of-a-nano-every/704106/4
    // LUT0 is the D input, which is connected to the flipflop output
        CCL.LUT0CTRLB = CCL_INSEL0_FEEDBACK_gc; // Input from sequencer
        CCL.TRUTH0 = 1; // Invert the input
        CCL.SEQCTRL0 = CCL_SEQSEL0_DFF_gc; // D flipflop
        // The following line configures using the system clock, OUTEN, and ENABLE
        CCL.LUT0CTRLA = CCL_OUTEN_bm | CCL_ENABLE_bm;
        // LUT1 is the D flipflop G input, which is always high
        CCL.TRUTH1 = 0xff; 
        CCL.LUT1CTRLA = CCL_ENABLE_bm; // Turn on LUT1
        CCL.CTRLA = 1; // Enable the CC
    //end magic

    //init pins
     pinMode(clockPin, OUTPUT);
     pinMode(latchPin, OUTPUT);
     pinMode(dataPin, OUTPUT);
     pinMode(pinWR, OUTPUT);
     pinMode(pinAO, OUTPUT);

 	//Reset/Enable all the sound channels ; I think this is what the original code said???
 	write_data(0x1C, 0x02);
    write_data(0x1C, 0x00);
    write_data(0x1C, 0x01);

 	//Disable the noise channels
    write_data(0x15, 0x00);

    //Disable envelopes on Channels 2 and 5
    write_data(0x18, 0x00);
    write_data(0x19, 0x00);

    //startup noise
    start_note(3, 24, 64);
    delay(32);
    start_note(0, 48, 64);
    delay(32);
    start_note(1, 52, 64);
    delay(32);
    start_note(2, 55, 64);
    delay(32);
    start_note(3, 60, 64);
    delay(32);
    start_note(4, 64, 64);
    delay(1028);

    stop_note(0);
    stop_note(1);
    stop_note(2);
    stop_note(3);
    stop_note(4);
    stop_note(5);
}

void loop(){

 unsigned long now = millis();

 if(Serial.available() > 0){
    parse_serial_in(Serial.read());
 }

//10ms ADSR check
 if ( (now - lastUpdate) > 10 ) {
     lastUpdate += 10;

     for (int i = 0; i < 6; i++){
         proc_attack(i);
         proc_decay(i);
         proc_release(i);
        }
    }
}