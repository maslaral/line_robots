#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMenu>
#include <QPoint>
#include <QMessageBox>
#include <robot.h>


class Canvas : public QGraphicsScene
{
public:
    explicit Canvas(QMenu *itemMenu, QObject *parent = nullptr);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void addVArrow(QPoint p2);
    void addHArrow(QPoint p2);
    void errorMsg(int error);

private:
    QMenu *myItemMenu;
    QGraphicsLineItem *line;        // place holder for custom line object
    QPolygonF triangle;
    QGraphicsPolygonItem arrow;

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
