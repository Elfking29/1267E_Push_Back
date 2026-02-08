#include "main.h"
#include "pros/rtos.h"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <utility>

PID::PID(double kp_fb,double ki_fb,double kd_fb, double kp_tu,double ki_tu,double kd_tu, double dt){
    this->kp_fb = kp_fb;
    this->ki_fb = ki_fb;
    this->kd_fb = kd_fb;

    this->kp_tu = kp_tu;
    this->ki_tu = ki_tu;
    this->kd_tu = kd_tu;

    this->dt=dt;
    this->ratio=1035/180.0;
    this->minimum=22;
    this->fb_max=67;
    this->tu_max=60;
    this->settle=3;
    this->e_break=12;
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

        delay(150);
}

void PID::go(double distangle, bool turn, int timeout){
    double target,arget,l_error,r_error,a_error;
    int loops=0;
    //Do Math and Prepare
    if (!turn){
        //Forwards/Backwards
        target = (360*distangle*60)/(3.25*3.1416*36);
        arget = 0;
    }
    else {
        //Turning
        target = distangle*this->ratio;
        arget = (distangle+imu.get_rotation());
    }
    double loe,roe,aoe,lp,rp,ap,li,ri,ai,ld,rd,ad,l_motor,r_motor,a_motor,e_motor,l_encode,r_encode=0;
    bool finish=false;
    this->tare_prepare();
    uint32_t time,start=millis();

    //Actual Loop
    while (!finish){
        if (!turn){
            //Forwards and Backwards
            l_encode = (FL.get_position()+ML.get_position()+BL.get_position())/3.0;
            r_encode = (FR.get_position()+MR.get_position()+BR.get_position())/3.0;
            //This averages all three motors, which is more accurate
            //Error for both sides
            l_error = target-l_encode;
            r_error = target-r_encode;
            //Proportional for both sides
            lp = this->kp_fb*l_error;
            rp = this->kp_fb*r_error;
            //Integral for both sides
            float arb_num = 100;
            li = l_error>std::abs(arb_num)?0:l_error==0?0:this->ki_fb*(li+this->dt*l_error);
            ri = r_error>std::abs(arb_num)?0:r_error==0?0:this->ki_fb*(ri+this->dt*r_error);
            //Derivative for both sides
            ld = this->kd_fb*(l_error-loe)/dt;
            rd = this->kd_fb*(r_error-roe)/dt;
            //Set previous error to error
            loe = l_error;
            roe = r_error;
            //Value before max and min
            l_motor = lp+li+ld;
            r_motor = rp+ri+rd;
            //Bound the values
            if (std::fabs(l_motor)>this->fb_max){l_motor=this->fb_max*get_sign(l_motor);}
            else if (std::fabs(l_motor)<this->minimum){l_motor=this->minimum*get_sign(l_motor);}

            if (std::fabs(r_motor)>this->fb_max){r_motor=this->fb_max*get_sign(r_motor);}
            else if (std::fabs(r_motor)<this->minimum){r_motor=this->minimum*get_sign(r_motor);}
        }
        else {
            //Turning

            //Angle Math
            //This isn't accurate right now for some reason
            a_error=10*(arget-imu.get_rotation()); 
            ap = this->kp_tu*a_error;
            float arb_num = 100;
            ai = a_error>std::abs(arb_num)?0:a_error==0?0:this->ki_tu*(li+this->dt*a_error);
            ad = this->kd_tu*(a_error-aoe)/this->dt;
            aoe = a_error;
            a_motor = ap+ai+ad;
            if (std::fabs(a_motor)>this->tu_max){a_motor=this->tu_max*get_sign(a_motor);}
            else if (std::fabs(a_motor)<this->minimum){a_motor=this->minimum*get_sign(a_motor);}

            //Encoder Math


            l_encode = (FL.get_position()+ML.get_position()+BL.get_position())/3.0;
            r_encode = -(FR.get_position()+MR.get_position()+BR.get_position())/3.0;
            l_error = target-l_encode;
            r_error = target-r_encode;
            lp = this->kp_fb*l_error;
            rp = this->kp_fb*r_error;
            li = l_error>std::abs(arb_num)?0:l_error==0?0:this->ki_fb*(li+this->dt*l_error);
            ri = r_error>std::abs(arb_num)?0:r_error==0?0:this->ki_fb*(ri+this->dt*r_error);
            ld = this->kd_fb*(l_error-loe)/dt;
            rd = this->kd_fb*(r_error-roe)/dt;
            loe = l_error;
            roe = r_error;
            e_motor = (lp+li+ld+rp+ri+rd)/2.0;
            if (std::fabs(e_motor)>this->tu_max){e_motor=this->tu_max*get_sign(e_motor);}
            else if (std::fabs(e_motor)<this->minimum){e_motor=this->minimum*get_sign(e_motor);}

            //Combine the 2
            l_motor=(e_motor+e_motor)/2;
            r_motor=-l_motor;

        }

        move_drive_motors(l_motor, r_motor);

        //Breakpoints
        if (std::fabs((l_error+r_error)/2)<=this->e_break){
            if (!turn || std::fabs(a_error)<=this->a_break || true){
                if (loops<this->settle){loops++;}
                else{finish=1;}
            }
            else{loops=0;}
        }
        else{loops=0;}
        if (millis()>=start+timeout && timeout!=-1){finish=1;}
        Task::delay_until(&time,this->dt);
    }
    this->set_finished();

}