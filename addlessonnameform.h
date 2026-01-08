#ifndef ADDLESSONNAMEFORM_H
#define ADDLESSONNAMEFORM_H

#include <QWidget>
#include"dataschedule.h"
#include"schedulejsonparser.h"
namespace Ui {
class AddLessonNameForm;
}

class AddLessonNameForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddLessonNameForm(QWidget *parent = nullptr);
    ~AddLessonNameForm();

private slots:
    bool SendLessonNameDataToJson();

private:
    Ui::AddLessonNameForm *ui;
    std::unique_ptr<DataSchedule> schedule;
    std::unique_ptr<ScheduleJsonParser> parseJson;
};

#endif // ADDLESSONNAMEFORM_H
