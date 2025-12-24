#include "main.h"

void high_auton(){
    lift_piston.retract();
    DrivePID drive(0.4,0,0.1,1.1,0,1.1);
    drive.q_go(8);
    delay(500);
    drive.q_go(90,1);
    delay(500);
    Intake.move(127);
    drive.q_go(30);
    delay(750);
    Intake.move(0);
    drive.q_go(48,1);
    delay(300);
    drive.q_go(-33);
    delay(250);
    drive.q_go(133,1);
    delay(250);
    Intake.move(64);
    Cover.move(64);
    drive.q_go(-12);
    Intake.move(127);
    Cover.move(127);

}