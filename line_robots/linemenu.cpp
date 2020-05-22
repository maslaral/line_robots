#include "linemenu.h"
#include <QtWidgets>

LineMenu::LineMenu(QWidget *parent) : QFrame(parent)
{
    // setting up the panel, this does not accept drops
    setAcceptDrops(false);

    // setting up the left arrow icon
    QLabel *leftIcon = new QLabel(this);
    QPixmap left(":/images/left.png");
    const int w = 32;
    const int h = 32;

    // leftIcon->setPixmap(left);
    leftIcon->setPixmap(left.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    leftIcon->setToolTip("Left Line"); // DON'T CHANGE - used to create line object
    leftIcon->move(8, 8);
    leftIcon->show();
    leftIcon->setAttribute(Qt::WA_DeleteOnClose);

    // setting up the right arrow icon
    QLabel *rightIcon = new QLabel(this);
    QPixmap right(":/images/right.png");

    rightIcon->setPixmap(right.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    rightIcon->setToolTip("Right Line"); // DON'T CHANGE - used to create line object
    rightIcon->move(8, 43);
    rightIcon->show();
    rightIcon->setAttribute(Qt::WA_DeleteOnClose);

    // setting up the up arrow icon
    QLabel *upIcon = new QLabel(this);
    QPixmap up(":/images/up.png");

    upIcon->setPixmap(up.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    upIcon->setToolTip("Up Line"); // DON'T CHANGE - used to create line object
    upIcon->move(43, 8);
    upIcon->show();
    upIcon->setAttribute(Qt::WA_DeleteOnClose);

    // setting up the down arrow icon
    QLabel *downIcon = new QLabel(this);
    QPixmap down(":/images/down.png");

    downIcon->setPixmap(down.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    downIcon->setToolTip("Down Line"); // DON'T CHANGE - used to create line object
    downIcon->move(43, 43);
    downIcon->show();
    downIcon->setAttribute(Qt::WA_DeleteOnClose);
}

void LineMenu::mousePressEvent(QMouseEvent *event)
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
