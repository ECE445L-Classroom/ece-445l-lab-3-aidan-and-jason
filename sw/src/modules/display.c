#include "../../inc/ST7735.h"


//write to lcd
void draw(uint32_t hour, uint32_t minute){
	// HELPFUL: ST7735_Color565(r,g,b) takes in 8 bit rgb values and returns the appropriate color in the ST7735 format
	ST7735_FillScreen(0x0000); // black bg, can change later
	ST7735_DrawCircle(50,50,0xFFFF); // this will be 10px in diameter and probably filled in, 
	// TODO: we're going to need to rewrite this method
	// draw the current time digitally:
	int x = 0;
	ST7735_SetCursor(0,0);
//	char *time = ['' '\0']; Aidan try finishing this later if you have time 
//	ST7735_OutString(time)
	ST7735_OutUDec(hour);
	if(hour/10){ // trying to make the printing look niceish by accounting for the number stuff
		x+=2;
	} else {
		x+=1;
	}
	ST7735_SetCursor(x,0);
	ST7735_OutChar(':');
	x++;
	ST7735_SetCursor(x,0);
	ST7735_OutUDec(minute);
	
	// draw alarm
	
	// draw clock hands
	
	// draw any other fun effects
	
}
//watch faces