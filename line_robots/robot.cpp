#include "robot.h"
#include <QProgressBar>

Robot::Robot(int x, int y, QGraphicsLineItem *line)
{
    // start rotation
    angle = 90;
    setRotation(angle);

    // start position
    this->x = x;
    this->y = y;
    this->line = line;
    setPos(x, y);
}

QRectF Robot::boundingRect() const
{
    return QRect(0,0,20,20);
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush Brush(Qt::gray);

    //basic colision detection
    if(scene()->collidingItems(this).isEmpty())
    {
        // no collision
        Brush.setColor(Qt::green);
    }
    else
    {
        // else collision
        // Brush.setColor(Qt::red);

        // set the position
        // DoCollision();
    }

    painter->fillRect(rec, Brush);
    painter->drawRect(rec);
}

void Robot::setSpeed(double barspeed)
{
    speed = barspeed;
}

void Robot::advance(int phase)
{
    if (!phase) return;

    // if a right line
    if (line->line().p2().x() - line->line().p1().x() > 0) {
        setPos(mapToParent(0, (-speed)));
    }
    // if a left line
    else if (line->line().p2().x() - line->line().p1().x() < 0) {
        setPos(mapToParent(0, speed));
    }
    // if a up line
    else if (line->line().p2().y() - line->line().p1().y() < 0) {
        setPos(mapToParent((-speed), 0));
    }
    // if a down line
    else {
        setPos(mapToParent((speed), 0));
    }

    // boundary for moving right
    if (this->pos().x() >= 554) {
        setPos(30, y);
    }
    // boundary for moving left
    else if (this->pos().x() <= 30) {
        setPos(524, y);
    }
    // boundary for moving up
    else if (this->pos().y() <= 0) {
        setPos(x, 436);
    }
    // boundary for moving down
    else if (this->pos().y() >= 436) {
        setPos(x, 30);
    }
}

void Robot::DoCollision()
{
    // get new position
    if(((qrand()%1)))
    {
        setRotation((rotation()+(180+qrand()%1)));
    }
    else{
         setRotation((rotation()+(-180+qrand()%-1)));
    }

    // see if the new position is in bounds +2 pushes away from the obeject it colides with
    QPointF newpoint = mapToParent(-(boundingRect().width()), -(boundingRect().width()+2));

    if(!scene()->sceneRect().contains((newpoint)))
    {
        // move back inbounds
        newpoint = mapToParent(100,-100);

    }
    else
    {
        // set new position
        setPos(newpoint);
    }
}
