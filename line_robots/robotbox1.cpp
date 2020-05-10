#include "robotbox1.h"

robotBox1::robotBox1(QWidget *parent) :
    QLabel(parent)
{

}

void robotBox1::mousePressEvent(QMouseEvent *ev)
{
    emit Mouse_Pressed();
}
