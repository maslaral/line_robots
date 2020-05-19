#include "robot.h"
#include <QProgressBar>

Robot::Robot(int x, int y, QGraphicsLineItem *line, QString type)
{
    // start rotation
    setRotation(90);

    // start position
    this->x = x;
    this->y = y;
    setPos(x, y);

    // line placed on
    this->line = line;

    // robot shape
    this->type = type;
}

QRectF Robot::boundingRect() const
{
    return QRect(0,0,20,20);
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    painter->setPen(Qt::black);

    if (this->type == "Circle Robot") {
        painter->setBrush(Qt::green);
        painter->drawEllipse(rec);
    }
    else if (this->type == "Square Robot") {
        painter->setBrush(Qt::blue);
        painter->drawRect(rec);
    }
}

void Robot::setSpeed(double barspeed)
{
    speed = barspeed;
}

void Robot::advance(int phase)
{
    if (!phase) return;

    // if a line pointing east
    if (line->line().p2().x() - line->line().p1().x() > 0) {
        setPos(mapToParent(0, (-speed)));
    }
    // if a line pointing west
    else if (line->line().p2().x() - line->line().p1().x() < 0) {
        setPos(mapToParent(0, speed));
    }
    // if a line pointing north
    else if (line->line().p2().y() - line->line().p1().y() < 0) {
        setPos(mapToParent((-speed), 0));
    }
    // if a line pointing south
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


// TODO: reimplement the collision detection code,
// current state doesn't work as robots would be in
// a state of constant collision since they are on
// a line.
void Robot::DoCollision()
{
    // get new position
    if(((qrand() % 1)))
    {
        setRotation((rotation() + (180 + qrand() % 1)));
    }
    else{
         setRotation((rotation()+(-180 + qrand() % -1)));
    }

    // see if the new position is in bounds + 2 pushes away from the obeject it colides with
    QPointF newpoint = mapToParent(-(boundingRect().width()), -(boundingRect().width() + 2));

    if(!scene()->sceneRect().contains((newpoint)))
    {
        // move back inbounds
        newpoint = mapToParent(100, -100);

    }
    else
    {
        // set new position
        setPos(newpoint);
    }
}
