#include "intersection.h"

intersection::intersection()
{
    blocker = nullptr;
    otherLine = nullptr;
}

void intersection::checkClear(Robot *thisPrev)
{
    if(blocker == nullptr){
        //check this line
        //check other line
    }
    else
    {
        //check blocker's parent
    }
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
