#ifndef ACADEMICRECORDWINDOW_H
#define ACADEMICRECORDWINDOW_H

#include <QWidget>
#include"accountingassessments.h"

class MainWindow;

namespace Ui {
class academicrecordwindow;
}

class academicrecordwindow : public QWidget
{
    Q_OBJECT

public:
    explicit academicrecordwindow(MainWindow* main,QWidget *parent = nullptr);
    ~academicrecordwindow();
    MainWindow*  mainwindow;
    accountingassessments* lesson;

private:

    Ui::academicrecordwindow *ui;
private slots:
    void BackMenu();
    void openLessons();

};

#endif // ACADEMICRECORDWINDOW_H
