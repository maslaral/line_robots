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
    return QRect(-10, -10, 20, 20);
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    painter->setPen(Qt::black);

    if (this->type == "Circle Robot") {
        painter->setBrush(Qt::green);
        painter->drawEllipse(rec);
    } else if (this->type == "Square Robot") {
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
    if (!phase)
        return;

    // check if at the boundary of board
    this->boundaryDetection();

    if (line->line().p2().x() - line->line().p1().x() > 0) {
        collisionDetectionEast();
        setPos(mapToParent(0, (-speed)));
    } else if (line->line().p2().x() - line->line().p1().x() < 0) {
        collisionDetectionWest();
        setPos(mapToParent(0, speed));
    } else if (line->line().p2().y() - line->line().p1().y() < 0) {
        collisionDetectionNorth();
        setPos(mapToParent((-speed), 0));
    } else {
        collisionDetectionSouth();
        setPos(mapToParent((speed), 0));
    }
}

void Robot::boundaryDetection()
{
    // boundary for moving east
    if (this->pos().x() >= 554) {
        setPos(30, y);
    }
    // boundary for moving west
    else if (this->pos().x() <= 30) {
        setPos(524, y);
    }
    // boundary for moving north
    else if (this->pos().y() <= 0) {
        setPos(x, 436);
    }
    // boundary for moving south
    else if (this->pos().y() >= 436) {
        setPos(x, 30);
    }
}

// Note: we have to do a nested for loop because the robots
// are not exactly aligned on the line. If we can get the robots
// to all align on the line exactly, this won't be needed and
// would simplify things.
void Robot::collisionDetectionEast()
{
    Robot *robot;
    QGraphicsItem *curItem;
    QPointF radar = pos();
    int overflow = 0;

    for (int j = -5; j <= 5; j++) {
        for (int i = 0; i <= RADAR_SEARCH_AREA; i++) {
            if (radar.x() + i > EAST_BORDER) {      // if greater than border, radar should look
                overflow += 1;                      // "around the corner" to the other side of
                radar.setX(WEST_BORDER + overflow); // of the canvas
            } else {
                radar.setX(radar.x() + i);
            }

            radar.setY(radar.y() + j);

            curItem = scene()->itemAt(radar, QTransform());
            if ((robot = dynamic_cast<Robot *>(curItem)) && (line == robot->line)) {
                if (speed > robot->speed) {
                    speed = robot->speed;
                    return;
                }
            }
            radar = pos();
        }
        overflow = 0;
    }
}

void Robot::collisionDetectionWest()
{
    Robot *robot;
    QGraphicsItem *curItem;
    QPointF radar = pos();
    int overflow = 0;

    for (int j = -5; j <= 5; j++) {
        for (int i = 0; i <= RADAR_SEARCH_AREA; i++) {
            if (radar.x() - i < WEST_BORDER) {
                overflow += 1;
                radar.setX(EAST_BORDER - overflow);
            } else {
                radar.setX(radar.x() - i);
            }

            radar.setY(radar.y() + j);

            curItem = scene()->itemAt(radar, QTransform());
            if ((robot = dynamic_cast<Robot *>(curItem)) && (line == robot->line)) {
                if (speed > robot->speed) {
                    speed = robot->speed;
                    return;
                }
            }
            radar = pos();
        }
        overflow = 0;
    }
}

void Robot::collisionDetectionNorth()
{
    Robot *robot;
    QGraphicsItem *curItem;
    QPointF radar = pos();
    int overflow = 0;

    for (int j = -5; j <= 5; j++) {
        for (int i = 0; i < RADAR_SEARCH_AREA; i++) {
            if (radar.y() - i < NORTH_BORDER) {
                overflow++;
                radar.setY(SOUTH_BORDER - overflow);
            } else {
                radar.setY(radar.y() - i);
            }

            radar.setX(radar.x() + j);

            curItem = scene()->itemAt(radar, QTransform());
            if ((robot = dynamic_cast<Robot *>(curItem)) && (line == robot->line)) {
                if (speed > robot->speed) {
                    speed = robot->speed;
                    return;
                }
            }
            radar = pos();
        }
        overflow = 0;
    }
}

void Robot::collisionDetectionSouth()
{
    Robot *robot;
    QGraphicsItem *curItem;
    QPointF radar = pos();
    int overflow = 0;

    for (int j = -5; j <= 5; j++) {
        for (int i = 0; i < RADAR_SEARCH_AREA; i++) {
            if (radar.y() + i > SOUTH_BORDER) {
                overflow++;
                radar.setY(NORTH_BORDER + overflow);
            } else {
                radar.setY(radar.y() + i);
            }

            radar.setX(radar.x() + j);

            curItem = scene()->itemAt(radar, QTransform());
            if ((robot = dynamic_cast<Robot *>(curItem)) && (line == robot->line)) {
                if (speed > robot->speed) {
                    speed = robot->speed;
                    return;
                }
            }
            radar = pos();
        }
        overflow = 0;
    }
}
