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
    Robot *closestCrosser = dynamic_cast<Robot *>(this->otherLine->getPrevRobot(place));
    if (thisPrev != nullptr || closestCrosser != nullptr) //do nothing if both are nullptr
    {
        if(thisPrev == nullptr) //place the blocker on this line if needed
        {
            if (otherLine->distance(this,closestCrosser) <= BLOCK_RADIUS)
            {
                blocker = makeBlocker(dynamic_cast<pathLine *>(this->parentItem()));
            }
        }
        else if (closestCrosser == nullptr) //place the blocker on other line if needed
        {
            if (dynamic_cast<pathLine *>(this->parentItem())->distance(this,thisPrev) <= BLOCK_RADIUS)
            {
                blocker = makeBlocker(otherLine);
            }
        }
        else //robots approaching from both directions; block farther away if needed
        {
            int thisDistance = dynamic_cast<pathLine *>(this->parentItem())->distance(this,thisPrev);
            int otherDistance = otherLine->distance(this,closestCrosser);
            if (thisDistance <= BLOCK_RADIUS && thisDistance <= otherDistance){
                blocker = makeBlocker(otherLine);
            }
            else if (otherDistance <= BLOCK_RADIUS && thisDistance <= otherDistance)
            {
                blocker = makeBlocker(dynamic_cast<pathLine *>(this->parentItem()));
            }
        }
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

        //dynamic_cast<QGraphicsItem *>(blocker)->setParentItem(nullptr);
        this->scene()->removeItem(dynamic_cast<QGraphicsItem *>(blocker));
        delete blocker;
        blocker = nullptr;
        qDebug() << "deleted blocker";
    }

}

//return a pointer to an invisible stationary robot to use to block intersection
Robot * intersection::makeBlocker(pathLine *myLine)
{
    Robot *newBlock = new Robot(this->pos().x(),this->pos().y(),myLine,"Square Robot");
    newBlock->setSpeed(0);
    newBlock->setVisible(false);
    newBlock->setParentItem(myLine);
    return newBlock;
}

QRectF intersection::boundingRect() const
{
    return QRect(-10, -10, 20, 20);
}

void intersection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

intersection::~intersection(){
    this->clean();
}
