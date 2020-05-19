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
             newLine->setZValue(-1);
             addItem(newLine);
        } else if (dragObjectType.contains("Robot")) { // dragging a robot object onto the canvas
           QGraphicsLineItem *lineDroppedOn = detectLine(&x,&y);
           if (lineDroppedOn){
               Robot* newRobot = new Robot(x + 10, y - 10, lineDroppedOn, dragObjectType);
               newRobot->setSpeed(10);
               newRobot->setZValue(1);
               addItem(newRobot);
           }
           else if (lineDroppedOn == nullptr && items().count() == 0){ // attempting to add robot with no lines in the canvas
               event->ignore();
               errorMsg(0);
           } else { // attempting to add robot add without hovering over a line
               event->ignore();
               errorMsg(1);
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
    int maxX = this->sceneRect().width()-SEARCH_RADIUS;
    int maxY = this->sceneRect().height()-SEARCH_RADIUS;
    if ((*x > SEARCH_RADIUS && *x < maxX) && (*y > SEARCH_RADIUS && *y < maxY)) {
    // detect line in 60px radius of drop location
        for (int i = -SEARCH_RADIUS; i <= SEARCH_RADIUS; i++) {
            for (int j = -SEARCH_RADIUS; j <= SEARCH_RADIUS; j++) {
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

// Shows a pop up error message, press 'ok' to close
void Canvas::errorMsg(int error)
{
    QMessageBox msgBox;
    switch(error){
    case 0:
        msgBox.setText("Error: Please add a line before adding a robot.");
        break;
    case 1:
        msgBox.setText("Error: Please place the robot on top of a line.");
        break;
    case 2:
        msgBox.setText("Error: Out of bounds placement.");
        break;
    case 3:
        msgBox.setText("Error: Line is too close to another line.");
        break;
    case 4:
        msgBox.setText("Error: Robot is too close to another robot.");
        break;
    }
    msgBox.exec();
}
