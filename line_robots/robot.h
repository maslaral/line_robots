#ifndef MYROBOT_H
#define MYROBOT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class MyRobot : public QGraphicsItem
{
public:
    MyRobot();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setSpeed(double);
protected:
   void advance(int phase);

private:
    qreal angle;
    qreal speed;
    void DoCollision();
};

#endif // MYITEM_H
