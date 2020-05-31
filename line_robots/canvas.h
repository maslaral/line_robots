#ifndef CANVAS_H
#define CANVAS_H

#include "pathline.h"
#include "addline.h"
#include "addrobot.h"
#include <robot.h>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
#include <QPoint>
#include <QUndoStack>
#include <QObject>

class Canvas : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Canvas(QMenu *itemMenu, QObject *parent = nullptr);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void errorMsg(int error);
    double setSpeedBox();
    QUndoStack *undoStack = nullptr;
    bool setRobotProperties();

private:
    const int LINE_SEARCH_RADIUS = 30;
    const int ROBOT_SEARCH_RADIUS = 30;
    pathLine *detectLine(int *x, int *y);
    bool detectRobot(int *x, int *y);
    QMenu *myItemMenu;
    bool inBounds(QPoint checkPixel, int buffer);
    int roboticSpeed;
    QColor roboticColor;
    void pollIntersections();
public slots:
    void tick();
};

#endif // CANVAS_H
