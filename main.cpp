#include "mainwindow.h"
#include"authregwindow.h"
#include <QApplication>
#include"addcabinetsdialog.h"
#include"addlessontimeform.h"
#include "addnameteachersform.h"
#include"primarydatascheudlemanagerform.h"
#include"addlessonnameform.h"
#include"schedulebuilderform.h"

int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    AuthRegWindow winAR;
    MainWindow mainWindow;
    ManagerWorker fs;
    fs.CreateFile(QDir::currentPath(),"Works.json");

    //AddCabinetsDialog form1;
    //AddLessonTimeForm form;
    //form1.show();
    //form.show();

   // AddNameTeachersForm f;
    //f.show();
    PrimaryDataScheudleManagerForm d;
    //d.show();
    AddLessonNameForm g;
    //g.show();
    // QObject::connect(&winAR, &AuthRegWindow::authSuccess, [&]() {
    //     mainWindow.show();
    //     winAR.close();
    // });

    ScheduleBuilderForm f;
    //f.show();
    // winAR.show();
   //mainWindow.show();


    return a.exec();
}
