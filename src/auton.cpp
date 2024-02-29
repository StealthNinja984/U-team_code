#include "auton.h"

double inchesToRotation (double inches)
{
    //return((inches/(3.5*M_PI*5/3))*360);
    return((inches/(3.5*M_PI*5/3))*360);
}

double degreesToRotation (double degrees)
{
    return(degrees*(200/90));
}

void drive(double dist, int speed, bool backwards=false, bool blocking=true) //driving forward and back
{
    double rotations = inchesToRotation(dist);
    if (backwards) //driving backwards
    {
        leftDrive.spinFor(reverse, rotations, deg, speed, velocityUnits::pct, false);
        rightDrive.spinFor(reverse, rotations, deg, speed, velocityUnits::pct, blocking);
    } else //driving forward
    {
        leftDrive.spinFor(fwd, rotations, deg, speed, velocityUnits::pct, false);
        rightDrive.spinFor(fwd, rotations, deg, speed, velocityUnits::pct, blocking);
    }
}

void turn(double dist, int speed, bool right=false, bool blocking=true) //turning function
{
    double rotations = degreesToRotation(dist);
    if (right) //turning to the right
    {
        leftDrive.spinFor(fwd, rotations, deg, speed, velocityUnits::pct, false);
        rightDrive.spinFor(reverse, rotations, deg, speed, velocityUnits::pct, blocking);
    } else //turning to the left
    {
        leftDrive.spinFor(reverse, rotations, deg, speed, velocityUnits::pct, false);
        rightDrive.spinFor(fwd, rotations, deg, speed, velocityUnits::pct, blocking);
    }
}

//startSpeed is the speed you start at. target is the speed you are trying to get to. goal is how far you want to go
void ramping (int startSpeed, int target, int goal)
{
    int rotations = inchesToRotation(goal);
    allDrives.resetPosition();
    int currentRotations = 0;
    int speed = startSpeed;

    while ((speed <= target) && (currentRotations <= rotations))
    {
        speed += 5;
        allDrives.spin(fwd, speed, velocityUnits::pct);
        wait(20, msec);
        currentRotations = allDrives.position(rotationUnits::deg);
    }

    while ((speed >= target) && (currentRotations <= rotations))
    {
        wait(20, msec);
        currentRotations = allDrives.position(rotationUnits::deg);
    }

    while ((speed > 0) && (currentRotations >= rotations))
    {
        speed -= 5;
        allDrives.spin(fwd, speed, velocityUnits::pct);
        currentRotations = allDrives.position(rotationUnits::deg);
        if (speed <= 0)
        {
            speed = 0;
            //allDrives.stop();
        }
        wait (10, msec);
    }
}

/*void prototypeRamping (double startSpeed, double maxSpeed, double rotationTarget, double stopPoint, double stopSpeed, double totalDist, bool reverse = false)
{
    allDrives.setPosition(0,deg);
    std::cout<<"prototype Ramping running"<<std::endl;
    double accelerate = inchesToRotation(rotationTarget);
    double decelerate = inchesToRotation(stopPoint);
    double overAllDist = inchesToRotation(totalDist);
    double speed = startSpeed;
    double m = (maxSpeed - startSpeed) / rotationTarget;
    double currentRotations = fabs(allDrives.position(rotationUnits::deg));
     std::cout<<"hi"<<std::endl;
    while((speed <= maxSpeed) && (currentRotations <= accelerate))
    {
        //std::cout<<"first while loop running"<<std::endl;
        currentRotations = fabs(allDrives.position(rotationUnits::deg));
        //std::cout<<currentRotations<<std::endl;
        speed = (m * currentRotations) + startSpeed;
        //std::cout<<speed<<std::endl;
        allDrives.spin(fwd, speed, pct);
        std::cout<<currentRotations<<std::endl;
        if (reverse)
        {
            allDrives.spin(fwd, (speed * -1), pct);
        }
        else
        {
            allDrives.spin(fwd, speed, pct);
        }
        wait(10, msec);
    }

    while((speed >= maxSpeed) && (currentRotations <= decelerate))
    {
        currentRotations = fabs (allDrives.position(rotationUnits::deg));
        wait(10, msec);
        std::cout<<"waiting"<<std::endl;
    }

    while((speed > 0 ) && (currentRotations >= decelerate))
    {
        std::cout<<speed<<std::endl;
        currentRotations = fabs (allDrives.position(rotationUnits::deg));
        double m = (stopSpeed - maxSpeed) / (totalDist - stopPoint);
        double b = (m * - totalDist) + stopSpeed;
        speed = (m * -1) * (currentRotations) + b;
        allDrives.spin(fwd, speed, pct);
        if (reverse)
        {
            allDrives.spin(fwd, (speed * -1), pct);
        }
        else
        {
            allDrives.spin(fwd, speed, pct);
        }
        wait(10, msec);
    }
}*/



void prototypeTurn (int targetHeading, int speed)
{
    int currentHeading = autonGyro.heading(deg);
    bool clockWise;
    double tolerance = (speed/10);
    if (currentHeading < 180)
    {
        if (targetHeading > currentHeading && (currentHeading + 180) > targetHeading)
        {
            clockWise = true;
        }
        else 
        {
            clockWise = false;
        }
    }
    else if (currentHeading >= 180)
    {
        if (targetHeading < currentHeading && (currentHeading - 180) < targetHeading)
        {
            clockWise = false;
        }
        else
        {
            clockWise = true;
        }
    }

    while (!(currentHeading == (targetHeading +- tolerance)))
    {
        if (clockWise)
        {
            currentHeading = autonGyro.heading(deg);
            if (currentHeading == (targetHeading +- tolerance))
            {
                break;
            }
            leftDrive.spin(fwd, speed, pct);
            rightDrive.spin(reverse, speed, pct);
            
        }
        else 
        {
            currentHeading = autonGyro.heading(deg);
            if (currentHeading == (targetHeading +- tolerance))
            {
                break;
            }
            leftDrive.spin(reverse, speed, pct);
            rightDrive.spin(fwd, speed, pct);
        }
        wait(10, msec);
    }
    
    allDrives.stop(hold);
}

void score()
{
    if (pneumaticToggle1)
    {
        leftWing.open();
    }
    else if (!pneumaticToggle1)
    {
        leftWing.close();
    }

    if (pneumaticToggle2)
    {
        rightWing.open();
    }
    else if (!pneumaticToggle2)
    {
        rightWing.close();
    }

    if (pneumaticToggle3)
    {
        lockWing.open();
    }
    else if (!pneumaticToggle3)
    {
        lockWing.close();
    }

    if (auton1)
    {
        std::cout<< "auton 1 has been selected" <<std::endl;
        //prototypeTurn(45, 20);
        //prototypeRamping(1, 10, 3, 7, 1, 10, true);
        ramping(0, 50, 10);
        prototypeTurn(180, 20);
        lockWing.open();
        prototypeTurn(170, 20);
        lift.spinToPosition(2546, deg, 50, velocityUnits::pct, true);
        flywheel.spin(fwd, 100, pct);
        //todo finish auton 1
    }
    else if (auton2)
    {
        std::cout<< "auton 2 has been selected" <<std::endl;
        ramping(0, 50, -11);
        lift.spinTo(810, deg, false);
        //todo code auton 2
    }
    else if (auton3)
    {
        std::cout<< "auton 3 has been selected" <<std::endl;
        ramping(0, 50, 26);
        rightPneumaticToggle();
        turn(45, 50, false, true);
        ramping(0, 25, 14);
        rightPneumaticToggle();
        turn(48, 50, false, true);
        ramping(0, 100, 22);
        drive(3, 25, true, true);
        //turn(115, 50, false, true);
        //ramping(0, 50, 25);
        //todo code auton 3
    }
    else if (auton4)
    {
        std::cout<< "auton 4 has been selected" <<std::endl;
        ramping(0, 50, -27);
        leftPneumaticToggle();
        ramping(0, 50, 11);
        //todo code auton 4
    }
    else 
    {
        std::cout<< "no auton selected. defaulting" <<std::endl;
        ramping(0, 50, -11);
        lift.spinTo(810, deg, false);
        //todo code default auton
    }
    
}