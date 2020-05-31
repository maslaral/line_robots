#include "canvas.h"
#include "pathline.h"
#include "pixelspiral.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QDebug>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMimeData>
#include <QPoint>

// canvas height = 466, width = 554
Canvas::Canvas(QMenu *itemMenu, QObject *parent) : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    undoStack = new QUndoStack(this);
}

void Canvas::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Canvas::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Canvas::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QString dragObjectType = event->mimeData()->text();

        int x = event->scenePos().x();
        int y = event->scenePos().y();

        if (dragObjectType.contains("Line")) {
            pathLine *newLine = pathLine::makeLine(dragObjectType, QPoint(x, y), this->sceneRect());
            newLine->setPen(QPen(Qt::black, 3));
            newLine->setAcceptDrops(true);
            newLine->setZValue(-1);
            qDebug()<<QPoint(x,y);
            undoStack->push(new AddLine(this, newLine, undoStack));

        } else if (dragObjectType.contains("Robot")) { // dragging a robot object onto the canvas
            pathLine *lineDroppedOn = detectLine(&x, &y);

            if (lineDroppedOn) {
                if (detectRobot(&x, &y)) {
                    event->ignore();
                    errorMsg(4);
                } else {
                    if (setRobotProperties()) {
                        Robot *newRobot = new Robot(x, y, lineDroppedOn, dragObjectType);
                        newRobot->setSpeed(roboticSpeed);
                        newRobot->setColor(roboticColor);
                        newRobot->setZValue(1);
                        undoStack->push(new AddRobot(lineDroppedOn, newRobot, undoStack));
                      
                    }
                }
            } else if (lineDroppedOn == nullptr
                       && items().count()
                              == 0) { // attempting to add robot with no lines in the canvas
                event->ignore();
                errorMsg(0);
            } else { // attempting to add robot add without hovering over a line
                event->ignore();
                errorMsg(1);
            }
        }
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

bool Canvas::setRobotProperties()
{
    QDialog robotCustomization;
    QVBoxLayout vbox(&robotCustomization);
    QInputDialog speedEdit;
    QColorDialog colorEdit;

    colorEdit.setOptions(QColorDialog::DontUseNativeDialog | QColorDialog::NoButtons);
    colorEdit.setCurrentColor(Qt::black);
    speedEdit.setOptions(QInputDialog::NoButtons);

    speedEdit.setLabelText("Robot Speed: ");
    speedEdit.setInputMode(QInputDialog::IntInput);
    speedEdit.setIntRange(1, 15);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal,
                               &robotCustomization);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &robotCustomization, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &robotCustomization, SLOT(reject()));

    vbox.addWidget(&speedEdit);
    vbox.addWidget(&colorEdit);
    vbox.addWidget(&buttonBox);

    robotCustomization.setLayout(&vbox);

    if (robotCustomization.exec() == QDialog::Accepted) {
        roboticSpeed = speedEdit.intValue();
        roboticColor = colorEdit.currentColor();
        return true;
    } else {
        return false;
    }
}

pathLine *Canvas::detectLine(int *x, int *y)
{
    QGraphicsItem *curItem;
    pathLine *line;
    PixelSpiral search(this);
    QPoint temp(*x, *y);
    search.setStart(temp);
    search.setRadius(LINE_SEARCH_RADIUS);
    while (search.hasNext()) {
        temp = search.nextPixel();
        if (this->inBounds(temp, LINE_SEARCH_RADIUS)) {
            qDebug()<<temp;
            curItem = itemAt(temp, QTransform());
            if ((line = dynamic_cast<pathLine *>(curItem))) {
                *x = temp.x();
                *y = temp.y();
                return line;
            }
        }
    }
    return nullptr;
}

bool Canvas::detectRobot(int *x, int *y)
{
    QGraphicsItem *curItem;
    Robot *robot;
    PixelSpiral search(this);
    QPoint temp(*x, *y);
    search.setStart(temp);
    search.setRadius(ROBOT_SEARCH_RADIUS);
    while (search.hasNext()) {
        temp = search.nextPixel();
        if (this->inBounds(temp, ROBOT_SEARCH_RADIUS)) {
            curItem = itemAt(temp, QTransform());
            if ((robot = dynamic_cast<Robot *>(curItem))) {
                return true;
            }
        }
    }
    return false;
}

// Shows a pop up error message, press 'ok' to close
void Canvas::errorMsg(int error)
{
    QMessageBox msgBox;
    switch (error) {
    case 0:
        msgBox.setText("Error: Please add a line before adding a robot.");
        break;
    case 1:
        msgBox.setText("Error: Please place the robot on top of a line.");
        break;
    case 2:
        msgBox.setText("Error: Out of bounds placement.");
        break;
    case 3:
        msgBox.setText("Error: Line is too close to another line.");
        break;
    case 4:
        msgBox.setText("Error: Robot is too close to another robot.");
        break;
    }
    msgBox.exec();
}

bool Canvas::inBounds(QPoint checkPixel, int buffer)
{
    /*if (checkPixel.x() >= 30 + buffer && checkPixel.x() <= this->sceneRect().width() - buffer
        && checkPixel.y() >= 30 + buffer && checkPixel.y() <= this->sceneRect().height() - buffer) {*/
    if (checkPixel.x() >= this->sceneRect().left() && checkPixel.x() <= this->sceneRect().right()
            && checkPixel.y() >= this->sceneRect().top() && checkPixel.y() <= this->sceneRect().bottom())
    {
        return true;
    } else {
        return false;
    }
}

// slot to implement an intersection check phase prior to triggering advance
// trigger this slot on each clock tick
void Canvas::tick()
{
    pollIntersections();
    this->advance();
}

//iterate through a list of lines and have them check their intersections
void Canvas::pollIntersections()
{
    QList<pathLine *> lineItems = this->getLines();
    for (auto it = lineItems.begin(); it != lineItems.end(); ++it)
    {
        (*it)->checkIntersections();
    }
}

// return a list of all the lines currently on the canvas
QList<pathLine *> Canvas::getLines()
{
    pathLine *aLine;
    QList<QGraphicsItem *> children = this->items();
    QList<pathLine *> linesOnly;

    for (auto it = children.begin(); it != children.end(); ++it)
    {
        if ((aLine = dynamic_cast<pathLine *>(*it)))
        {
            linesOnly.append(dynamic_cast<pathLine *>(*it));
        }
    }
    return linesOnly;
}
//filter a mixed list of lines and return only the horizontals
QList<pathLine *> Canvas::extractHorizontalLines(QList<pathLine *> mixedLines)
{
    QList<pathLine *> horizontals;
    for (auto it = mixedLines.begin(); it != mixedLines.end(); ++it)
    {
        if ((*it)->line().toLine().x1() != (*it)->line().toLine().x2())
        {
            horizontals.append(*it);
        }
    }
    return horizontals;
}

// filter a mixed list of lines and return only the verticals
QList<pathLine *> Canvas::extractVerticalLines(QList<pathLine *> mixedLines)
{
    QList<pathLine *> verticals;
    for (auto it = mixedLines.begin(); it != mixedLines.end(); ++it)
    {
        if ((*it)->line().toLine().y1() != (*it)->line().toLine().y2())
        {
            verticals.append(*it);
        }
    }
    return verticals;
}
