#include "DriverControl.h"

bool flywheelToggle = false;
bool pneumaticToggle1 = false;
bool pneumaticToggle2 = false;
bool pneumaticToggle3 = false;
bool pneumaticToggle4 = false;

void FlywheelToggle () //variable toggle
{
    if (flywheelToggle)
    {
        flywheelToggle = false;
        std::cout<<"true"<<std::endl;
    }
    else if (!flywheelToggle)
    {
        flywheelToggle = true;
        std::cout<<"false"<<std::endl;
    }
}

void rightPneumaticToggle () //variable toggle
{
    if (pneumaticToggle1)
    {
        pneumaticToggle1 = false;
        std::cout<<"pneumatic 1 open"<<std::endl;
    }
    else if (!pneumaticToggle1)
    {
        pneumaticToggle1 = true;
        std::cout<<"pneumatic 1 closed"<<std::endl;
    }

    if (pneumaticToggle1)
    {
        leftWing.open();
    }
    else if (!pneumaticToggle1)
    {
        leftWing.close();
    }
}

void leftPneumaticToggle () //variable toggle
{
    if (pneumaticToggle2)
    {
        pneumaticToggle2 = false;
        std::cout<<"pneumatic 2 open"<<std::endl;
    }
    else if (!pneumaticToggle2)
    {
        pneumaticToggle2 = true;
        std::cout<<"pneumatic 2 closed"<<std::endl;
    }

    if (pneumaticToggle2)
    {
        rightWing.open();
    }
    else if (!pneumaticToggle2)
    {
        rightWing.close();
    }
}

void lockPneumaticToggle () //variable toggle
{
    if (pneumaticToggle3)
    {
        pneumaticToggle3 = false;
        std::cout<<"pneumatic 1 open"<<std::endl;
    }
    else if (!pneumaticToggle3)
    {
        pneumaticToggle3 = true;
        std::cout<<"pneumatic 1 closed"<<std::endl;
    }

    if (pneumaticToggle3)
    {
        lockWing.open();
    }
    else if (!pneumaticToggle3)
    {
        lockWing.close();
    }
}

void hangPneumaticToggle () //variable toggle
{
    if (pneumaticToggle4)
    {
        pneumaticToggle4 = false;
        std::cout<<"pneumatic 4 open"<<std::endl;
    }
    else if (!pneumaticToggle4)
    {
        pneumaticToggle4 = true;
        std::cout<<"pneumatic 4 closed"<<std::endl;
    }

    if (pneumaticToggle4)
    {
        hangWing.open();
    }
    else if (!pneumaticToggle4)
    {
        hangWing.close();
    }
}
void liftUp ()
{
    std::cout<< "r1 pressed" <<std::endl;
    lift.spin(fwd, 100, pct);
}

void liftDown ()
{
    std::cout<< "r2 pressed" <<std::endl;
    lift.spin(reverse, 100, pct);
}

void liftStop()
{
    lift.stop(hold);
}

void driverControl () 
{
    bool leftArrowPressing = false;
    bool rightArrowPressing = false;
    bool aPressing = false;
    bool yPressing = false;
    bool l2Pressing = false;

    while (true)
    {
        int axis2 = Controller1.Axis2.position(); //left vertical
        int axis3 = Controller1.Axis3.position(); //right vertical
        bool r1 = Controller1.ButtonR1.pressing(); //right up trigger 
        bool r2 = Controller1.ButtonR2.pressing(); //right down trigger
        bool rightArrow = Controller1.ButtonRight.pressing();//right arrow variable
        bool leftArrow = Controller1.ButtonLeft.pressing();
        bool buttonA = Controller1.ButtonA.pressing();//a button variable
        bool buttonY = Controller1.ButtonY.pressing();//y button variable
        bool l2 = Controller1.ButtonL2.pressing();

        leftDrive.spin(fwd, axis3, pct);
        rightDrive.spin(fwd, axis2, pct);

        Controller1.ButtonR1.pressed(liftUp);
        Controller1.ButtonR1.released(liftStop);
        Controller1.ButtonR2.pressed(liftDown);
        Controller1.ButtonR2.released(liftStop);

        /*std::cout<< Controller1.ButtonR1.pressing() <<std::endl;
        if (Controller1.ButtonR1.pressing()) //lift controls
        {
            std::cout<< "r1 pressed" <<std::endl;
            lift.spin(reverse, 50, pct);
        }
        else if (r2)
        {
            lift.spin(fwd, 50, pct);
        }
        else 
        {
            lift.stop(hold);
        }*/

        if (buttonA && !aPressing) //kicker toggle
        {
            FlywheelToggle();
            aPressing = true;
            std::cout<<"a pressed"<<std::endl;
        }
        else if (!buttonA && aPressing)
        {
            aPressing = false;
        }

        if (buttonY && !yPressing) //left pneumatic wing
        {
            rightPneumaticToggle();
            yPressing = true; 
            std::cout<<"y pressed"<<std::endl;
        }
        else if (!buttonY && yPressing)
        {
            yPressing = false;
        }

        if (rightArrow && !rightArrowPressing)
        {
            leftPneumaticToggle();
            rightArrowPressing = true;
            std::cout<<"right arrow pressed"<<std::endl;
        }
        else if (!rightArrow && rightArrowPressing)
        {
            rightArrowPressing = false;
        }

        if (leftArrow && !leftArrowPressing)
        {
            lockPneumaticToggle();
            leftArrowPressing = true;
            std::cout<<"right arrow pressed"<<std::endl;
        }
        else if (!leftArrow && leftArrowPressing)
        {
            leftArrowPressing = false;
        }

        if  (flywheelToggle) //spin the flywheel motor
        {
            flywheel.spin(fwd, 100, pct);
        }
        else if(!flywheelToggle)
        {
            flywheel.stop();
        }

        if (l2 && !l2Pressing)
        {
            hangPneumaticToggle();
            l2Pressing = true;
            std::cout<<"l2 pressed"<<std::endl;
        }
        else if (!l2 && l2Pressing)
        {
            l2Pressing = false;
        }

        /*if (pneumaticToggle1)
        {
            rightWing.open();
        }
        else if (!pneumaticToggle1)
        {
            rightWing.close();
        }

        if (pneumaticToggle2)
        {
            leftWing.open();
        }
        else if (!pneumaticToggle2)
        {
            leftWing.close();
        }*/
        
        wait(20, msec);

    }
}

