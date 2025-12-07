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

struct Task;

class ParserJson
{
private:

public:
    ParserJson();

    QString ReadyDataVersion(const QString& jsonDataServer);

    void SaveJsonPassport(QWidget* w);
    void SaveJsonExtraData(QWidget* w);

    static void addJsonArrayToModel(const QJsonArray & value, QStandardItem* parent);

    std::optional<QJsonObject> findObject(const QString& file, const QString& ID);


    bool parseWork(const QString& name, const QString& desc,
                   const QDate& date, const QTime& time,
                   const QString& priority,QString& path);

    Task UploadWork(const QJsonObject& obj);

    QVector<std::tuple<QString, QDate,QTime>>& getInfoWorks(const QJsonArray& arr);

    bool DeleteObjectInArray(int number_object);

    QJsonArray deleteObject(const QJsonArray& arr, int number_object);
private:
    std::unique_ptr<PassPort> Pass;
    std::unique_ptr<ExtraData> extraData;
    std::unique_ptr<FileManager> fileManager;
    QVector<std::tuple<QString, QDate,QTime>> infoList;

};

#endif // PARSERJSON_H
