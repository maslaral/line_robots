#ifndef PAUSEABLETIMER_H
#define PAUSEABLETIMER_H

#include <QObject>
#include <QWidget>
#include <QTimer>

class pauseableTimer : public QTimer
{
    Q_OBJECT
public:
    explicit pauseableTimer(QObject *parent = nullptr);
public slots:
    void toggleActive();

signals:
    void isRunning(bool isRunning);
};

#endif // PAUSEABLETIMER_H
