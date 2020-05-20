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

    this->speed = rand() % 20 + 1;


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

double Robot::getSpeed()
{
    return speed;
}

void Robot::advance(int phase)
{
    if (!phase) return;

    this->boundary();

    // if a line pointing east
    if (line->line().p2().x() - line->line().p1().x() > 0) {
        collisionDetectionEast();
        setPos(mapToParent(0, (-speed)));
    }
    // if a line pointing west
    else if (line->line().p2().x() - line->line().p1().x() < 0) {
        collisionDetectionWest();
        setPos(mapToParent(0, speed));
    }
    // if a line pointing north
    else if (line->line().p2().y() - line->line().p1().y() < 0) {
        collisionDetectionNorth();
        setPos(mapToParent((-speed), 0));
    }
    // if a line pointing south
    else {
        collisionDetectionSouth();
        setPos(mapToParent((speed), 0));
    }
}

void Robot::boundary()
{
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

void Robot::collisionDetectionEast()
{
    QGraphicsItem *curItem;
    Robot *robot;
    QPointF radar = this->pos();

    for (int i = 0; i < 30; i++) {
        for (int j = -5; j <= 5; j++) {
            if (radar.x() > 524) {
                radar.setX(30 + i);
            } else {
                radar.setX(radar.x() + i);
            }
            radar.setX(radar.x() + i);
            radar.setY(radar.y() + j);
            curItem = this->scene()->itemAt(radar, QTransform());
            if ((robot = dynamic_cast<Robot*>(curItem))) {
                if (this->speed > robot->getSpeed()) {
                    this->speed = robot->getSpeed();
                    return;
                }
            }
            radar.setX(this->pos().x());
            radar.setY(this->pos().y());
        }
    }
}

void Robot::collisionDetectionWest()
{
    QGraphicsItem *curItem;
    Robot *robot;
    QPointF radar = this->pos();

    for (int i = 0; i < 30; i++) {
        for (int j = -5; j <= 5; j++) {
            if (radar.x() < 30) {
                radar.setX(524 - i);
            } else {
                radar.setX(radar.x() - i);
            }

            radar.setY(radar.y() + j);
            curItem = this->scene()->itemAt(radar, QTransform());
            if ((robot = dynamic_cast<Robot*>(curItem))) {
                if (this->speed > robot->getSpeed()) {
                    this->speed = robot->getSpeed();
                    return;
                }
            }
            radar.setX(this->pos().x());
            radar.setY(this->pos().y());
        }
    }
}


void Robot::collisionDetectionNorth()
{
    QGraphicsItem *curItem;
    Robot *robot;
    QPointF radar = this->pos();

    for (int i = 0; i < 60; i++) {
        for (int j = -5; j <= 5; j++) {
            if (radar.y() < 30) {
                radar.setY(436 - i);
            } else {
                radar.setY(radar.y() - i);
            }

            radar.setX(radar.x() + j);
            curItem = this->scene()->itemAt(radar, QTransform());
            if ((robot = dynamic_cast<Robot*>(curItem))) {
                if (this->speed > robot->getSpeed()) {
                    this->speed = robot->getSpeed();
                    return;
                }
            }
            radar.setX(this->pos().x());
            radar.setY(this->pos().y());
        }
    }
}

void Robot::collisionDetectionSouth()
{
    QGraphicsItem *curItem;
    Robot *robot;
    QPointF radar = this->pos();

    for (int i = 0; i < 60; i++) {
        for (int j = -5; j <= 5; j++) {
            if (radar.y() > 436) {
                radar.setY(30 + i);
            } else {
                radar.setY(radar.y() + i);
            }

            radar.setX(radar.x() + j);
            curItem = this->scene()->itemAt(radar, QTransform());
            if ((robot = dynamic_cast<Robot*>(curItem))) {
                if (this->speed > robot->getSpeed()) {
                    this->speed = robot->getSpeed();
                    return;
                }
            }
            radar.setX(this->pos().x());
            radar.setY(this->pos().y());
        }
    }
}
