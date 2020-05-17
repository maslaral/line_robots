#include "pathline.h"
#include <QString>
#include <QPoint>
#include <QRectF>
#include <QLineF>
#include <QPolygonF>
#include <QGraphicsPolygonItem>

pathLine* pathLine::makeLine(QString lineType, QPoint location, QRectF bounds){
    if (lineType=="Left Line") {
        return new west(location, bounds);
    } else if (lineType=="Right Line") {
        return new east(location, bounds);
    } else if (lineType=="Up Line") {
        return new north(location, bounds);
    } else if (lineType=="Down Line") {
        return new south(location, bounds);
    }
    return nullptr;
}

QGraphicsPolygonItem* pathLine::makeArrow(QPoint location, int bearing){
    QGraphicsPolygonItem *newArrowHead;
    QPolygonF arrow;
    arrow << QPointF(0, 0) << QPointF(10, 10) << QPointF(-10, 10);
    newArrowHead = new QGraphicsPolygonItem(arrow);
    newArrowHead->setRotation(bearing);
    newArrowHead->setBrush(Qt::SolidPattern);
    newArrowHead->setPos(location);
    return newArrowHead;
}


north::north(QPoint location, QRectF bounds){
    QPoint top;
    QPoint bottom;
    QGraphicsPolygonItem* myArrowHead;

    top.setX(location.x());
    top.setY(bounds.top());
    bottom.setX(location.x());
    bottom.setY(bounds.bottom());
    this->setLine(QLineF(bottom,top));

    top.setY(top.y()-5);
    myArrowHead = makeArrow(top, 0);
    myArrowHead->setParentItem(this);
}

south::south(QPoint location, QRectF bounds){
    QPoint top;
    QPoint bottom;
    QGraphicsPolygonItem* myArrowHead;

    top.setX(location.x());
    top.setY(bounds.top());
    bottom.setX(location.x());
    bottom.setY(bounds.bottom());
    this->setLine(QLineF(top,bottom));

    bottom.setY(bottom.y()+5);
    myArrowHead = makeArrow(bottom, 180);
    myArrowHead->setParentItem(this);
}

west::west(QPoint location, QRectF bounds){
    QPoint left;
    QPoint right;
    QGraphicsPolygonItem* myArrowHead;

    left.setX(bounds.left());
    left.setY(location.y());
    right.setX(bounds.right());
    right.setY(location.y());
    this->setLine(QLineF(right,left));

    left.setX(left.x()-5);
    myArrowHead = makeArrow(left, 270);
    myArrowHead->setParentItem(this);
}

east::east(QPoint location, QRectF bounds){
    QPoint left;
    QPoint right;
    QGraphicsPolygonItem* myArrowHead;

    left.setX(bounds.left());
    left.setY(location.y());
    right.setX(bounds.right());
    right.setY(location.y());
    this->setLine(QLineF(left,right));

    right.setX(right.x()+5);
    myArrowHead = makeArrow(right, 90);
    myArrowHead->setParentItem(this);
}
