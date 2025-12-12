#include "main.h"

void high_auton(){
    lift_piston.retract();
    DrivePID drive(0.4,0,0.1,1.1,0,1);
    drive.q_go(10);
    delay(500);
    drive.q_go(90,1);
    delay(500);
    Intake.move(127);
    drive.q_go(30);
    delay(750);
    Intake.move(0);
    drive.q_go(45,1);
    delay(300);
    drive.q_go(-30);
    delay(250);
    drive.q_go(130,1);
    delay(250);
    drive.q_go(-13);
    Intake.move(127);
    Cover.move(127);

}