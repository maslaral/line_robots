#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include "robotmenu.h"
#include "pauseabletimer.h"

#include <QtWidgets>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Canvas(itemMenu, this);

    //Sets the size of the canvas
    scene->setSceneRect(0,0,554,466);

    //sets the canvas on the scene
    ui->canvas->setScene(scene);

    //Smoth out the movement of the robot
    ui->canvas->setRenderHint(QPainter::Antialiasing);

    //Draw out the boundry of the scene
    // QPen mypen = QPen(Qt::black, 2);

    // QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    // QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    // QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    // QLineF ButtomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    // scene->addLine(TopLine,mypen);
    // scene->addLine(LeftLine,mypen);
    // scene->addLine(RightLine,mypen);
    // scene->addLine(ButtomLine,mypen);

    // connect(ui->robotMenu, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed()));
    //Add robot
   // int RobotCount = 1;

   // for(int i = 0; i< RobotCount; i++)
   // {
   //     MyRobot *Robot = new MyRobot();
   //     scene->addItem(Robot);
   // }


   // movement timer, advance is used for the progresion of the robot.
   timer = new pauseableTimer(this);
   connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
   connect(timer, SIGNAL(isRunning(bool)), this, SLOT(setPause(bool)));
   connect(ui->pauseButton, SIGNAL(clicked()), timer, SLOT(toggleActive()));

}

void MainWindow::clearData()
{
     scene->clear();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPause(bool timerActive){
    qDebug()<<"signalled";
    qDebug()<<"old: "<<ui->pauseButton->text();
    if(timerActive){
        ui->pauseButton->setText("Pause");
        qDebug()<<"timer was stopped, now running";
    } else {
        ui->pauseButton->setText("Run");
        qDebug()<<"timer was running, no stopped";
    }
    qDebug()<<"new: "<<ui->pauseButton->text();
    ui->pauseButton->repaint();

}

void MainWindow::on_butClear_clicked()
{
    clearData();
	
    // QPen mypen = QPen(Qt::blue);

    // QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    // QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    // QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    // QLineF ButtomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    // scene->addLine(TopLine,mypen);
    // scene->addLine(LeftLine,mypen);
    // scene->addLine(RightLine,mypen);
    // scene->addLine(ButtomLine,mypen);
}

/*
void MainWindow::Mouse_Pressed()
{
    int barSpeed1;
    double barSpeed2;
    barSpeed1 = ui->progressBar->value();
    barSpeed2 = static_cast<double>(barSpeed1);
}
*/


