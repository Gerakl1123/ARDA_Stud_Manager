#ifndef ADDWORK_H
#define ADDWORK_H

#include <QDialog>
#include"../parserjson.h"
#include"priviewworks.h"
#include"assignmentplanner.h"
class ParserJson;
class PriviewWorks;

namespace Ui {
class AddWork;
}

struct Task
{
    QString nameT;
    QString descT;
    QDate dateT;
    QTime timeT;
    QString priorityT;

    Task(const QString& name,const QString& desc,const QDate& date,const QTime& time,const QString& priority)
        : nameT(name),descT(desc),dateT(date),timeT(time),priorityT(priority) {}
    Task() = default;
    // bool operator ==(const Task& other) const{
    //     return priorityT == other.priorityT;
    // }

};

class AddWork : public QDialog
{
    Q_OBJECT
public slots:
    void onPriviewReceived(const QJsonObject& obj);
signals:
   // void CreteatedWork();
public:
    explicit AddWork(PriviewWorks* p,AssignmentPlanner* planner,QWidget *parent = nullptr);
    ~AddWork();
    void createWork();
    void setWork(const QString& name,const QString& desc,const QDate& date,const QTime& time,const QString& priority);
private:
    Ui::AddWork *ui;
    AssignmentPlanner* planner_;
    std::unique_ptr<ParserJson> parser;
   // std::unique_ptr<Task> taskP;
    QString path_;
    QString name_;
    QString desc_;
    QDate date_;
    QTime time_;
    QString priority_;
};

#endif // ADDWORK_H
