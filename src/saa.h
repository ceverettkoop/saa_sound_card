#ifndef SAA_H
#define SAA_H

//Pin connected to clock pin (SH_CP) of 74HC595
static const int clockPin = 8;
//Pin connected to latch pin (ST_CP) of 74HC595
static const int latchPin = 9;
////Pin connected to Data in (DS) of 74HC595
static const int dataPin = 10;
//pin connected to WR pin of SAA1099 - active low indicates writing data
static const int pinWR = 2 ; //2 for pcb 11 for proto
//AO pin of SAA1099 -indicates address or control register target
static const int pinAO = 3; //3 for pcb 12 for proto

void mode_latch();
void mode_write();
void mode_inactive();
void write_data(unsigned char address, unsigned char data);

#endif /* IO_H */
