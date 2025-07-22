#include "mainwindow.h"
#include "authregwindow.h"
#include "windowsmanagerstudent.h"
#include"include/Contest.h"

#include <QApplication>


#include <windows.h>
#include <string>

int main(int argc, char *argv[])
{

    QApplication app(argc,argv);
    AuthRegWindow winAR;
    MainWindow mainWindow;

    QObject::connect(&winAR, &AuthRegWindow::authSuccess, [&]() {
        mainWindow.show();
        winAR.close();
    });


    winAR.show();

    return app.exec();
}
