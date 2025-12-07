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
    mainWindow.setWindowIcon(QIcon("C:/Users/Gera/Desktop/JSONS/free-icon-graduate-hat-3561706.png"));
   // ExtraDataDialog dlg;
   // dlg.exec();
    // IODataBaseHandler h;
    // h.createConnectionsDB(DatabaseTypes::LESSON,"600-is1k");

    //AssignmentPlanner planer;
    //AddWork w;
    //PriviewWorks p;
   // p.show();
    //w.show();
    //planer.show();
    //NotificationManager m;
    //m.show();
    //m.NotificationStart(Notification::Easy);

    // QObject::connect(&winAR, &AuthRegWindow::authSuccess, [&]() {
    //     mainWindow.show();
    //     winAR.close();
    // });


    // winAR.show();
    mainWindow.show();


    return a.exec();
}
