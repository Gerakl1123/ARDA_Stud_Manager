#ifndef ASSIGNMENTPLANNER_H
#define ASSIGNMENTPLANNER_H

#include <QWidget>
#include<QPropertyAnimation>

class NotificationManager;
class AddWork;
class PriviewWorks;
class MainWindow;

namespace Ui {
class AssignmentPlanner;
}

class AssignmentPlanner : public QWidget
{
    Q_OBJECT

public:
    explicit AssignmentPlanner(MainWindow* main,QWidget *parent = nullptr);
    ~AssignmentPlanner();

private slots:

    void openAdder();
    void openPriviewWorks();
    void openSettingsNotification();
private:
    Ui::AssignmentPlanner *ui;
    AddWork* add;
    NotificationManager* notific;
    PriviewWorks* priview;
    MainWindow* main_;

};

#endif // ASSIGNMENTPLANNER_H
