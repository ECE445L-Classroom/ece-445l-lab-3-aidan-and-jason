#include <stdint.h>
#include "../../inc/tm4c123gh6pm.h"
#include "../../inc/Timer2A.c"
#include "speaker.h"

extern int speakerStatus;

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

//initialize output for speaker (PF1)
void speakerInit(){
    SYSCTL_RCGCGPIO_R |= 0x20;
    while((SYSCTL_PRGPIO_R&0x20) == 0){};
    GPIO_PORTF_PCTL_R &= ~0x0000000F0;
    GPIO_PORTF_AMSEL_R &= ~0x02;
    GPIO_PORTF_DIR_R |= 0x02;   // OUTPUT
    GPIO_PORTF_AFSEL_R &= ~0x02;      //  regular port function
    GPIO_PORTF_DEN_R |= 0x02;         //  enable digital port		
		Timer2A_Init(&speakerOutput, 4000, 3); // enable interrupt for noise
}

//output sound using squarewave with a delay
void speakerOutput(){
	if(speakerStatus){
		PF1 ^= 0x02;
	}
}

void speakerTest(void){
	Timer2A_Init(&speakerOutput, 2000, 3);
	Clock_Delay1ms(200);
	Timer2A_Stop();
}

void speakerMode(int status){
	// TODO: worried about previous status stuff
  if(status){
    Timer2A_Init(&speakerOutput, 4000, 3);
  }
  else{
    Timer2A_Stop();
  }
}

void speakerOn(){
		Timer2A_Init(&speakerOutput, 4000, 3);
}

void speakerOff(){
		Timer2A_Stop();
}