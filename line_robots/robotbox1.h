#ifndef ROBOTBOX1_H
#define ROBOTBOX1_H

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class robotBox1 : public QLabel
{
    Q_OBJECT
public:
    explicit robotBox1(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *ev) override;

signals:
    void Mouse_Pressed();
};

#endif // ROBOTBOX1_H
