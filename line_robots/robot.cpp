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

void Robot::boundaryDetection()
{/*
    // boundary for moving east
    if (this->pos().x() >= this->scene()->sceneRect().right()) {
        setPos(this->scene()->sceneRect().left(), y);
    }
    // boundary for moving west
    else if (this->pos().x() <= this->scene()->sceneRect().left()) {
        setPos(this->scene()->sceneRect().right(), y);
    }
    // boundary for moving north
    else if (this->pos().y() <= this->scene()->sceneRect().top()) {
        setPos(x, this->scene()->sceneRect().bottom());
    }
    // boundary for moving south
    else if (this->pos().y() >= this->scene()->sceneRect().bottom()) {
        setPos(x, this->scene()->sceneRect().top());
    }*/
}

void Robot::collisionDetectionEast()
{
   /* //get the robots on the parent line and sort them in the direction of travel
    QList<QGraphicsItem *> siblings = this->parentItem()->childItems();
    auto compare = [](QGraphicsItem *i, QGraphicsItem *j)->bool{return i->pos().x() < j->pos().x();};
    std::sort(siblings.begin(),siblings.end(),compare);

    //find the robot ahead of this one
    auto it = siblings.begin();
    while (it != siblings.end() && (*it)->pos().x() <= this->pos().x())
    {
        ++it;
    }
    if (it == siblings.end())
    {
        it = siblings.begin();
    }
    if ((*it)->pos().x() == this->pos().x()) {
        return;
    }
    else
    {   //check how far away the leading robot is and adjust speed if needed
        int clearAhead = (*it)->pos().x() - this->pos().x();
        clearAhead += this->scene()->sceneRect().right();
        clearAhead %= static_cast<int>(this->scene()->sceneRect().right());

        if (clearAhead <= RADAR_SEARCH_AHEAD)
        {
            avoidLineCollision(*it,1);
            if (speed == 0) {   // if speed was set to 0
                restoreSpeed(); // restore it to the value stored in tempSpeed
            }
        }
    }*/

    /*QGraphicsItem *curItem;
    QPointF radar = pos();
    int overflow = 0;

    for (int i = 0; i <= RADAR_SEARCH_AHEAD; i++) {
        if (radar.x() + i > EAST_BORDER) {      // if greater than border, radar should look
            overflow += 1;                      // "around the corner" to the other side of
            radar.setX(WEST_BORDER + overflow); // of the canvas
        } else {
            radar.setX(radar.x() + i); // otherwise, just look ahead
        }

        curItem = scene()->itemAt(radar, QTransform());

        if (avoidLineCollision(curItem)) {
            return;
        }

        radar = pos(); // reset the radar to current position
        overflow = 0;  // reset the overflow value
    }

    if (speed == 0) {   // if speed was set to 0
        restoreSpeed(); // restore it to the value stored in tempSpeed
    }*/
}

void Robot::collisionDetectionWest()
{
   /* QGraphicsItem *curItem;
    QPointF radar = pos();
    int overflow = 0;

    for (int i = 0; i <= RADAR_SEARCH_AHEAD; i++) {
        if (radar.x() - i < WEST_BORDER) {
            overflow += 1;
            radar.setX(EAST_BORDER - overflow);
        } else {
            radar.setX(radar.x() - i);
        }

        curItem = scene()->itemAt(radar, QTransform());

        if (avoidLineCollision(curItem,1)) {
            return;
        }

        radar = pos();
        overflow = 0;
    }

    if (speed == 0) {
        restoreSpeed();
    }*/
}

void Robot::collisionDetectionNorth()
{
    /*QGraphicsItem *curItem;
    QPointF radar = pos();
    int overflow = 0;

    for (int i = 0; i < RADAR_SEARCH_AHEAD; i++) {
        if (radar.y() - i < NORTH_BORDER) {
            overflow++;
            radar.setY(SOUTH_BORDER - overflow);
        } else {
            radar.setY(radar.y() - i);
        }

        curItem = scene()->itemAt(radar, QTransform());

        if (avoidLineCollision(curItem,1)) {
            return;
        }

        radar = pos();
        overflow = 0;
    }

    if (speed == 0) {
        restoreSpeed();
    }*/
}

void Robot::collisionDetectionSouth()
{
    /*QGraphicsItem *curItem;
    QPointF radar = pos();
    int overflow = 0;

    for (int i = 0; i < RADAR_SEARCH_AHEAD; i++) {
        if (radar.y() + i > SOUTH_BORDER) {
            overflow++;
            radar.setY(NORTH_BORDER + overflow);
        } else {
            radar.setY(radar.y() + i);
        }

        curItem = scene()->itemAt(radar, QTransform());

        if (avoidLineCollision(curItem,1)) {
            return;
        }

        radar = pos();
        overflow = 0;
    }

    if (speed == 0) {
        restoreSpeed();
    }*/
}

bool Robot::avoidIntersectionCollision(QGraphicsItem *curItem)
{
    Robot *robot;

    if ((robot = dynamic_cast<Robot *>(curItem)) && (line != robot->line)) {
        if (robot->speed >= speed) {
            saveSpeed();
            speed = 0;
        }
        return true;
    }

    return false;
}

bool Robot::avoidLineCollision(QGraphicsItem *curItem, int clearAhead)
{
    Robot *robot;
    if (clearAhead <= RADAR_SEARCH_AHEAD){
        if ((robot = dynamic_cast<Robot *>(curItem)) && (line == robot->line)) {
            if (speed > robot->speed) {
                speed = robot->speed;
                saveSpeed();
                return true;
            } else if (speed == 0 && robot->speed == 0) {
                restoreSpeed();
                return true;
            }
        }
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
