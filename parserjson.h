#ifndef PARSERJSON_H
#define PARSERJSON_H
#include<QJsonDocument>
#include<QJsonObject>
#include"FileChooicer.h"
#include"ManagerDataCore/Data.h"
#include"ManagerDataCore/passport.h"
#include"ManagerDataCore/extradata.h"
#include<optional>
#include<QStandardItem>
#include <QJsonArray>
#include<QJsonValue>
#include<QJsonObject>
#include<QHash>
#include<QDate>
#include <QMap>
#include<QPair>
#include<QTime>
#include"dataschedule.h"
struct Task;

class ParserJson
{
private:

public:
    ParserJson();

    QString ReadyDataVersion(const QString& jsonDataServer);


    static void addJsonArrayToModel(const QJsonArray & value, QStandardItem* parent);

    std::optional<QJsonObject> findObject(const QString& file, const QString& ID);


    bool parseWork(const QString& name, const QString& desc,
                   const QDate& date, const QTime& time,
                   const QString& priority,QString& path);

    Task UploadWork(const QJsonObject& obj);

    QVector<std::tuple<QString, QDate,QTime>>& getInfoWorks(const QJsonArray& arr);

    bool DeleteObjectInArrayWorks(int number_object);

    QJsonArray deleteObject(const QJsonArray& arr, int number_object);


    QList<QHash<QString,QString>> ParsingJsonEditorForm(const QString& filename);
    QList<QHash<QString,QString>> parsingJsonArray(const QJsonArray& arr);
    QHash<QString, QString> parsingJsonObject(const QJsonObject& obj);

    //typedef QList<QHash<QString,QString>> LHSS;



private:
    std::unique_ptr<FileManager> fileManager;
    QVector<std::tuple<QString, QDate,QTime>> infoList;

};

#endif // PARSERJSON_H
