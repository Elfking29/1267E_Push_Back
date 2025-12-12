#include "main.h"
//this is example, I only got one line finished...

void low_auton(){
    DrivePID drive(0.4,0,0.1,1.1,0,1);
    drive.q_go(5);

}