#include <stdint.h>
#include "../../inc/tm4c123gh6pm.h"
#include "switch.h"
// PE0 is mode select
// PE1 is edit time
// PE2 is move right
// PE3 is change appearence (later)

extern int switchIn;

//read switches and return which switches are pressed
void GPIOPortE_Handler(void){
  GPIO_PORTE_ICR_R = 0x0F; // clear interrupt flags 0-3
  switchIn = GPIO_PORTE_DATA_R & 0xF;
  // moved logic to main to make returning easier
  /* int selectSwitch = switchIn & 0x01;
     int editTimeSwitch = switchIn & 0x02;
     int moveSwitch = switchIn & 0x04;
     int appearanceSwitch = switchIn & 0x08;
     */
}


//edge triggered switches setup 
void switchInit(void){       
  SYSCTL_RCGCGPIO_R |= 0x00000010; // (a) activate clock for port E
  while((SYSCTL_PRGPIO_R&0x10) == 0){};

  GPIO_PORTE_DIR_R &= ~0x0F;    // (c) make PE0 to PE3 in (built-in button)
  GPIO_PORTE_DEN_R |= 0x0F;     //     enable digital I/O on PE0123
  GPIO_PORTE_PUR_R |= 0x0F;     //     enable weak pull-up on PE0123
  GPIO_PORTE_IS_R &= ~0x0F;     // (d) PE0123 is edge-sensitive
  GPIO_PORTE_IBE_R &= ~0x0F;    //     PE0123 is not both edges
  GPIO_PORTE_IEV_R &= ~0x0F;    //     PE0123 falling edge event
  GPIO_PORTE_ICR_R = 0x0F;      // (e) clear flags 0-3
  GPIO_PORTE_IM_R |= 0x0F;      // (f) arm interrupt on PE0123
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
  NVIC_EN0_R = 0x00000010;      // (h) enable interrupt 4 in NVIC
}