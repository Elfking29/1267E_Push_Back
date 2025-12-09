#include "main.h"

int joystick_math(int joystick_value, int deadzone){
    //https://www.vexforum.com/t/optimizing-exponential-drive/73719
    if (std::abs(joystick_value) < deadzone ){
        return 0;
    }
    else {
        return get_sign(joystick_value)*(1.2*pow(1.0356,std::abs(joystick_value))
        -1.2+0.2*std::abs(joystick_value));
    }
}

int get_sign(double value){
    if (value == 0){
        return 1;
    }
    else {
        return value/fabs(value);
    }
}

bool within(double number, double target, double range){
    if (number<target+range and number>target-range){return true;}
    return false;
}

void move_drive_motors(float Left_value, float Right_value){
    //Move all motors with given value [-127,127]
	FL.move(Left_value);
    ML.move(Left_value);
	BL.move(Left_value);
		
	FR.move(Right_value);
    MR.move(Right_value);
	BR.move(Right_value);
}