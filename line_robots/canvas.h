#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMenu>
#include <QPoint>
#include <robot.h>
#include <QMessageBox>
#include "pathline.h"


class Canvas : public QGraphicsScene
{
public:
    explicit Canvas(QMenu *itemMenu, QObject *parent = nullptr);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void errorMsg(int error);

private:
    const int SEARCH_RADIUS = 30;
    QGraphicsLineItem* detectLine(int *x, int *y);
    QMenu *myItemMenu;
};

#endif // CANVAS_H
