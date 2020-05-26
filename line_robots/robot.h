#ifndef ROBOT_H
#define ROBOT_H

#include "pathline.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

class Robot : public QGraphicsItem
{
public:
    explicit Robot(int, int, pathLine *, QString);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setSpeed(double);
    void setColor(QColor);

protected:
    void advance(int phase);
    void boundaryDetection();
    void collisionDetectionNorth();
    void collisionDetectionSouth();
    void collisionDetectionEast();
    void collisionDetectionWest();
    bool avoidIntersectionCollision(QGraphicsItem *curItem);
    bool avoidLineCollision(QGraphicsItem *curItem);
    void saveSpeed();
    void restoreSpeed();

private:
    int const RADAR_SEARCH_AHEAD = 60;
    int const RADAR_SEARCH_INTER = 15;
    int const EAST_BORDER = 524;
    int const WEST_BORDER = 30;
    int const NORTH_BORDER = 30;
    int const SOUTH_BORDER = 436;

    int speed;
    int tempSpeed;
    int x;
    int y;
    QString type;
    pathLine *line;
    QColor color;
};

#endif // MYITEM_H
