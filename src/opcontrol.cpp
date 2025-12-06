#include "main.h"
#include <random>

void opcontrol() {
	// Define opcontrol variables and pre-opcontrol code here
	uint32_t sleep_time = millis();

	bool tube_lock=false;
	bool lift_lock=false;
	bool lift_state=false;

	//Brake Types
	Intake.set_brake_mode(MOTOR_BRAKE_COAST);
	Cover.set_brake_mode(MOTOR_BRAKE_COAST);

	//Set Default States
	lift_piston.extend();
	colory.set_led_pwm(100);
	tube_piston.retract();

	int color=10;
	
	// Active opcontrol code
	while (true){

		
		// Drive code
		int deadzone=5;
		int leftX = joystick_math(Con1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X),deadzone);
		int leftY = joystick_math(Con1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),deadzone);
		int rightX = joystick_math(Con1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X),deadzone);
		int rightY = joystick_math(Con1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y),deadzone);

		int leftVal = rightY+leftY+leftX;
		int rightVal = rightY+leftY-leftX;

		// currently set split arcade
		FL.move(leftVal);
		ML.move(leftVal);
		BL.move(leftVal);

		FR.move(rightVal);
		MR.move(rightVal);
		BR.move(rightVal);


		// Buttons
		int button_a = Con1.get_digital(E_CONTROLLER_DIGITAL_A); // unassigned 
		int button_b = Con1.get_digital(E_CONTROLLER_DIGITAL_B); // unassigned 
		int button_x = Con1.get_digital(E_CONTROLLER_DIGITAL_X); // unassigned 
		int button_y = Con1.get_digital(E_CONTROLLER_DIGITAL_Y); // unassigned
		
		int button_up = Con1.get_digital(E_CONTROLLER_DIGITAL_UP); // unassigned 
		int button_down = Con1.get_digital(E_CONTROLLER_DIGITAL_DOWN); // unassigned 
		int button_left = Con1.get_digital(E_CONTROLLER_DIGITAL_LEFT); // unassigned 
		int button_right = Con1.get_digital(E_CONTROLLER_DIGITAL_RIGHT); // unassigned		

		int button_l1 = Con1.get_digital(E_CONTROLLER_DIGITAL_L1); // Match Load Collector 
		int button_l2 = Con1.get_digital(E_CONTROLLER_DIGITAL_L2); // High/Low Switcher 
		int button_r1 = Con1.get_digital(E_CONTROLLER_DIGITAL_R1); // Scoring forward 
		int button_r2 = Con1.get_digital(E_CONTROLLER_DIGITAL_R2); // Scoring reverse
		// End Buttons

		//Full Intake
		if (button_r1){
			Intake.move(127);
			Cover.move(127);
		}
		else if (button_r2){
			Intake.move(-127);
			Cover.move(-127);
		}
		else{
			Intake.brake();
			Cover.brake();
		}

		//Tube Collector
		if (button_l1 and !tube_lock){
			tube_piston.toggle();
			tube_lock=true;
		}
		else if (!button_l1){tube_lock=false;}

		//High/Low Switcher
		if (button_l2 and !lift_lock){
			lift_piston.toggle();
			lift_lock=true;
			lift_state=!lift_state;
		}
		else if (!button_l2){lift_lock=false;}

		//Color Sorting
		if (1==1){
			if (within(colory.get_hue(),220-color,10)){
				lift_piston.retract();
			}
			else {lift_piston.extend();}
		}
		pros::screen::print(TEXT_LARGE,2,"%f",colory.get_hue());
		 
		//10 msec loop
		pros::Task::delay_until(&sleep_time, 10);
	}
}