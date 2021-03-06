#ifndef PIXELSPIRAL_H
#define PIXELSPIRAL_H

#include "canvas.h"
#include <QObject>
#include <QPoint>

class PixelSpiral : public QObject
{
    Q_OBJECT
private:
    QPoint current;
    int maxPixels;
    int curPixel;
    int direction;
    int maxStep;
    int curStep;

public:
    explicit PixelSpiral(Canvas *parent = nullptr);
    void setStart(QPoint origin);
    void setRadius(int radius);
    bool hasNext();
    void reset();
    QPoint nextPixel();
};

#endif // PIXELSPIRAL_H
