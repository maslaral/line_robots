#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMenu>
#include <QPoint>
#include <MyRobot.h>
#include "ui_mainwindow.h"


class Canvas : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Canvas(QMenu *itemMenu, QObject *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QMenu *myItemMenu;
    QGraphicsLineItem *line;        // place holder for custom line obj

    int x, y;
    QLineF test;
};

#endif // CANVAS_H
