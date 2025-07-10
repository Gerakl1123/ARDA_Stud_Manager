<<<<<<< HEAD
<<<<<<< HEAD
#include "mainwindow.h"
#include"authregwindow.h"
#include"windowsmanagerstudent.h"
#include <QApplication>
#include<QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");

    AuthRegWindow winAR;
    MainWindow mainW;
    mainW.setMaximumSize(800,600);

    winAR.setMaximumSize(800, 600);


    QObject::connect(&winAR, &AuthRegWindow::authSuccess, [&]() {
        mainW.show();
        winAR.close();
    });

    winAR.resize(200,200);
    winAR.show();
    return a.exec();
}
=======
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
        winAR.close();  
    });


    winAR.show();

    return a.exec();
}
>>>>>>> 7acdfd58b9ccc84905bc36da7d0a7cba70d1e82e
=======
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
        winAR.close();  
    });


    winAR.show();

    return a.exec();
}
>>>>>>> 7acdfd58b9ccc84905bc36da7d0a7cba70d1e82e
