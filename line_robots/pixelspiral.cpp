#include "pixelspiral.h"
#include "canvas.h"
#include <QPoint>

PixelSpiral::PixelSpiral(Canvas *parent) : QObject(parent)
{
    //this->setParent(parent);
    current.setX(0);
    current.setY(0);
    maxPixels = 0;
    this->reset();
}

void PixelSpiral::reset()
{
    curPixel = 0;
    direction = 0;
    maxStep = 1;
    curStep = 0;
}

void PixelSpiral::setStart(QPoint origin)
{
    current.setX(origin.x());
    current.setY(origin.y());
}

void PixelSpiral::setRadius(int radius)
{
    maxPixels = 2 * radius - 1;
    maxPixels *= maxPixels;
}

bool PixelSpiral::hasNext()
{
    Canvas *genericCanvas;
    if (parent() == nullptr) {
        return false;
    } else if (!(genericCanvas = dynamic_cast<Canvas *>(parent()))) {
        return false;
    } else if (curPixel < maxPixels) {
        return true;
    } else {
        return false;
    }
}

QPoint PixelSpiral::nextPixel()
{
    QPoint thisPixel = current;
    ++curPixel;
    switch (direction) {
    case 0:
        current.setX(current.x() + 1);
        break;
    case 1:
        current.setY(current.y() - 1);
        break;
    case 2:
        current.setX(current.x() - 1);
        break;
    case 3:
        current.setY(current.y() + 1);
        break;
    }
    ++curStep;
    if (curStep == maxStep) {
        ++direction;
        direction %= 4;
        curStep = 0;
        if (direction % 2 == 0) {
            ++maxStep;
        }
    }

    return thisPixel;
}
