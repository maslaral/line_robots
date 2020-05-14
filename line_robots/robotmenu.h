#ifndef ROBOTMENU_H
#define ROBOTMENU_H

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class RobotMenu : public QLabel
{
    Q_OBJECT
public:
    explicit RobotMenu(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *ev) override;

signals:
    void Mouse_Pressed();
};

#endif // ROBOTMENU_H
