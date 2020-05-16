#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMenu>
#include <QPoint>
#include <robot.h>
#include "pathline.h"


class Canvas : public QGraphicsScene
{
public:
    explicit Canvas(QMenu *itemMenu, QObject *parent = nullptr);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private:
    QGraphicsLineItem* detectLine(int *x, int *y);
    QMenu *myItemMenu;
    pathLine *line;        // place holder for custom line object
    //QPolygonF triangle;
    //QGraphicsPolygonItem arrow;

    QPoint point1;
    QPoint point2;
    int x, y;
    int i, j;
    int tmp;

    int height = 466;
    int width = 554;
    QLineF test;
};

#endif // CANVAS_H
