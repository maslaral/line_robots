#ifndef PATHLINE_H
#define PATHLINE_H

#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QRectF>
#include <QWidget>

class pathLine : public QGraphicsLineItem
{
protected:
    QGraphicsPolygonItem *makeArrow(QPoint Location, int bearing);

public:
    static pathLine *makeLine(QString lineType, QPoint location, QRectF bounds);
    virtual QPointF getSnapPoint(QPointF nearPoint) = 0;
};

class north : public pathLine {

public:
    north(QPoint location, QRectF bounds);
    QPointF getSnapPoint(QPointF nearPoint);
};

class south : public pathLine {

public:
    south(QPoint location, QRectF bounds);
    QPointF getSnapPoint(QPointF nearPoint);
};

class east : public pathLine {

public:
    east(QPoint location, QRectF bounds);
    QPointF getSnapPoint(QPointF nearPoint);
};

class west : public pathLine {

public:
    west(QPoint location, QRectF bounds);
    QPointF getSnapPoint(QPointF nearPoint);
};

#endif // PATHLINE_H
