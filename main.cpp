#include "mainwindow.h"
#include"authregwindow.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AuthRegWindow winAR;
    MainWindow mainWindow;


    QObject::connect(&winAR, &AuthRegWindow::authSuccess, [&]() {
        mainWindow.show();
        winAR.close();  // закроет окно авторизации, но приложение не завершится
    });


    winAR.show();

    return a.exec();
}
