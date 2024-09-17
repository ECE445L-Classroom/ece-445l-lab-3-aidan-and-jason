// Lab3Main.c
// Runs on LM4F120/TM4C123
// Uses ST7735.c to display the clock
// patterns to the LCD.
//    16-bit color, 128 wide by 160 high LCD
// Mark McDermott, Daniel Valvano and Jonathan Valvano
// Lab solution, do not post
// August 3,2024

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2024

 Copyright 2024 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// Specify your hardware connections, feel free to change
// PD0 is squarewave output to speaker
// PE0 is mode select
// PE1 is edit time
// PE2 is move right
// PE3 is change appearence (later)
// if alarm is sounding, any button will quiet the alarm

#include <stdio.h>
#include <stdint.h>
#include "../inc/ST7735.h"
#include "modules/display.h"
#include "modules/interrupt.h"
#include "modules/speaker.h"
#include "modules/switch.h"
#include "../inc/PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/Timer0A.h"
#include "../inc/Switch.h"
#include "Lab3.h"

#define PD0                   (*((volatile unsigned long *)0x40007004))
#define PE0                   (*((volatile unsigned long *)0x40024004))
#define PE1                   (*((volatile unsigned long *)0x40024008))
#define PE2                   (*((volatile unsigned long *)0x40024010))
#define PE3                   (*((volatile unsigned long *)0x40024020))
// ---------- Prototypes   -------------------------
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode

uint32_t RiseCount, FallCount;
void Rise(void){
  PE0 ^= 0x01;
  RiseCount++;
}
void Fall(void){
  PE0 ^= 0x01;
  FallCount++;
}
// global declarations
int switchIn;
int rawTime;

int main(void){
  int selectSwitch;
  int editTimeSwitch;
  int moveSwitch;
  int appearanceSwitch;
  int mode;     //  0 for normal displaying mode, 1 for editing time, 2 for editing alarm
  int displayMode = 0;  //  possible idea to toggle between digital time and clock face, 0 for digital 1 for clock face
  int hour;
  int minute;
  DisableInterrupts();
  PLL_Init(Bus80MHz);    // bus clock at 80 MHz
  switchInit();
  //Switch_Init(&Rise, &Fall);
  //display init
  ST7735_InitB();
  speakerInit();
  EnableInterrupts();
  while(1){
      // handle switch input unconditionally using global variable (grab lines from switch.c)

      // read switches
      selectSwitch = switchIn & 0x01;
      editTimeSwitch = switchIn & 0x02;
      moveSwitch = switchIn & 0x04;
      appearanceSwitch = switchIn & 0x08;

      // switching mode
      if(selectSwitch){
        mode = (mode+1) % 3;
      }
      

      //store time in temporary local variable

/*    handle switch logic:
      1) if an alarm is sounding, then clear alarm on any switch input
      2) if switch to edit time is pressed, then enter "edit mode" (while loop which is only cleared once a time is confirmed and drawn)
       by possibly drawing an arrow and changing the raw time variable according to the change then drawing the temporary value
         once the select switch is pressed with a time, then confirm change and draw
*/      

      //draw
      hour = rawTime/60;
      minute = rawTime%60;
      
      int time = hour * 100 + minute;   //time in the form 1234 for 12:34
      for(int i = 0; i < 4; i++){
        
      }
      

      
  }
}

