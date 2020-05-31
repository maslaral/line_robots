#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QGraphicsItem>
#include "robot.h"
#include "pathline.h"

class intersection : public QGraphicsItem
{
public:
    intersection();
    ~intersection();
    void checkClear(Robot *thisPrev);
    void setCross(pathLine *crossingLine);
    void clean();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
    Robot *blocker;
    pathLine *otherLine;
    Robot *makeBlocker(pathLine *myLine);
    const int BLOCK_RADIUS = 60;
};

#endif // INTERSECTION_H
