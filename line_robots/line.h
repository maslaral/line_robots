#ifndef LINE_H
#define LINE_H

#include <QPoint>
#include <QPainter>
#include <QPen>
#include "canvaswidget.h"

class Line : public CanvasWidget
{
public:
    explicit Line(CanvasWidget *parent, QPoint, int);
    void paintEvent(QPaintEvent *);
    int getStartX();
    int getStartY();
    int getEndX();
    int getEndY();

private:
    int x1;			// beg x point
    int y1;			// beg y point
    int x2;			// end x point
    int y2;			// end y point
    int direction;	// TODO: convert from int to enum
                    // for now, the mapping are:
                    // 0 = left
                    // 1 = rigt
                    // 2 = up
                    // 3 = down
};

#endif // LINE_H
