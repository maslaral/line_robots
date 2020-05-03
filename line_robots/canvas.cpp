#include "canvas.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsItem>

//canvas height = 466, length 554
Canvas::Canvas(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        x = event->scenePos().x();
        y = event->scenePos().y();

        // horizontal line
        line = new QGraphicsLineItem(QLineF(x, 0, x, 466));

        // vertical line
//        line = new QGraphicsLineItem(QLineF(0, y, 554, y));
        qDebug() << "X: " << x << ", Y:" << y;
        line->setPen(QPen(Qt::black, 10));
        addItem(line);
    }
}
