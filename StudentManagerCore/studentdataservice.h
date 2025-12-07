#ifndef STUDENTDATASERVICE_H
#define STUDENTDATASERVICE_H
#include<QStackedWidget>

#include <QWidget>
#include<QVBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include"../ManagerDataCore/addfullinfostudent.h"

class MainWindow;

namespace Ui {
class StudentDataService;
}

class StudentDataService : public QWidget
{
    Q_OBJECT

public:
    explicit StudentDataService(MainWindow* main,QWidget *parent = nullptr);
    ~StudentDataService();

private:
    Ui::StudentDataService *ui;
    void setupConnections();

    MainWindow* mainWindow;

private slots:

    void onAddStudentClicked();
    void onPrintFile();
    void backMainMenu();
    void onSortStudent();
    void onDeleteStudent();
    void onFindStudent();

    void onAddInfoStud();
};


#endif // STUDENTDATASERVICE_H
