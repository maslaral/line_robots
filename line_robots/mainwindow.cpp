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
    ui->canvas->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

