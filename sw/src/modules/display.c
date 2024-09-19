#include "../../inc/ST7735.h"
#include "images.h"

extern int rawTime;
extern int alarm;
//write to lcd
void draw(int mode){
	// HELPFUL: ST7735_Color565(r,g,b) takes in 8 bit rgb values and returns the appropriate color in the ST7735 format
	//ST7735_FillScreen(0x0000); // black bg, can change later
	//ST7735_DrawCircle(50,50,0xFFFF); // this will be 10px in diameter and probably filled in, 
	// TODO: we're going to need to rewrite this method
	// draw the current time digitally:
	//if(mode == 1){return;}
	int x = 1;
	ST7735_SetCursor(x,0);
	uint32_t hour = rawTime/60;
	uint32_t minute = rawTime%60;
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_OutUDec(hour);
	if(hour/10){ // trying to make the printing look niceish by accounting for the number stuff
		x+=2;
	} else {
		x+=1;
	}
	ST7735_SetCursor(x,0);
	ST7735_OutChar(':');
	x++;
	if(minute < 10){
		ST7735_SetCursor(x,0);
		ST7735_OutUDec(0);
		x++;
	}
	ST7735_SetCursor(x,0);
	ST7735_OutUDec(minute);
	
	// draw alarm
	uint32_t alarmhour = alarm/60;
	uint32_t alarmminute = alarm%60;
	
	x = 15;
	ST7735_SetTextColor(ST7735_ORANGE);
	ST7735_SetCursor(x,0);
	ST7735_OutUDec(alarmhour);
	if(alarmhour/10){ // trying to make the printing look niceish by accounting for the number stuff
		x+=1;
	}
	x++;
	ST7735_SetCursor(x,0);
	ST7735_OutChar(':');
	x++;
	ST7735_SetCursor(x,0);
	if(alarmminute < 10){
		ST7735_SetCursor(x,0);
		ST7735_OutUDec(0);
		x++;
	}
	ST7735_SetCursor(x,0);
	ST7735_OutUDec(alarmminute);
	
	// draw clock bg and hands
	ST7735_DrawBitmap(24,120,clock,80,80);
	//ST7735_Line(x1, y1, x2, y2, color);
	//ST7735_Line(x1, y1, x2, y2, color);

	
	
	// draw any other fun effects
	// TODO: super mario thingy
	
}
//watch faces