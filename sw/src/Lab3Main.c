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
int speakerStatus;
int alarm = 677; // the time for the alarm, stored in the same manner as the global time (except no seconds)

int main(void){
  int button1;
  int button2;
  int button3;
  int button4;
	int lb1;
	int lb2;
	int lb3;
	int lb4;
  int mode = 0;     //  0 for normal displaying mode, 1 for editing time, 2 for editing alarm
  int displayMode = 0;  //  possible idea to toggle between digital time and clock face, 0 for digital 1 for clock face
  int digitPlace = 0;
	int hour;
  int minute;
	int debug = 0;
	int editTime = 0;
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
			
		// TODO: still poorly made buttons
      //if(button1 || button2 || button3 || button4){
        //speakerStatus = (speakerStatus+1)%2;
      //}

      // switching mode
      if(button4 && !(lb4)){
        mode = (mode+1) % 3;
      }
			
			// TODO: button logic (mode, switches, ect)
			/*    handle switch logic:
      1) if an alarm is sounding, then clear alarm on any switch input
      2) if switch to edit time is pressed, then enter "edit mode" (while loop which is only cleared once a time is confirmed and drawn)
       by possibly drawing an arrow and changing the raw time variable according to the change then drawing the temporary value
         once the select switch is pressed with a time, then confirm change and draw
*/    
      
			switch(mode) {
				case 0: // default
					// button 1: snooze (logic not done here)
					// button 2: 
					// button 3: change face of switch
					// button 4: switch mode at any time
					break;
				case 1: // edit time
					// button 1: confirm
					// button 2: select digit/place (can use underscore to show what is selected)
					// button 3: increment selected digit
					if(button3 && !(lb3)){rawTime++;}
					// button 4: switch mode at any time (also works as a confirm)
					break;
				case 2: // edit alarm
					// button 1: confirm
					// button 2: select digit/place (can use underscore to show what is selected)
					// button 3: increment selected digit
					if(button3 && !(lb3)){alarm++;}
					// button 4: switch mode at any time
					break;
				default:
					break;
			};
			

      //store time in temporary local variable
  
			hour = rawTime/60;
      minute = rawTime%60;
			
			
			// alarm logic
			 //if(rawTime == alarm){ // this is wrong, I just don't know how to get rid of the seconds yet
			 	// enable the interrupt for the square wave (might be unneeded read/write)
			 	//speakerStatus = 1;
			//}
			
			if((button1 || button2 || button3 || button4) && speakerStatus){
				speakerStatus = 0; // disable the interrupt
				// TODO: add snooze?
			}

      //draw the clock face, hands, display digital time, and alarm setup.
			draw(mode);
      
      int time = hour * 100 + minute;   //time in the form 1234 for 12:34
			
			lb1 = button1;
			lb2 = button2;
			lb3 = button3;
			lb4 = button4;
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