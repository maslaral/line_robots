#include "intersection.h"
#include <QDebug>

intersection::intersection()
{
    blocker = nullptr;
    otherLine = nullptr;
}

void intersection::checkClear(Robot *thisPrev)
{
    QPoint place = this->pos().toPoint();
    QGraphicsItem *closestCrosser = this->otherLine->getPrevRobot(place);

}

void intersection::setCross(pathLine *crossingLine)
{
    otherLine = crossingLine;
}

void intersection::clean()
{
    if(blocker !=  nullptr)
    {
        blocker->setParentItem(nullptr);
        delete blocker;
    }

}

QRectF intersection::boundingRect() const
{
    return QRect(-10, -10, 20, 20);
}

void intersection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}
