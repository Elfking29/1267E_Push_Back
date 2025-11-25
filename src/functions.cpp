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
    else{return false;}
}