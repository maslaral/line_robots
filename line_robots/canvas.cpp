#include "canvas.h"
#include "ui_mainwindow.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsItem>
#include <QMimeData>
#include <QPoint>
#include "pathline.h"
#include "pixelspiral.h"

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
               if (detectRobot(&x, &y)) {
                   event->ignore();
                   errorMsg(4);
               }
               else {
                   Robot* newRobot = new Robot(x + 10, y - 10, lineDroppedOn, dragObjectType);
                   newRobot->setZValue(1);
                   addItem(newRobot);
               }
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
    PixelSpiral search(this);
    QPoint temp(*x,*y);
    search.setStart(temp);
    search.setRadius(LINE_SEARCH_RADIUS);
    while(search.hasNext()) {
        temp = search.nextPixel();
        if (this->inBounds(temp, LINE_SEARCH_RADIUS)){
            curItem = itemAt(temp, QTransform());
            if ((line = dynamic_cast<QGraphicsLineItem*>(curItem))) {
                *x=temp.x();
                *y=temp.y();
                return line;
            }
        }
    }
    return nullptr;
}

bool Canvas::detectRobot(int *x, int *y){
    QGraphicsItem *curItem;
    Robot *robot;
    PixelSpiral search(this);
    QPoint temp(*x,*y);
    search.setStart(temp);
    search.setRadius(ROBOT_SEARCH_RADIUS);
    while(search.hasNext()) {
        temp = search.nextPixel();
        if (this->inBounds(temp, ROBOT_SEARCH_RADIUS)){
            curItem = itemAt(temp, QTransform());
            if ((robot = dynamic_cast<Robot*>(curItem))) {
                return true;
            }
        }
    }
    return false;
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

bool Canvas::inBounds(QPoint checkPixel, int buffer){
    if (checkPixel.x() >= 0 + buffer && checkPixel.x() <= this->sceneRect().width()-buffer &&
            checkPixel.y() >= 0 + buffer && checkPixel.y() <= this->sceneRect().height()-buffer) {
        return true;
    } else {
        return false;
    }
}
