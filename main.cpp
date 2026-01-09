#include "mainwindow.h"
#include"authregwindow.h"
#include <QApplication>
#include"addcabinetsdialog.h"
#include"addlessontimeform.h"
#include "addnameteachersform.h"
#include"primarydatascheudlemanagerform.h"
#include"addlessonnameform.h"
#include"schedulebuilderform.h"
#include"add_lesson_schedule_dialog.h"
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
