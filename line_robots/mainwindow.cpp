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

    createActions();
    createMenus();

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
    connect(timer, SIGNAL(timeout()), scene, SLOT(tick()));
    connect(timer, SIGNAL(isRunning(bool)), this, SLOT(setPause(bool)));
    connect(ui->pauseButton, SIGNAL(clicked()), timer, SLOT(toggleActive()));
    connect(ui->speed, SIGNAL(valueChanged(int)), timer, SLOT(setFrameRate(int)));
    connect(timer, SIGNAL(isRunning(bool)), ui->lineMenu, SLOT(setDisabled(bool)));
    connect(timer, SIGNAL(isRunning(bool)), ui->robotMenu, SLOT(setDisabled(bool)));
    connect(timer, SIGNAL(isRunning(bool)), toolsMenu, SLOT(setDisabled(bool)));
}

void MainWindow::clearData()
{
    scene->clear();
    scene->undoStack->clear();
}

bool MainWindow::confirmAction(int action)
{
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    switch(action){
    case 0:
        msgBox.setText("Are you sure you want to quit?");
        if(msgBox.exec() == QMessageBox::Yes){
            return true;
        }
        break;
    case 1:
        msgBox.setText("Are you sure you want to PERMANENTLY delete all objects?");
        if(msgBox.exec() == QMessageBox::Yes){
            return true;
        }
        break;
    }
    return false;
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

void MainWindow::exit()
{
    bool tmp = confirmAction(0);
    if(tmp == true){
        this->close();
    }
}

void MainWindow::undo()
{
    scene->undoStack->undo();
}

void MainWindow::redo()
{
    scene->undoStack->redo();
}

void MainWindow::clear()
{
    bool tmp = confirmAction(1);
    if(tmp == true){
        clearData();
        this->timer->stop();
        this->setPause(false);
        ui->lineMenu->setEnabled(true);
        ui->robotMenu->setEnabled(true);
    }
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(undoAct);
    toolsMenu->addAction(redoAct);
    toolsMenu->addSeparator();
    toolsMenu->addAction(clearAct);
}

void MainWindow::createActions()
{
    exitAct = new QAction(tr("&Exit"), this);
    connect(exitAct, &QAction::triggered, this, &MainWindow::exit);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setStatusTip("Undo latest addition to the canvas");
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setStatusTip("Redo latest addition to the canvas");
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    clearAct = new QAction(tr("&Clear"), this);
    clearAct->setStatusTip("Permanently remove all objects from the canvas");
    connect(clearAct, &QAction::triggered, this, &MainWindow::clear);
}
