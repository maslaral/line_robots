#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class CanvasMatrix;

class CanvasWidget : public QFrame
{
public:
    explicit CanvasWidget(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    CanvasMatrix* matrix;
};

#endif // CANVASWIDGET_H
