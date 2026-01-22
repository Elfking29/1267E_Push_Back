#include "main.h"
#include "pros/abstract_motor.hpp"
using namespace pros;

// VEXCode Style Robot Configuration

// Controller
pros::Controller Con1(pros::E_CONTROLLER_MASTER);

// Drive Motors
// NOTE: negative port number for reverse

// port numbers are placeholders
Motor FL (-16,v5::MotorGears::blue);
Motor ML (-17,v5::MotorGears::blue);
Motor BL (-19,v5::MotorGears::blue);

Motor FR (9,v5::MotorGears::blue);
Motor MR (1,v5::MotorGears::blue);
Motor BR (10,v5::MotorGears::blue);

// Intake + Scoring Motors

// also placeholder port numbers
Motor Intake (14,v5::MotorGears::green);
Motor Middle (11,v5::MotorGears::green);
Motor Switcher (-13,v5::MotorGears::green);

// Pneumatics 
pros::adi::Pneumatics tube_piston('b', false); 
pros::adi::Pneumatics lift_piston('f', false); 

// Sensors

adi::DigitalIn auto_selector('d');
pros::Imu imu(12);
pros::Rotation vertical_encoder(-21);
pros::Optical colory(11); //Red ~10, Blue ~210, Default ~40


//Variables
bool color;
bool hilo;