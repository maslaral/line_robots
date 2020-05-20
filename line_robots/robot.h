#ifndef ROBOT_H
#define ROBOT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "pathline.h"

class Robot : public QGraphicsItem
{
public:
    explicit Robot(int, int, QGraphicsLineItem*, QString);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setSpeed(double);
    double getSpeed();
protected:
   void advance(int phase);
   void boundary();
   void collisionDetectionNorth();
   void collisionDetectionSouth();
   void collisionDetectionEast();
   void collisionDetectionWest();

private:
    qreal angle;
    qreal speed;
    int x;
    int y;
    QString type;
    QGraphicsLineItem* line;
    void DoCollision();
};

#endif // MYITEM_H
