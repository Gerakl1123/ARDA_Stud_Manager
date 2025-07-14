
#include "mainwindow.h"
#include"authregwindow.h"
#include"windowsmanagerstudent.h"
#include<QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

AuthRegWindow winAR;
MainWindow mainWindow;
//
//
QObject::connect(&winAR, &AuthRegWindow::authSuccess, [&]() {
    mainWindow.show();
    winAR.close();
});
//
//
winAR.show();


    return a.exec();
}

