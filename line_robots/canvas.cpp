#include "canvas.h"
#include "ui_mainwindow.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsItem>
#include <QMimeData>
#include <QPoint>
#include "pathline.h"

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

        int x = event->scenePos().x();
        int y = event->scenePos().y();

        if (dragObjectType.contains("Line")) {
             pathLine *newLine = pathLine::makeLine(dragObjectType,QPoint(x,y),this->sceneRect());
             newLine->setPen(QPen(Qt::black, 3));
             newLine->setAcceptDrops(true);
             addItem(newLine);
        } else if (dragObjectType.contains("Robot")) { // dragging a robot object onto the canvas
           QGraphicsLineItem *lineDroppedOn = detectLine(&x,&y);
           if (lineDroppedOn){
               Robot* newRobot = new Robot(x + 10, y - 10, lineDroppedOn, dragObjectType);
               newRobot->setSpeed(10);
               addItem(newRobot);
           } else {
               event->ignore();
           }
        }
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

QGraphicsLineItem* Canvas::detectLine(int *x, int *y){
    QGraphicsItem *curItem;
    QGraphicsLineItem *line;

    // TODO: Add some type of error statement if the user tries to place
    // the line it doesn't let them
    // if statement ensure not placing too close to boundary to start
    if ((*x > 30 && *x < 524) && (*y > 30 && *y < 436)) {
    // detect line in 60px radius of drop location
        for (int i = -30; i <= 30; i++) {
            for (int j = -30; j <= 30; j++) {
                curItem = itemAt(*x + i, *y + j, QTransform());
                if ((line = dynamic_cast<QGraphicsLineItem*>(curItem))) {
                    *x+=i; //adjust coordinates
                    *y+=j;
                    return line;
                }
           }
        }
    }
    return nullptr; //so we can detect found state in caller
}

