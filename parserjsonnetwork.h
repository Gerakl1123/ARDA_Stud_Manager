#ifndef PARSERJSONNETWORK_H
#define PARSERJSONNETWORK_H
#include<QJsonDocument>
#include<QJsonObject>

class ParserJsonNetWork
{
private:

public:
    ParserJsonNetWork();

    QString ReadyDataVersion(const QString& jsonDataServer);
};

#endif // PARSERJSONNETWORK_H
