#include "pros/optical.hpp"
using namespace pros;
//Using extern in C++ isn't great practice, but it is easier and what VEXCode uses.

// Controller
extern pros::Controller Con1;

// Drive Motors
extern Motor FL;
extern Motor ML;
extern Motor BL;
extern Motor FR;
extern Motor MR;
extern Motor BR;

// Intake + Scoring Motors
extern Motor Intake;
extern Motor Cover;

// Pneumatics 
extern pros::adi::Pneumatics antler_l;
extern pros::adi::Pneumatics antler_r;

// Sensors
extern adi::DigitalIn auto_selector;
extern pros::Imu imu;
extern pros::Rotation vertical_encoder;

//Variables
extern bool color;
extern bool hilo;