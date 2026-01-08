#ifndef ADD_LESSON_SCHEDULE_DIALOG_H
#define ADD_LESSON_SCHEDULE_DIALOG_H

#include <QDialog>

namespace Ui {
class Add_Lesson_Schedule_Dialog;
}

class Add_Lesson_Schedule_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Lesson_Schedule_Dialog(QWidget *parent = nullptr);
    ~Add_Lesson_Schedule_Dialog();

private:
    Ui::Add_Lesson_Schedule_Dialog *ui;
};

#endif // ADD_LESSON_SCHEDULE_DIALOG_H
