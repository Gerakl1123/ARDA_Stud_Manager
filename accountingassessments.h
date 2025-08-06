#ifndef ACCOUNTINGASSESSMENTS_H
#define ACCOUNTINGASSESSMENTS_H

#include <QWidget>
#include<QSettings>
#include"StudentDataHandler.h"


class academicrecordwindow;
class MainWindow;

namespace Ui {
class accountingassessments;
}

class accountingassessments : public QWidget
{
    Q_OBJECT

public:
    explicit accountingassessments(MainWindow* mainWindow, QWidget *parent = nullptr);

    ~accountingassessments();

private:
    Ui::accountingassessments *ui;
    std::unique_ptr<ImportSaveData> obj;
    MainWindow* backWindow;

    void Back();
};

#endif // ACCOUNTINGASSESSMENTS_H
