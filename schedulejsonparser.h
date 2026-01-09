#ifndef SCHEDULEJSONPARSER_H
#define SCHEDULEJSONPARSER_H
#include<QString>
#include"dataschedule.h"
#include<QMap>
#include<QTime>
#include<QPair>
#include<QSet>
#include"dataschedule.h"
#include<QFile>

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

    /**
 * Извлекает массив из JSON файла
 * Читает файл парсит JSON ищет первый массив (он и так 1)
 * Его данные сохраняет в массив
 * Если файл не существует или нет массива возвращает пустой массив
 * Удаляет оригинальный файл после чтения
 */
    static QJsonArray getArrayFromJsonFile(QFile& file);

};

#endif // SCHEDULEJSONPARSER_H
