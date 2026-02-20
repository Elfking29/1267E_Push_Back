#include "main.h"
#include "pros/motors.h"

void high_auton(){
        PID drive(0.4,0,0.1,1.1,0,0.7);
        //Go to match loader
        Top.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        drive.go(-30, 0);
        drive.go(-90,1,1500);
        //Load
        loader.extend();
        delay(400);
        Intake.move(127);
        Middle.move(96);
        Top.brake();
        drive.go(-8,0,1000);
        delay(500);
        drive.go(-1,0,250);
        delay(250);
        //Go to goal
        Intake.move(-64);
        Middle.move(-64);
        drive.go(6,0);
        Intake.move(32);
        Middle.move(0);
        loader.retract();
        delay(250);
        triangle.extend();
        drive.go(25,0,1200);
        Intake.move(127);
        Middle.move(-127);
        Top.move(127);
        delay(250);
        Middle.move(127);
        delay(1600);
        Top.set_brake_mode(E_MOTOR_BRAKE_COAST);
        //Go to 3 blocks
        drive.go(-8,0);
}