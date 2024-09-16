#include <stdint.h>
#include "../../inc/tm4c123gh6pm.h"
#include "speaker.h"

#define PD0                   (*((volatile unsigned long *)0x40007004))

void Clock_Delay(volatile uint32_t ulCount){
  while(ulCount){
    ulCount--;
  }
}

// ------------Clock_Delay1ms------------
// Simple delay function which delays about n milliseconds.
// Inputs: n, number of msec to wait
// Outputs: none
void Clock_Delay1ms(volatile uint32_t n){
  while(n){
    Clock_Delay(23746);  // 1 msec, tuned at 80 MHz, originally part of LCD module
    n--;
  }
}

//initialize output for speaker (PD0)
void SpeakerInit(){
    SYSCTL_RCGCGPIO_R |= 0x08;
    while((SYSCTL_PRGPIO_R&0x08) == 0){};
    GPIO_PORTC_PCTL_R &= ~0x00000000F;
    GPIO_PORTC_AMSEL_R &= ~0x01;
    GPIO_PORTC_DIR_R |= 0x01;   // OUTPUT
    GPIO_PORTC_AFSEL_R &= ~0x01;      //  regular port function
    GPIO_PORTC_DEN_R |= 0x01;         //  enable digital port
}

//output sound using squarewave with a delay
void SpeakerOutput(){
    for(int i = 0; i < 30; i++){
        PD0 ^= 0x01;
        Clock_Delay1ms(1);
        PD0 ^= 0x01;
    }
}