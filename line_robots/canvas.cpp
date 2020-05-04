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
    // vertical line
    if (event->button() == Qt::LeftButton){
        x = event->scenePos().x();
        y = event->scenePos().y();


        line = new QGraphicsLineItem(QLineF(x, 0, x, 466));
        line->setPen(QPen(Qt::black, 10));
        addItem(line);
    }
    // horizontal line
    if (event->button() == Qt::RightButton){
        x = event->scenePos().x();
        y = event->scenePos().y();

        test = QLineF(180, y, 170+554, y);
        line = new QGraphicsLineItem(QLineF(180, y, 160+554, y));
        qDebug() << "X: " << x << ", Y:" << y;
        qDebug() << test.length();
        line->setPen(QPen(Qt::black, 10));
        addItem(line);
    }

}
