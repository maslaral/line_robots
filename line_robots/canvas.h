#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMenu>
#include <QPoint>
#include <robot.h>
#include <QMessageBox>
#include <QInputDialog>
#include "pathline.h"


class Canvas : public QGraphicsScene
{
public:
    explicit Canvas(QMenu *itemMenu, QObject *parent = nullptr);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void errorMsg(int error);
    double setSpeedBox();

private:
    const int LINE_SEARCH_RADIUS = 30;
    const int ROBOT_SEARCH_RADIUS = 15;
    QGraphicsLineItem* detectLine(int *x, int *y);
    bool detectRobot(int *x, int *y);
    QMenu *myItemMenu;
    bool inBounds(QPoint checkPixel, int buffer);
    double roboticSpeed;
    int tempSpeed;
};

#endif // CANVAS_H
