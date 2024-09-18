// Declare functions for speaker module here
#ifndef SPEAKER_H_
#define SPEAKER_H_
#include <stdint.h>

#define PF1                   (*((volatile unsigned long *)0x40025008))

void speakerInit(void);
void speakerOutput(void);
void Clock_Delay1ms(volatile uint32_t n);
void speakerMode(int status);

#endif