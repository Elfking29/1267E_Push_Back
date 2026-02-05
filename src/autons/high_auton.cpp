#include "main.h"

void high_auton(){
    Con1.clear();
    PID drive(0.4,0,0.1,1.1,0,0.7);
    drive.go(-12,0);
    delay(250);
    drive.go(90,1);
}