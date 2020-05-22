#include <QtWidgets>
#include "robotmenu.h"

RobotMenu::RobotMenu(QWidget *parent)
    : QFrame(parent)
{
    // setting up the panel, this does not accept drops
    setAcceptDrops(false);

    // setting up the left arrow icon
    QLabel *robotCircle = new QLabel(this);
    QPixmap circle(":/images/circle.png");
    const int w = 30;
    const int h = 30;

    robotCircle->setPixmap(circle.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    robotCircle->setToolTip("Circle Robot");		// DON'T CHANGE - used to create robot object
    robotCircle->move(8, 8);
    robotCircle->show();
    robotCircle->setAttribute(Qt::WA_DeleteOnClose);

    // setting up the left arrow icon
    QLabel *robotSquare = new QLabel(this);
    QPixmap square(":/images/square.png");

    robotSquare->setPixmap(square.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    robotSquare->setToolTip("Square Robot");		// DON'T CHANGE - used to create robot object
    robotSquare->move(43, 8);
    robotSquare->show();
    robotSquare->setAttribute(Qt::WA_DeleteOnClose);
}


void RobotMenu::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel *>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);
    mimeData->setText(child->toolTip());

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}

void RobotMenu::changeEvent(QEvent *event) {
    this->repaint();
}
