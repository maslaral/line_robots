#ifndef LINEMENU_H
#define LINEMENU_H

#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class LineMenu : public QFrame
{
public:
    explicit LineMenu(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void changeEvent(QEvent *event) override;
};

#endif // LINEMENU_H
