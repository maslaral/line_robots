#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Canvas(itemMenu, this);
    scene->setSceneRect(170,1,554,466);
    ui->canvas->setScene(scene);

    int RobotCount = 1;

    for(int i = 0; i< RobotCount; i++)
    {
        MyRobot *Robot = new MyRobot();
        scene->addItem(Robot);
    }

   //Movement timer, advance is used for the progresion of the robot.
   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
   timer->start(100);

}

void MainWindow::clearData()
{
     scene->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_butClear_clicked()
{
     clearData();
}
