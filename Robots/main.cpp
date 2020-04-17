//Basic setup of the board


#include <iostream>
#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Create Scence
    QGraphicsScene * scene = new QGraphicsScene();

    //Create an item to pout into the scene
    QGraphicsRectItem * rect = new QGraphicsRectItem();
    rect ->setRect(0, 0, 250, 250);

    QGraphicsRectItem * line = new QGraphicsRectItem();
    line ->setRect(50, 0, 1, 250);

    QGraphicsRectItem * line2 = new QGraphicsRectItem();
    line2 ->setRect(100, 0, 1, 250);

    QGraphicsRectItem * line3 = new QGraphicsRectItem();
    line3 ->setRect(150, 0, 1, 250);

    QGraphicsRectItem * line4 = new QGraphicsRectItem();
    line4 ->setRect(200, 0, 1, 250);

    //add item into the scene
    scene -> addItem(rect);
    scene -> addItem(line);
    scene -> addItem(line2);
    scene -> addItem(line3);
    scene -> addItem(line4);

    //add view
    QGraphicsView * view = new QGraphicsView(scene);


    view->show();

    return a.exec();

}
