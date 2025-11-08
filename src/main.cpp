#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/misc.h"

void initialize() {}

int auto_select = 0;

void disabled() {}

void competition_initialize() {}

void autonomous() {

	// Runs auto code based on prior selection
	if (auto_select == 0) {
		// No auto

	} else if (auto_select == 1) {
		// High (right side) auto
		
	} else if (auto_select == 2) {
		// Low (left side) auto

	} else if (auto_select == 3) {
		// Skills auto

	}
}

void opcontrol() {
	// Define opcontrol variables and pre-opcontrol code here



	// Active opcontrol code
	while (true){

		// Drive code


		// Buttons
		int button_a = Con1.get_digital(E_CONTROLLER_DIGITAL_A); // unassigned 
		int button_b = Con1.get_digital(E_CONTROLLER_DIGITAL_B); // unassigned 
		int button_x = Con1.get_digital(E_CONTROLLER_DIGITAL_X); // unassigned 
		int button_y = Con1.get_digital(E_CONTROLLER_DIGITAL_Y); // unassigned
		
		int button_up = Con1.get_digital(E_CONTROLLER_DIGITAL_UP); // unassigned 
		int button_down = Con1.get_digital(E_CONTROLLER_DIGITAL_DOWN); // unassigned 
		int button_left = Con1.get_digital(E_CONTROLLER_DIGITAL_LEFT); // unassigned 
		int button_right = Con1.get_digital(E_CONTROLLER_DIGITAL_RIGHT); // unassigned		

		int button_l1 = Con1.get_digital(E_CONTROLLER_DIGITAL_L1); // unassigned 
		int button_l2 = Con1.get_digital(E_CONTROLLER_DIGITAL_L2); // unassigned 
		int button_r1 = Con1.get_digital(E_CONTROLLER_DIGITAL_R1); // unassigned 
		int button_r2 = Con1.get_digital(E_CONTROLLER_DIGITAL_R2); // unassigned
		// End Buttons

	
	}
}