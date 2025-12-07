#ifndef ACADEMICRECORDWINDOW_H
#define ACADEMICRECORDWINDOW_H

#include <QWidget>
#include"accountingassessments.h"
#include"recordbook.h"
#include"project.h"
#include"coursework.h"
#include"diploma.h"

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

private:
    Ui::academicrecordwindow *ui;
private slots:
    void BackMenu();
    void openLessons();
    void openRecorderBooks();
    void openProject();
    void openCourseWork();
    void openDiploma();
};

#endif // ACADEMICRECORDWINDOW_H
