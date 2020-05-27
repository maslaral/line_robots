#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QComboBox>
#include <QGraphicsView>
#include <QMainWindow>

class Canvas;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void addRobot(double x, double y);
    void clearData();
    void pauseSimulation();
    ~MainWindow();

private slots:
    void on_butClear_clicked();
    // void Mouse_Pressed();
    void setPause(bool isRunning);

    void on_butUndo_clicked();

    void on_butRedo_clicked();

private:
    Ui::MainWindow *ui;

    QVector<double> qv_x, qv_y;

    Canvas *scene;
    QGraphicsView *view;
    QMenu *itemMenu;

    // movement
    QTimer *timer;
};

#endif // MAINWINDOW_H
