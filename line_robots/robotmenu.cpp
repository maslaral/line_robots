#include "robotmenu.h"

RobotMenu::RobotMenu(QWidget *parent) :
    QLabel(parent)
{

}

void RobotMenu::mousePressEvent(QMouseEvent *ev)
{
    emit Mouse_Pressed();
}
