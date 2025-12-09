#include "main.h"

void high_auton(){
    lift_piston.retract();
    DrivePID drive(0.4,0,0.1,0.43,0,0.8);
    drive.q_go(31);
    delay(750);
    drive.q_go(-90,1);
    delay(500);
    drive.q_go(-25);
    Cover.move(127);
}