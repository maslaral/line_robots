#include "robot.h"

class RobotData : public QSharedData
{
public:

};

Robot::Robot() : data(new RobotData)
{

}

Robot::Robot(const Robot &rhs) : data(rhs.data)
{

}

Robot &Robot::operator=(const Robot &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Robot::~Robot()
{

}

void Robot::setSpeed(int userSpeed)
{
    speed = userSpeed;
}

void Robot::setDirection(int userDirection)
{
    direction = userDirection;
}

void Robot::setShape(int userShape)
{
    shape = userShape;
}

void Robot::changeSpeed(int robotSpeed)
{
    speed = robotSpeed;
}

int Robot::getSpeed()
{
    return speed;
}

int Robot::setDirection()
{
    return direction;
}

int Robot::setShape()
{
    return shape;
}
