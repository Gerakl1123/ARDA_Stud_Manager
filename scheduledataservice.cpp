#include "scheduledataservice.h"
#include"QFile"
#include"LogicOperation.h"


ScheduleDataService::ScheduleDataService()
    : schedule(std::make_unique<DataSchedule>())
{}

QSet<QString> ScheduleDataService::GetCabinetsJson()
{

    QFile file("Расписание/cabinets.json");
    if(!file.exists()) return{};

    LogicOperation::ValidFile(file,ModeValidator::ReadFile);

    QByteArray bArr = file.readAll();
    QJsonObject mainObject = QJsonDocument::fromJson(bArr).object();

    QJsonArray arr = mainObject["Кабинеты"].toArray();

    for(const auto& value : arr)
    {
        if(!value.isObject()) return {};
        QJsonObject obj = value.toObject();

        schedule->cabinets.insert(obj["Кабинет"].toString());
    }
    return schedule->cabinets;

}

QSet<QString> ScheduleDataService::GetLessonNameJson()
{

    QFile file("Расписание/lesson_name.json");
    if(!file.exists()) return{};

    LogicOperation::ValidFile(file,ModeValidator::ReadFile);

    QByteArray bArr = file.readAll();
    QJsonObject mainObject = QJsonDocument::fromJson(bArr).object();

    QJsonArray arr = mainObject["Название пар"].toArray();

    for(const auto& v : arr)
    {
        if(!v.isObject()) return {};

        QJsonObject obj =v.toObject();
        schedule->LessonsName.insert(obj["Название пары"].toString());

    }
    return schedule->LessonsName;

}

QMap<int, QPair<QTime, QTime> > ScheduleDataService::GetLessonTimeJson()
{

    QFile file("Расписание/lesson_time.json");
    if(!file.exists()) return{};

    LogicOperation::ValidFile(file,ModeValidator::ReadFile);

    QByteArray bArr = file.readAll();
    QJsonObject mainObject = QJsonDocument::fromJson(bArr).object();

    QJsonArray arr = mainObject["Пары"].toArray();
    for(const auto& value : arr)
    {
        if(!value.isObject()) return {};

        QJsonObject obj = value.toObject();

        QString pairStr = obj["Пара"].toString();
        bool ok;
        int lessonNumber = pairStr.toInt(&ok);

        if (!ok || lessonNumber <= 0) {
            return {};
        }

        QString beginStr = obj["Начало"].toString().trimmed();
        QString endStr = obj["Конец"].toString().trimmed();

        QTime beginTime = QTime::fromString(beginStr, "HH:mm");
        QTime endTime = QTime::fromString(endStr, "HH:mm");


        schedule->lessonsTime[lessonNumber] = qMakePair(beginTime, endTime);

    }

    return schedule->lessonsTime;
}

QSet<Teacher> ScheduleDataService::GetTeacherNameJson()
{

    QFile file("Расписание/teachers.json");
    if(!file.exists()) return{};

    LogicOperation::ValidFile(file,ModeValidator::ReadFile);

    QByteArray bArr = file.readAll();
    QJsonObject mainObject = QJsonDocument::fromJson(bArr).object();

    QJsonArray arr = mainObject["Учителя"].toArray();

    for(const auto& value : arr)
    {
        if(!value.isObject()) return {};

        QJsonObject obj = value.toObject();
        QString name = obj["Имя"].toString();
        QString MiddleName = obj["Фамилия"].toString();
        QString LastName =obj["Отчество"].toString();

        schedule->Teachers.insert({name,MiddleName,LastName});

    }

    return schedule->Teachers;
}
