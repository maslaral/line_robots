#ifndef PATHLINE_H
#define PATHLINE_H

#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QRectF>
#include <QWidget>
#include <functional>
#include <deque>

class pathLine : public QGraphicsLineItem
{
protected:
    QGraphicsPolygonItem *makeArrow(QPoint Location, int bearing);
    void adjustInlineSpeeds(QList<QGraphicsItem *> *siblingRobots, std::function<int(int,int)> distance);
    std::deque<QGraphicsItem *> wrapBuffer;
    virtual void wrapRobots(QList<QGraphicsItem *> *siblingRobots) = 0;
    QList<QGraphicsItem *> extractRobots(QList<QGraphicsItem *> mixedSiblings);
    QList<QGraphicsItem *> extractIntersections(QList<QGraphicsItem *> mixedSiblings);
    void removeArrow(QList<QGraphicsItem *> *mixedSiblings);
    virtual QList<QGraphicsItem *> getSortedChildren() = 0;
public:
    static pathLine *makeLine(QString lineType, QPoint location, QRectF bounds);
    virtual QPointF getSnapPoint(QPointF nearPoint) = 0;
    void checkIntersections();
    void addIntersections();
    void cleanIntersections();
};

class north : public pathLine {

public:
    north(QPoint location, QRectF bounds);
    QPointF getSnapPoint(QPointF nearPoint);
protected:
    void advance(int phase);
    void wrapRobots(QList<QGraphicsItem *> *siblingRobots);
    QList<QGraphicsItem *> getSortedChildren();
};

class south : public pathLine {

public:
    south(QPoint location, QRectF bounds);
    QPointF getSnapPoint(QPointF nearPoint);
protected:
    void advance(int phase);
    void wrapRobots(QList<QGraphicsItem *> *siblingRobots);
    QList<QGraphicsItem *> getSortedChildren();
};

class east : public pathLine {

public:
    east(QPoint location, QRectF bounds);
    QPointF getSnapPoint(QPointF nearPoint);
protected:
    void advance(int phase);
    void wrapRobots(QList<QGraphicsItem *> *siblingRobots);
    QList<QGraphicsItem *> getSortedChildren();
};

class west : public pathLine {

public:
    west(QPoint location, QRectF bounds);
    QPointF getSnapPoint(QPointF nearPoint);
protected:
    void advance(int phase);
    void wrapRobots(QList<QGraphicsItem *> *siblingRobots);
    QList<QGraphicsItem *> getSortedChildren();
};

#endif // PATHLINE_H
