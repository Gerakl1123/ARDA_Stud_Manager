#ifndef SCHEDULEJSONPARSER_H
#define SCHEDULEJSONPARSER_H
#include<QString>
#include"dataschedule.h"
#include<QMap>
#include<QTime>
#include<QPair>
#include<QSet>
#include"dataschedule.h"
class ScheduleJsonParser
{
public:
    ScheduleJsonParser();
public:
    bool setDataLessonTime(const QString &filename, const QMap<int,QPair<QTime,QTime>>& data);
    bool setDataCabinets(const QString &filename,const QSet<QString>& data);
    bool setDataTeachers(const QString &filename,const QSet<Teacher>& data);
    bool setLessonNameCabinets(const QString& filename,const QSet<QString>& data);

    QJsonObject parseScheudleToJson(const DataSchedule* scheudle);
};

#endif // SCHEDULEJSONPARSER_H
