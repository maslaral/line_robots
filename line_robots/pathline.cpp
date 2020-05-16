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

north::north(QPoint location, QRectF bounds){
    QPoint top;
    QPoint bottom;

    top.setX(location.x());
    top.setY(bounds.top());
    bottom.setX(location.x());
    bottom.setY(bounds.bottom());
    this->setLine(QLineF(bottom,top));
    QPolygonF arrow;
    arrow << QPointF(0, 0) << QPointF(10, 10) << QPointF(-10, 10);
    QGraphicsPolygonItem *arrowObject = new QGraphicsPolygonItem(arrow,this);
    arrowObject->setBrush(Qt::SolidPattern);
    arrowObject->setPos(location.x(),bounds.top()-5);
}

south::south(QPoint location, QRectF bounds){
    QPoint top;
    QPoint bottom;
    top.setX(location.x());
    top.setY(bounds.top());
    bottom.setX(location.x());
    bottom.setY(bounds.bottom());
    this->setLine(QLineF(top,bottom));
    QPolygonF arrow;
    arrow << QPointF(0, 0) << QPointF(10, -10) << QPointF(-10, -10);
    QGraphicsPolygonItem *arrowObject = new QGraphicsPolygonItem(arrow,this);
    arrowObject->setBrush(Qt::SolidPattern);
    arrowObject->setPos(location.x(),bounds.bottom()+5);
}

west::west(QPoint location, QRectF bounds){
    QPoint left;
    QPoint right;
    left.setX(bounds.left());
    left.setY(location.y());
    right.setX(bounds.right());
    right.setY(location.y());
    this->setLine(QLineF(right,left));
    QPolygonF arrow;
    arrow << QPointF(0, 0) << QPointF(10, -10) << QPointF(10, 10);
    QGraphicsPolygonItem *arrowObject = new QGraphicsPolygonItem(arrow,this);
    arrowObject->setBrush(Qt::SolidPattern);
    arrowObject->setPos(bounds.left()-5,location.y());
}

east::east(QPoint location, QRectF bounds){
    QPoint left;
    QPoint right;
    left.setX(bounds.left());
    left.setY(location.y());
    right.setX(bounds.right());
    right.setY(location.y());
    this->setLine(QLineF(left,right));
    QPolygonF arrow;
    arrow << QPointF(0, 0) << QPointF(-10, -10) << QPointF(-10, 10);
    QGraphicsPolygonItem *arrowObject = new QGraphicsPolygonItem(arrow,this);
    arrowObject->setBrush(Qt::SolidPattern);
    arrowObject->setPos(bounds.right()+5,location.y());
}
