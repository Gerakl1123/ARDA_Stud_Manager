#ifndef ADD_LESSON_SCHEDULE_DIALOG_H
#define ADD_LESSON_SCHEDULE_DIALOG_H

#include <QDialog>
#include"primarydatascheudlemanagerform.h"
#include"schedulebuilderform.h"

class MainWindow;

namespace Ui {
class Add_Lesson_Schedule_Dialog;
}

class Add_Lesson_Schedule_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Lesson_Schedule_Dialog(MainWindow* main,QWidget *parent = nullptr);
    ~Add_Lesson_Schedule_Dialog();
private slots:
    void openInstanceForm()
    {
        instanceBaseData = new PrimaryDataScheudleManagerForm(this,nullptr);
        this->hide();
        instanceBaseData->show();
    }
    void ConstructScheudleForm()
    {
        ConstructScheudle = new ScheduleBuilderForm(this,nullptr);
        this->hide();
        ConstructScheudle->show();

    }

    void backMenu();
private:
    Ui::Add_Lesson_Schedule_Dialog *ui;
    PrimaryDataScheudleManagerForm* instanceBaseData;
    ScheduleBuilderForm* ConstructScheudle;
    MainWindow* windowBack;
};

#endif // ADD_LESSON_SCHEDULE_DIALOG_H
