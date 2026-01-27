#include "main.h"
#include "pros/misc.h"
#include <random>

void opcontrol() {
	logo();
	// Define opcontrol variables and pre-opcontrol code here
	uint32_t sleep_time = millis();
	int count=0;

	bool antler_lock=false;
	bool lift_lock=false;
	int sort_lock=0;
	double current_color;

	//Brake Types
	Intake.set_brake_mode(MOTOR_BRAKE_COAST);
	Middle.set_brake_mode(MOTOR_BRAKE_COAST);
	Switcher.set_brake_mode(MOTOR_BRAKE_BRAKE);

	//Set Default States
	//lift_piston.extend();
	loader.retract();
	backer.extend();


	int hue[] = {220,5}; //Blue, Red

	
	// Active opcontrol code
	while (true){
	
		// Drive code
		int deadzone=5;
		int leftX = 0.5*joystick_math(Con1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X),deadzone);
		int leftY = joystick_math(Con1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),deadzone);
		int rightX = joystick_math(Con1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X),deadzone);
		int rightY = joystick_math(Con1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y),deadzone);

		int leftVal = -rightY-leftY+leftX;
		int rightVal = -rightY-leftY-leftX;

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

		//Intake
			if (button_r1){
				Intake.move(127);
				Middle.move(127);
			}
			else if (button_r2){
				Intake.move(-127);
				Middle.move(-127);
			}
			else {
				Intake.brake();
				Middle.brake();
			}

			if (button_l1){
				Switcher.move(127);
			}
			else if (button_l2){
				Switcher.move(-127);
			}
			else {
				Switcher.brake();
			}
		
			

		//Antler extension toggler
		if (button_a and !antler_lock){
			antler_l.toggle();
			antler_r.toggle();
			antler_lock=true;
		}
		else if (!button_a){antler_lock=false;}

		//High/Low Switcher
		if (button_l2 and !lift_lock){
			lift_piston.toggle();
			lift_lock=true;
			if (!lift_piston.is_extended()){sort_lock=1;}
			else if (sort_lock!=2){sort_lock=0;}
		}
		else if (!button_l2){lift_lock=false;}


		//Color Sorting
		//This part manually toggles color sorting
		if (Con1.get_digital_new_press(DIGITAL_DOWN)){
			loader.toggle();
			backer.toggle();
		}
	
		
		//Printing
		if (!count%20){Con1.print(0, 0, "Sort 0-ON: %d",sort_lock);count=0;}
		else if (!count%15){Con1.print(1, 0, "Bat:%d Con:%d",pros::battery::get_capacity(),Con1.get_battery_capacity());}
		else if (!count%10){}//Con1.print(2, 0, "Line 3");}
		else if (!count%5){}//Could do Rumble here


		//10 msec loop
		pros::Task::delay_until(&sleep_time, 10);
		count++;
	}
}