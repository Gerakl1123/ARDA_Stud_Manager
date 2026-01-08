#ifndef ADDNAMETEACHERSFORM_H
#define ADDNAMETEACHERSFORM_H

#include <QWidget>
#include"dataschedule.h"
#include"schedulejsonparser.h"
namespace Ui {
class AddNameTeachersForm;
}

class AddNameTeachersForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddNameTeachersForm(QWidget *parent = nullptr);
    ~AddNameTeachersForm();

private slots:
    void setNamesTeachersData(const QString& name,const QString& MiddleName,const QString& LastName);
private:
    Ui::AddNameTeachersForm *ui;
    std::unique_ptr<DataSchedule> schedule;
    std::unique_ptr<ScheduleJsonParser> jsonParser;

    inline static size_t counter = 0;

};

#endif // ADDNAMETEACHERSFORM_H
