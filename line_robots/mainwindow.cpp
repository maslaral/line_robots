#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include "robotbox1.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Canvas(itemMenu, this);

    // sets the size of the canvas
    scene->setSceneRect(0,0,554,466);

    // sets the canvas on the scene
    ui->canvas->setScene(scene);

    // smoth out the movement of the robot
    ui->canvas->setRenderHint(QPainter::Antialiasing);

    // draw out the boundry of the scene
    QPen mypen = QPen(Qt::blue);

    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF ButtomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    scene->addLine(TopLine,mypen);
    scene->addLine(LeftLine,mypen);
    scene->addLine(RightLine,mypen);
    scene->addLine(ButtomLine,mypen);

<<<<<<< HEAD
    connect(ui->robot1, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed()));
    //Add robot
   // int RobotCount = 1;

   // for(int i = 0; i< RobotCount; i++)
   // {
   //     MyRobot *Robot = new MyRobot();
   //     scene->addItem(Robot);
   // }
=======
    // add robot
    int robotCount = 1;

    for(int i = 0; i < robotCount; i++)
    {
        Robot *robot = new Robot();
        scene->addItem(robot);
    }
>>>>>>> master

   // movement timer, advance is used for the progresion of the robot.
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
	
	QPen mypen = QPen(Qt::blue);

     QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
     QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
     QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
     QLineF ButtomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

     scene->addLine(TopLine,mypen);
     scene->addLine(LeftLine,mypen);
     scene->addLine(RightLine,mypen);
     scene->addLine(ButtomLine,mypen);
}

void MainWindow::Mouse_Pressed()
{
    int barSpeed1;
    double barSpeed2;
    barSpeed1 = ui->progressBar->value();
    barSpeed2 = static_cast<double>(barSpeed1);
    MyRobot *Robot = new MyRobot();
    Robot->setSpeed(barSpeed2);
    scene->addItem(Robot);    
}


