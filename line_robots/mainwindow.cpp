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
}

MainWindow::~MainWindow()
{
    delete ui;
}

