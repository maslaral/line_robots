#include "robot.h"
#include "qprogressbar.h"

MyRobot::MyRobot()
{
    //start rotation

    angle = 90;
    setRotation(angle);
    //set speed

    //speed = 5;

    //start position

    int StartX = 100;
    int StartY = -100;

    setPos((mapToParent(StartX,StartY)));
}

QRectF MyRobot::boundingRect() const
{
    return QRect(0,0,20,20);
}

void MyRobot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush Brush(Qt::gray);

    //basic colision detection

    if(scene()->collidingItems(this).isEmpty())
    {
        //no collision
        Brush.setColor(Qt::green);

    }
    else
    {
        //else collision
        Brush.setColor(Qt::red);

        //set the position
        DoCollision();
    }

    painter -> fillRect(rec,Brush);
    painter -> drawRect(rec);



}

void MyRobot::setSpeed(double barspeed)
{
    speed = barspeed;
}

void MyRobot::advance(int phase)
{
    if(!phase) return;

    //point is space where the robot is
    QPointF location = this->pos();

    //set speed on the canvas
    setPos(mapToParent(0,-(speed)));
}

void MyRobot::DoCollision()
{
    //get new position
    if(((qrand()%1)))
    {
        setRotation((rotation()+(180+qrand()%1)));
    }
    else{
         setRotation((rotation()+(-180+qrand()%-1)));
    }

    //see if the new position is in bounds +2 pushes away from the obeject it colides with
    QPointF newpoint = mapToParent(-(boundingRect().width()), -(boundingRect().width()+2));

    if(!scene()->sceneRect().contains((newpoint)))
    {
        //move back inbounds
        newpoint = mapToParent(100,-100);

    }
    else
    {
        //set new position
        setPos(newpoint);
    }

}
