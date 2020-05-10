#include "canvas.h"
#include "ui_mainwindow.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsItem>
#include <QMimeData>

// canvas height = 466, length 554
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

        // TODO: figure out how to utilize direction
        // gets the tooltip text that was passed via mimedata
        if (dragObjectType == "Left Line" || dragObjectType == "Right Line") {
            x = event->scenePos().x();
            y = event->scenePos().y();

            test = QLineF(180, y, 170 + 554, y);
            line = new QGraphicsLineItem(QLineF(180, y, 160 + 554, y));
            line->setPen(QPen(Qt::black, 3));
            addItem(line);
        } else {
            x = event->scenePos().x();
            y = event->scenePos().y();

            line = new QGraphicsLineItem(QLineF(x, 0, x, 466));
            line->setPen(QPen(Qt::black, 3));
            addItem(line);
        }
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}
