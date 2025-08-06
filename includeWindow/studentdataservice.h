#ifndef STUDENTDATASERVICE_H
#define STUDENTDATASERVICE_H
#include<QStackedWidget>

#include <QWidget>
#include<QVBoxLayout>
#include<QLabel>
#include<QLineEdit>

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

    void onAddStudentClicked();
    void onPrintFile();
    void backMainMenu();
    void onSortStudent();
    void onDeleteStudent();
    void onFindStudent();

    MainWindow* mainWindow;

private slots:

};


#endif // STUDENTDATASERVICE_H
