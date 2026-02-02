#include "main.h"
#include "pros/rtos.h"
#include <cmath>
#include <stdexcept>
#include <utility>

PID::PID(double kp_fb,double ki_fb,double kd_fb, double kp_tu,double ki_tu,double kd_tu, double dt){
    this->kp_fb = kp_fb;
    this->ki_fb = ki_fb;
    this->kd_fb = kd_fb;

    this->kp_tu = kp_tu;
    this->ki_tu = ki_tu;
    this->kd_tu = kd_tu;

    this->finish=false;
    this->dt=dt;
    this->ratio=600/360.0;
    this->minimum=20;
    this->fb_max=90;
    this->tu_max=60;
    this->settle=3;
    this->e_break=10;
    this->a_break=2;
}

void PID::tare_prepare(){
    delay(50);
    //Set correct encoder units (degrees)
	FL.set_encoder_units(MOTOR_ENCODER_DEGREES);
    ML.set_encoder_units(MOTOR_ENCODER_DEGREES);
	BL.set_encoder_units(MOTOR_ENCODER_DEGREES);
	FR.set_encoder_units(MOTOR_ENCODER_DEGREES);
    MR.set_encoder_units(MOTOR_ENCODER_DEGREES);
	BR.set_encoder_units(MOTOR_ENCODER_DEGREES);

	//Set motor position to 0
	FL.tare_position();
    ML.tare_position();
	BL.tare_position();
	FR.tare_position();
    MR.tare_position();
	BR.tare_position();

    //Set IMU to 0
    imu.tare_rotation();
}

void PID::set_finished(){
        FL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        BL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        FR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        BR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        ML.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        MR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    
        FL.brake();
        BL.brake();
        FR.brake();
        BR.brake();
        ML.brake();
        MR.brake();
}

void PID::go(double distangle, bool turn, int timeout){
    double target,arget,l_error,r_error,a_error;
    int hiloi = 1-2*hilo;
    int loops=0;
    //Do Math and Prepare
    if (!turn){
        //Forwards/Backwards
        target = (360*distangle*60)/(3.25*3.1416*36);
        arget = 0;
    }
    else {
        //Turning
        target = distangle*this->ratio*hiloi;
        arget = (distangle+imu.get_rotation())*hiloi;
    }
    double loe,roe,aoe,li,ri,l_motor,r_motor,a_motor=0;

    this->tare_prepare();
    double time,start=millis();

    //Actual Loop
    while (!this->finish){
        if (!turn){
            //Forwards and Backwards
            double l_encode = (FL.get_position()+ML.get_position()+BL.get_position())/3.0;
            double r_encode = (FR.get_position()+MR.get_position()+BR.get_position())/3.0;
            //This averages all three motors, which is more accurate
            //Error for both sides
            double l_error = target-l_encode;
            double r_error = target-r_encode;
            //Proportional for both sides
            double lp = this->kp_fb*l_error;
            double rp = this->kp_fb*r_error;
            //Integral for both sides
            float arb_num = 100;
            double li = l_error>std::abs(arb_num)?0:l_error==0?0:this->ki_fb*(li+this->dt*l_error);
            double ri = r_error>std::abs(arb_num)?0:r_error==0?0:this->ki_fb*(ri+this->dt*r_error);
            //Derivative for both sides
            double ld = this->kd_fb*(l_error-loe)/dt;
            double rd = this->kd_fb*(r_error-roe)/dt;
            //Set previous error to error
            double loe = l_error;
            double roe = r_error;
            //Value before max and min
            double l_motor = lp+li+ld;
            double r_motor = rp+ri+rd;
            //Bound the values
            if (std::fabs(l_motor)>this->fb_max){l_motor=this->fb_max*hiloi;}
            else if (std::fabs(l_motor)<this->minimum){l_motor=this->minimum*hiloi;}

            if (std::fabs(r_motor)>this->fb_max){r_motor=this->fb_max*hiloi;}
            else if (std::fabs(r_motor)<this->minimum){r_motor=this->minimum*hiloi;}
        }
        else {
            //Turning

            //Angle Math
            double a_error=10*(target-imu.get_rotation()); 
            double ap = this->kp_tu*a_error;
            float arb_num = 100;
            double ai = a_error>std::abs(arb_num)?0:a_error==0?0:this->ki_tu*(li+this->dt*a_error);
            double ad = this->kd_tu*(a_error-aoe)/this->dt;
            aoe = a_error;
            a_motor = ap+ai+ad;
            if (std::fabs(a_motor)>this->tu_max){a_motor=this->tu_max*hiloi;}
            else if (std::fabs(a_motor)<this->minimum){a_motor=this->minimum*hiloi;}

            //Encoder Math
            double l_encode = (FL.get_position()+ML.get_position()+BL.get_position())/3.0;
            double r_encode = -(FR.get_position()+MR.get_position()+BR.get_position())/3.0;
            double l_error = target-l_encode;
            double r_error = target-r_encode;
            double lp = this->kp_fb*l_error;
            double rp = this->kp_fb*r_error;
            double li = l_error>std::abs(arb_num)?0:l_error==0?0:this->ki_fb*(li+this->dt*l_error);
            double ri = r_error>std::abs(arb_num)?0:r_error==0?0:this->ki_fb*(ri+this->dt*r_error);
            double ld = this->kd_fb*(l_error-loe)/dt;
            double rd = this->kd_fb*(r_error-roe)/dt;
            double loe = l_error;
            double roe = r_error;
            double e_motor = (lp+li+ld+rp+ri+rd)/2.0;
            if (std::fabs(e_motor)>this->tu_max){e_motor=this->tu_max*hiloi;}
            else if (std::fabs(e_motor)<this->minimum){e_motor=this->minimum*hiloi;}

            //Combine the 2
            double l_motor=(a_motor+e_motor)/2;
            double r_motor=-l_motor;

        }

        move_drive_motors(l_motor, r_motor);

        //Breakpoints
        if (std::fabs(l_error)<=this->e_break && std::fabs(r_error)<=this->e_break){
            if (!turn || std::fabs(a_error)<=this->a_break){
                if (loops<this->settle){loops++;}
                else{this->finish=1;}
            }
            else{loops=0;}
        }
        else{loops=0;}
        if (millis()>=start+timeout && timeout!=-1){this->finish=1;}
    }
    this->set_finished();

}