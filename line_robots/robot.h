#ifndef ROBOT_H
#define ROBOT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Robot : public QGraphicsItem
{
public:
    Robot();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
   void advance(int phase);

private:
    qreal angle;
    qreal speed;
    void DoCollision();
    QPointF location;
};

#endif // MYITEM_H
