#include "robot.h"
#include "pathline.h"
#include <QProgressBar>
#include <QList>
#include <algorithm>

Robot::Robot(int x, int y, pathLine *line, QString type)
{
    // start rotation
    setRotation(90);

    // start position
    this->x = x;
    this->y = y;
    setPos(x, y);

    // line placed on
    this->line = line;

    // snap location to line
    this->setPos(this->line->getSnapPoint(this->pos()));
    this->x = this->pos().x();
    this->y = this->pos().y();

    // robot shape
    this->type = type;
}

QRectF Robot::boundingRect() const
{
    return QRect(-10, -10, 20, 20);
}

QPolygonF Robot::boundingDiamond() const
{
    QPolygonF diamond;
    diamond.append(QPointF(0, 12));
    diamond.append(QPointF(-12, 0));
    diamond.append(QPointF(0, -12));
    diamond.append(QPointF(12, 0));
    return diamond;
}

QPolygonF Robot::boundingTriangle() const
{
    QPolygonF triangle;
    triangle.append(QPointF(12, 12));
    triangle.append(QPointF(12, -12));
    triangle.append(QPointF(-12, 0));
    return triangle;
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QPolygonF diamond = boundingDiamond();
    QPolygonF triangle = boundingTriangle();

    painter->setPen(Qt::NoPen);
    painter->setBrush(this->color);

    if (this->type == "Circle Robot") {
        painter->drawEllipse(rec);
    } else if (this->type == "Square Robot") {
        painter->drawRect(rec);
    } else if (this->type == "Diamond Robot") {
        painter->drawPolygon(diamond);
    } else if (this->type == "Triangle Robot") {
        painter->drawPolygon(triangle);
    }
}

void Robot::setSpeed(double barspeed)
{
    speed = barspeed;
    maxSpeed = speed;
}

void Robot::setColor(QColor color)
{
    this->color = color;
}

void Robot::advance(int phase)
{
    if (phase) // robots move on the action phase, not the prep phase
    {
        // check if at the boundary of board
        //this->boundaryDetection();

        if (line->line().p2().x() - line->line().p1().x() > 0) {
            //collisionDetectionEast();
            setPos(mapToParent(0, (-speed)));
        } else if (line->line().p2().x() - line->line().p1().x() < 0) {
            //collisionDetectionWest();
            setPos(mapToParent(0, speed));
        } else if (line->line().p2().y() - line->line().p1().y() < 0) {
            //collisionDetectionNorth();
            setPos(mapToParent((-speed), 0));
        } else {
            //collisionDetectionSouth();
            setPos(mapToParent((speed), 0));
        }
    }
}

bool Robot::avoidLineCollision(QGraphicsItem *curItem, int clearAhead)

{
    Robot *robot;
    if (clearAhead <= RADAR_SEARCH_AHEAD){
        speed = std::min(speed, dynamic_cast<Robot *>(curItem)->getSpeed());
    }

    else
    {
        speed = std::min(++speed, maxSpeed); //accelerate if path is clear
    }
    else
    {
        speed = std::min(++speed, maxSpeed); //accelerate if path is clear
    }

    return false;
}

void Robot::saveSpeed()
{
    if (speed > 0) {
        tempSpeed = speed;
    }
}

void Robot::restoreSpeed()
{
    speed = tempSpeed;
}

int Robot::getBufferSpace()
{
    return RADAR_SEARCH_AHEAD;
}

int Robot::getSpeed()
{
    return speed;
}

