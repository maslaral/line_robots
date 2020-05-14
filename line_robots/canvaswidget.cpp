#include <QtWidgets>
#include <QString>
#include <QPainter>

#include "canvaswidget.h"
#include "line.h"
#include "canvasmatrix.h"

CanvasWidget::CanvasWidget(QWidget *parent)
    : QFrame(parent)
{
    // min and max must be set in order to represent
    // canavs coordinates as a matrix accurately
    setMinimumSize(600, 600);
    setMaximumSize(600, 600);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    matrix = new CanvasMatrix();	// matrix that represents the board
}

void CanvasWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void CanvasWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        int direction = 0;

        // gets the tooltip text that was passed via mimedata
        // and sets the direction accordingly
        if (event->mimeData()->text() == "Left Line")
            direction = 0;
        else if (event->mimeData()->text() == "Right Line")
            direction = 1;
        else if (event->mimeData()->text() == "Up Line")
            direction = 2;
        else if (event->mimeData()->text() == "Down Line")
            direction = 3;

        // creating the new line, adding it to the matrix that represents
        // the board, and then calling show to repaint the canvas
        Line* newLine = new Line(this, event->pos(), direction);
        matrix->addLine(newLine);
        newLine->show();

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void CanvasWidget::dragMoveEvent(QDragMoveEvent *event)
{
    // get the position where the object is going
    // to be dropped
    QPoint drop_position = event->pos();
    int x = drop_position.x();
    int y = drop_position.y();

    // TODO: Fix and get working for the new line drawing method
    // This checks if there's a child anywhere near the line
    // that is being placed. Intended to prevent lines being placed
    // too close together. This worked when I was dropping a pixelmap, but
    // is not working when drawing a line.

    bool occupied = false;

    for (int i = -60; i <= 60; i++) {
        for (int j = -60; j <= 60; j++) {
            if (childAt(x + i, y + i) != nullptr) {
                occupied = true;
                event->ignore();
                return;
            }
        }
    }

    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
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
