//timer engine
#include "../../inc/Timer0A.h"
#include <stdint.h>

extern int rawTime;

void incrementTime(){
    rawTime++;
}

void timerInit(int priority){
    Timer0A_Init(&incrementTime, 80000000, priority);
}

