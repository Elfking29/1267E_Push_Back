#include "main.h"
#include "pros/abstract_motor.hpp"
using namespace pros;

// VEXCode Style Robot Configuration

// Controller
pros::Controller Con1(pros::E_CONTROLLER_MASTER);

// Drive Motors
// NOTE: negative port number for reverse

// port numbers are placeholders
Motor FL (1,v5::MotorGears::blue);
Motor ML (2,v5::MotorGears::blue);
Motor BL (3,v5::MotorGears::blue);

Motor FR (-4,v5::MotorGears::blue);
Motor MR (-5,v5::MotorGears::blue);
Motor BR (-6,v5::MotorGears::blue);

// Intake + Scoring Motors

// also placeholder port numbers
Motor Intake (-7,v5::MotorGears::blue);
Motor Cover (-8,v5::MotorGears::blue);

// Pneumatics 


// Sensors

