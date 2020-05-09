#ifndef ROBOT_HPP
#define ROBOT_HP

class Robot
{
private:
	int speed;
	int direction;
	int shape;
public:
	Robot();
	void setSpeed(int);
	void setDirection(int);
	void setShape(int);
	void changeSpeed(int);
	int getSpeed();
	int setDirection();
	int setShape();
	virtual ~Robot();
};

#endif // !ROBOT_HPP
