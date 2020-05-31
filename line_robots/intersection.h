#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QGraphicsItem>
#include "robot.h"
#include "pathline.h"

class intersection : public QGraphicsItem
{
public:
    intersection();
    void checkClear();
    void setCross(pathLine *crossingLine);
private:
    Robot *blocker;
    pathLine *otherLine;
};

#endif // INTERSECTION_H
