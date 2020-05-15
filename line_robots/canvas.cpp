#include "canvas.h"
#include "ui_mainwindow.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsItem>
#include <QMimeData>

// canvas height = 466, width = 554
Canvas::Canvas(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
}

void Canvas::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
            event->acceptProposedAction();
    } else {
            event->ignore();
    }
}

void Canvas::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Canvas::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {

        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QString dragObjectType = event->mimeData()->text();

        x = event->scenePos().x();
        y = event->scenePos().y();

        if (dragObjectType == "Left Line" || dragObjectType == "Right Line") {
            point1.setX(0);
            point1.setY(y);
            point2.setX(width);
            point2.setY(y);

            // pointing left
            if (dragObjectType == "Left Line"){
                line = new QGraphicsLineItem(QLineF(point2, point1));
                line->setPen(QPen(Qt::black, 3));
                addItem(line);
                addHArrow(point1);
            }
            //pointing right
            else{
                line = new QGraphicsLineItem(QLineF(point1, point2));
                line->setPen(QPen(Qt::black, 3));
                addItem(line);
                addHArrow(point2);
            }
        }

        // vertical lines
        else if (dragObjectType == "Up Line" || dragObjectType == "Down Line") {
            point1.setX(x);
            point1.setY(height);
            point2.setX(x);
            point2.setY(0);

            // pointing up
            if (dragObjectType == "Up Line"){
                line = new QGraphicsLineItem(QLineF(point1, point2));
                line->setPen(QPen(Qt::black, 3));
                addItem(line);
                addVArrow(point2);
            }
            // pointing down
            else{
                line = new QGraphicsLineItem(QLineF(point2, point1));
                line->setPen(QPen(Qt::black, 3));
                addItem(line);
                addVArrow(point1);
            }
        }

        else if (dragObjectType == "Circle Robot") {
            Robot* newRobot = new Robot(x, y);
            newRobot->setSpeed(10);
            addItem(newRobot);
        }

        event->acceptProposedAction();
    } else {
        event->ignore();
    }

    // for checking end points of lines
    j=0;
        for (i=5; i<items().count(); i++){
            if (items().at(i)->type() == 6){
                j++;
                QGraphicsLineItem *listLine = dynamic_cast<QGraphicsLineItem *>(items().at(i));
                qDebug() << "Line " << j << "p1: " << listLine->line().p1() << "\tp2: " << listLine->line().p2();
                if (listLine->line().p2().x()-listLine->line().p1().x() < 0){
                    qDebug() << "West";
                }
                else if (listLine->line().p2().x()-listLine->line().p1().x() > 0){
                    qDebug() << "East";
                }
                else if (listLine->line().p2().y()-listLine->line().p1().y() < 0){
                    qDebug() << "North";
                }
                else{
                    qDebug() << "South";
                }
            }
        }
        qDebug() << "****************";
}

void Canvas::addVArrow(QPoint p2)
{
    tmp = p2.x();
    triangle.clear();

    // pointing down
    if (p2.y() == height){
        triangle << QPointF(tmp, height) << QPointF(tmp-10, height-10) << QPointF(tmp+10, height-10)/* << QPointF(tmp, 466)*/;
    }
    // pointing up
    else if (p2.y() == 0){
        triangle << QPointF(tmp - 10, 10) << QPointF(tmp + 10, 10) << QPointF(tmp, 0);
    }
    addPolygon(triangle, QPen(Qt::black), QBrush(Qt::SolidPattern));
}

void Canvas::addHArrow(QPoint p2)
{
    tmp = p2.y();
    triangle.clear();

    // pointing right
    if (p2.x() == width){
        triangle << QPointF(width, tmp) << QPointF(width-10, y-10) << QPointF(width-10, y+10)/* << QPointF(tmp, 466)*/;
    }
    //pointing left
    else if (p2.x() == 0){
        triangle << QPointF(0,tmp) << QPointF(10, tmp+10) << QPointF(10, tmp-10);
    }
    addPolygon(triangle, QPen(Qt::black), QBrush(Qt::SolidPattern));
}
