using namespace vex;

extern brain Brain;
extern controller Controller1;
extern competition Competition;


extern motor leftFront;
extern motor leftMiddle;
extern motor leftBack;
extern motor rightFront;
extern motor rightMiddle;
extern motor rightBack;

extern motor lift;
extern motor flywheel;

extern inertial autonGyro;

extern pneumatics leftWing;
extern pneumatics rightWing;
extern pneumatics lockWing;
extern pneumatics hangWing;

extern motor_group leftDrive;
extern motor_group rightDrive;

extern motor_group allDrives;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
