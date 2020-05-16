#include "pauseabletimer.h"
#include <QDebug>
pauseableTimer::pauseableTimer(QObject *parent) : QTimer(parent)
{

}

void pauseableTimer::toggleActive() {
    if(this->pauseableTimer::isActive()) {
        this->pauseableTimer::stop();
        qDebug()<<"stop";
    } else {
        this->pauseableTimer::start(100);
        qDebug()<<"start";
    }
    emit isRunning(this->pauseableTimer::isActive());
}
