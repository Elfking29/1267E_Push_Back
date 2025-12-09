#include "main.h"
//this is example, I only got one line finished...

void low_auton(){
    chassis.setPose(0, 0, 0);
    // move the robot to x = 0, y = 2, and face heading 0
    chassis.moveToPose(0, 2, 0, 4000);
    // wait until the robot has traveled 2 inches
    chassis.waitUntil(2);
    //ignore below.. vvv

    
    // output "traveled 10 inches" to the console
    std::cout << "traveled 10 inches" << std::endl;
    // turn the robot to face 270 degrees
    // this will wait for the last motion to complete before running
    chassis.turnToHeading(270, 4000);
    // wait until the robot has traveled 45 degrees
    chassis.waitUntil(45);
    // output "traveled 45 degrees" to the console
    std::cout << "traveled 45 degrees" << std::endl;

}