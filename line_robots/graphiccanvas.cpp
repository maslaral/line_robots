#include "graphiccanvas.h"

#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QPainter>

GraphicCanvas::GraphicCanvas(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    setAcceptDrops(true);
}
