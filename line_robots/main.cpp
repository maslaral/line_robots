#include "mainwindow.h"
#include <QApplication>
#include <time.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    srand(time(NULL));
    return a.exec();
}
