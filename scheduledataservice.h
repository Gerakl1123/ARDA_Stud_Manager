#ifndef SCHEDULEDATASERVICE_H
#define SCHEDULEDATASERVICE_H

#include <QObject>
#include"dataschedule.h"

class ScheduleDataService : public QObject
{
    Q_OBJECT
public:
    ScheduleDataService();

public slots:
    QSet<QString> GetCabinetsJson();
    QSet<QString> GetLessonNameJson();
    QMap<int,QPair<QTime,QTime>> GetLessonTimeJson();
    QSet<Teacher> GetTeacherNameJson();

private:
    std::unique_ptr<DataSchedule> schedule;

};

#endif // SCHEDULEDATASERVICE_H
