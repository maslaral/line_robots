#include "line.h"

Line::Line(CanvasWidget* parent, QPoint pos, int dir)
     : CanvasWidget(parent)
{
    direction = dir;

    // if direction is left or right, set the line width
    // if direction is up or down, set the line height
    if (direction == 0 || direction == 1) {
        x1 = pos.x() - 100;
        y1 = pos.y();
        x2 = x1 + 200;
        y2 = y1;
    } else {
        x1 = pos.x();
        y1 = pos.y() - 100;
        x2 = x1;
        y2 = y1 + 200;
    }
}

int Line::getStartX()
{
     return x1;
}

int Line::getStartY()
{
    return y1;
}

int Line::getEndX()
{
    return x2;
}

int Line::getEndY()
{
    return y2;
}

void Line::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;

    // setting the style of the line and the ellipse
    pen.setWidth(4);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setBrush(Qt::black);

    // drawing the line on the coordinates
    painter.drawLine(x1, y1, x2, y2);

    // drawing the end point of the line, adjustments for alignment purposes
    if (direction == 0)
        painter.drawEllipse(x1 - 3, y1 - 5, 10, 10);
    else if (direction == 1)
        painter.drawEllipse(x2 + 3, y2 - 5, 10, 10);
    else if (direction == 2)
        painter.drawEllipse(x1 - 5, y1 - 3, 10, 10);
    else
        painter.drawEllipse(x2 - 5, y2 + 3, 10, 10);
}
