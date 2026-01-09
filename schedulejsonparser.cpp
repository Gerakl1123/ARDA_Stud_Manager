#include "schedulejsonparser.h"
#include<QFile>
#include"LogicOperation.h"
#include"FileChooicer.h"
#include"LogicOperation.h"

ScheduleJsonParser::ScheduleJsonParser() {}

bool ScheduleJsonParser::setDataLessonTime(const QString& filename,const QMap<int, QPair<QTime, QTime> > &data)
{
    QFile file(filename);

    QJsonArray arr = getArrayFromJsonFile(file);

    LogicOperation::ValidFile(file,ModeValidator::WriteFile);


    for(const auto&[key,value] : data.toStdMap())
    {

        QJsonObject obj;
        obj["Пара"] = QString::number(key);
        obj["Начало"] = value.first.toString("HH:mm");
        obj["Конец"] = value.second.toString("HH:mm");
        arr.append(obj);

    }
    QJsonObject MainObj;


    if(arr.isEmpty()) return false;


    MainObj["Пары"] = arr;


    QJsonDocument doc(MainObj);

    file.write(doc.toJson());

    return true;
}

bool ScheduleJsonParser::setDataCabinets(const QString &filename, const QSet<QString> &data)
{
    QFile file(filename);

    QJsonArray arr = getArrayFromJsonFile(file);

    LogicOperation::ValidFile(file,ModeValidator::WriteFile);

    for(const auto& c : data)
    {
        QJsonObject obj;
        obj["Кабинет"] = c;
        arr.append(obj);
    }
    QJsonObject MainObj;


    if(arr.isEmpty()) return false;

    MainObj["Кабинеты"]=arr;

    QJsonDocument doc(MainObj);
    file.write(doc.toJson());
    return true;
}
bool ScheduleJsonParser::setDataTeachers(const QString &filename, const QSet<Teacher> &data)
{
    QFile file(filename);

    QJsonArray arr = getArrayFromJsonFile(file);

    LogicOperation::ValidFile(file,ModeValidator::WriteFile);

    for(const auto& teacher : data)
    {
        QJsonObject obj;
        obj["Имя"] = teacher.firstName;
        obj["Фамилия"] = teacher.middleName;
        obj["Отчество"] = teacher.lastName;
        arr.append(obj);
    }
    QJsonObject MainObj;

    if(arr.isEmpty()) return false;

    MainObj["Учителя"]=arr;

    QJsonDocument doc(MainObj);
    file.write(doc.toJson());
    return true;
}

bool ScheduleJsonParser::setLessonNameCabinets(const QString &filename, const QSet<QString> &data)
{
    QFile file(filename);

    QJsonArray arr = getArrayFromJsonFile(file);

    LogicOperation::ValidFile(file,ModeValidator::WriteFile);

    for(const auto& lesson : data)
    {
        QJsonObject obj;
        obj["Название пары"] = lesson;
        arr.append(obj);
    }

    QJsonObject MainObj;

    if(arr.isEmpty()) return false;

    MainObj["Название пар"]=arr;

    QJsonDocument doc(MainObj);
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

QJsonArray ScheduleJsonParser::getArrayFromJsonFile(QFile &file)
{
    if(!file.exists()) return QJsonArray();

    LogicOperation::ValidFile(file,ModeValidator::ReadFile);

    QByteArray bArr = file.readAll();
    QJsonParseError error;
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(bArr,&error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << error.errorString();
        return QJsonArray();
    }

    if(!doc.isObject())  return QJsonArray();

    QJsonObject mainObject = doc.object();
    QJsonArray array;

    auto it = std::find_if(mainObject.constBegin(),mainObject.constEnd(),[](const QJsonValue& v){
        return v.isArray();
    });


    if (it != mainObject.constEnd()) {
         array = it->toArray();
    }
    else
    {
        return QJsonArray();
    }

    LogicOperation::ValidFile(file,ModeValidator::DeleteWrite);
    file.close();

    return array;

}
