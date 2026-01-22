#include "main.h"
#include "pros/abstract_motor.hpp"
using namespace pros;

// VEXCode Style Robot Configuration

// Controller
pros::Controller Con1(pros::E_CONTROLLER_MASTER);

// Drive Motors
// NOTE: negative port number for reverse

// port numbers are placeholders
Motor FL (-17,v5::MotorGears::blue);
Motor ML (-18,v5::MotorGears::blue);
Motor BL (-20,v5::MotorGears::blue);

Motor FR (8,v5::MotorGears::blue);
Motor MR (9,v5::MotorGears::blue);
Motor BR (10,v5::MotorGears::blue);

// Intake + Scoring Motors

// also placeholder port numbers
Motor Intake (-3,v5::MotorGears::blue);
Motor Cover (-12,v5::MotorGears::blue);

// Pneumatics 
pros::adi::Pneumatics antler_l('a', false); 
pros::adi::Pneumatics antler_r('b', false); 

// Sensors
pros::Imu imu(16);
pros::Rotation vertical_encoder(-21);


//Variables
bool color;
bool hilo;