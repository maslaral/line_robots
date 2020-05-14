#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class LineWidget : public QFrame
{
public:
    explicit LineWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // LINEWIDGET_H
