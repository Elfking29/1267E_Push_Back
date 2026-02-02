#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/screen.hpp"

void opcontrol() {

	//Test

	imu.reset(true);
	delay(3000);
	imu.tare_rotation();
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
	screen::set_eraser(0x000000);
	int v=18;
	while ((int)imu.get_rotation()!=180){
		if ((int)imu.get_rotation()<180){
			move_drive_motors(v, -v);
		}
		else {
			move_drive_motors(-v, v);
		}
		screen::erase();
		screen::print(E_TEXT_MEDIUM,0,"%i",(int)imu.get_rotation());
		screen::print(E_TEXT_MEDIUM,1,"%i",(int)FL.get_position());
		screen::print(E_TEXT_MEDIUM,2,"%i",(int)ML.get_position());
		screen::print(E_TEXT_MEDIUM,3,"%i",(int)BL.get_position());
		screen::print(E_TEXT_MEDIUM,4,"%i",(int)FR.get_position());
		screen::print(E_TEXT_MEDIUM,5,"%i",(int)MR.get_position());
		screen::print(E_TEXT_MEDIUM,6,"%i",(int)BR.get_position());
		delay(10);
	}
	screen::print(E_TEXT_MEDIUM,7,"Done");
	while (1==1){}
	//low_auton();

	//End Test

	logo();
	// Define opcontrol variables and pre-opcontrol code here
	uint32_t sleep_time = millis();
	int count=0;

	double current_color;
	//Brake Types
	Intake.set_brake_mode(MOTOR_BRAKE_COAST);
	Middle.set_brake_mode(MOTOR_BRAKE_COAST);
	Top.set_brake_mode(MOTOR_BRAKE_BRAKE);

	//Set Default States
	//lift_piston.extend();
	loader.retract();
	triangle.extend();


	int hue[] = {220,5}; //Blue, Red

	
	// Active opcontrol code
	while (true){
	
		// Drive code
		int deadzone=10;
		int leftX = 0.5*joystick_math(Con1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X),deadzone);
		int leftY = joystick_math(Con1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),deadzone);
		int rightX = joystick_math(Con1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X),deadzone);
		int rightY = joystick_math(Con1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y),deadzone);

		int leftVal = rightY+leftY+leftX;
		int rightVal = +rightY+leftY-leftX;

		// currently set split arcade
		FL.move(leftVal);
		ML.move(leftVal);
		BL.move(leftVal);

		FR.move(rightVal);
		MR.move(rightVal);
		BR.move(rightVal);

		//Intake
			if (Con1.get_digital(E_CONTROLLER_DIGITAL_R1)){
				Intake.move(127);
				Middle.move(127);
			}
			else if (Con1.get_digital(E_CONTROLLER_DIGITAL_R2)){
				Intake.move(-127);
				Middle.move(-127);
			}
			else {
				Intake.brake();
				Middle.brake();
			}
			if (Con1.get_digital(E_CONTROLLER_DIGITAL_L1)){
				Top.move(127);
			}
			else if (Con1.get_digital(E_CONTROLLER_DIGITAL_L2)){
				Top.move(-127);
			}
			else {
				Top.brake();
			}


		
			

		//Antler extension toggler
		if (Con1.get_digital_new_press(DIGITAL_A)){
			antler_l.toggle();
			antler_r.toggle();
		}

		//Triangle or Loader
		if (Con1.get_digital_new_press(DIGITAL_DOWN)){
			if (!loader.is_extended()&&triangle.is_extended()){
				triangle.retract();
				loader.extend();
			}
			else if (loader.is_extended()&&!triangle.is_extended()){
				loader.retract();
			}
		}
		
		if (load_button.get_value() && !loader.is_extended()){triangle.extend();}
		else if (loader.is_extended()){triangle.retract();}

		/*
		if (Con1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
			triangle.toggle();
			loader.toggle();
		}
		*/
		
	
		
		//Printing
		if (!count%20){Con1.print(0, 0, "%i",leftX);count=0;}
		else if (!count%15){Con1.print(1, 0, "Bat:%d Con:%d",pros::battery::get_capacity(),Con1.get_battery_capacity());}
		else if (!count%10){}//Con1.print(2, 0, "Line 3");}
		else if (!count%5){}//Could do Rumble here


		//10 msec loop
		pros::Task::delay_until(&sleep_time, 10);
		count++;
	}
}