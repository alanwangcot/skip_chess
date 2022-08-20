#include "mainwindow.h"
#include "gameboard.h"
#include <QApplication>
#include <QWindow>
#include "preparewindow.h"


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
//    MainWindow w;
    PrepareWindow pw;
//    w.show();
    pw.show();
    return a.exec();
}
