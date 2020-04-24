#include "Robot.hpp"

Robot::Robot()
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

Robot::~Robot()
{
}
