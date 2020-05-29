#include "pathline.h"
#include "robot.h"
#include <QGraphicsPolygonItem>
#include <QLineF>
#include <QPoint>
#include <QPolygonF>
#include <QRectF>
#include <QString>
#include <QList>
#include <QDebug>

pathLine *pathLine::makeLine(QString lineType, QPoint location, QRectF bounds)
{
    if (lineType == "Left Line") {
        return new west(location, bounds);
    } else if (lineType == "Right Line") {
        return new east(location, bounds);
    } else if (lineType == "Up Line") {
        return new north(location, bounds);
    } else if (lineType == "Down Line") {
        return new south(location, bounds);
    }
    return nullptr;
}

QGraphicsPolygonItem *pathLine::makeArrow(QPoint location, int bearing)
{
    QGraphicsPolygonItem *newArrowHead;
    QPolygonF arrow;
    arrow << QPointF(0, 0) << QPointF(10, 10) << QPointF(-10, 10);
    newArrowHead = new QGraphicsPolygonItem(arrow);
    newArrowHead->setRotation(bearing);
    newArrowHead->setBrush(Qt::SolidPattern);
    newArrowHead->setPos(location);
    return newArrowHead;
}


//iterate through a list of sibling robots on this line, and send each robot the distance to the robot ahead
void pathLine::adjustInlineSpeeds(QList<QGraphicsItem *> *siblingRobots, std::function<int(int,int)> distance)
{
    int clearAhead;
    QGraphicsItem *ahead = siblingRobots->last();
    for (auto it = siblingRobots->begin(); it != siblingRobots->end(); ++it)
    {
        if (ahead->pos().y() == (*it)->pos().y())
        {
            clearAhead = distance(ahead->pos().x(), (*it)->pos().x());
        }
        else
        {
            clearAhead = distance(ahead->pos().y(), (*it)->pos().y());
        }
        qDebug() << (*it)->pos() << ahead->pos() << clearAhead;
        dynamic_cast<Robot *>(*it)->avoidLineCollision(dynamic_cast<Robot *>(ahead),clearAhead);
        ahead = *it;
    }
}

//delete all non-robots from a list of graphics items
void pathLine::removeNonRobots(QList<QGraphicsItem *> *mixedSiblings)
{
    Robot *aRobot;
    auto place = mixedSiblings->begin();
    while (place != mixedSiblings->end()) //remove all non-robots from list
    {
        if (!(aRobot = dynamic_cast<Robot *>(*place))) {
            place = mixedSiblings->erase(place);
        }
        else
        {
            ++place;
        }
    }
}


north::north(QPoint location, QRectF bounds)
{
    QPoint top;
    QPoint bottom;
    QGraphicsPolygonItem *myArrowHead;

    top.setX(location.x());
    top.setY(bounds.top());
    bottom.setX(location.x());
    bottom.setY(bounds.bottom());
    this->setLine(QLineF(bottom, top));

    top.setY(top.y() - 5);
    myArrowHead = makeArrow(top, 0);
    myArrowHead->setParentItem(this);
}

QPointF north::getSnapPoint(QPointF nearPoint){
    return QPointF(this->line().x1(), nearPoint.y());
}

// adjust the speed of all child robots of this line on the prep phase of advance
void north::advance(int phase) {
    if (!phase)
    {
        //list the children
        QList<QGraphicsItem *> siblings = this->childItems();

        //define ordering function to sort the robots by travel direction
        auto compare = [](QGraphicsItem *i, QGraphicsItem *j)->bool{return i->pos().y() < j->pos().y();};

        removeNonRobots(&siblings);

        std::sort(siblings.begin(),siblings.end(),compare); // sort robots in travel direction

        this->wrapRobots(&siblings);

        if (siblings.size() > 1) //if there are multiple robots on this line, have the robots radar each other
        {
            auto clearAhead = [this](int i, int j)->int{ //define distance calculation for this direction
                int distance = j - i;
                distance += this->scene()->sceneRect().bottom();
                distance %= static_cast<int>(this->scene()->sceneRect().bottom());
                return distance;
            };
            adjustInlineSpeeds(&siblings, clearAhead);         }
    }
}

void north::wrapRobots(QList<QGraphicsItem *> *siblingRobots)
{
    auto it = siblingRobots->begin();
    while (it != siblingRobots->end() && (*it)->pos().y() < this->line().p2().y())
    {
        wrapBuffer.push_back(*it);
        siblingRobots->erase(it);
    }
    if (!wrapBuffer.empty()) {
        int requiredGap = dynamic_cast<Robot *>(wrapBuffer.front())->getBufferSpace();
        if (siblingRobots->empty())
        {
            siblingRobots->append(dynamic_cast<QGraphicsItem *>(wrapBuffer.front()));
            wrapBuffer.pop_front();
            siblingRobots->last()->setPos(this->line().p1());
        }
        else if (siblingRobots->last()->pos().y() < this->scene()->sceneRect().bottom() - requiredGap)
        {
            siblingRobots->append(dynamic_cast<QGraphicsItem *>(wrapBuffer.front()));
            wrapBuffer.pop_front();
            siblingRobots->last()->setPos(this->line().p1());
        }
    }
}

south::south(QPoint location, QRectF bounds)
{
    QPoint top;
    QPoint bottom;
    QGraphicsPolygonItem *myArrowHead;

    top.setX(location.x());
    top.setY(bounds.top());
    bottom.setX(location.x());
    bottom.setY(bounds.bottom());
    this->setLine(QLineF(top, bottom));

    bottom.setY(bottom.y() + 5);
    myArrowHead = makeArrow(bottom, 180);
    myArrowHead->setParentItem(this);
}

QPointF south::getSnapPoint(QPointF nearPoint){
    return QPointF(this->line().x1(), nearPoint.y());
}

// adjust the speed of all child robots of this line on the prep phase of advance
void south::advance(int phase) {
    if (!phase)
    {
        //list the children
        QList<QGraphicsItem *> siblings = this->childItems();

        //define ordering function to sort the robots by travel direction
        auto compare = [](QGraphicsItem *i, QGraphicsItem *j)->bool{return i->pos().y() > j->pos().y();};

        removeNonRobots(&siblings);

        std::sort(siblings.begin(),siblings.end(),compare); // sort robots in travel direction

        this->wrapRobots(&siblings);

        if (siblings.size() > 1) //if there are multiple robots on this line, have the robots radar each other
        {
            auto clearAhead = [this](int i, int j)->int{ //define distance calculation for this direction
                int distance = i - j;
                distance += this->scene()->sceneRect().bottom();
                distance %= static_cast<int>(this->scene()->sceneRect().bottom());
                return distance;
            };
            adjustInlineSpeeds(&siblings, clearAhead);        }
    }
}

void south::wrapRobots(QList<QGraphicsItem *> *siblingRobots)
{
    auto it = siblingRobots->begin();
    while (it != siblingRobots->end() && (*it)->pos().y() > this->line().p2().y())
    {
        wrapBuffer.push_back(*it);
        siblingRobots->erase(it);
    }
    if (!wrapBuffer.empty()) {
        int requiredGap = dynamic_cast<Robot *>(wrapBuffer.front())->getBufferSpace();
        if (siblingRobots->empty())
        {
            siblingRobots->append(dynamic_cast<QGraphicsItem *>(wrapBuffer.front()));
            wrapBuffer.pop_front();
            siblingRobots->last()->setPos(this->line().p1());
        }
        else if (siblingRobots->last()->pos().y() > this->scene()->sceneRect().top() + requiredGap)
        {
            siblingRobots->append(dynamic_cast<QGraphicsItem *>(wrapBuffer.front()));
            wrapBuffer.pop_front();
            siblingRobots->last()->setPos(this->line().p1());
        }
    }
}

west::west(QPoint location, QRectF bounds)
{
    QPoint left;
    QPoint right;
    QGraphicsPolygonItem *myArrowHead;

    left.setX(bounds.left());
    left.setY(location.y());
    right.setX(bounds.right());
    right.setY(location.y());
    this->setLine(QLineF(right, left));

    left.setX(left.x() - 5);
    myArrowHead = makeArrow(left, 270);
    myArrowHead->setParentItem(this);
}

QPointF west::getSnapPoint(QPointF nearPoint){
    return QPointF(nearPoint.x(), this->line().y1());
}

// adjust the speed of all child robots of this line on the prep phase of advance
void west::advance(int phase) {
    if (!phase)
    {
        //list the children
        QList<QGraphicsItem *> siblings = this->childItems();

        //define ordering function to sort the robots by travel direction
        auto compare = [](QGraphicsItem *i, QGraphicsItem *j)->bool{return i->pos().x() < j->pos().x();};

        removeNonRobots(&siblings);

        std::sort(siblings.begin(),siblings.end(),compare); // sort robots in travel direction

        this->wrapRobots(&siblings);

        if (siblings.size() > 1) //if there are multiple robots on this line, have the robots radar each other
        {
            auto clearAhead = [this](int i, int j)->int{ //define distance calculation for this direction
                int distance = j - i;
                distance += this->scene()->sceneRect().right();
                distance %= static_cast<int>(this->scene()->sceneRect().right());
                return distance;
            };
            adjustInlineSpeeds(&siblings, clearAhead);        }
    }
}

void west::wrapRobots(QList<QGraphicsItem *> *siblingRobots)
{
    auto it = siblingRobots->begin();
    while (it != siblingRobots->end() && (*it)->pos().x() < this->line().p2().x())
    {
        wrapBuffer.push_back(*it);
        siblingRobots->erase(it);
    }
    if (!wrapBuffer.empty()) {
        int requiredGap = dynamic_cast<Robot *>(wrapBuffer.front())->getBufferSpace();
        if (siblingRobots->empty())
        {
            siblingRobots->append(dynamic_cast<QGraphicsItem *>(wrapBuffer.front()));
            wrapBuffer.pop_front();
            siblingRobots->last()->setPos(this->line().p1());
        }
        else if (siblingRobots->last()->pos().x() < this->scene()->sceneRect().right() - requiredGap)
        {
            siblingRobots->append(dynamic_cast<QGraphicsItem *>(wrapBuffer.front()));
            wrapBuffer.pop_front();
            siblingRobots->last()->setPos(this->line().p1());
        }
    }
}

east::east(QPoint location, QRectF bounds)
{
    QPoint left;
    QPoint right;
    QGraphicsPolygonItem *myArrowHead;

    left.setX(bounds.left());
    left.setY(location.y());
    right.setX(bounds.right());
    right.setY(location.y());
    this->setLine(QLineF(left, right));

    right.setX(right.x() + 5);
    myArrowHead = makeArrow(right, 90);
    myArrowHead->setParentItem(this);
}

QPointF east::getSnapPoint(QPointF nearPoint){
    return QPointF(nearPoint.x(), this->line().y1());
}

// adjust the speed of all child robots of this line on the prep phase of advance
void east::advance(int phase) {
    if (!phase)
    {
        //list the children
        QList<QGraphicsItem *> siblings = this->childItems();

        //define ordering function to sort the robots by travel direction
        auto compare = [](QGraphicsItem *i, QGraphicsItem *j)->bool{return i->pos().x() > j->pos().x();};

        removeNonRobots(&siblings);

        std::sort(siblings.begin(),siblings.end(),compare); // sort robots in travel direction

        this->wrapRobots(&siblings);

        if (siblings.size() > 1) //if there are multiple robots on this line, have the robots radar each other
        {
            auto clearAhead = [this](int i, int j)->int{ //define distance calculation for this direction
                int distance = i - j;
                distance += this->scene()->sceneRect().right();
                distance %= static_cast<int>(this->scene()->sceneRect().right());
                return distance;
            };
            adjustInlineSpeeds(&siblings, clearAhead);
        }
    }
}

void east::wrapRobots(QList<QGraphicsItem *> *siblingRobots)
{
    auto it = siblingRobots->begin();
    while (it != siblingRobots->end())
    {
        if ((*it)->pos().x() > this->line().p2().x())
        {
            wrapBuffer.push_back(*it);
            qDebug() << (*it)->pos();
            it = siblingRobots->erase(it);
        }
        else
        {
            ++it;
        }
    }
    if (!wrapBuffer.empty()) {
        int requiredGap = dynamic_cast<Robot *>(wrapBuffer.front())->getBufferSpace();
        if (siblingRobots->empty())
        {
            siblingRobots->append(dynamic_cast<QGraphicsItem *>(wrapBuffer.front()));
            wrapBuffer.pop_front();
            siblingRobots->last()->setPos(this->line().p1());
        }
        else if (siblingRobots->last()->pos().x() > this->scene()->sceneRect().left() + requiredGap)
        {
            qDebug() << "wrap";
            siblingRobots->append(dynamic_cast<QGraphicsItem *>(wrapBuffer.front()));
            wrapBuffer.pop_front();
            siblingRobots->last()->setPos(this->line().p1());
        }
    }
}
