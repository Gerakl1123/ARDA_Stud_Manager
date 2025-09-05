#include "mainwindow.h"
#include"authregwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthRegWindow winAR;
    MainWindow mainWindow;
    mainWindow.setWindowIcon(QIcon("C:/Users/Gera/Desktop/JSONS/free-icon-graduate-hat-3561706.png"));


    // QObject::connect(&winAR, &AuthRegWindow::authSuccess, [&]() {
    //     mainWindow.show();
    //     winAR.close();
    // });


    // winAR.show();

mainWindow.show();
    return a.exec();
}
