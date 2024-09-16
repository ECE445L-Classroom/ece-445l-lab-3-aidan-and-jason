//timer engine
#include "../../inc/Timer0A.h"
#include "../Lab3Main.c"

void timerInit(int priority){
    Timer0A_Init(&incrementTime, 80000000, 0);
}

void incrementTime(){
    rawTime++;
}


//edge triggered switches setup