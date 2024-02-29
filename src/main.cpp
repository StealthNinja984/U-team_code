/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       26LSHUMWAY                                                */
/*    Created:      12/11/2023, 9:33:26 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

bool pressing = false;

void preAuton ()
{
    vexcodeInit();
}

int main() {
    autonGyro.calibrate();
    wait(2, seconds);
    Competition.drivercontrol(driverControl);
    Competition.autonomous(score);
    preAuton();
    allDrives.setStopping(hold);

    getTextSize();
    drawAll();
    
    while(true) 
    {
        if (Brain.Screen.pressing() && !pressing)
        {
            updateAll();
            pressing = true;
        }
        else if (!Brain.Screen.pressing() && pressing)
        {
            pressing = false;
        }
        wait (20, msec);
    }
}

