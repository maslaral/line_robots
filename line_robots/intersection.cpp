#include "intersection.h"

intersection::intersection()
{
    blocker = nullptr;
    otherLine = nullptr;
}

void intersection::checkClear()
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
