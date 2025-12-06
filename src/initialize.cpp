#include "main.h"
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
	imu.reset(true);
	colory.set_led_pwm(100);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

 void competition_initialize() {
	int auto_select = 0;
    bool lock = false;
    screen::print(pros::E_TEXT_MEDIUM,2,"0");
	while (1==1){
		if (auto_selector.get_value() and !lock){
            lock=true;
			auto_select+=1;
			auto_select%=4;
			screen::print(pros::E_TEXT_MEDIUM,2,"%d",auto_select);
            pros::Task::delay(10); //Delay before repeat
		}
        else if (!auto_selector.get_value()){lock=false;}
	}
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    high_auton();
}
