#include "parserjson.h"
#include<QFile>
#include"Validator.h"
#include<QMessageBox>
#include<QLineEdit>
#include<QJsonArray>
#include<QJsonDocument>
#include <QJsonObject>
#include"LogicOperation.h"
#include"NotificationCORE/addwork.h"
#include"JsonKeys.h"
#include<QSpinBox>
#include<QCheckBox>

ParserJson::ParserJson()
{
    fileManager = std::make_unique<FileManager>(nullptr);

}

QString ParserJson::ReadyDataVersion(const QString& jsonDataServer)
{

    QJsonDocument doc = QJsonDocument::fromJson(jsonDataServer.toUtf8());

    if (!doc.isObject()) {
        QMessageBox::warning(nullptr, "Error", "Не коректный json Проблема с сервером ждите исправления");
        return "";
    }

    QJsonObject obj = doc.object();
    QString ver = obj["version"].toString();

    return ver;
}

std::optional<QJsonObject> ParserJson::findObject(const QString &filename, const QString &ID)
{
    QFile file(filename);

    QJsonObject currObj;
    try{
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }catch(const std::logic_error& e)
    {
        QMessageBox::warning(nullptr,"Error", e.what());
        return std::nullopt;
    }

    QByteArray bArr = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(bArr);

    QJsonArray arr(doc.array());

    for(const auto& c : arr)
    {
        if(!c.isObject()) continue;

        currObj = c.toObject();

        auto it = currObj.find("ID");

        if (it != currObj.end() && it.value().toString() == ID) {
            qDebug() << "it != end";
            return currObj;
        }
    }

    return std::nullopt;
}

bool ParserJson::parseWork(const QString &name, const QString &desc, const QDate &date, const QTime &time, const QString &priority, QString &path)
{
    bool result = Validator::ValidWorkData(name,date,time,priority);
    if(!result) return false;

    QFile file(path);


    QJsonArray arrayWorks = LogicOperation::rewriteFile(file);

    try
    {
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }
    catch(const std::invalid_argument& e)
    {
        return false;
    }


    QJsonObject obj;

    obj["Название задачи"] = name;
    obj["Описание задачи"] = desc;
    obj["Окончание даты задачи"] = date.toString("dd.MM.yyyy");
    obj["Окончание времени задачи"] = time.toString("HH:mm");
    obj["Приоритет задачи"] = priority;

    arrayWorks.append(obj);

    QJsonDocument doc(arrayWorks);

    file.write(doc.toJson());
    file.close();

        return true;
}

Task ParserJson::UploadWork(const QJsonObject &obj)
{


    QString name = obj["Название задачи"].toString();
    QString desc = obj["Описание задачи"].toString();
    QString dateStr = obj["Окончание даты задачи"].toString();
    QString timeStr = obj["Окончание времени задачи"].toString();
    QString priority = obj["Приоритет задачи"].toString();
    QDate date = QDate::fromString(dateStr, "dd.MM.yyyy");
    QTime time = QTime::fromString(timeStr,"HH:mm");


    return Task(name,desc,date,time,priority);
}

QVector<std::tuple<QString, QDate,QTime>>& ParserJson::getInfoWorks(const QJsonArray &arr)
{
    infoList.clear();

    qDebug() << "=== ДЕБАГ PARSER ===";
    qDebug() << "Размер массива:" << arr.size();

    for(const auto& c : arr)
    {
        if(!c.isObject()) continue;

        QJsonObject obj = c.toObject();

        QString name = obj["Название задачи"].toString();
        QTime time = obj["Окончание времени задачи"].toVariant().toTime();
        QString dateStr = obj["Окончание даты задачи"].toString();
        qDebug()<< dateStr << "dateSTR";
        QDate date = QDate::fromString(dateStr,"dd.MM.yyyy");
        infoList.append({name, date, time});
    }

    qDebug() << "=== КОНЕЦ ПАРСИНГА ===";
    qDebug() << "size infoList->" << infoList.size();

    return infoList;
}

bool ParserJson::DeleteObjectInArrayWorks(int number_object)
{
    QFile file(Planner::Works);

    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::invalid_argument& e)
    {
        return false;
    }


    QByteArray bArr = file.readAll();

    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(bArr);
    QJsonArray arr = doc.array();

    QJsonArray newArr = deleteObject(arr,number_object);

    QJsonDocument newDoc(newArr);

    try
    {
        Validator::isFileValid(file,ModeValidator::DeleteWrite);
    }
    catch(const std::invalid_argument& e)
    {
        return false;
    }


    file.write(newDoc.toJson());
    file.close();

    return true;

}

QJsonArray ParserJson::deleteObject(const QJsonArray &arr, int number_object)
{

    QJsonArray newArr;
    int local = 0;
    for(const auto& c : arr)
    {
        if(!c.isObject()) continue;

        if(local == number_object) continue;

        QJsonObject obj = c.toObject();

        newArr.append(obj);
        ++local;
    }


    return newArr;
}

QList<QHash<QString, QString>> ParserJson::ParsingJsonEditorForm(const QString &filename)
{

    QFile file(filename);
    Validator::isFileValid(file,ModeValidator::ReadFile);

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QList<QHash<QString,QString>> data;

    if (doc.isArray()) {
        data = parsingJsonArray(doc.array());
    }else if(doc.isObject())
    {
        data.append(parsingJsonObject(doc.object()));
    }


    qDebug() << data.size();
    file.close();
    return data;

}

QList<QHash<QString,QString>> ParserJson::parsingJsonArray(const QJsonArray &arr)
{
    QList<QHash<QString,QString>> dataJson;

    dataJson.reserve(arr.size());

    for(const auto& v : arr )
    {
        if(v.isObject())
        {
            dataJson.emplaceBack(parsingJsonObject(v.toObject()));
        }
    }
    return dataJson;
}

QHash<QString,QString> ParserJson::parsingJsonObject(const QJsonObject &obj)
{
    QHash<QString, QString> result;

    result.reserve(obj.size());

    for(auto i = obj.begin();  i != obj.end(); ++i)
    {
        QString key = i.key();
        const QJsonValue& value = i.value();

        if(value.isString()){
            result.insert(std::move(key),value.toString());
        }else if(value.isArray())
        {
            for(const auto& c : value.toArray())
            {
                result.insert(std::move(key),c.toString());
            }
        }

    }

    return result;
}


