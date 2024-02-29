#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller Controller1;
competition Competition;
 
motor leftFront(PORT10, ratio18_1, true); 
motor leftMiddle(PORT8, ratio18_1, true);
motor leftBack(PORT7, ratio18_1);
motor rightFront(PORT1, ratio18_1);
motor rightMiddle(PORT3, ratio18_1);
motor rightBack(PORT2, ratio18_1, true);

motor lift(PORT4, ratio18_1);
motor flywheel(PORT5, ratio6_1, true);

inertial autonGyro(PORT12);

pneumatics leftWing = pneumatics (Brain.ThreeWirePort.A);
pneumatics rightWing = pneumatics (Brain.ThreeWirePort.B);
pneumatics lockWing = pneumatics (Brain.ThreeWirePort.C);
pneumatics hangWing = pneumatics (Brain.ThreeWirePort.D);


motor_group leftDrive = motor_group(leftFront, leftMiddle, leftBack);
motor_group rightDrive = motor_group(rightFront, rightMiddle, rightBack);

motor_group allDrives = motor_group(leftFront, leftMiddle, leftBack, rightFront, rightMiddle, rightBack);
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}