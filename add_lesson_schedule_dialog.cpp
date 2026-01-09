#include "add_lesson_schedule_dialog.h"
#include "ui_add_lesson_schedule_dialog.h"
#include"mainwindow.h"

Add_Lesson_Schedule_Dialog::Add_Lesson_Schedule_Dialog(MainWindow *qMain, QWidget *parent)
    : QDialog(parent)
    ,windowBack(qMain)
    , ui(new Ui::Add_Lesson_Schedule_Dialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->btnInstanceData,&QPushButton::clicked,this,&Add_Lesson_Schedule_Dialog::openInstanceForm);
    connect(ui->btnAddSchedule,&QPushButton::clicked,this,&Add_Lesson_Schedule_Dialog::ConstructScheudleForm);
    connect(ui->btnQuit,&QPushButton::clicked,this,&Add_Lesson_Schedule_Dialog::backMenu);

}

Add_Lesson_Schedule_Dialog::~Add_Lesson_Schedule_Dialog()
{
    delete ui;
}

void Add_Lesson_Schedule_Dialog::backMenu()
{
    this->close();
    windowBack->show();

}
