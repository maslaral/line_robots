#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMenu>
#include <QPoint>

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
};

#endif // CANVAS_H
