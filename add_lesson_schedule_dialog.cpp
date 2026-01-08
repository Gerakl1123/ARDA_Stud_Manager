#include "add_lesson_schedule_dialog.h"
#include "ui_add_lesson_schedule_dialog.h"

Add_Lesson_Schedule_Dialog::Add_Lesson_Schedule_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Add_Lesson_Schedule_Dialog)
{
    ui->setupUi(this);
}

Add_Lesson_Schedule_Dialog::~Add_Lesson_Schedule_Dialog()
{
    delete ui;
}
