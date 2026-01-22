#include "mainwindow.h"
#include"authregwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    AuthRegWindow winAR;
    MainWindow mainWindow;
    ManagerWorker fs;
    fs.CreateFile(QDir::currentPath(),"Works.json");
   mainWindow.show();


    return a.exec();
}
