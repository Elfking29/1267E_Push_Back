#include "main.h"

void high_auton(){
    lift_piston.retract();
    DrivePID drive(0.4,0,0.1,1.1,0,0.7);
    drive.q_go(32.5);
    delay(250);
    drive.q_go(-80,1);
    delay(250);
    drive.q_go(-22);
    Switcher.move(127);
}