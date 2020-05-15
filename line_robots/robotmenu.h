#ifndef ROBOTMENU_H
#define ROBOTMENU_H

#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class RobotMenu : public QFrame
{
public:
    explicit RobotMenu(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // ROBOTMENU_H
