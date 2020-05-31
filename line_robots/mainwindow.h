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
    bool confirmAction(int action);
    ~MainWindow();

private slots:
    void exit();
    void undo();
    void redo();
    void clear();

    // void Mouse_Pressed();
    void setPause(bool isRunning);

private:
    Ui::MainWindow *ui;

    QVector<double> qv_x, qv_y;

    void createMenus();
    void createActions();
    QMenu *fileMenu;
    QMenu *toolsMenu;
    QAction *exitAct;
    QAction *clearAct;
    QAction *undoAct;
    QAction *redoAct;

    Canvas *scene;
    QGraphicsView *view;
    QMenu *itemMenu;

    // movement
    QTimer *timer;
};

#endif // MAINWINDOW_H
