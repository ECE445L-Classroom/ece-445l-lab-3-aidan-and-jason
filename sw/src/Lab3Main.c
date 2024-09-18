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
// PF1 is squarewave output to speaker
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
#include "../inc/Timer2A.h"
#include "../inc/Switch.h"
#include "Lab3.h"

// ---------- Prototypes   -------------------------
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode

void Rise(void); // no clue what these do Jason
void Fall(void);
uint32_t RiseCount, FallCount;

// global declarations
volatile int switchIn;
volatile int rawTime;

int main(void){
  int button1;
  int button2;
  int button3;
  int button4;
  int mode = 0;     //  0 for normal displaying mode, 1 for editing time, 2 for editing alarm
  int displayMode = 0;  //  possible idea to toggle between digital time and clock face, 0 for digital 1 for clock face
  int hour;
  int minute;
	int alarm;		// the time for the alarm, stored in the same manner as the global time (except no seconds) '
	int alarmFlag = 0;
  int speakerStatus = 0;
	int debug = 0;
  DisableInterrupts();
  PLL_Init(Bus80MHz);    // bus clock at 80 MHz
  ST7735_InitR(INITR_REDTAB);
  ST7735_InvertDisplay(1);
	ST7735_FillScreen(0x0000);
  //Switch_Init(&Rise, &Fall);
  speakerInit(); // valvano case...
	switchInit();
  timerInit(2);
  EnableInterrupts();
  while(1){
      // handle switch input unconditionally using global variable (grab lines from switch.c)
      // read switches
			debug = switchIn;
      button1 = switchIn & 0x01;
      button2 = switchIn & 0x02;
      button3 = switchIn & 0x04;
      button4 = switchIn & 0x08;
			

      if(button1 || button2 || button3 || button4){
        speakerStatus = 1;
        speakerMode(1);
      }
      else if(speakerStatus == 1 && switchIn == 0){
        speakerMode(0);
        speakerStatus = 0;
      }
      // switching mode
      if(button4){
        mode = (mode+1) % 3;
      }
      

      //store time in temporary local variable

/*    handle switch logic:
      1) if an alarm is sounding, then clear alarm on any switch input
      2) if switch to edit time is pressed, then enter "edit mode" (while loop which is only cleared once a time is confirmed and drawn)
       by possibly drawing an arrow and changing the raw time variable according to the change then drawing the temporary value
         once the select switch is pressed with a time, then confirm change and draw
*/      
			hour = rawTime/60;
      minute = rawTime%60;
			
			
			// alarm logic
			if(hour == alarm/60 && minute == rawTime%60){ // this is wrong, I just don't know how to get rid of the seconds yet
				// enable the interrupt for the square wave (might be unneeded read/write)
				alarmFlag = 1;
			}
			
			if((button1 || button2 || button3 || button4) && alarmFlag){
				alarmFlag = 0; // disable the interrupt
				// TODO: add snooze?
			}

      //draw the clock face, hands, display digital time, and alarm setup.
			draw(hour, minute);
      
      int time = hour * 100 + minute;   //time in the form 1234 for 12:34
      for(int i = 0; i < 4; i++){
        
      }    
  }
}

void Rise(void){
  PE0 ^= 0x01;
  RiseCount++;
}
void Fall(void){
  PE0 ^= 0x01;
  FallCount++;
}