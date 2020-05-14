#ifndef ROBOT_H
#define ROBOT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Robot : public QGraphicsItem
{
public:
    explicit Robot(int, int);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setSpeed(double);
protected:
   void advance(int phase);

private:
    qreal angle;
    qreal speed;
    int x;
    int y;
    void DoCollision();
};

#endif // MYITEM_H
