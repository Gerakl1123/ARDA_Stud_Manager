#ifndef PRIVIEWWORKS_H
#define PRIVIEWWORKS_H

#include <QDialog>
#include<QFile>
#include"addwork.h"
#include"assignmentplanner.h"
class AddWork;
namespace Ui {
class PriviewWorks;
}

class PriviewWorks : public QDialog
{
    Q_OBJECT
signals:
    void Priview(const QJsonObject& obj);
public slots:
    void openWorks(int local);
public:
    explicit PriviewWorks(AssignmentPlanner* planner,QWidget *parent = nullptr);
    ~PriviewWorks();
    void priviewWorks();
private:
    AssignmentPlanner* planner_;
    inline static int works = 0;
    AddWork* w;
    QJsonArray CurrArr;
    std::unique_ptr<ParserJson> parser;
    void BuildWorks();
    QVector<std::tuple<QString, QDate,QTime>> infoList;
    Ui::PriviewWorks *ui;

};

#endif // PRIVIEWWORKS_H
