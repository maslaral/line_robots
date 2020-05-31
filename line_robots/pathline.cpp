#include "pathline.h"
#include "robot.h"
#include "intersection.h"
#include "canvas.h"
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
        //qDebug() << (*it)->pos() << ahead->pos() << clearAhead;
        dynamic_cast<Robot *>(*it)->avoidLineCollision(dynamic_cast<Robot *>(ahead),clearAhead);
        ahead = *it;
    }
}


//extract just the robots from a mixed list of children
QList<QGraphicsItem *> pathLine::extractRobots(QList<QGraphicsItem *> mixedSiblings)
{
    QList<QGraphicsItem *> robotsOnly;
    Robot *aRobot;
    for (auto it = mixedSiblings.begin(); it != mixedSiblings.end(); ++it)
    {
        if((aRobot = dynamic_cast<Robot *>(*it)))
        {
            robotsOnly.append(*it);
        }
    }
    return robotsOnly;
}

//extract the intersections from a mixed list of children
QList<QGraphicsItem *> pathLine::extractIntersections(QList<QGraphicsItem *> mixedSiblings)
{
    QList<QGraphicsItem *> intersectionsOnly;
    intersection *anIntersection;
    for (auto it = mixedSiblings.begin(); it != mixedSiblings.end(); ++it)
    {
        if((anIntersection = dynamic_cast<intersection *>(*it)))
        {
           intersectionsOnly.append(*it);
        }
    }
    return intersectionsOnly;
}

// remove the arrow from a list of the lines children
void pathLine::removeArrow(QList<QGraphicsItem *> *mixedSiblings)
{
    QGraphicsPolygonItem *anArrow;
    auto place = mixedSiblings->begin();
    while (place != mixedSiblings->end()) //remove all non-robots from list
    {
        if ((anArrow = dynamic_cast<QGraphicsPolygonItem *>(*place))) {
            place = mixedSiblings->erase(place);
        }
        else
        {
            ++place;
        }
    }
}

// find all of the intersections on this line, get their closest approaching robot, and trigger the intersection detection
void pathLine::checkIntersections()
{
    intersection *anIntersection;
    Robot *aRobot;
    bool found = false;
    QList<QGraphicsItem *> children = this->getSortedChildren();
    for (auto it = children.begin(); it != children.end(); ++it)
        {
            if ((anIntersection = dynamic_cast<intersection*>(*it)))
            {
                auto j = it;
                ++j;
                found = false;
                while (!found && j !=children.end())
                {
                    if ((aRobot = dynamic_cast<Robot *>(*j)) && dynamic_cast<QGraphicsItem *>(aRobot)->isVisible() == true)
                    {
                        anIntersection->checkClear(aRobot);
                        found = true;
                    }
                    else
                    {
                        ++j;
                    }
                }
                if (!found)
                {
                    anIntersection->checkClear(nullptr);
                }
            }
        }
}


void pathLine::cleanIntersections()
{
    QList<QGraphicsItem *> intList = extractIntersections(childItems());
    for (auto it = intList.begin(); it != intList.end(); ++it)
    {
        dynamic_cast<intersection *>(*it)->clean();
    }
}

//return the closest robot approaching a point
QGraphicsItem * pathLine::getPrevRobot(QPoint intersectionLoc)
{
    intersection *tempIntersection = new intersection();
    Robot *aRobot;
    tempIntersection->setPos(intersectionLoc);
    tempIntersection->setParentItem(this);
    QList<QGraphicsItem *> children = this->getSortedChildren();
    auto it = children.begin();
    bool found = false;
    while (it != children.end() && !found)
    {
        if (tempIntersection == *it)
        {
            found = true;
            qDebug()<<"found intersection";
        }
        else
        {
            ++it;
        }
    }
    if (it != children.end())
    {
        ++it;
    }
    found = false;
    while (it != children.end() && !found)
    {
        if ((aRobot = dynamic_cast<Robot *>(*it)) && dynamic_cast<QGraphicsItem *>(aRobot)->isVisible() == true)
        {
            qDebug() << "found previous robot";
            found = true;
        }
        else
        {
            ++it;
        }
    }
    this->scene()->removeItem(dynamic_cast<QGraphicsItem *>(tempIntersection));
    delete tempIntersection;
    qDebug() << "deleted temp intersection";
    if (found)
    {
        return (*it);
    }
    else
    {
        return nullptr;
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

    top.setY(top.y() - ARROW_OFFSET);
    myArrowHead = makeArrow(top, 0);
    myArrowHead->setParentItem(this);
}

QPointF north::getSnapPoint(QPointF nearPoint){
    return QPointF(this->line().x1(), nearPoint.y());
}

//return list of children sorted with closest to the end of the line first
QList<QGraphicsItem *> north::getSortedChildren(){
    QList<QGraphicsItem *> children = this->childItems();
    auto compare = [](QGraphicsItem *i, QGraphicsItem *j)->bool{return i->pos().y() < j->pos().y();};
    std::sort(children.begin(),children.end(),compare); // sort robots in travel direction
    removeArrow(&children);
    return children;
}

// adjust the speed of all child robots of this line on the prep phase of advance
void north::advance(int phase) {
    if (!phase)
    {
        //QList<QGraphicsItem *> siblings = this->getSortedChildren();
        QList<QGraphicsItem *>siblings = this->extractRobots(this->getSortedChildren());
        //removeNonRobots(&siblings);
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

// put robots in a queue to renter the scen when they drive off the edge.
// add robots from queue to beginning of line if there is room
void north::wrapRobots(QList<QGraphicsItem *> *siblingRobots)
{
    auto it = siblingRobots->begin();
    while (it != siblingRobots->end() && (*it)->pos().y() < this->line().p2().y()) // check for passing end of line
    {
        // move robot from line to holding queue and hide it
        wrapBuffer.push_back(*it);
        (*it)->setParentItem(nullptr);
        (*it)->setActive(false);
        (*it)->setVisible(false);
        it = siblingRobots->erase(it);
    }
    if (!wrapBuffer.empty()) { //front() only safe on nonempty queue
        int requiredGap = dynamic_cast<Robot *>(wrapBuffer.front())->getBufferSpace();
        if (siblingRobots->empty() ||
                (
                    siblingRobots->last()->pos().y() < this->scene()->sceneRect().bottom() - requiredGap)
                )//check for sufficient room to rejoin line
        {
            //move robot from holding queue to line and show it
            siblingRobots->append(dynamic_cast<QGraphicsItem *>(wrapBuffer.front()));
            wrapBuffer.pop_front();
            siblingRobots->last()->setPos(this->line().p1());
            siblingRobots->last()->setParentItem(this);
            siblingRobots->last()->setActive(true);
            siblingRobots->last()->setVisible(true);
        }
    }
}

void north::addIntersections()
{
    QList<pathLine *> crosses = dynamic_cast<Canvas *>(this->scene())->extractHorizontalLines(dynamic_cast<Canvas *>(this->scene())->getLines());
    intersection *newInt = nullptr;
    for (auto it = crosses.begin(); it != crosses.end(); ++it)
    {
        newInt = new intersection();
        newInt->setParentItem(this);
        newInt->setCross(*it);
        newInt->setPos(this->line().x1(),(*it)->line().y1());
        newInt = nullptr;
    }
}

//get the distance between two object on a line
int north::distance(QGraphicsItem *from, QGraphicsItem *to)
{
    int distance = to->pos().y() - from->pos().y();
    distance += this->scene()->sceneRect().bottom();
    distance %= static_cast<int>(this->scene()->sceneRect().bottom());
    return distance;
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

    bottom.setY(bottom.y() + ARROW_OFFSET);
    myArrowHead = makeArrow(bottom, 180);
    myArrowHead->setParentItem(this);
}

QPointF south::getSnapPoint(QPointF nearPoint){
    return QPointF(this->line().x1(), nearPoint.y());
}
//return list of children sorted with closest to the end of the line first
QList<QGraphicsItem *> south::getSortedChildren(){
    QList<QGraphicsItem *> children = this->childItems();
    auto compare = [](QGraphicsItem *i, QGraphicsItem *j)->bool{return i->pos().y() > j->pos().y();};
    std::sort(children.begin(),children.end(),compare); // sort robots in travel direction
    removeArrow(&children);
    return children;
}
// adjust the speed of all child robots of this line on the prep phase of advance
void south::advance(int phase) {
    if (!phase)
    {
        QList<QGraphicsItem *>siblings = this->extractRobots(this->getSortedChildren());

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

// put robots in a queue to renter the scen when they drive off the edge.
// add robots from queue to beginning of line if there is room
void south::wrapRobots(QList<QGraphicsItem *> *siblingRobots)
{
    auto it = siblingRobots->begin();
    while (it != siblingRobots->end() && (*it)->pos().y() > this->line().p2().y()) // check for passing end of line
    {
        // move robot from line to holding queue and hide it
        wrapBuffer.push_back(*it);
        (*it)->setParentItem(nullptr);
        (*it)->setActive(false);
        (*it)->setVisible(false);
        it = siblingRobots->erase(it);
    }
    if (!wrapBuffer.empty()) { //front() only safe on nonempty queue
        int requiredGap = dynamic_cast<Robot *>(wrapBuffer.front())->getBufferSpace();
        if (siblingRobots->empty() ||
                (siblingRobots->last()->pos().y() > this->scene()->sceneRect().top() + requiredGap)
           ) //check for sufficient room to rejoin line
        {
            //move robot from holding queue to line and show it
            siblingRobots->append(dynamic_cast<QGraphicsItem *>(wrapBuffer.front()));
            wrapBuffer.pop_front();
            siblingRobots->last()->setPos(this->line().p1());
            siblingRobots->last()->setParentItem(this);
            siblingRobots->last()->setActive(true);
            siblingRobots->last()->setVisible(true);
        }
    }
}
void south::addIntersections()
{
    QList<pathLine *> crosses = dynamic_cast<Canvas *>(this->scene())->extractHorizontalLines(dynamic_cast<Canvas *>(this->scene())->getLines());
    intersection *newInt = nullptr;
    for (auto it = crosses.begin(); it != crosses.end(); ++it)
    {
        newInt = new intersection();
        newInt->setParentItem(this);
        newInt->setCross(*it);
        newInt->setPos(this->line().x1(),(*it)->line().y1());
        newInt = nullptr;
    }
}

//get the distance between two object on a line
int south::distance(QGraphicsItem *from, QGraphicsItem *to)
{
    int distance = from->pos().y() - to->pos().y();
    distance += this->scene()->sceneRect().bottom();
    distance %= static_cast<int>(this->scene()->sceneRect().bottom());
    return distance;
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

    left.setX(left.x() - ARROW_OFFSET);
    myArrowHead = makeArrow(left, 270);
    myArrowHead->setParentItem(this);
}

QPointF west::getSnapPoint(QPointF nearPoint){
    return QPointF(nearPoint.x(), this->line().y1());
}
//return list of children sorted with closest to the end of the line first
QList<QGraphicsItem *> west::getSortedChildren(){
    QList<QGraphicsItem *> children = this->childItems();
    auto compare = [](QGraphicsItem *i, QGraphicsItem *j)->bool{return i->pos().x() < j->pos().x();};
    std::sort(children.begin(),children.end(),compare); // sort robots in travel direction
    removeArrow(&children);
    return children;
}
// adjust the speed of all child robots of this line on the prep phase of advance
void west::advance(int phase) {
    if (!phase)
    {
        QList<QGraphicsItem *>siblings = this->extractRobots(this->getSortedChildren());

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

// put robots in a queue to renter the scen when they drive off the edge.
// add robots from queue to beginning of line if there is room
void west::wrapRobots(QList<QGraphicsItem *> *siblingRobots)
{
    auto it = siblingRobots->begin();
    while (it != siblingRobots->end() && (*it)->pos().x() < this->line().p2().x()) // check for passing end of line
    {
        // move robot from line to holding queue and hide it
        wrapBuffer.push_back(*it);
        (*it)->setParentItem(nullptr);
        (*it)->setActive(false);
        (*it)->setVisible(false);
        it = siblingRobots->erase(it);
    }
    if (!wrapBuffer.empty()) { //front() only safe on nonempty queue
        int requiredGap = dynamic_cast<Robot *>(wrapBuffer.front())->getBufferSpace();
        if (siblingRobots->empty()
            || (siblingRobots->last()->pos().x() < this->scene()->sceneRect().right() - requiredGap)
            ) //check for sufficient room to rejoin line
        {
            //move robot from holding queue to line and show it
            siblingRobots->append(dynamic_cast<QGraphicsItem *>(wrapBuffer.front()));
            wrapBuffer.pop_front();
            siblingRobots->last()->setPos(this->line().p1());
            siblingRobots->last()->setParentItem(this);
            siblingRobots->last()->setActive(true);
            siblingRobots->last()->setVisible(true);
        }
    }
}

void west::addIntersections()
{
    QList<pathLine *> crosses = dynamic_cast<Canvas *>(this->scene())->extractVerticalLines(dynamic_cast<Canvas *>(this->scene())->getLines());
    intersection *newInt = nullptr;
    for (auto it = crosses.begin(); it != crosses.end(); ++it)
    {
        newInt = new intersection();
        newInt->setParentItem(this);
        newInt->setCross(*it);
        newInt->setPos((*it)->line().x1(),this->line().y1());
        newInt = nullptr;
    }
}

//get the distance between two object on a line
int west::distance(QGraphicsItem *from, QGraphicsItem *to)
{
    int distance = to->pos().x() - from->pos().x();
    distance += this->scene()->sceneRect().right();
    distance %= static_cast<int>(this->scene()->sceneRect().right());
    return distance;
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

    right.setX(right.x() + ARROW_OFFSET);
    myArrowHead = makeArrow(right, 90);
    myArrowHead->setParentItem(this);
}

QPointF east::getSnapPoint(QPointF nearPoint){
    return QPointF(nearPoint.x(), this->line().y1());
}
//return list of children sorted with closest to the end of the line first
QList<QGraphicsItem *> east::getSortedChildren(){
    QList<QGraphicsItem *> children = this->childItems();
    auto compare = [](QGraphicsItem *i, QGraphicsItem *j)->bool{return i->pos().x() > j->pos().x();};
    std::sort(children.begin(),children.end(),compare); // sort robots in travel direction
    removeArrow(&children);
    return children;
}
// adjust the speed of all child robots of this line on the prep phase of advance
void east::advance(int phase) {
    if (!phase)
    {
        QList<QGraphicsItem *>siblings = this->extractRobots(this->getSortedChildren());

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

// put robots in a queue to renter the scen when they drive off the edge.
// add robots from queue to beginning of line if there is room
void east::wrapRobots(QList<QGraphicsItem *> *siblingRobots)
{
    auto it = siblingRobots->begin();
    while (it != siblingRobots->end())
    {
        if (it != siblingRobots->end() && (*it)->pos().x() > this->line().p2().x()) // check for passing end of line
        {
            // move robot from line to holding queue and hide it
            wrapBuffer.push_back(*it);
            (*it)->setParentItem(nullptr);
            (*it)->setActive(false);
            (*it)->setVisible(false);
            it = siblingRobots->erase(it);
        }
        else
        {
            ++it;
        }
    }
    if (!wrapBuffer.empty()) { //front() only safe on nonempty queue
        //get the space the robot needs
        int requiredGap = dynamic_cast<Robot *>(wrapBuffer.front())->getBufferSpace();
        if (siblingRobots->empty() ||
                (siblingRobots->last()->pos().x() > this->scene()->sceneRect().left() + requiredGap)
            ) //check for sufficient room to rejoin line
        {
            //move robot from holding queue to line and show it
            siblingRobots->append(dynamic_cast<QGraphicsItem *>(wrapBuffer.front()));
            wrapBuffer.pop_front();
            siblingRobots->last()->setPos(this->line().p1()); //rejoin at beginning
            siblingRobots->last()->setParentItem(this);
            siblingRobots->last()->setActive(true);
            siblingRobots->last()->setVisible(true);
        }
    }
}

void east::addIntersections()
{
    QList<pathLine *> crosses = dynamic_cast<Canvas *>(this->scene())->extractVerticalLines(dynamic_cast<Canvas *>(this->scene())->getLines());
    intersection *newInt = nullptr;
    for (auto it = crosses.begin(); it != crosses.end(); ++it)
    {
        newInt = new intersection();
        newInt->setParentItem(this);
        newInt->setCross(*it);
        newInt->setPos((*it)->line().x1(),this->line().y1());
        newInt = nullptr;
    }
}

//get the distance between two object on a line
int east::distance(QGraphicsItem *from, QGraphicsItem *to)
{
    int distance = from->pos().x() - to->pos().x();
    distance += this->scene()->sceneRect().right();
    distance %= static_cast<int>(this->scene()->sceneRect().right());
    return distance;
}
