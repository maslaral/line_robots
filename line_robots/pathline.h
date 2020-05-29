#ifndef PATHLINE_H
#define PATHLINE_H

#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QRectF>
#include <QWidget>
#include <functional>

class pathLine : public QGraphicsLineItem
{
protected:
    QGraphicsPolygonItem *makeArrow(QPoint Location, int bearing);
    void adjustInlineSpeeds(QList<QGraphicsItem *> *siblingRobots, std::function<int(int,int)> distance);
    void removeNonRobots(QList<QGraphicsItem *> *siblings);

public:
    static pathLine *makeLine(QString lineType, QPoint location, QRectF bounds);
    virtual QPointF getSnapPoint(QPointF nearPoint) = 0;
};

class north : public pathLine {

public:
    north(QPoint location, QRectF bounds);
    QPointF getSnapPoint(QPointF nearPoint);
protected:
    void advance(int phase);
};

class south : public pathLine {

public:
    south(QPoint location, QRectF bounds);
    QPointF getSnapPoint(QPointF nearPoint);
protected:
    void advance(int phase);
};

class east : public pathLine {

public:
    east(QPoint location, QRectF bounds);
    QPointF getSnapPoint(QPointF nearPoint);
protected:
    void advance(int phase);
};

class west : public pathLine {

public:
    west(QPoint location, QRectF bounds);
    QPointF getSnapPoint(QPointF nearPoint);
protected:
    void advance(int phase);
};

#endif // PATHLINE_H
