#include "schedulejsonparser.h"
#include<QFile>
#include"LogicOperation.h"
#include"FileChooicer.h"
ScheduleJsonParser::ScheduleJsonParser() {}

bool ScheduleJsonParser::setDataLessonTime(const QString& filename,const QMap<int, QPair<QTime, QTime> > &data)
{
    QFile file(filename);

    LogicOperation::ValidFile(file,ModeValidator::DeleteWrite);


    QJsonArray arr;

    for(const auto&[key,value] : data.toStdMap())
    {

        QJsonObject obj;
        obj["Пара"] = QString::number(key);
        obj["Начало"] = value.first.toString("HH:mm");
        obj["Конец"] = value.second.toString("HH:mm");
        arr.append(obj);
    }

    if(arr.isEmpty()) return false;
    QJsonObject MainObj;
    MainObj["Пары"] = arr;

    QJsonDocument doc(MainObj);

    file.write(doc.toJson());

    return true;
}

bool ScheduleJsonParser::setDataCabinets(const QString &filename, const QSet<QString> &data)
{
    QFile file(filename);

    LogicOperation::ValidFile(file,ModeValidator::DeleteWrite);

    QJsonArray arr;
    QJsonObject mainObj;
    for(const auto& c : data)
    {
        QJsonObject obj;
        obj["Кабинет"] = c;
        arr.append(obj);
    }
    if(arr.isEmpty()) return false;

    mainObj["Кабинеты"]=arr;

    QJsonDocument doc(mainObj);
    file.write(doc.toJson());
    return true;
}

bool ScheduleJsonParser::setDataTeachers(const QString &filename, const QSet<Teacher> &data)
{
    QFile file(filename);

    LogicOperation::ValidFile(file,ModeValidator::DeleteWrite);

    QJsonArray arr;
    QJsonObject mainObj;

    for(const auto& teacher : data)
    {
        QJsonObject obj;
        obj["Имя"] = teacher.firstName;
        obj["Фамилия"] = teacher.middleName;
        obj["Отчество"] = teacher.lastName;
        arr.append(obj);
    }

    if(arr.isEmpty()) return false;

    mainObj["Учителя"] = arr;

    QJsonDocument doc(mainObj);
    file.write(doc.toJson());

    return true;
}

bool ScheduleJsonParser::setLessonNameCabinets(const QString &filename, const QSet<QString> &data)
{
    QFile file(filename);

    LogicOperation::ValidFile(file,ModeValidator::DeleteWrite);

    QJsonArray arr;
    QJsonObject mainObj;

    for(const auto& lesson : data)
    {
        QJsonObject obj;
        obj["Название пары"] = lesson;
        arr.append(obj);
    }

    if(arr.isEmpty()) return false;

    mainObj["Название пар"] = arr;

    QJsonDocument doc(mainObj);
    file.write(doc.toJson());


    return true;


}

QJsonObject ScheduleJsonParser::parseScheudleToJson(const DataSchedule *scheudle)
{


    QJsonObject obj;

    obj["Пара"] = scheudle->currentPair;
    obj["Начало"] = scheudle->currentStartTime.toString("HH:mm");
    obj["Конец"] = scheudle->currentEndTime.toString("HH:mm");
    obj["Предмет"] = scheudle->currentLessonName;
    obj["Преподаватель"] = scheudle->currentTeacher.getFullName();
    obj["Кабинет"] = scheudle->currentCabinet;
    obj["Дата"] = scheudle->currentDate.toString("dd.MM.yyyy");



    return obj;

}
