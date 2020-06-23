#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    w.setFixedSize(w.size());         // для фиксация размера главного окна

    return a.exec();
}
