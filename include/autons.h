#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

void high_auton();
void low_auton();

//pid stuff

extern lemlib::Drivetrain drivetrain;
extern lemlib::TrackingWheel vertical_tracking_wheel;
extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::Chassis chassis;