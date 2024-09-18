#ifndef SWITCH_H_
#define SWITCH_H_

// Switch reading function declarations here
#define PE0                   (*((volatile unsigned long *)0x40024004))
#define PE1                   (*((volatile unsigned long *)0x40024008))
#define PE2                   (*((volatile unsigned long *)0x40024010))
#define PE3                   (*((volatile unsigned long *)0x40024020))

void GPIOPortE_Handler(void);
void switchInit(void);
#endif