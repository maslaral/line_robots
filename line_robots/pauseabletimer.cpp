#include "pauseabletimer.h"
#include <QDebug>
pauseableTimer::pauseableTimer(QObject *parent) : QTimer(parent) {}

// when this slot is triggered, the active status of the timer is inverted
void pauseableTimer::toggleActive()
{
    if (this->pauseableTimer::isActive()) {
        this->pauseableTimer::stop();
        qDebug() << "stop";
    } else {
        this->pauseableTimer::start();
        qDebug() << "start";
    }
    emit isRunning(this->pauseableTimer::isActive());
}

// when triggered, accepts a frame rate in timeouts per second and sets the
// timeout interval
void pauseableTimer::setFrameRate(int newFrameRate)
{
    this->setInterval(1000 / newFrameRate);
}
