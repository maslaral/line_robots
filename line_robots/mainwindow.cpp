#include "mainwindow.h"
#include "canvas.h"
#include "pauseabletimer.h"
#include "robotmenu.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Canvas(itemMenu, this);

    // Sets the size of the canvas
    scene->setSceneRect(0, 0, 554, 466);

    // sets the canvas on the scene
    ui->canvas->setScene(scene);

    // Smoth out the movement of the robot
    ui->canvas->setRenderHint(QPainter::Antialiasing);

    // movement timer, advance is used for the progresion of the robot.
    timer = new pauseableTimer(this);

    // connect timer object to ui widgets
    timer->setInterval(1000 / ui->speed->value());
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(timer, SIGNAL(isRunning(bool)), this, SLOT(setPause(bool)));
    connect(ui->pauseButton, SIGNAL(clicked()), timer, SLOT(toggleActive()));
    connect(ui->speed, SIGNAL(valueChanged(int)), timer, SLOT(setFrameRate(int)));
    connect(timer, SIGNAL(isRunning(bool)), ui->lineMenu, SLOT(setDisabled(bool)));
    connect(timer, SIGNAL(isRunning(bool)), ui->robotMenu, SLOT(setDisabled(bool)));
}

void MainWindow::clearData()
{
    scene->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// update the pause button control based on the state of the timer.
void MainWindow::setPause(bool timerActive)
{
    if (timerActive) {
        ui->pauseButton->setText("Pause");
    } else {
        ui->pauseButton->setText("Run");
    }
    ui->pauseButton->repaint(); // required so text visibly updates
}

void MainWindow::on_butClear_clicked()
{
    clearData();
    this->timer->stop();
    this->setPause(false);
}
