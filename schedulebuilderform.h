#ifndef SCHEDULEBUILDERFORM_H
#define SCHEDULEBUILDERFORM_H

#include <QWidget>
#include"dataschedule.h"
#include"scheduledataservice.h"
#include"schedulejsonparser.h"
#include<QJsonArray>

namespace Ui {
class ScheduleBuilderForm;
}

class ScheduleBuilderForm : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleBuilderForm(QWidget *parent = nullptr);
    ~ScheduleBuilderForm();
public slots:
    void BuildScheudle();
    void SaveScheudle();
    void DeleteItemList(const int item_ROW);

    void SetCabinets(const QString& cabinet)
    {
        scheudle->currentCabinet = cabinet;
       // scheudle->cabinets.insert(cabinet);
    }

    void SetLessonName(const QString& lessonName)
    {
        scheudle->currentLessonName = lessonName;
       // scheudle->LessonsName.insert(lessonName);
    }

    void SetLessonTime(const int pair, const QPair<QTime,QTime>& times)
    {
        scheudle->currentPair = pair;
        scheudle->currentStartTime = times.first;
        scheudle->currentEndTime = times.second;
        //scheudle->lessonsTime[pair] = times;
    }

    void SetTeachers(const Teacher& teacher)
    {
        scheudle->currentTeacher = teacher;
        //scheudle->Teachers.insert(teacher);
    }

    void SetDatePair(const QDate& datePair)
    {
        scheudle->currentDate = datePair;
        //scheudle->datePair.insert(datePair);
    }
private:
    Ui::ScheduleBuilderForm *ui;
    std::unique_ptr<DataSchedule> scheudle;
    std::unique_ptr<ScheduleDataService> scheudleDataService;
    std::unique_ptr<ScheduleJsonParser> parseScheudle;
    QJsonArray mainArr;
    void BuildDataComboBox();
};

#endif // SCHEDULEBUILDERFORM_H
