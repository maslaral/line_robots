/* =============================================================
   Purpose: The Line Widgets class sets up the left panel of the
            application which contains the icons that are dragged
            and dropped. It also has some drag events which send
            data to the canvas widget via mimedata to continue
            the action.
----------------------------------------------------------------
   Notes: 	The icon tool tip is really important, and should
            not be changed because the text is being passed to
            the canvas widget and then used in the declaration
            of a line object to save the direction.This allows
            the direction of the line to be indicated when
            dragging and dropping lines.
==============================================================*/
#include <QtWidgets>
#include "linewidget.h"

LineWidget::LineWidget(QWidget *parent)
    : QFrame(parent)
{
    // setting up the panel, this does not accept drops
    setMinimumSize(200, 600);
    setMaximumSize(200, 600);
    setFrameStyle(QFrame::NoFrame);
    setAcceptDrops(false);

    // setting up the left arrow icon
    QLabel *leftIcon = new QLabel(this);
    QPixmap left(":/images/left.png");
    int w = 30;
    int h = 30;

    leftIcon->setPixmap(left.scaled(w, h, Qt::IgnoreAspectRatio));
    leftIcon->setToolTip("Left Line");		// DON'T CHANGE - used to create line object
    leftIcon->move(10, 10);
    leftIcon->show();
    leftIcon->setAttribute(Qt::WA_DeleteOnClose);

    // setting up the right arrow icon
    QLabel *rightIcon = new QLabel(this);
    QPixmap right(":/images/right.png");
    w = 30;
    h = 30;

    rightIcon->setPixmap(right.scaled(w, h, Qt::IgnoreAspectRatio));
    rightIcon->setToolTip("Right Line");	// DON'T CHANGE - used to create line object
    rightIcon->move(60, 10);
    rightIcon->show();
    rightIcon->setAttribute(Qt::WA_DeleteOnClose);

    // setting up the up arrow icon
    QLabel *upIcon = new QLabel(this);
    QPixmap up(":/images/up.png");
    w = 30;
    h = 30;

    upIcon->setPixmap(up.scaled(w, h, Qt::IgnoreAspectRatio));
    upIcon->setToolTip("Up Line");			// DON'T CHANGE - used to create line object
    upIcon->move(10, 60);
    upIcon->show();
    upIcon->setAttribute(Qt::WA_DeleteOnClose);

    // setting up the down arrow icon
    QLabel *downIcon = new QLabel(this);
    QPixmap down(":/images/down.png");
    w = 30;
    h = 30;

    downIcon->setPixmap(down.scaled(w, h, Qt::IgnoreAspectRatio));
    downIcon->setToolTip("Down Line");		// DON'T CHANGE - used to create line object
    downIcon->move(60, 60);
    downIcon->show();
    downIcon->setAttribute(Qt::WA_DeleteOnClose);
}

void LineWidget::mousePressEvent(QMouseEvent *event)
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
