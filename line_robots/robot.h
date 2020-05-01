#ifndef ROBOT_H
#define ROBOT_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class RobotData;
    int speed;
    int direction;
    int shape;
class Robot
{
    public:
        Robot();
        Robot(const Robot &);
        Robot &operator=(const Robot &);
        void setSpeed(int);
        void setDirection(int);
        void setShape(int);
        void changeSpeed(int);
        int getSpeed();
        int setDirection();
        int setShape();
        ~Robot();

private:
    QSharedDataPointer<RobotData> data;
};

#endif // ROBOT_H
